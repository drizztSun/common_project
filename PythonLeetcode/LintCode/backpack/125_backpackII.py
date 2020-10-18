"""
Description
There are n items and a backpack with size m. Given array A representing the size of each item and array V representing the value of each item.

What's the maximum value can you put into the backpack?

A[i], V[i], n, m are all integers.
You can not split an item.
The sum size of the items you want to put into backpack can not exceed m.
Each item can only be picked up once
Have you met this question in a real interview?
Example
Example 1:

Input: m = 10, A = [2, 3, 5, 7], V = [1, 5, 2, 4]
Output: 9
Explanation: Put A[1] and A[3] into backpack, getting the maximum value V[1] + V[3] = 9
Example 2:

Input: m = 10, A = [2, 3, 8], V = [2, 5, 8]
Output: 10
Explanation: Put A[0] and A[2] into backpack, getting the maximum value V[0] + V[2] = 10
Challenge
O(nm) memory is acceptable, can you do it in O(m) memory?
"""


class BackPackII:

    """
    @param m: An integer m denotes the size of a backpack
    @param A: Given n items with size A[i]
    @param V: Given n items with value V[i]
    @return: The maximum value
    """
    # Space(M)
    def doit(self, m, A, V):
        # write your code here
        n, dp = len(A), [0 for _ in range(m+1)]

        for j in range(n):
            for i in reversed(range(1, m+1)):
                if i >= A[j]:
                    dp[i] = max(dp[i], dp[i-A[j]] + V[j])
        return dp[-1]


    """
    @param m: An integer m denotes the size of a backpack
    @param A: Given n items with size A[i]
    @param V: Given n items with value V[i]
    @return: The maximum value
    """
    # Space(N*M)
    def doit1(self, m, A, V):
        # write your code here
        n = len(A)
        dp = [[0 for _ in range(n + 1)] for _ in range(m+1)]

        for j in range(1, n + 1):
            for i in range(1, m+1):
                # compare ( first j-1 objects put into i's A, dp[i][j-1] )
                # with dp[i-A[j-1]][j-1] (Must put A[j] into pack, so the dp[i-A[j-1]][j-1], first 'j-1' objects into 'i-A[j-1]' V
                if i >= A[j-1]:
                    dp[i][j] = max(dp[i][j-1], dp[i-A[j-1]][j-1] + V[j-1])
                else:
                    dp[i][j] = dp[i][j-1]
        return dp[m][n]


    """
    @param m: An integer m denotes the size of a backpack
    @param A: Given n items with size A[i]
    @param V: Given n items with value V[i]
    @return: The maximum value
    """
    # Space(2 * M)
    def doit(self, m, A, V):
        # write your code here
        dp, n = [[0 for _ in range(m+1)] for _ in range(2)], len(A)

        for j in range(0, n):
            for i in range(1, m+1):
                #
                index = j & 1
                dp[index][i] = dp[index ^ 1][i]
                if i >= A[j]:
                    dp[index][i] = max(dp[index][i], dp[index ^ 1][i - A[j]] + V[j])

        return dp[n&1][-1]


if __name__ == "__main__":

    res = BackPackII().doit(100, [77, 22, 29, 50, 99], [92, 22, 87, 46, 90]) # 133

    res = BackPackII().doit(200, [79, 58, 86, 11, 28, 62, 15, 68], [83, 14, 54, 79, 72, 52, 48, 62]) # 334
