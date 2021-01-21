"""
64. Minimum Path Sum

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

 

Example 1:


Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
Example 2:

Input: grid = [[1,2,3],[4,5,6]]
Output: 12
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 200
0 <= grid[i][j] <= 100

"""



class MinPathSum:
    
    """
        Approach 2: Dynamic Programming 2D
        Algorithm

        We use an extra matrix dpdp of the same size as the original matrix. In this matrix, dp(i, j)dp(i,j) represents the minimum sum of the path from the index (i, j)(i,j) to the bottom rightmost element. 
        We start by initializing the bottom rightmost element of dpdp as the last element of the given matrix. 
        Then for each element starting from the bottom right, we traverse backwards and fill in the matrix with the required minimum sums. Now, we need to note that at every element, we can move either rightwards or downwards. 
        Therefore, for filling in the minimum sum, we use the equation:

        dp(i, j)= min(dp(i+1,j),dp(i,j+1))

        taking care of the boundary conditions.

        The following figure illustrates the process:

        Current
        1 / 17

        Complexity Analysis

        Time complexity : O(mn). We traverse the entire matrix once.

        Space complexity : O(mn). Another matrix of the same size is used.
    """
    def doit_dp_(self, grid: list) -> int:
        
        m, n = len(grid), len(grid[0])
        dp = [[0 for _ in range(n)] for _ in range(m)]

        for i in range(m):
            for j in range(n):
                dp[i][j] += grid[i][j]
                if i == 0 and j == 0:
                    continue
                
                if i == 0:
                    dp[i][j] += dp[i][j-1]
                elif j == 0:
                    dp[i][j] += dp[i-1][j]
                else:
                    dp[i][j] += min(dp[i-1][j], dp[i][j-1])

        return dp[m-1][n-1]

    """
        Approach 4: Dynamic Programming (Without Extra Space)
        Algorithm

        This approach is same as Approach 2, with a slight difference. Instead of using another dpdp matrix. We can store the minimum sums in the original matrix itself, since we need not retain the original matrix here. Thus, the governing equation now becomes:

        grid(i, j) = grid(i,j)+\min \big(\mathrm{grid}(i+1,j), \mathrm{grid}(i,j+1)\big)grid(i,j)=grid(i,j)+min(grid(i+1,j),grid(i,j+1))

        Complexity Analysis

        Time complexity : O(mn)O(mn). We traverse the entire matrix once.

        Space complexity : O(1)O(1). No extra space is used.
    """

    def doit_dp_1(self, grid: list) -> list:

        m, n = len(grid), len(grid[0])
        for i in range(m):
            for j in range(n):

                if i == 0 and j == 0: 
                    continue
                elif i == 0:
                    grid[i][j] += grid[i][j-1]
                elif j == 0:
                    grid[i][j] += grid[i-1][j]
                else:
                    grid[i][j] += min(grid[i-1][j], grid[i][j-1])

        return grid[m-1][n-1]