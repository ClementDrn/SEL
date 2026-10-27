"""Hand-calculated anchors for the independent fixture reference."""
import unittest
from fractions import Fraction
from low_precision_reference import decode, encode, levels, product_bits, round_fp32_integer


class LowPrecisionReferenceTests(unittest.TestCase):
    def test_published_values(self):
        self.assertEqual(levels(2, 1), tuple(map(Fraction, (0, .5, 1, 1.5, 2, 3, 4, 6))))
        self.assertEqual(decode(126, 4, 3), 448)
        self.assertEqual(decode(123, 5, 2), 57344)
        self.assertEqual(decode(1, 4, 3), Fraction(1, 512))
        self.assertEqual(decode(1, 5, 2), Fraction(1, 65536))

    def test_midpoints_and_saturation(self):
        for e, m in ((2, 1), (4, 3), (5, 2)):
            sign = 1 << (e + m)
            grid = levels(e, m)
            for code, value in enumerate(grid):
                self.assertEqual(encode(value, e, m), code)
                if code:
                    self.assertEqual(encode(-value, e, m), sign | code)
                if code + 1 < len(grid):
                    midpoint = (value + grid[code + 1]) / 2
                    self.assertEqual(encode(midpoint, e, m), code if code % 2 == 0 else code + 1)
            self.assertEqual(encode(grid[-1] * 10, e, m), len(grid) - 1)
            self.assertEqual(encode(-grid[-1] * 10, e, m), sign | (len(grid) - 1))

    def test_binary32_rounding(self):
        self.assertEqual(round_fp32_integer(2**24 + 1), 2**24)
        self.assertEqual(round_fp32_integer(2**24 + 3), 2**24 + 4)
        self.assertEqual(round_fp32_integer(-(2**24 + 3)), -(2**24 + 4))
        # Carry into the next exponent binade.
        self.assertEqual(round_fp32_integer(2**25 - 1), 2**25)

    def test_dot_products(self):
        for e, m in ((2, 1), (4, 3), (5, 2)):
            maximum = levels(e, m)[-1]
            self.assertEqual(product_bits([maximum, maximum, Fraction(1)],
                                          [Fraction(2), Fraction(-2), Fraction(1)],
                                          1, 3, 1, e, m), [encode(Fraction(1), e, m)])
            self.assertEqual(product_bits([Fraction(0)], [Fraction(-1)], 1, 1, 1, e, m),
                             [1 << (e + m)])
        # FP32 loses the middle one; exact/unrounded accumulation would yield one.
        self.assertEqual(product_bits(list(map(Fraction, (57344, 1, -57344))),
                                      list(map(Fraction, (57344, 1, 57344))),
                                      1, 3, 1, 5, 2), [0])


if __name__ == '__main__':
    unittest.main()
