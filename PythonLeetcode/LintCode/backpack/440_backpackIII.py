
# 440 BackPack III

# Given n kind of items with size Ai and value Vi( each item has an infinite number available)
# and a backpack with size m. What's the maximum value can you put into the backpack

# Notice
# You cannot divide item into small pieces and the total size of items you choose should smaller or equal to m.

# Example
# Given 4 items with size [2, 3, 5, 7] and value [1, 5, 2, 4], and a backpack with size 10. The maximum value is 15.



class BackPackIII:


    def doit(self, A, V, m):
        """
        @param A: an integer array
        @param V: an integer array
        @param m: An integer
        @return: an array
        """
        # write your code here
        dp = [[0 for _ in range(m+1)] for _ in range(len(A)+1)]

        for i in range(1, len(A) + 1):
            for j in range(1, m+1):
                dp[i][j] = dp[i-1][j]
                for c in reversed(range(1, j//A[i-1] + 1)):
                    dp[i][j] = max(dp[i][j], dp[i][j - c * A[i-1]] + c * V[i-1])

        return dp[-1][-1]


    def doit(self, A, V, m):
        """
        @param A: an integer array
        @param V: an integer array
        @param m: An integer
        @return: an array
        """
        dp = [0 for _ in range(m+1)]

        for i in range(len(A)):
            # each iter, put a new element into the bakcpack
            for j in range(A[i], m + 1):
                # each iter 'i', dp[j] is keeping value in 'i-1'. so dp[j] == dp[j][i-1]
                # so dp[j][i] should be dp[j][i-1] or greater. because it means we could put 0 'i' object into backpack
                # then start from '0' to m, [A[j], m]
                # if "dp[j - A[i]] + V[i]" is bigger, it means we can put one 'V[i]' into the backpack dp[j]
                # Why we doesn't check more objects here. because of dp[j- A[i]] already have (n >= 0) V[i]
                # this is because of wwe starts from [0, m]
                dp[j] = max(dp[j], dp[j - A[i]] + V[i])

        return dp[-1]


if __name__ == "__main__":

    res = BackPackIII().doit([], [], 100) #0

    res = BackPackIII().doit([2, 3, 5, 7], [1, 5, 2, 4], 10) #15

    pass