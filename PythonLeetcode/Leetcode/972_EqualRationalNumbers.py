# 972. Equal Rational Numbers

# Given two strings S and T, each of which represents a non-negative rational number, return True if and only if they represent the same number.
# The strings may use parentheses to denote the repeating part of the rational number.

# In general a rational number can be represented using up to three parts: an integer part, a non-repeating part, and a repeating part.
# The number will be represented in one of the following three ways:

# <IntegerPart> (e.g. 0, 12, 123)
# <IntegerPart><.><NonRepeatingPart>  (e.g. 0.5, 1., 2.12, 2.0001)
# <IntegerPart><.><NonRepeatingPart><(><RepeatingPart><)> (e.g. 0.1(6), 0.9(9), 0.00(1212))
# The repeating portion of a decimal expansion is conventionally denoted within a pair of round brackets.  For example:

# 1 / 6 = 0.16666666... = 0.1(6) = 0.1666(6) = 0.166(66)

# Both 0.1(6) or 0.1666(6) or 0.166(66) are correct representations of 1 / 6.


# Example 1:

# Input: S = "0.(52)", T = "0.5(25)"
# Output: true
# Explanation:
# Because "0.(52)" represents 0.52525252..., and "0.5(25)" represents 0.52525252525..... , the strings represent the same number.

# Example 2:

# Input: S = "0.1666(6)", T = "0.166(66)"
# Output: true

# Example 3:

# Input: S = "0.9(9)", T = "1."
# Output: true
# Explanation:
# "0.9(9)" represents 0.999999999... repeated forever, which equals 1.  [See this link for an explanation.]
# "1." represents the number 1, which is formed correctly: (IntegerPart) = "1" and (NonRepeatingPart) = "".


class IsRationalEqual:

    """
    Approach 1: Fraction Class
    Intuition

    As both numbers represent a fraction, we need a fraction class to handle fractions. It should help us add two fractions together, keeping the answer in lowest terms.

    Algorithm

    We need to make sense of the fraction we are given. The hard part is the repeating part.

    Say we have a string like S = "0.(12)". It represents (for r = 1 / 100):

    S = 12/100 + 12/10000 + 12/10^6 + 12/10^8 + 12/10^10 +⋯

    S = 12 * (r + r^2 + r^3 + ...)

    S = 12 ∗ (r / (1 - r))

    as the sum (r + r^2 + r^3 + ...) is a geometric sum.

    In general, for a repeating part x with length k, we have r = 10^{-k} and the contribution is xr/{1-r}

    The other two parts are easier, as it is just a literal interpretation of the value.

    Complexity Analysis

    Time Complexity: O(1), if we take the length of S, TS,T as O(1).

    Space Complexity: O(1).
    """

    def doit(self, S: str, T: str):

        from fractions import Fraction

        def convert(w):

            if "." not in w:
                return Fraction(int(w), 1)

            i = w.index(".")
            ans = Fraction(int(w[:i]), 1)

            w = w[i + 1:]
            if "(" not in w:
                if w:
                    ans += Fraction(int(w), 10 ** len(w))
                return ans

            i = w.index("(")
            if i:
                ans += Fraction(int(w[:i]), 10 ** i)

            w = w[i + 1: -1]
            ans += Fraction(int(w), 10 ** i * (10 ** len(w) - 1))
            return ans

        return convert(S) == convert(T)

    def doit1(self, S: str, T: str):
        def f(s):
            i = s.find('(')
            if i >= 0:
                s = s[:i] + s[i + 1:-1] * 20
            return float(s[:20])
        return f(S) == f(T)


if __name__ == "__main__":

    res = IsRationalEqual().doit(S="0.(52)", T="0.5(25)")

    res = IsRationalEqual().doit(S="0.1666(6)", T="0.166(66)")

    res = IsRationalEqual().doit(S="0.9(9)", T="1.")
