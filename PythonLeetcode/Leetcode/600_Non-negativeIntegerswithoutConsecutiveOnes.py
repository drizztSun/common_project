"""
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
"""


class FindIntegers(object):

    """
    Approach #3 Using Bit Manipulation [Accepted]
    Algorithm

    Before we discuss the idea behind this approach, we consider another simple idea that will be used in the current approach.

    Suppose, we need to find the count of binary numbers with nn bits such that these numbers don't contain consecutive 1's.
    In order to do so, we can look at the problem in a recursive fashion. Suppose f[i] gives the count of such binary numbers with i bits.
    In order to determine the value of f[n], which is the requirement, we can consider the cases shown below:

    Now, we look at the case, where numnum contains some consecutive 1's. The idea will be the same as the last example, with the only exception taken when the two consecutive 1's are encountered. Let's say, num = \text{1011010}num=1011010(7 bit number). Now, as per the last discussion, we start with the MSB. We find a \text{1}1 at this position. Thus, we initially fix a \text{0}0 at this position to consider the numbers in the range \textbf{0}\text{000000} -> \textbf{0}\text{111111}0000000−>0111111, by varying the 6 LSB bits only. The count of the required numbers in this range is again given by f[6]f[6].

    Now, we fix a \text{1}1 at the MSB and move on to the second bit. It is a \text{0}0, so we have no choice but to fix \text{0}0 at this position and to proceed with the third bit. It is a \text{1}1, so we fix a \text{0}0 here, considering the numbers in the range \textbf{100}\text{0000} -> \textbf{100}\text{1111}1000000−>1001111. This accounts for a factor of f[4]f[4]. Now, we fix a \text{1}1 at the third positon, and proceed with the fourth bit. It is a \text{1}1(consecutive to the previous \text{1}1). Now, initially we fix a \text{0}0 at the fourth position, considering the numbers in the range \textbf{1010}\text{000} -> \textbf{1010}\text{111}1010000−>1010111. This adds a factor of f[3]f[3] to the required count.

    Now, we can see that till now the numbers in the range \textbf{0}\text{000000} -> \textbf{0}\text{111111}0000000−>0111111, \textbf{100}\text{0000} -> \textbf{100}\text{1111}1000000−>1001111, \textbf{1010}\text{000} -> \textbf{1010}\text{111}1010000−>1010111 have been considered. But, if we try to consider any number larger than \text{1010111}1010111, it leads to the presence of two consecutive 1's in the new number at the third and fourth position. Thus, all the valid numbers upto numnum have been considered with this, giving a resultant count of f[6] + f[4] + f[3]f[6]+f[4]+f[3].



    """
    def doit_dp(self, num: int) -> int:

        fn = [0 for _ in range(32)]
        fn[0] = 1
        fn[1] = 2

        for i in range(2, 32):
            fn[i] = fn[i - 1] + fn[i - 2]

        i = 30
        total = 0
        pre_bit = 0

        while i >= 0:
            # discard bit is 0, because it is consider as 1, it will exceed the num
            if (num & (1 << i)) != 0:
                total += fn[i]
                if pre_bit == 1:
                    # if it is first 11, cal and quit, because the rest number til to num, will have 10011xxx, that has consecutive 11.
                    total -= 1
                    break
                pre_bit = 1
            else:
                pre_bit = 0

            i -= 1

        return total + 1

    def doit_dp(self, num: int) -> int:
        dp = [0] * 32
        dp[0] = 2
        dp[1] = 2
        dp[2] = 3
        s = '{0:b}'.format(num)
        n = len(s)
        for i in range(3, n + 2):
            dp[i] = dp[i - 1] + dp[i - 2] - 1
        res = 0
        res += dp[n]
        for i in range(1, n):
            if s[i] == '1' and s[i - 1] == '1':
                res += (dp[n - i] - 2)
                break
            elif s[i] == '1':
                res += (dp[n - i] - 1)

        return res


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

    def doit_dp_1(self, num):
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

    res = FindIntegers().doit_dp(2)

    pass