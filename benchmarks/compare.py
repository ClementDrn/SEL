#!/usr/bin/env python3
"""Compare separate Release executables, alternating backend order each round.

Executables emit raw samples as CSV. This runner checks that both backends ran
all cases, collects repeated measurements, and writes median timings and spread.
"""
import argparse
import csv
import io
import math
from pathlib import Path
import platform
import re
import statistics
import subprocess
import sys

from generate_benchmarks import VALUE_TYPES, discover_products


BACKENDS = ('scalar', 'simd')
SAMPLE_COLUMNS = [
    'shape', 'type', 'explicit_simd', 'ns_per_product',
    'products', 'elapsed_ns', 'checksum',
]


def uses_intrinsics(shape, value_type):
    """Mirror shape eligibility, including scalar-only narrow/odd-width products."""
    left, right = shape.split('*')
    rows, inner = map(int, left.split('x'))
    _, columns = map(int, right.split('x'))
    return (value_type == 'int8'
            or (value_type in ('float', 'int') and
                (columns >= 4 or (2 <= rows <= 4 and 2 <= inner <= 4 and columns == 2
                                  and (inner == 2 or (value_type == 'float' and inner == 4 and rows < 4)))))
            or (value_type == 'int4' and inner % 2 == 0 and columns % 2 == 0 and columns >= 4))


def positive_int(value):
    """argparse validator for a nonempty sample count."""
    result = int(value)
    if result <= 0:
        raise argparse.ArgumentTypeError('must be positive')
    return result


def duration(value):
    """Use the same duration bounds as the C++ executables."""
    result = float(value)
    if not math.isfinite(result) or not 0 < result <= 60000:
        raise argparse.ArgumentTypeError('must be finite and in (0, 60000] ms')
    return result


def expected_cases():
    """Discover required CSV keys using the generator's shape/type definitions."""
    headers = Path(__file__).resolve().parents[1] / 'include/SEL/Maths/Matrices'
    cases = set()
    for rows, inner, columns in discover_products(headers, rectangular=True):
        shape = '{}x{}*{}x{}'.format(rows, inner, inner, columns)
        for _, label in VALUE_TYPES:
            cases.add((shape, label))
    return cases


def parse_sample(output, backend, sample_ms, expected):
    """Validate one executable's CSV; return case -> (ns/product, checksum)."""
    reader = csv.DictReader(io.StringIO(output))
    if reader.fieldnames != SAMPLE_COLUMNS:
        raise ValueError('Malformed benchmark header from ' + backend)

    results = {}
    for row in reader:
        # DictReader represents extra fields with a None key and missing fields
        # with None values. Reject both before converting any numbers.
        if None in row or any(value is None for value in row.values()):
            raise ValueError('Malformed benchmark row from ' + backend)
        key = (row['shape'], row['type'])
        if key in results or key not in expected:
            raise ValueError('Duplicate or unexpected case: ' + str(key))

        ns_per_product = float(row['ns_per_product'])
        product_count = int(row['products'])
        elapsed_ns = int(row['elapsed_ns'])
        checksum = float(row['checksum'])
        if (not math.isfinite(ns_per_product) or ns_per_product <= 0
                or product_count <= 0 or elapsed_ns <= 0 or not math.isfinite(checksum)):
            raise ValueError('Invalid benchmark measurement: ' + str(key))

        # Check the reported average and minimum duration against raw counts.
        # Small rounding differences are expected in the printed ns/product.
        if (elapsed_ns < sample_ms * 1e6
                or not math.isclose(ns_per_product, elapsed_ns / product_count, rel_tol=1e-9)):
            raise ValueError('Inconsistent benchmark timing: ' + str(key))
        explicit = backend == 'simd' and uses_intrinsics(*key)
        if row['explicit_simd'] != str(int(explicit)):
            raise ValueError('Incorrect backend flag: ' + str(key))
        results[key] = (ns_per_product, checksum)

    if set(results) != expected:
        raise ValueError('Missing benchmark cases from ' + backend)
    return results


def sample(executable, backend, sample_ms, expected):
    """Run one backend sequentially; a process failure invalidates the round."""
    completed = subprocess.run(
        [str(executable), '--sample-ms', str(sample_ms)],
        stdout=subprocess.PIPE, stderr=subprocess.PIPE,
        universal_newlines=True, check=True,
    )
    return parse_sample(completed.stdout, backend, sample_ms, expected)


def cpu_name():
    """Prefer Linux's model name, falling back to portable platform metadata."""
    cpuinfo = Path('/proc/cpuinfo')
    if cpuinfo.exists():
        for line in cpuinfo.read_text().splitlines():
            if line.startswith('model name'):
                return line.partition(':')[2].strip()
    return platform.processor() or platform.machine()


