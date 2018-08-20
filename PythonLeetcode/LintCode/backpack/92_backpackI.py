

class BackPack:
    """
    @param m: An integer m denotes the size of a backpack
    @param A: Given n items with size A[i]
    @return: The maximum size
    """
    import collections
    def doit1(self, m, A):
        # write your code here

        def search(D, rest, cnt):

            if not D or rest == 0:
                return 0

            val = 0
            for i, c in enumerate(D):
                if rest >= D[i] and cnt[D[i]] > 0:
                    cnt[D[i]] -= 1
                    val = max( val, search(D[:i] + D[i+1:], rest - D[i], cnt) + D[i])
                    cnt[D[i]] += 1

            return val

        cnt = collections.Counter(A)
        return search(A, m, cnt)



    """
    @param m: An integer m denotes the size of a backpack
    @param A: Given n items with size A[i]
    @return: The maximum size
    """
    # O(N*V)
    def doit(self, m, A):

        dp = [[0 for _ in range(m+1)] for _ in range(len(A)+1)]

        for i in range(1, len(A)+1):

            for j in range(1, m+1):

                if j >= A[i-1]:
                    #  dp[i-1][j]  ------- (1) Don't put i into the backpack
                    #  dp[i-1][j - A[i-1]] + A[i-1]  ---- (2) if we put i into it, we have to find the maximum if first 'i-1'
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j - A[i-1]] + A[i-1])
                else:
                    dp[i][j] = dp[i-1][j]

        return dp[len(A)][m]


    """
    @param m: An integer m denotes the size of a backpack
    @param A: Given n items with size A[i]
    @return: The maximum size
    """
    def doit(self, m, A):

        dp = [0 for _ in range(m+1)]

        for j in range(1, len(A)+1):

            for i in reversed(range(m + 1)):

                if i >= A[j-1]:
                    dp[i] = max(dp[i], dp[i-A[j-1]] + A[j-1])

        return dp[-1]


if __name__ == "__main__":

    res = BackPack().doit(10, [3,4,8,5])

    res = BackPack().doit(90, [12,3,7,4,5,13,2,8,4,7,6,5,7])

    pass