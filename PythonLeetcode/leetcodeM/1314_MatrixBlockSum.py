"""
1314. Matrix Block Sum


Given a m * n matrix mat and an integer K, return a matrix answer where each answer[i][j] is the sum of all elements mat[r][c] for i - K <= r <= i + K, j - K <= c <= j + K, and (r, c) is a valid position in the matrix.
 

Example 1:

Input: mat = [[1,2,3],[4,5,6],[7,8,9]], K = 1
Output: [[12,21,16],[27,45,33],[24,39,28]]
Example 2:

Input: mat = [[1,2,3],[4,5,6],[7,8,9]], K = 2
Output: [[45,45,45],[45,45,45],[45,45,45]]
 

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n, K <= 100
1 <= mat[i][j] <= 100

"""


class MatrixBlockSum:

    def doit_(self, mat: list, k: int) -> list:

        m, n = len(mat), len(mat[0])
        presums = [[0 for _ in range(n)] for _ in range(m)]
        
        for i in range(m):
            tmp = 0
            for j in range(n):
                tmp += mat[i][j]
                presums[i][j] = tmp + (presums[i-1][j] if i > 0 else 0)
                
        def build(i, j):
            sx, sy = max(0, i - k), max(0, j - k)
            ex, ey = min(m-1, i + k), min(n-1, j + k)
            
            res = presums[ex][ey]
            
            if sy > 0:
                res -= presums[ex][sy-1]
            
            if sx > 0:
                res -= presums[sx - 1][ey]
                
            if sx > 0 and sy > 0:
                res += presums[sx-1][sy-1]
            
            return res
            
        ans = [[0 for _ in range(n)] for _ in range(m)]
        for i in range(m):
            for j in range(n):
                ans[i][j] = build(i, j)
                
        return ans
        