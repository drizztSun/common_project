"""
960. Delete Columns to Make Sorted III

# We are given an array A of N lowercase letter strings, all of the same length.

# Now, we may choose any set of deletion indices, and for each string, we delete all the characters in those indices.

# For example, if we have an array A = ["babca","bbazb"] and deletion indices {0, 1, 4}, then the final array after deletions is ["bc","az"].

# Suppose we chose a set of deletion indices D such that after deletions, the final array has every element (row) in lexicographic order.

# For clarity, A[0] is in lexicographic order (ie. A[0][0] <= A[0][1] <= ... <= A[0][A[0].length - 1]), A[1] is in lexicographic order (ie. A[1][0] <= A[1][1] <= ... <= A[1][A[1].length - 1]), and so on.

# Return the minimum possible value of D.length.


# Example 1:

# Input: ["babca","bbazb"]
# Output: 3
# Explanation: After deleting columns 0, 1, and 4, the final array is A = ["bc", "az"].
# Both these rows are individually in lexicographic order (ie. A[0][0] <= A[0][1] and A[1][0] <= A[1][1]).
# Note that A[0] > A[1] - the array A isn't necessarily in lexicographic order.

# Example 2:

# Input: ["edcba"]
# Output: 4
# Explanation: If we delete less than 4 columns, the only row won't be lexicographically sorted.

# Example 3:

# Input: ["ghi","def","abc"]
# Output: 0
# Explanation: All rows are already lexicographically sorted.
"""


class MinDeletionSize:

    """
    Approach 1: Dynamic Programming
    Intuition and Algorithm

    This is a tricky problem that is hard to build an intuition about.

    First, lets try to find the number of columns to keep, instead of the number to delete. At the end, we can subtract to find the desired answer.

    Now, let's say we must keep the first column C. The next column D we keep must have all rows lexicographically sorted (ie. C[i] <= D[i]),
    and we can say that we have deleted all columns between C and D.

    Now, we can use dynamic programming to solve the problem in this manner.
    Let dp[k] be the number of columns that are kept in answering the question for input [row[k:] for row in A].
    The above gives a simple recursion for dp[k].

    Complexity Analysis

    Time Complexity: O(N * W^2), where N is the length of A, and W is the length of each word in A.

    Space Complexity: O(W).
    """

    def doit_dp(self, A):

        dp = [1 for _ in range(len(A[0]))]

        for i in range(len(A[0]) - 2, -1, -1):

            for j in range(i + 1, len(A[0])):

                if all(row[i] <= row[j] for row in A):
                    dp[i] = max(dp[i], 1 + dp[j])

        return len(A[0]) - max(dp)

    def doit_dp_1(self, A):
        dp = [(1, 1)] * len(A[0])
        for i in range(len(dp)):
            if i > 0:
                max_pre = None
                for pre in range(i - 1, -1, -1):
                    for word in A:
                        if word[pre] > word[i]:
                            pre -= 1
                            break
                    else:
                        if max_pre is None or dp[pre][1] > dp[max_pre][1]:
                            max_pre = pre

                max_len = 1 if max_pre is None else max(1, dp[max_pre][1] + 1)
                overall = max(dp[i - 1][0], max_len)
                dp[i] = (overall, max_len)
        # print(dp)
        return len(dp) - dp[-1][0]


if __name__ == "__main__":

    res = MinDeletionSize().doit(["babca", "bbazb"])

    res = MinDeletionSize().doit(["edcba"])

    res = MinDeletionSize().doit(["ghi", "def", "abc"])

    pass
