"""
1139. Largest 1-Bordered Square



Given a 2D grid of 0s and 1s, return the number of elements in the largest square subgrid that has all 1s on its border, or 0 if such a subgrid doesn't exist in the grid.

 

Example 1:

Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
Output: 9
Example 2:

Input: grid = [[1,1,0,0]]
Output: 1
 

Constraints:

1 <= grid.length <= 100
1 <= grid[0].length <= 100
grid[i][j] is 0 or 1

"""



class Largest1BorderedSquare:


    def doit_(self, A):
        m, n = len(A), len(A[0])
        res = 0
        top, left = [a[:] for a in A], [a[:] for a in A]
        for i in range(m):
            for j in range(n):
                if A[i][j]:
                    if i: top[i][j] = top[i - 1][j] + 1
                    if j: left[i][j] = left[i][j - 1] + 1

        for r in range(min(m, n), 0, -1):
            for i in range(m - r + 1):
                for j in range(n - r + 1):
                    if min(top[i + r - 1][j], top[i + r - 1][j + r - 1], left[i][j + r - 1], left[i + r - 1][j + r - 1]) >= r:
                        return r * r
        return 0
    
    def doit_(self, grid: list) -> int:

        m, n = len(grid), len(grid[0])

        top = [[0 for _ in range(n)] for _ in range(m)]
        left = [[0 for _ in range(n)] for _ in range(m)]

        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    top[i][j], left[i][j] = 1, 1 
                    if i > 0:
                        top[i][j] = top[i-1][j] + 1
                    if j > 0:
                        left[i][j] = left[i][j-1] + 1

        for r in range(min(m, n), 0, -1):

            for i in range(m-r+1):
                for j in range(n-r+1):
                    if min(top[i + r -1][j], top[i+r-1][j+r-1], left[i][j+r-1], left[i+r-1][j+r-1]) >= r:
                        return r * r
                
        return 0




        