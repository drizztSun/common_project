"""
50. Pow(x, n)

Implement pow(x, n), which calculates x raised to the power n (i.e. xn).



Example 1:

Input: x = 2.00000, n = 10
Output: 1024.00000
Example 2:

Input: x = 2.10000, n = 3
Output: 9.26100
Example 3:

Input: x = 2.00000, n = -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25


Constraints:

-100.0 < x < 100.0
-231 <= n <= 231-1
-104 <= xn <= 104
"""


class PowXN:

    def myPow(self, x: float, n: int) -> float:

        if n == 0:
            return 1
        elif n < 0:
            return 1 / self.myPow(x, -n)
        elif n == 2:
            return x*x
        elif n%2 == 0:
            return self.myPow(self.myPow(x, n/2), 2)
        else:
            return x*self.myPow(self.myPow(x, n//2), 2)

    def doit(self, x: float, n: int) -> float:

        res = 1
        m = abs(n)

        while m > 0:
            if m % 2 == 1:
                res *= x
            x *= x
            m //= 2

        return res if n > 0 else 1 / res


if __name__ == '__main__':

    print(PowXN().doit(2.000, 10))