def collect_samples(executables, sample_count, sample_ms, expected):
    """Collect per-case timings while checking outputs across rounds/backends."""
    timings = {backend: {key: [] for key in expected} for backend in BACKENDS}
    checksums = {}
    for round_index in range(sample_count):
        # Alternate which backend runs first to reduce systematic ordering bias.
        # Run processes sequentially so they never compete with each other.
        order = BACKENDS if round_index % 2 == 0 else tuple(reversed(BACKENDS))
        for backend in order:
            print('Round {}/{}: {}'.format(round_index + 1, sample_count, backend),
                  file=sys.stderr, flush=True)
            measurements = sample(executables[backend], backend, sample_ms, expected)
            for key, (ns_per_product, checksum) in measurements.items():
                if key in checksums and not math.isclose(
                        checksums[key], checksum, rel_tol=1e-9, abs_tol=1e-9):
                    raise ValueError('Backend checksum mismatch: ' + str(key))
                checksums[key] = checksum
                timings[backend][key].append(ns_per_product)
    return timings


def case_sort_key(case):
    """Sort dimensions numerically (8 before 16), then by the shared type order."""
    shape, value_type = case
    dimensions = tuple(map(int, re.findall(r'\d+', shape)))
    type_labels = [label for _, label in VALUE_TYPES]
    return dimensions, type_labels.index(value_type)


def summarize(timings, sample_count, sample_ms):
    """Build the public CSV rows. Spread is a range, not a confidence interval."""
    rows = []
    for shape, value_type in sorted(timings['scalar'], key=case_sort_key):
        key = (shape, value_type)
        off_samples = timings['scalar'][key]
        on_samples = timings['simd'][key]
        off_ns = statistics.median(off_samples)
        on_ns = statistics.median(on_samples)
        off_spread = 100 * (max(off_samples) - min(off_samples)) / off_ns
        on_spread = 100 * (max(on_samples) - min(on_samples)) / on_ns
        path = 'explicit' if uses_intrinsics(shape, value_type) else 'generic fallback'
        rows.append(dict(
            shape=shape, type=value_type, off_ns=off_ns, on_ns=on_ns,
            speedup=off_ns / on_ns, off_spread_pct=off_spread,
            on_spread_pct=on_spread, on_path=path,
            samples=sample_count, sample_ms=sample_ms,
        ))
    return rows


def print_summary(rows):
    """Present the same fields as the CSV, rounded only for terminal readability."""
    print('\n{:<15} {:<9} {:>12} {:>12} {:>9} {:>10} {:>10}  {}'.format(
        'Product', 'Type', 'SIMD off ns', 'SIMD on ns', 'Speedup',
        'Off spread', 'On spread', 'On path'))
    for row in rows:
        print('{:<15} {:<9} {:>12.3f} {:>12.3f} {:>8.3f}x {:>9.1f}% {:>9.1f}%  {}'.format(
            row['shape'], row['type'], row['off_ns'], row['on_ns'], row['speedup'],
            row['off_spread_pct'], row['on_spread_pct'], row['on_path']))


def write_report(path, rows, flags, sample_count, sample_ms):
    """Keep build/machine metadata beside the exported numeric results."""
    with path.open('w', newline='') as stream:
        writer = csv.DictWriter(stream, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)
    metadata = [
        flags,
        'Platform: ' + platform.platform(),
        'CPU: ' + cpu_name(),
        'Samples: ' + str(sample_count),
        'Minimum sample ms: ' + str(sample_ms),
    ]
    path.with_suffix('.metadata.txt').write_text('\n'.join(metadata) + '\n')
    print('\nSaved ' + str(path))


def parse_arguments():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--scalar', type=Path, required=True)
    parser.add_argument('--simd', type=Path, required=True)
    parser.add_argument('--metadata', type=Path,
                        help='CMake-generated flags file (defaults beside executable)')
    parser.add_argument('--samples', type=positive_int, default=7)
    parser.add_argument('--sample-ms', type=duration, default=20)
    parser.add_argument('--csv', type=Path, help='save summary CSV; metadata saved alongside')
    return parser.parse_args()


def main():
    args = parse_arguments()
    metadata = args.metadata or args.scalar.resolve().parent / 'flags-Release.txt'
    flags = metadata.read_text()
    print(flags.rstrip())
    print('Platform: ' + platform.platform())
    print('CPU: ' + cpu_name())
    print('Samples/backend/case: {}; minimum sample: {} ms'.format(args.samples, args.sample_ms))
    print('Auto-vectorization uses normal Release settings. Batch throughput includes output stores.')
    print('Speedup = off/on; >1 favors explicit SIMD. Spread = (max-min)/median.')
    print('Small differences within spread are inconclusive. Calibration adds runtime.', flush=True)

    expected = expected_cases()
    executables = {'scalar': args.scalar.resolve(), 'simd': args.simd.resolve()}
    timings = collect_samples(executables, args.samples, args.sample_ms, expected)
    rows = summarize(timings, args.samples, args.sample_ms)
    print_summary(rows)
    if args.csv:
        write_report(args.csv, rows, flags, args.samples, args.sample_ms)


if __name__ == '__main__':
    try:
        main()
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        print('Benchmark comparison failed: ' + str(error), file=sys.stderr)
        if isinstance(error, subprocess.CalledProcessError) and error.stderr:
            print(error.stderr.rstrip(), file=sys.stderr)
        sys.exit(1)
