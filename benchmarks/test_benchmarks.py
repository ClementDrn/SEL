#!/usr/bin/env python3
"""Protocol and discovery checks; arithmetic is validated by the executables."""
import argparse
import io
import subprocess
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import compare
import generate_benchmarks


class DiscoveryTests(unittest.TestCase):
    """Coverage comes from filenames, including shapes added in the future."""

    def test_discovers_products_without_reading_headers(self):
        with tempfile.TemporaryDirectory() as directory:
            headers = Path(directory)
            for name in ('Mat2x2.hpp', 'Mat2x3.hpp', 'Mat3x2.hpp', 'Mat3x3.hpp'):
                # Any attempt to parse implementations would fail on these files.
                (headers / name).write_text('deliberately not C++')
            source, count = generate_benchmarks.generate(headers)
            self.assertEqual(count, 8)
            self.assertEqual(source.count('matrixBench::run<'), 48)
            self.assertEqual(generate_benchmarks.generate(headers), (source, count))
            (headers / 'Mat5x5.hpp').write_text('another shape')
            extended, count = generate_benchmarks.generate(headers)
            self.assertEqual(count, 9)
            self.assertIn('sel::Mat5x5<double>', extended)

    def test_empty_discovery_fails(self):
        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaises(ValueError):
                generate_benchmarks.generate(Path(directory))

    def test_current_coverage(self):
        expected = compare.expected_cases()
        source, products = generate_benchmarks.generate(
            Path(__file__).resolve().parents[1] / 'include/SEL/Maths/Matrices')
        self.assertEqual(len(expected), products * 6)
        self.assertEqual(source.count('matrixBench::run<'), len(expected))

    def test_int4_backend_selection_is_shape_specific(self):
        int4_cases = {shape for shape, value_type in compare.expected_cases()
                      if value_type == 'int4'}
        self.assertEqual(len(int4_cases), 30)
        explicit = {shape for shape in int4_cases if compare.uses_intrinsics(shape, 'int4')}
        self.assertEqual(explicit, {'{}x{}*{}x{}'.format(n, n, n, n) for n in (4, 8, 16, 32)})


class ProtocolTests(unittest.TestCase):
    """Bad executable output must fail rather than silently skew a comparison."""

    header = 'shape,type,explicit_simd,ns_per_product,products,elapsed_ns,checksum\n'
    expected = {('2x2*2x2', 'float')}

    def read(self, body, backend='scalar'):
        """Exercise the process-to-parser boundary without launching a binary."""
        completed = subprocess.CompletedProcess([], 0, self.header + body, '')
        with patch.object(compare.subprocess, 'run', return_value=completed):
            return compare.sample(Path('unused'), backend, 1, self.expected)

    def test_valid_both_backends(self):
        for backend, enabled in [('scalar', 0), ('simd', 1)]:
            body = '2x2*2x2,float,{},10,100000,1000000,24\n'.format(enabled)
            self.assertEqual(self.read(body, backend),
                             {('2x2*2x2', 'float'): (10.0, 24.0)})

    def test_int4_backend_flags_for_square_and_fallback_products(self):
        for shape, explicit in [('4x4*4x4', 1), ('8x8*8x8', 1),
                                ('16x16*16x16', 1), ('32x32*32x32', 1),
                                ('2x2*2x2', 0), ('3x3*3x3', 0),
                                ('4x2*2x4', 0), ('4x3*3x4', 0), ('4x4*4x3', 0)]:
            expected = {(shape, 'int4')}
            for backend in ('scalar', 'simd'):
                enabled = explicit if backend == 'simd' else 0
                row = '{},int4,{},10,100000,1000000,-24\n'.format(shape, enabled)
                self.assertEqual(compare.parse_sample(self.header + row, backend, 1, expected),
                                 {(shape, 'int4'): (10.0, -24.0)})
                wrong = row.replace(',int4,{},'.format(enabled), ',int4,{},'.format(1 - enabled))
                with self.assertRaisesRegex(ValueError, 'Incorrect backend flag'):
                    compare.parse_sample(self.header + wrong, backend, 1, expected)

    def test_rejects_missing_duplicate_and_unexpected_cases(self):
        valid = '2x2*2x2,float,0,10,100000,1000000,24\n'
        for body in ('', valid * 2, valid.replace('2x2*2x2', '3x3*3x3'),
                     '2x2*2x2,float,0,10\n', valid.rstrip() + ',extra\n'):
            with self.subTest(body=body), self.assertRaises(ValueError):
                self.read(body)

    def test_rejects_invalid_timings_checksums_and_backend(self):
        for values in [('nan', '100000', '1000000', '24', '0'),
                       ('0', '100000', '1000000', '24', '0'),
                       ('10', '0', '1000000', '24', '0'),
                       ('20', '100000', '1000000', '24', '0'),
                       ('10', '100', '1000', '24', '0'),
                       ('10', '100000', '1000000', 'inf', '0'),
                       ('10', '100000', '1000000', '24', '1')]:
            ns, count, elapsed, checksum, enabled = values
            with self.subTest(values=values), self.assertRaises(ValueError):
                self.read('2x2*2x2,float,{},{},{},{},{}\n'.format(
                    enabled, ns, count, elapsed, checksum))

    def test_invalid_duration(self):
        for value in ('0', '-1', 'nan', 'inf', '60001'):
            with self.subTest(value=value), self.assertRaises(argparse.ArgumentTypeError):
                compare.duration(value)


