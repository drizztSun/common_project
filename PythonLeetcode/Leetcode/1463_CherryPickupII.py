"""
1463. Cherry Pickup II

Given a rows x cols matrix grid representing a field of cherries. Each cell in grid represents the number of cherries that you can collect.

You have two robots that can collect cherries for you, Robot #1 is located at the top-left corner (0,0) , and Robot #2 is located at the top-right corner (0, cols-1) of the grid.

Return the maximum number of cherries collection using both robots  by following the rules below:

From a cell (i,j), robots can move to cell (i+1, j-1) , (i+1, j) or (i+1, j+1).
When any robot is passing through a cell, It picks it up all cherries, and the cell becomes an empty cell (0).
When both robots stay on the same cell, only one of them takes the cherries.
Both robots cannot move outside of the grid at any moment.
Both robots should reach the bottom row in the grid.


Example 1:



Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
Output: 24
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
Total of cherries: 12 + 12 = 24.
Example 2:



Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
Output: 28
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
Total of cherries: 17 + 11 = 28.
Example 3:

Input: grid = [[1,0,0,3],[0,0,0,3],[0,0,3,3],[9,0,3,3]]
Output: 22
Example 4:

Input: grid = [[1,1],[1,1]]
Output: 4


Constraints:

rows == grid.length
cols == grid[i].length
2 <= rows, cols <= 70
0 <= grid[i][j] <= 100
"""


