# 868. Binary Gap

# Given a positive integer N, find and return the longest distance between two consecutive 1's in the binary representation of N.

# If there aren't two consecutive 1's, return 0.


# Example 1:

# Input: 22
# Output: 2
# Explanation:
# 22 in binary is 0b10110.
# In the binary representation of 22, there are three ones, and two consecutive pairs of 1's.
# The first consecutive pair of 1's have distance 2.
# The second consecutive pair of 1's have distance 1.
# The answer is the largest of these two distances, which is 2.

# Example 2:

# Input: 5
# Output: 2
# Explanation:
# 5 in binary is 0b101.

# Example 3:

# Input: 6
# Output: 1
# Explanation:
# 6 in binary is 0b110.

# Example 4:

# Input: 8
# Output: 0
# Explanation:
# 8 in binary is 0b1000.
# There aren't any consecutive pairs of 1's in the binary representation of 8, so we return 0.


# Note:

# 1 <= N <= 10^9

class BinaryGap:

    """
    Approach 2: One Pass
    Intuition

    In Approach 1, we created an array A of indices i for which N had the ith bit set.

    Since we only care about consecutive values of this array A, we don't need to store the whole array.
    We only need to remember the last value seen.

    Algorithm

    We'll store last, the last value added to the virtual array A. If N has the ith bit set, a candidate answer is i - last,
    and then the new last value added to A would be last = i.
    """

    def doit(self, N):

        last = None
        ans = 0
        for i in range(32):
            if (N >> i) & 1:
                if last is not None:
                    ans = max(ans, i - last)
                last = i
        return ans

    def doit(self, N):

        i, ans, last = 0, 0, -1
        while N:
            i += 1
            if N % 2 == 1:
                if last != -1 and ans < i - last:
                    ans = i - last
                last = i
            N //= 2

        return ans


if __name__ == '__main__':

    res = BinaryGap().doit(22)
