


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

    pass








