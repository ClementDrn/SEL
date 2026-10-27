"""Independent exact OCP reference for fixture generation (no SEL source reads)."""

from bisect import bisect_left
from fractions import Fraction
from functools import lru_cache


@lru_cache(None)
def levels(exponent_bits, mantissa_bits):
    """Return the ordered, nonnegative finite grid as exact rational values."""
    maximum_code = {(2, 1): 7, (4, 3): 126, (5, 2): 123}[(exponent_bits, mantissa_bits)]
    bias = (1 << (exponent_bits - 1)) - 1
    result = []
    for code in range(maximum_code + 1):
        exponent, mantissa = divmod(code, 1 << mantissa_bits)
        significand = mantissa + ((1 << mantissa_bits) if exponent else 0)
        result.append(Fraction(significand) * Fraction(2) ** (
            max(exponent, 1) - bias - mantissa_bits))
    return tuple(result)


def encode(value, exponent_bits, mantissa_bits):
    """Encode a rational value with nearest-even rounding and finite saturation."""
    grid = levels(exponent_bits, mantissa_bits)
    magnitude = abs(value)
    upper = bisect_left(grid, magnitude)
    if upper == len(grid):
        code = len(grid) - 1
    elif upper == 0:
        code = 0
    else:
        lower = upper - 1
        code = min((lower, upper), key=lambda i: (abs(grid[i] - magnitude), i % 2))
    return code | ((1 << (exponent_bits + mantissa_bits)) if value < 0 else 0)


def decode(code, exponent_bits, mantissa_bits):
    """Decode a finite encoding exactly; rational zero does not retain its sign."""
    sign = 1 << (exponent_bits + mantissa_bits)
    return levels(exponent_bits, mantissa_bits)[code & (sign - 1)] * (-1 if code & sign else 1)


def round_fp32_integer(value):
    """Round a fixed-point integer to 24 significant bits, ties to even.

    Product units are powers of two >= 2^-32; these fixtures cannot reach
    FP32 underflow or overflow. No host float/double rounding is involved.
    """
    magnitude = abs(value)
    shift = max(0, magnitude.bit_length() - 24)
    if shift:
        quotient, remainder = divmod(magnitude, 1 << shift)
        halfway = 1 << (shift - 1)
        quotient += remainder > halfway or (remainder == halfway and quotient % 2)
        magnitude = quotient << shift
    return -magnitude if value < 0 else magnitude


def product_bits(left, right, rows, inner, columns, exponent_bits, mantissa_bits):
    """Return output encodings after ordered FP32 accumulation of quantized inputs."""
    # Every decoded value is an integer multiple of the minimum subnormal.
    unit = levels(exponent_bits, mantissa_bits)[1]
    a = [int(value / unit) for value in left]
    b = [int(value / unit) for value in right]
    result = []
    for row in range(rows):
        for column in range(columns):
            total = round_fp32_integer(a[row * inner] * b[column])
            negative_zero = total == 0 and ((a[row * inner] < 0) != (b[column] < 0))
            for k in range(1, inner):
                term = round_fp32_integer(a[row * inner + k] * b[k * columns + column])
                term_negative = (a[row * inner + k] < 0) != (b[k * columns + column] < 0)
                next_total = round_fp32_integer(total + term)
                negative_zero = (total == 0 and term == 0 and negative_zero and term_negative)
                total = next_total
            code = encode(total * unit * unit, exponent_bits, mantissa_bits)
            if total == 0 and negative_zero:
                code |= 1 << (exponent_bits + mantissa_bits)
            result.append(Fraction(code))
    return result
