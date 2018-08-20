import os


# 221. Maximal Square
# Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.
# For example, given the following matrix:
# 1 0 1 0 0
# 1 0 1 1 1
# 1 1 1 1 1
# 1 0 0 1 0

class maximalSquare:

    def doit(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        if not matrix or not matrix[0]:
            return 0

        m, n = len(matrix), len(matrix[0])
        D = [[0] * n for _ in range(m)]
        ans = 0

        for i in range(n):
            D[0][i] = int(matrix[0][i])
            if D[0][i]:
                ans = 1

        for j in range(m):
            D[j][0] = int(matrix[j][0])
            if D[j][0]:
                ans = 1
        

        for i in range(1, m):

            for j in range(1, n):

                if matrix[i][j] == '0':
                    D[i][j] = 0
                else:
                    s = min(D[i-1][j], D[i][j-1])
                    D[i][j] = (s + 1) if D[i-1][j-1] >= s else D[i-1][j-1] + 1
                
                ans = max(ans, D[i][j])

        return ans * ans


    def doit1(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        if not matrix:
            return 0
        
        n, m = len(matrix), len(matrix[0])
        dp = [[0] * (m + 1) for _ in range(n + 1)]
        
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                if matrix[i-1][j-1] == '1':
                    dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1

        ans = max(x for row in dp for x in row)
        return ans ** 2

    def doit2(self, matrix):

        if not matrix:
            return 0
        
        m, n = len(matrix), len(matrix[0])
        D = [ [0] * (n+1) for _ in range(m+1)]
        ans = 0
        
        for i in range(1, m+1):
            for j in range(1, n+1):
                
                if matrix[i-1][j-1] == '1':
                    
                    D[i][j] = min(D[i-1][j-1], D[i][j-1], D[i-1][j]) + 1
                    ans = max(D[i][j], ans)

        return ans ** 2



if __name__ == "__main__":

    M = [
        ['1', '0', '1', '0', '0'],
        ['1', '0', '1', '1', '0'],
        ['1', '1', '1', '1', '1'],
        ['1', '0', '0', '1', '0'],
    ]


    res = maximalSquare().doit2(M)


    res = maximalSquare().doit([["1"]])

    M = [["1","0","1","0","0","1","1","1","0"],
         ["1","1","1","0","0","0","0","0","1"],
         ["0","0","1","1","0","0","0","1","1"],
         ["0","1","1","0","0","1","0","0","1"],
         ["1","1","0","1","1","0","0","1","0"],
         ["0","1","1","1","1","1","1","0","1"],
         ["1","0","1","1","1","0","0","1","0"],
         ["1","1","1","0","1","0","0","0","1"],
         ["0","1","1","1","1","0","0","1","0"],
         ["1","0","0","1","1","1","0","0","0"]]

    res = maximalSquare().doit(M)

    pass
