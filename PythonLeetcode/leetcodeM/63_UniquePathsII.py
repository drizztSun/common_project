"""
63. Unique Paths II

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and space is marked as 1 and 0 respectively in the grid.

 

Example 1:


Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right
Example 2:


Input: obstacleGrid = [[0,1],[0,0]]
Output: 1
 

Constraints:

m == obstacleGrid.length
n == obstacleGrid[i].length
1 <= m, n <= 100
obstacleGrid[i][j] is 0 or 1.


"""


class UniquePathsWithObstacles:

    def doit_dp(self, obstacleGrid: list) -> int:

        m, n = len(obstacleGrid), len(obstacleGrid[0])

        dp = [[0 for _ in range(n)] for _ in range(m)]
        dp[0][0] = 1
        
        for i in range(m):
        
            for j in range(n):

                if obstacleGrid[i][j] == 1:
                    dp[i][j] = 0
                    continue
                
                dp[i][j] += dp[i-1][j] if i > 0 else 0
                dp[i][j] += dp[i][j-1] if j > 0 else 0
                
        return dp[-1][-1]