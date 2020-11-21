"""
372. Super Pow

Your task is to calculate a**b mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.



Example 1:

Input: a = 2, b = [3]
Output: 8
Example 2:

Input: a = 2, b = [1,0]
Output: 1024
Example 3:

Input: a = 1, b = [4,3,3,8,5,2]
Output: 1
Example 4:

Input: a = 2147483647, b = [2,0,0]
Output: 1198


Constraints:

1 <= a <= 231 - 1
1 <= b.length <= 2000
0 <= b[i] <= 9
b doesn't contain leading zeros.



"""


class SuperPow

    def doit_1(self, a, b):
        """
        :type a: int
        :type b: List[int]
        :rtype: int
        """
        if a == 1:
            return 1
        if not a % 1337:
            return 0

        phi = (7 - 1) * (191 - 1)
        b = int(''.join(map(str, b))) % phi
        return (a ** b) % 1337

    def doit_2(self, a, b):
        """
        :type a: int
        :type b: List[int]
        :rtype: int
        """
        result = 1
        for digit in b:
            result = pow(result, 10, 1337) * pow(a, digit, 1337) % 1337
        return result

    """
    Optimized Solution - Order of number of digits of b

    The algorithm can be described using this example where b = [7,8,5]
    a^785 = a^700 * a^80 * a^5 = ((a^70 * a^8)^10) * ( a^5)
    (((a^7)^10 * a^8)^10) * ( a^5)
    First iteration: a^7 and (a^7)^10 = a^70
    Second iteration = a^70 * a^8 and (a^78)^10 = a^780
    Third iteration = a^780 * a ^5 = a^785
    """
    def superPow(self, a, b):
        """
        :type a: int
        :type b: List[int]
        :rtype: int
        """
        def compute_pow(a, b):
            if b == 0:
                return 1
            elif b == 1:
                return a
            elif b & 1:
                x = compute_pow(a, (b - 1) // 2) % 1337
                return int(((a % 1337) * (x * x) % 1337) % 1337)
            else:
                x = compute_pow(a, b // 2) % 1337
                return int((x * x) % 1337)

        a, result = a % 1337, 1
        for i in range(len(b)):
            result = (result * compute_pow(a, b[i])) % 1337
            result = compute_pow(result, 10) if i != len(b) - 1 else result
        return result

    def doit_3(self, a: int, b: list) -> int:
        """
        :type a: int
        :type b: List[int]
        :rtype: int
        """
        base = 1337

        def powmod(a, b):
            a %= base
            i, result = 0, 1
            while i < b:
                result = (result * a) % base
                i += 1
            return result

        def PowByK(a, b, k):
            if k < 0:
                return 1

            return (powmod(PowByK(a, b, k - 1), 10) * powmod(a, b[k])) % base

        return PowByK(a, b, len(b) - 1)


if __name__ == '__main__':

    SuperPow().doit_(a = 2, b = [3])

    SuperPow().doit_(a = 1, b = [4,3,3,8,5,2])

    SuperPow().doit_(a = 2147483647, b = [2,0,0])
