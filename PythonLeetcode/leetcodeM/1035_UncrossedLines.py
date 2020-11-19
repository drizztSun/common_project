"""
1035. Uncrossed Lines

# We write the integers of A and B (in the order they are given) on two separate horizontal lines.

# Now, we may draw connecting lines: a straight line connecting two numbers A[i] and B[j] such that:

# A[i] == B[j];
# The line we draw does not intersect any other connecting (non-horizontal) line.
# Note that a connecting lines cannot intersect even at the endpoints: each number can only belong to one connecting line.

# Return the maximum number of connecting lines we can draw in this way.


# Example 1:


# Input: A = [1,4,2], B = [1,2,4]
# Output: 2
# Explanation: We can draw 2 uncrossed lines as in the diagram.
# We cannot draw 3 uncrossed lines, because the line from A[1]=4 to B[2]=4 will intersect the line from A[2]=2 to B[1]=2.

# Example 2:

# Input: A = [2,5,1,2,5], B = [10,5,2,1,5,2]
# Output: 3

# Example 3:

# Input: A = [1,3,7,1,7,5], B = [1,9,2,5,1]
# Output: 2


# Note:

# 1 <= A.length <= 500
# 1 <= B.length <= 500
# 1 <= A[i], B[i] <= 2000
# Accepted
"""


class MaxUncrossedLines:

    # (DP)
    def doit_dp(self, A, B):

        nums = set(A) & set(B)
        def f(x): return x in nums
        A, B = filter(f, A), filter(f, B)

        # dp[i][j] is ith A and jth B
        dp = [[0 for _ in range(len(B) + 1)] for _ in range(len(A) + 1)]

        # add one more zero in both row and column avoid boundary condition
        for i in range(1, len(A) + 1):

            for j in range(1, len(B) + 1):

                if A[i-1] == B[j-1]:
                    dp[i][j] = dp[i-1][j-1] + 1
                else:
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1])

        return dp[-1][-1]

    # (DP)
    def doit_dp_1(self, A, B):

        nums = set(A) & set(B)
        def f(x): return x in nums
        A, B = list(filter(f, A)), list(filter(f, B))
        a_, b_ = len(A), len(B)

        prev, cur = [0 for _ in range(b_ + 1)], [0 for _ in range(b_ + 1)]

        for i in range(1, a_ + 1):
            prev, cur = cur, prev
            for j in range(1, b_ + 1):

                if A[i-1] == B[j-1]:
                    cur[j] = prev[j-1] + 1
                else:
                    cur[j] = max(cur[j-1], prev[j])

        return cur[-1]


if __name__ == '__main__':

    res = MaxUncrossedLines().doit(A=[1, 4, 2], B=[1, 2, 4])  # 2

    res = MaxUncrossedLines().doit(A=[2, 5, 1, 2, 5], B=[10, 5, 2, 1, 5, 2])  # 3

    res = MaxUncrossedLines().doit(A=[1, 3, 7, 1, 7, 5], B=[1, 9, 2, 5, 1])  # 2

    pass
