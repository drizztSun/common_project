# 1014. Best Sightseeing Pair

# Given an array A of positive integers, A[i] represents the value of the i-th sightseeing spot,
# and two sightseeing spots i and j have distance j - i between them.

# The score of a pair (i < j) of sightseeing spots is (A[i] + A[j] + i - j) :
# the sum of the values of the sightseeing spots, minus the distance between them.

# Return the maximum score of a pair of sightseeing spots.


# Example 1:

# Input: [8,1,5,2,6]
# Output: 11
# Explanation: i = 0, j = 2, A[i] + A[j] + i - j = 8 + 5 + 0 - 2 = 11


# Note:

# 2 <= A.length <= 50000
# 1 <= A[i] <= 1000

class MaxScoreSightseeingPair:

    def doit(self, A):

        ans, maxv = 0, 0
        for i, c in enumerate(A):

            if c - i + maxv > ans:
                ans = c - i + maxv

            maxv = max(maxv, c + i)

        return ans

    def doit(self, A):

        ninf = float('-inf')
        best, x0, x1, xs = 0, A[0], ninf, [A[0]]
        for i, x in enumerate(A[1:], 1):
            x2, x3 = x - i, x + i
            if x1 <= x2:
                x0, x1 = xs[-1], x2
                best = max(x0 + x1, best)
            if x0 < x3:
                x0, x1, xs = x3, ninf, [x3]
        return best


if __name__ == '__main__':

    res = MaxScoreSightseeingPair().doit([8, 1, 5, 2, 6])

    pass
