#!/usr/bin/env python3
"""Generate deterministic Catch2 fixtures using exact, independent arithmetic."""

import argparse
from fractions import Fraction
from pathlib import Path
import random
import re


def multiply(left, right, rows, inner, columns):
    """Compute row-by-column products without using SEL or floating-point math."""
    return [sum((left[row * inner + k] * right[k * columns + column]
                 for k in range(inner)), Fraction(0))
            for row in range(rows) for column in range(columns)]


def verified_product(left, right, rows, inner, columns):
    result = multiply(left, right, rows, inner, columns)

    # Cross-check with an outer-product accumulation using a different traversal.
    verified = [Fraction(0)] * (rows * columns)
    for k in range(inner):
        for column in range(columns):
            for row in range(rows):
                verified[row * columns + column] += (
                    left[row * inner + k] * right[k * columns + column])
    if result != verified:
        raise ValueError("Independent reference calculations disagree")
    return result


def fixtures(rows, inner, columns, unsigned):
    left = [Fraction(i + 1) for i in range(rows * inner)]
    right = [Fraction((i * 3 + 2) % 11) for i in range(inner * columns)]
    if not unsigned:
        left = [value if i % 2 else -value for i, value in enumerate(left)]
    yield "asymmetric", left, right
    yield "zero left", [Fraction(0)] * len(left), right
    yield "zero right", left, [Fraction(0)] * len(right)

    if rows == inner:
        identity = [Fraction(row == column)
                    for row in range(rows) for column in range(inner)]
        yield "identity left", identity, right
    if inner == columns:
        identity = [Fraction(row == column)
                    for row in range(inner) for column in range(columns)]
        yield "identity right", left, identity

    # Isolate each output location and each contributing inner coordinate.
    for row in range(rows):
        for column in range(columns):
            for k in range(inner):
                basis_left = [Fraction(0)] * len(left)
                basis_right = [Fraction(0)] * len(right)
                basis_left[row * inner + k] = Fraction(2)
                basis_right[k * columns + column] = Fraction(3)
                yield f"basis {row},{k},{column}", basis_left, basis_right

    if not unsigned:
        yield "cancellation", [Fraction(1)] * len(left), [
            Fraction(1 if k % 2 == 0 else -1)
            for k in range(inner) for column in range(columns)]
        yield "fractional", [value / 10 for value in left], [value / 10 for value in right]

    # The seed depends only on the shape, so adding shapes preserves old fixtures.
    rng = random.Random(rows * 10000 + inner * 100 + columns)
    for index in range(32):
        minimum = 0 if unsigned else -9
        yield f"seeded {index}", [Fraction(rng.randint(minimum, 9)) for _ in left], [
            Fraction(rng.randint(minimum, 9)) for _ in right]


def cpp_values(values):
    return "{" + ", ".join(f"{value.numerator}.0L / {value.denominator}.0L"
                            for value in values) + "}"


def generate(shapes):
    lines = ['// Generated file. Edit generate_multiplication_tests.py instead.',
             '#include "MultiplicationChecks.hpp"',
             '#include <catch2/catch_template_test_macros.hpp>', '']
    combinations = 0
    for rows, inner in sorted(shapes):
        for right_rows, columns in sorted(shapes):
            if right_rows != inner or (rows, columns) not in shapes:
                continue
            combinations += 1
            name = f"{rows}x{inner} * {inner}x{columns} -> {rows}x{columns}"
            lines += [f'TEMPLATE_TEST_CASE("{name}", "[matrix][multiplication]",',
                      '                   int, unsigned int, float, double)', '{']
            for unsigned in (True, False):
                condition = 'if constexpr (std::is_unsigned_v<TestType>)' if unsigned else 'else'
                lines += [f'    {condition}', '    {']
                for label, left, right in fixtures(rows, inner, columns, unsigned):
                    expected = verified_product(left, right, rows, inner, columns)
                    # Fractional cases apply only to floating-point instantiations.
                    indent = '        '
                    if label == 'fractional':
                        lines += ['        if constexpr (std::is_floating_point_v<TestType>)',
                                  '        {']
                        indent += '    '
                    lines += [
                        f'{indent}matrixTests::checkProduct<TestType,',
                        f'{indent}    sel::Mat{rows}x{inner}<TestType>, sel::Mat{inner}x{columns}<TestType>,',
                        f'{indent}    sel::Mat{rows}x{columns}<TestType>, {rows}, {inner}, {columns}>(',
                        f'{indent}    "{label}", {cpp_values(left)},',
                        f'{indent}    {cpp_values(right)},',
                        f'{indent}    {cpp_values(expected)});']
                    if label == 'fractional':
                        lines.append('        }')
                lines.append('    }')
            lines += ['}', '']
    if combinations == 0:
        raise ValueError("No compatible matrix shapes found")
    return '\n'.join(lines), combinations


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--headers', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()

    # Header names are sufficient; multiplication implementations are never read.
    shapes = set()
    for header in args.headers.glob('Mat*x*.hpp'):
        match = re.fullmatch(r'Mat([1-9][0-9]*)x([1-9][0-9]*)\.hpp', header.name)
        if match:
            shapes.add(tuple(map(int, match.groups())))

    # Hand-calculated anchors also guard the reference arithmetic itself.
    assert verified_product([1, 2, 3, 4], [5, 6, 7, 8], 2, 2, 2) == [19, 22, 43, 50]
    assert verified_product([1, -2, 3, 4, 5, -6], [7, 8, 9, 10, 11, 12], 2, 3, 2) == [22, 24, 7, 10]
    source, combinations = generate(shapes)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(source, encoding='utf-8')
    print(f'Generated {combinations} matrix multiplication combinations from {len(shapes)} shapes')


if __name__ == '__main__':
    main()
