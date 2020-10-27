"""
43. Multiply Strings

Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.

Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.



Example 1:

Input: num1 = "2", num2 = "3"
Output: "6"
Example 2:

Input: num1 = "123", num2 = "456"
Output: "56088"


Constraints:

1 <= num1.length, num2.length <= 200
num1 and num2 consist of digits only.
Both num1 and num2 do not contain any leading zero, except the number 0 itself.

"""


class MultiplyString:

    def doit(self, num1: str, num2: str) -> str:

        def convertToInt(num):
            integer = 0

            for digit in num:
                integer *= 10
                integer += (ord(digit) - ord("0"))

            return integer

        integer1 = convertToInt(num1)
        integer2 = convertToInt(num2)

        return str(integer1 * integer2)

    def doit(self, num1: str, num2: str):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """
        if not num1 or not num2 or num1 == '0' or num2 == '0':
            return '0'

        res = [0] * (len(num1) + len(num2))

        for i, c in enumerate(reversed(num1)):
            for j, f in enumerate(reversed(num2)):
                res[i + j] += int(c) * int(f)

        for i in range(len(num1) + len(num2) - 1):
            accum, res[i] = divmod(res[i], 10)
            res[i + 1] += accum

        if res[-1] == 0:
            res.pop()

        return ''.join([str(i) for i in reversed(res)])
