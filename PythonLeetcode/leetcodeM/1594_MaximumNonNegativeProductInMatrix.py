"""
1594. Maximum Non Negative Product in a Matrix


You are given a rows x cols matrix grid. Initially, you are located at the top-left corner (0, 0), and in each step, you can only move right or down in the matrix.

Among all possible paths starting from the top-left corner (0, 0) and ending in the bottom-right corner (rows - 1, cols - 1), find the path with the maximum non-negative product. 
The product of a path is the product of all integers in the grid cells visited along the path.

Return the maximum non-negative product modulo 109 + 7. If the maximum product is negative return -1.

Notice that the modulo is performed after getting the maximum product.

 

Example 1:

Input: grid = [[-1,-2,-3],
               [-2,-3,-3],
               [-3,-3,-2]]
Output: -1
Explanation: It's not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.
Example 2:

Input: grid = [[1,-2,1],
               [1,-2,1],
               [3,-4,1]]
Output: 8
Explanation: Maximum non-negative product is in bold (1 * 1 * -2 * -4 * 1 = 8).
Example 3:

Input: grid = [[1, 3],
               [0,-4]]
Output: 0
Explanation: Maximum non-negative product is in bold (1 * 0 * -4 = 0).
Example 4:

Input: grid = [[ 1, 4,4,0],
               [-2, 0,0,1],
               [ 1,-1,1,1]]
Output: 2
Explanation: Maximum non-negative product is in bold (1 * -2 * 1 * -1 * 1 * 1 = 2).
 

Constraints:

1 <= rows, cols <= 15
-4 <= grid[i][j] <= 4


"""


class MaximumNotNegetiveProduct:

    def doit_dp(self, grid: list) -> int:

        m, n = len(grid), len(grid[0])

        dpmax = [[float('-inf') for _ in range(n)] for _ in range(m)]
        dpmin = [[float('inf') for _ in range(n)] for _ in range(m)]

        dpmax[0][0], dpmin[0][0] = grid[0][0], grid[0][0]
        direct = (-1, 0, -1);

        for i in range(m):

            for j in range(n):

                for k in range(2):

                    x, y = i + direct[k], j + direct[k+1]

                    if x < 0 or y < 0: continue

                    dpmax[i][j] = max(dpmax[i][j], dpmax[x][y] * grid[i][j], dpmin[x][y] * grid[i][j])
                    dpmin[i][j] = min(dpmin[i][j], dpmax[x][y] * grid[i][j], dpmin[x][y] * grid[i][j])

        maxv = max(dpmax[m-1][n-1], dpmin[m-1][n-1])
        
        return -1 if maxv < 0 else (maxv % (10**9 + 7))