class ComparisonTests(unittest.TestCase):
    """Check aggregation and ordering with known timings, without measuring time."""

    def test_summary_uses_medians_and_preserves_csv_columns(self):
        # Unsorted values distinguish median aggregation from selecting a round.
        explicit = ('2x2*2x2', 'float')
        fallback = ('2x2*2x2', 'double')
        timings = {
            'scalar': {explicit: [30, 10, 20], fallback: [30, 10, 20]},
            'simd': {explicit: [5, 15, 10], fallback: [5, 15, 10]},
        }
        rows = compare.summarize(timings, 3, 20)
        self.assertEqual(list(rows[0]), [
            'shape', 'type', 'off_ns', 'on_ns', 'speedup', 'off_spread_pct',
            'on_spread_pct', 'on_path', 'samples', 'sample_ms',
        ])
        self.assertEqual(rows[0]['off_ns'], 20)
        self.assertEqual(rows[0]['on_ns'], 10)
        self.assertEqual(rows[0]['speedup'], 2)
        self.assertEqual(rows[0]['off_spread_pct'], 100)
        self.assertEqual(rows[0]['on_spread_pct'], 100)
        self.assertEqual(rows[0]['on_path'], 'explicit')
        self.assertEqual(rows[1]['on_path'], 'generic fallback')

    def test_rounds_alternate_backend_order(self):
        key = ('2x2*2x2', 'float')
        executables = {'scalar': Path('scalar'), 'simd': Path('simd')}

        def measured_sample(executable, backend, sample_ms, expected):
            return {key: (20 if backend == 'scalar' else 10, 42)}

        with patch.object(compare, 'sample', side_effect=measured_sample) as sample:
            with patch.object(compare.sys, 'stderr', io.StringIO()):
                timings = compare.collect_samples(executables, 2, 1, {key})
        self.assertEqual([call[0][1] for call in sample.call_args_list],
                         ['scalar', 'simd', 'simd', 'scalar'])
        self.assertEqual(timings['scalar'][key], [20, 20])
        self.assertEqual(timings['simd'][key], [10, 10])

    def test_int4_summary_distinguishes_square_and_rectangular_paths(self):
        keys = [('4x4*4x4', 'int4'), ('4x2*2x4', 'int4')]
        timings = {backend: {key: [10, 11, 12] for key in keys} for backend in compare.BACKENDS}
        paths = {(row['shape'], row['type']): row['on_path']
                 for row in compare.summarize(timings, 3, 20)}
        self.assertEqual(paths[keys[0]], 'explicit')
        self.assertEqual(paths[keys[1]], 'generic fallback')

    def test_checksum_mismatch_invalidates_comparison(self):
        key = ('2x2*2x2', 'float')
        executables = {'scalar': Path('scalar'), 'simd': Path('simd')}
        samples = [{key: (20, 42)}, {key: (10, 43)}]
        with patch.object(compare, 'sample', side_effect=samples):
            with patch.object(compare.sys, 'stderr', io.StringIO()):
                with self.assertRaisesRegex(ValueError, 'checksum mismatch'):
                    compare.collect_samples(executables, 1, 1, {key})


if __name__ == '__main__':
    unittest.main()