class CherryPickupII:

    def doit_dp(self, grid) -> int:

        n, m = len(grid), len(grid[0])
        dp = [[0] * (m + 2) for _ in range(m + 2)]
        dp[0][m-1] = grid[0][0] + grid[0][m-1]

        for i in range(1, n): # each level
            tmp = [[0] * (m + 2) for _ in range(m + 2)]
            # each time, you can move one more to left or right, so the most one is i+1 or m-1-i
            for j in range(min(i + 1, m)): # robot 1'col,
                for k in range(max(m - i - 1, 0), m): # robot 2'col
                    if j != k:
                        tmp[j][k] = max(dp[j-1][k],   dp[j][k],   dp[j+1][k],
                                        dp[j-1][k-1], dp[j][k-1], dp[j+1][k-1],
                                        dp[j-1][k+1], dp[j][k+1], dp[j+1][k+1])
                        tmp[j][k] += grid[i][j] + grid[i][k]

            dp = tmp[:][:]

        return max(max(i) for i in dp)

    def doit_dp(self, grid: list) -> int:

        memo = {}

        def search(r, c1, c2):

            if (r, c1, c2) in memo:
                return memo[(r, c1, c2)]

            if r == len(grid) - 1:
                return grid[-1][c1] + grid[-1][c2]

            maxv = -1
            for i in (c1-1, c1, c1+1):
                for j in (c2-1, c2, c2+1):
                    if 0 <= i < len(grid[0]) and 0 <= j < len(grid[0]) and i != j:
                        maxv = max(maxv, search(r+1, i, j))
            maxv += grid[r][c1] + grid[r][c2]
            memo[(r, c1, c2)] = maxv
            return maxv

        return search(0, 0, len(grid[0])-1)


    """
    Approach #1: Dynamic Programming (Top Down)
    Intuition
    
    In this part, we will explain how to think of this approach step by step.
    
    If you are only interested in the pure algorithm, you can jump to the algorithm part.
    
    We need to move two robots! Note that the order of moving robot1 or robot2 does not matter since it would not impact the cherries we can pick. The number of cherries we can pick only depends on the tracks of our robots.
    
    Therefore, we can move the robot1 and robot2 in any order we want. We aim to apply DP, so we are looking for an order that suitable for DP.
    
    Let's try a few possible moving orders.
    
    Can we move robot1 firstly to the bottom row, and then move robot2?
    
    Maybe not. In this case, the movement of robot1 will impact the movement of robot2. In other words, the optimal track of robot2 depends on the track of robot1. 
    If we want to apply DP, we need to record the whole track of robot1 as the state. The number of sub-problems is too much.
    
    In fact, in any case, when we move one robot several steps earlier than the other, the movement of the first robot will impact the movement of the second robot.
    
    Unless we move them synchronously (i.e., move one step of robot1 and robot2 at the same time).
    
    Let's define the DP state as (row1, col1, row2, col2), where (row1, col1) represents the location of robot1, and (row2, col2) represents the location of robot2.
    
    If we move them synchronously, robot1 and robot2 will always on the same row. Therefore, row1 == row2.
    
    Let row = row1. The DP state is simplified to (row, col1, col2), where (row, col1) represents the location of robot1, and (row, col2) represents the location of robot2.


    """
    def doit_dp_Topdown(self, grid: list) -> int:
        from functools import lru_cache

        m, n = len(grid), len(grid[0])

        @lru_cache(None)
        def dp(row, col1, col2):
            if col1 < 0 or col1 >= n or col2 < 0 or col2 >= n:
                return float("-inf")

            # current cell
            result = grid[row][col1] + (grid[row][col2] if col1 != col2 else 0)

            # transition
            if row != m-1:
                result += max(dp(row+1, new_col1, new_col2) for new_col1 in [col1, col1+1, col1-1] for new_col2 in [col2, col2+1, col2-1])
            return result

        return dp(0, 0, n-1)

    """
    Approach #2: Dynamic Programming (Bottom Up)
    Intuition
    
    Similarly, we need a three-dimension array dp[row][col1][col2] to store calculated results:
    
    dp[row][col1][col2] represents the maximum cherries we can pick if robot1 starts at (row, col1) and robot2 starts at (row, col2).
    
    Remember, we move robot1 and robot2 synchronously, so they are always on the same row.
    
    The base cases are that robot1 and robot2 both start at the bottom row. In this case, we only need to calculate the cherry at current cells.
    
    Otherwise, apply the transition equation to get the maximum cherries we can pick in the future.
    
    Since the base case is at the bottom row, we need to iterate from the bottom row to the top row when filling the dp array.
    
    You can use state compression to save the first dimension since we only need dp[row+1] when calculating dp[row].
    
    You can change the meaning of dp[row][col1][col2] and some corresponding codes to get some other similar approaches. For example, let dp[row][col1][col2] mean the maximum cherries we can pick if robot1 ends at (row, col1) and robot2 ends at (row, col2).
    
    Algorithm
    
    Define a three-dimension dp array where each dimension has a size of m, n, and n respectively.
    
    dp[row][col1][col2] represents the maximum cherries we can pick if robot1 starts at (row, col1) and robot2 starts at (row, col2).
    
    To compute dp[row][col1][col2] (transition equation):
    
    Collect the cherry at (row, col1) and (row, col2). Do not double count if col1 == col2.
    
    If we are not in the last row, we need to add the maximum cherries we can pick in the future.
    
    The maximum cherries we can pick in the future is the maximum of dp[row+1][new_col1][new_col2], where new_col1 can be col1, col1+1, or col1-1, and new_col2 can be col2, col2+1, or col2-1.
    
    Finally, return dp[0][0][last_column].

    Complexity Analysis
    
    Let MM be the number of rows in grid and NN be the number of columns in grid.
    
    Time Complexity: \mathcal{O}(MN^2)O(MN 
    2
     ), since our dynamic programming has three nested for-loops, which have MM, NN, and NN iterations respectively. In total, it costs \mathcal{O}(M \cdot N \cdot N) = \mathcal{O}(MN^2)O(M⋅N⋅N)=O(MN 
    2
     ).
    
    Space Complexity: \mathcal{O}(MN^2)O(MN 
    2
     ) if not use state compression, since our dp array has \mathcal{O}(M \cdot N \cdot N) = \mathcal{O}(MN^2)O(M⋅N⋅N)=O(MN 
    2
     ) elements. \mathcal{O}(N^2)O(N 
    2
     ) if use state compression, since we can reuse the first dimension, and our dp array only has \mathcal{O}(N \cdot N) = \mathcal{O}(N^2)O(N⋅N)=O(N 
    2
     ) elements.
    """
    def doit_dp_Bottoump(self, grid: list) -> int:

        M, N = len(grid), len(grid[0])
        dp = [[[0] * N for _ in range(N)] for _ in range(M)]

        for r in range(M-1, -1, -1):
            for c1 in range(N):
                for c2 in range(N):
                    maxv = grid[r][c1] if c1 == c2 else (grid[r][c1] + grid[r][c2])
                    if r+1 < M:
                        maxv += max(dp[r+1][i][j] for i in (c1-1, c1, c1+1) for j in (c2-1, c2, c2+1) if 0 <= i < N and 0 <= j < N)

                    dp[r][c1][c2] = maxv

        return dp[0][0][N-1]


if __name__ == '__main__':

    CherryPickupII().doit_dp(grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]])

    CherryPickupII().doit_dp(grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]])


