"""
1363. Largest Multiple of Three

Given an integer array of digits, return the largest multiple of three that can be formed by concatenating some of the given digits in any order.

Since the answer may not fit in an integer data type, return the answer as a string.

If there is no answer return an empty string.



Example 1:

Input: digits = [8,1,9]
Output: "981"
Example 2:

Input: digits = [8,6,7,1,0]
Output: "8760"
Example 3:

Input: digits = [1]
Output: ""
Example 4:

Input: digits = [0,0,0,0,0,0]
Output: "0"


Constraints:

1 <= digits.length <= 10^4
0 <= digits[i] <= 9
The returning answer must not contain unnecessary leading zeros.

"""


class LargestMultipleOfThree:

    def doit_math(self, digits: list) -> str:

        digits.sort(reverse=True)
        total = sum(digits)

        if total % 3 == 0:
            if digits[0] == 0:
                return "0"

            return "".join(map(lambda i: str(i), digits))

        N = len(digits)
        b11, b12, b21, b22 = N, N, N, N

        for i in reversed(range(len(digits))):

            if digits[i] % 3 == 1:
                if b11 == N:
                    b11 = i
                elif b12 == N:
                    b12 = i

            if digits[i] % 3 == 2:
                if b21 == N:
                    b21 = i
                elif b22 == N:
                    b22 = i

        if total % 3 == 1:
            if b11 != N:
                digits.pop(b11)
            elif b21 != N and b22 != N:
                digits.pop(b21)
                digits.pop(b22)

            return "".join(map(lambda i: str(i), digits))

        elif total % 3 == 2:

            if b21 != N:
                digits.pop(b21)
            elif b11 != N and b12 != N:
                digits.pop(b11)
                digits.pop(b12)

            return "".join(map(lambda i: str(i), digits))

        return ""

    def doit_dp(self, digits: list) -> str:

        pass