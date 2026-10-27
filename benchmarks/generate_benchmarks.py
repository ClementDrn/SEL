#!/usr/bin/env python3
"""Generate one benchmark call per compatible shape and element type.

Only public header filenames describe the shapes. Neither discovery nor code
emission depends on matrix implementation details.
"""
import argparse
from pathlib import Path
import re


# Keep C++ spellings and CSV labels together so the runner uses the same cases.
VALUE_TYPES = (
    ('sel::int4', 'int4'),
    ('std::int8_t', 'int8'),
    ('int', 'int'),
    ('unsigned int', 'unsigned'),
    ('float', 'float'),
    ('double', 'double'),
)
HEADER_PATTERN = re.compile(r'Mat([1-9][0-9]*)x([1-9][0-9]*)\.hpp')


def discover_products(headers):
    """Return sorted (rows, inner, columns) products with an available result."""
    shapes = set()
    for header in headers.glob('Mat*x*.hpp'):
        match = HEADER_PATTERN.fullmatch(header.name)
        if match:
            shapes.add(tuple(map(int, match.groups())))

    products = []
    for rows, inner in sorted(shapes):
        for right_rows, columns in sorted(shapes):
            if inner == right_rows and (rows, columns) in shapes:
                products.append((rows, inner, columns))
    if not products:
        raise ValueError('No compatible matrix shapes found')
    return products


def generate(headers):
    """Emit the shared executable source and return its product-shape count."""
    products = discover_products(headers)
    # Both targets compile this source. CMake clears external SIMD definitions;
    # the generated switch then enables the backend before any SEL header loads.
    lines = [
        '// Generated file. Edit generate_benchmarks.py instead.',
        '#if SEL_BENCH_EXPLICIT_SIMD',
        '#define SEL_INTRINSIC_MATRIX_MUL',
        '#endif',
        '#include "MultiplicationBenchmark.hpp"',
        '',
        'int main(int argc, char** argv)',
        '{',
        '    try',
        '    {',
        '        const double sampleMs = matrixBench::settings(argc, argv);',
    ]
    for rows, inner, columns in products:
        for cpp_type, label in VALUE_TYPES:
            lines.extend([
                f'        matrixBench::run<{cpp_type}, sel::Mat{rows}x{inner}<{cpp_type}>,',
                f'            sel::Mat{inner}x{columns}<{cpp_type}>, {rows}, {inner}, {columns}>("{label}", sampleMs);',
            ])
    # Report validation/configuration failures to stderr, leaving stdout as CSV.
    lines.extend([
        '        return 0;',
        '    }',
        '    catch (const std::exception& error)',
        '    {',
        '        std::cerr << error.what() << "\\n";',
        '        return 1;',
        '    }',
        '}',
        '',
    ])
    return '\n'.join(lines), len(products)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--headers', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    source, count = generate(args.headers)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(source)
    print('Generated {} products, {} benchmark cases per backend'.format(
        count, count * len(VALUE_TYPES)))


if __name__ == '__main__':
    main()
