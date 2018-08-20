
# 50. Pow(x, n)

# Implement pow(x, n), which calculates x raised to the power n (xn).

# Example 1:

# Input: 2.00000, 10
# Output: 1024.00000

# Example 2:

# Input: 2.10000, 3
# Output: 9.26100

# Example 3:

# Input: 2.00000, -2
# Output: 0.25000
# Explanation: 2-2 = 1/22 = 1/4 = 0.25
# Note:

# -100.0 < x < 100.0
# n is a 32-bit signed integer, within the range [?231, 231 ? 1]


class MyPow(object):
    def doit(self, x, n):
        """
        :type x: float
        :type n: int
        :rtype: float
        """
        if not n:
            return 1
        
        v, n = (True, -n) if n < 0 else (False, n)
        base, res = x, 1
        while n:
            if n & 1:
                res *= base
            base *= base
            n >>= 1
            
        return 1/res if v else res


if __name__ == "__main__":

    res = MyPow().doit(2.000, -2)

    res = MyPow().doit(2.1000, -3)

    res = MyPow().doit(2.0000, 10)