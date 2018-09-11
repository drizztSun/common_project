# 633. Sum of Square Numbers

# Given a non-negative integer c, your task is to decide whether there're two 
# integers a and b such that a2 + b2 = c.

# Example 1:
# Input: 5
# Output: True
# Explanation: 1 * 1 + 2 * 2 = 5

# Example 2:
# Input: 3
# Output: False
import math

class JudgeSquareSum:
    def doit(self, c):
        """
        :type c: int
        :rtype: bool
        """
        if c == 0:
            return True

        for i in range(c):
            a = i * i
            b = c - a
            if b < a:
                return False
            else:
                sq = math.sqrt(b)
                if sq == int(sq):
                    return True


    def doit(self, c):
        """
        :type c: int
        :rtype: bool
        """
        if c % 4 == 3:
            return False

        from itertools import groupby

        def prime_factors(n):
            i = 2
            while i*i <= n:
                while n % i == 0:
                    yield i
                    n //= i
                i += 1
            if n > 1:
                yield n

        for p, m in groupby(prime_factors(c)):
            if p % 4 == 3 and sum(1 for _ in m) % 2 == 1:
                return False

        return True

if __name__ == "__main__":

    res = JudgeSquareSum().doit(5)

    res = JudgeSquareSum().doit(3)