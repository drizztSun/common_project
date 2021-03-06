# 910. Smallest Range II

# Given an array A of integers, for each integer A[i] we need to choose either x = -K or x = K, and add x to A[i] (only once).

# After this process, we have some array B.

# Return the smallest possible difference between the maximum value of B and the minimum value of B.


# Example 1:

# Input: A = [1], K = 0
# Output: 0
# Explanation: B = [1]

# Example 2:

# Input: A = [0,10], K = 2
# Output: 6
# Explanation: B = [2,8]

# Example 3:

# Input: A = [1,3,6], K = 3
# Output: 3
# Explanation: B = [4,6,3]


# Note:

# 1 <= A.length <= 10000
# 0 <= A[i] <= 10000
# 0 <= K <= 10000

"""
Approach 1: Linear Scan
Intuition

As in Smallest Range I, smaller A[i] will choose to increase their value ("go up"), and bigger A[i] will decrease their value ("go down").

Algorithm

We can formalize the above concept: if A[i] < A[j], we don't need to consider when A[i] goes down while A[j] goes up.
This is because the interval (A[i] + K, A[j] - K) is a subset of (A[i] - K, A[j] + K) (here, (a, b) for a > b denotes (b, a) instead.)

That means that it is never worse to choose (up, down) instead of (down, up).
We can prove this claim that one interval is a subset of another, by showing both A[i] + K and A[j] - K are between A[i] - K and A[j] + K.

For sorted A, say A[i] is the largest i that goes up. Then A[0] + K, A[i] + K, A[i+1] - K, A[A.length - 1] - K
are the only relevant values for calculating the answer: every other value is between one of these extremal values.
"""


class SmallestRangeII:

    def doit(self, A, K):

        A.sort()
        ans = A[-1] - A[0]

        for i in range(len(A) - 1):
            ans = min(ans, max(A[-1] - K, A[i] + K) -
                      min(A[0] + K, A[i+1] - K))
        return ans

    def doit(self, A, K):
        A = list(dict.fromkeys(A))
        A.sort()

        min_a = A[0]
        max_a = A[-1]

        end = min_a
        res = max_a - min_a
        for i in range(len(A)-1, 0, -1):
            if A[i] < end:
                break

            x = A[i] - 2 * K

            min_a = min(x, min_a)
            max_a = max(x, A[i-1], end)
            end = max(end, x)

            if max_a - min_a < res:
                res = max_a - min_a

        return res


if __name__ == '__main__':

    res = SmallestRangeII().doit(A=[1], K=0)  # 0

    res = SmallestRangeII().doit(A=[0, 10], K=2)  # 6

    res = SmallestRangeII().doit(A=[1, 3, 6], K=3)  # 3

    pass
