

# 600. Non-negative Integers without Consecutive Ones
#    Given a positive integer n, find the number of non-negative integers less than or equal to n,
#    whose binary representations do NOT contain consecutive ones.
#
#    Example 1:
#    Input: 5
#    Output: 5
#    Explanation:
#
#    Here are the non-negative integers <= 5 with their corresponding binary representations:
#
#   0 : 0
#   1 : 1
#   2 : 10
#   3 : 11
#   4 : 100
#   5 : 101
#
# Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule.
#   Note: 1 <= n <= 109

class FindIntegers(object):

    # Say X is the given number, and A = a list of that number in binary. For example, if X = 1234 = 0b10011010010,
    # A = [1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0].

    # We will perform a ‘flag-dp’: let dp[i][flag] = the answer for the number corresponding to A[i:],
    # where flag = 1 if we have written a lower number than A[i] at some point in our writing process
    # (and can now freely write higher numbers), else flag = 0.

    # 1234 has bit-length 11. With that example, we would try to write 11 binary digits (without writing consecutive 1s) from left to right,
    # such that the number it represents is less than or equal to 1234.

    # If our flag is down (flag = 0), then we cannot write a higher number than A[i].
    # If A[i] = 1, then we can write ‘10’ or ‘0’.
    # If A[i] = 0, we can only write ‘0’.
    # We should check as we write a zero, to lower our flag if we wrote a lower number. This is what dp[.][A[i]] and dp[.][A[i+1]] do.

    # If our flag is up, then we can freely write ‘10’ or ‘0’.

    def doit(self, num):
        """
        :type num: int
        :rtype: int
        """
        A = map(int, bin(num)[2:])
        N = len(A)
        dp = [[0, 0] for _ in range(N + 2)]
        dp[N] = dp[N + 1] = [1, 1]

        for i in range(N-1, -1, -1):
            dp[i][0] = dp[i+1][A[i]] + A[i] * dp[i+2][i+1 < N and A[i+1]]
            dp[i][1] = dp[i+1][1] + dp[i+2][1]

        return dp[0][0]

    ##############
    def doit2(self, num):
        """
        :type num: int
        :rtype: int
        """
        dp = [1, 2]
        for x in range(2, 32):
            dp.append(dp[x - 1]+ dp[x - 2])
        bnum = bin(num)[2:]
        size = len(bnum)
        ans = dp[size]
        for idx in range(1, size):
            if bnum[idx] == bnum[idx - 1] == '1':
                break
            if bnum[idx] == bnum[idx - 1] == '0':
                ans -= dp[size - idx] - dp[size - idx - 1]
        return ans

# x, y are used to calculate Fibonacci numbers.
# num & 1 and num & 2 will check if num ends with 11 in binary.

# Why can I use fibonacci numbers?
# a(n) = the number of valid integers less than 2^n
# a(5) = the number of valid integers less than 0b100000

# It equals to the number of valid integers in [0b0, 0b10000[ and in [0b10000, 0b11000[.
# The number of valid integers [0b0, 0b10000[, which is like ‘0b0XXXX’, equals to a(4).
# The number of valid integers [0b10000, 0b11000[, which is like ‘0b101XX’, equals to a(3).

# So a(5) = a(4) + a(3).
# This rule is the same for other values of n, and it is the same as Fibonacci numbers recurrence relation definition.


    def doit(self, num):
        """
        :type num: int
        :rtype: int
        """
        x, y = 1, 2
        num += 1
        res = 0

        while num:

            if num & 1 and num & 2:
                res = 0

            res += x * (num & 1)

            num >>= 1

            x, y =  y, x + y

        return res

    def doit2(self, num):

        """
        :type num: int
        :rtype: int
        """
        res, x, y, = 0, 1, 2

        while num:
            res, x, y, num = res if not num & 1 else x if num & 2 else res + x, y, x + y, num >> 1

        return res


if __name__ == "__main__":

    res = FindIntegers().doit(5)

    pass