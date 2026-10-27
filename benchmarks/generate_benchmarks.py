#!/usr/bin/env python3
"""Generate one benchmark call per compatible shape and element type.

Public header filenames describe legacy shapes; an independent product list adds
rectangular coverage. Neither source reads matrix implementation details.
"""
import argparse
import json
from pathlib import Path
import re


# Keep C++ spellings and CSV labels together so the runner uses the same cases.
VALUE_TYPES = (
    ('sel::Int4', 'int4'),
    ('std::int8_t', 'int8'),
    ('int', 'int'),
    ('unsigned int', 'unsigned'),
    ('float', 'float'),
    ('double', 'double'),
)
HEADER_PATTERN = re.compile(r'Mat([1-9][0-9]*)x([1-9][0-9]*)\.hpp')


def discover_products(headers, rectangular=False):
    """Discover legacy products and optionally add generic rectangular products."""
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
    if rectangular:
        extra = Path(__file__).resolve().parents[1] / 'tests/Matrices/rectangular_products.json'
        products = sorted(set(products) | {tuple(product) for product in json.loads(extra.read_text())})
    return products


def generate(headers, rectangular=False):
    """Emit the shared executable source and return its product-shape count."""
    products = discover_products(headers, rectangular)
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
        def matrix_type(r, c):
            return f'sel::Matrix<{{cpp_type}}, {r}, {c}>' if rectangular else f'sel::Mat{r}x{c}<{{cpp_type}}>'
        for cpp_type, label in VALUE_TYPES:
            left = matrix_type(rows, inner).format(cpp_type=cpp_type)
            right = matrix_type(inner, columns).format(cpp_type=cpp_type)
            lines.extend([
                f'        matrixBench::run<{cpp_type}, {left},',
                f'            {right}, {rows}, {inner}, {columns}>("{label}", sampleMs);',
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
    source, count = generate(args.headers, rectangular=True)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(source)
    print('Generated {} products, {} benchmark cases per backend'.format(
        count, count * len(VALUE_TYPES)))


if __name__ == '__main__':
    main()
