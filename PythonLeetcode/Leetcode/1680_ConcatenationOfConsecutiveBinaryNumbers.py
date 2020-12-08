"""
1680. Concatenation of Consecutive Binary Numbers

Given an integer n, return the decimal value of the binary string formed by concatenating the binary representations of 1 to n in order, modulo 109 + 7.



Example 1:

Input: n = 1
Output: 1
Explanation: "1" in binary corresponds to the decimal value 1.
Example 2:

Input: n = 3
Output: 27
Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
After concatenating them, we have "11011", which corresponds to the decimal value 27.
Example 3:

Input: n = 12
Output: 505379714
Explanation: The concatenation results in "1101110010111011110001001101010111100".
The decimal value of that is 118505380540.
After modulo 109 + 7, the result is 505379714.


Constraints:

1 <= n <= 105
"""


class ConcatenatedBinary:

    # O(n)
    def doit_1(self, n: int) -> int:
        return int(''.join("{0:b}".format(i) for i in range(1, n+1)), 2) % (10**9 + 7)

    # O(n)
    def doit_2(self, n: int) -> int:
        from math import log2
        res = 1
        mod = 10**9+7
        for i in range(2, n+1):
            res = ((res << int(log2(i))+1) + i) % mod
        return res

    """
    Reference: https://stackoverflow.com/questions/64450456/concatenation-of-binary-representation-of-first-n-positive-integers-in-ologn-t
    The idea is the calculation of the concatenatedBinary in range [a, b), where 2^(t-1) <= a < b <= 2^t can be done 
    in roughly O(1) time (or O(log(b-a)) if considering the time to calculate power).
    
    Let l = 2^t, n = b - a, then concatenatedBinary(a, b) = a*l^(n-1) + (a+1)*l^(n-2) + (a+2)*l^(n-3)... + (b- 1)*l^0 
    (it's easy to verify if you expand the expression from b)
    So that concatenatedBinary(a, b) = (a*(l^n-1) + (l^n-1)/(l-1) - n) / (l-1)
    
    log(n)
    """
    def doit_best(self, n: int) -> int:
        acc = 0
        M = 10 ** 9 + 7

        def split_by_bit_length(n):
            """
            Split the numbers in [1, n) by bit-length.
            Produces triples (a, b, 2**k). Each triple represents a subinterval
            [a, b) of [1, n), with a < b, all of whose elements has bit-length k.
            [(1, 2, 2), (2, 4, 4), (4, 8, 8), (8, 10, 16)]
            """
            a = 1
            while n > a:
                b = 2 * a
                yield (a, min(n, b), b)
                a = b

        def subinterval_concat(a, b, l):
            """
            Concatenation of values in [a, b), all of which have the same bit-length k.
            l is 2**k.
            Equivalently, sum(i * l**(b - 1 - i)) for i in range(a, b)) modulo M.
            """
            n = b - a
            inv = pow(l - 1, -1, M)
            q = (pow(l, n, M) - 1) * inv
            return (a * q + (q - n) * inv) % M

        for a, b, l in split_by_bit_length(n + 1):
            acc = (acc * pow(l, b - a, M) + subinterval_concat(a, b, l)) % M

        return acc