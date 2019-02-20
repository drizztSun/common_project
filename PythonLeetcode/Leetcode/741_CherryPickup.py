

# 741. Cherry Pickup

# In a N x N grid representing a field of cherries, each cell is one of three possible integers.

# 0 means the cell is empty, so you can pass through;
# 1 means the cell contains a cherry, that you can pick up and pass through;
# -1 means the cell contains a thorn that blocks your way.
# Your task is to collect maximum number of cherries possible by following the rules below:

# Starting at the position (0, 0) and reaching (N-1, N-1) by moving right or down through valid path cells (cells with value 0 or 1);
# After reaching (N-1, N-1), returning to (0, 0) by moving left or up through valid path cells;
# When passing through a path cell containing a cherry, you pick it up and the cell becomes an empty cell (0);
# If there is no valid path between (0, 0) and (N-1, N-1), then no cherries can be collected.

# Example 1:
# Input: grid =
# [[0, 1, -1],
#  [1, 0, -1],
#  [1, 1,  1]]

# Output: 5
# Explanation: 

# The player started at (0, 0) and went down, down, right right to reach (2, 2).
# 4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
# Then, the player went left, up, up, left to return home, picking up one more cherry.
# The total number of cherries picked up is 5, and this is the maximum possible.

# Note:

# grid is an N by N 2D array, with 1 <= N <= 50.
# Each grid[i][j] is an integer in the set {-1, 0, 1}.
# It is guaranteed that grid[0][0] and grid[N-1][N-1] are not -1. 



class CherryPickup:



# The idea is to use self.memo[(i1, j1, i2, j2)] to store the maximum number of cherries that can be collected starting from (i1, j1) to (N-1, N-1) then to(i2, j2).
# Note that since I am taking a step at each end at the same time, i1+j1 is always equal to i2+j2, therefore there are only O(N^3) states
# (and I am using the full quadruple to store the state for the sake of clearness).
    # <DP> <O(N^3)>
    def doit(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        
        def dp(i1, j1, i2, j2):
            
            if (i1, j1, i2, j2) in memo:
                return memo[(i1, j1, i2, j2)]

            if i1 == N or j1 == N or i2 == N or j2 == N:
                return -1

            if i1 == N-1 and j1 == N-1 and i2 == N-1 and j2 == N-1:
                return grid[-1][-1]

            if grid[i1][j1] == -1 or grid[i2][j2] == -1:
                return -1

            # now can take a step in two directions at each end, which amounts to 4 combinations in total
            dd = dp(i1+1, j1, i2+1, j2)
            dr = dp(i1+1, j1, i2, j2+1)
            rd = dp(i1, j1+1, i2+1, j2)
            rr = dp(i1, j1+1, i2, j2+1)

            maxCob = max([dd, dr, rd, rr])

            # find if there is a way to reach the end
            if maxCob == -1:
                out = -1

            else:
                # same cell only one 
                if i1 == i2 and j1 == j2:
                    out = maxCob + grid[i1][j1]
                # diff one so we use both
                else:
                    out = maxCob + grid[i1][j1] + grid[i2][j2]

                
            memo[(i1, j1, i2, j2)] = out
            return out

        memo = {}
        N = len(grid)

        return max(dp(0, 0, 0, 0), 0);

    # <DP>
    def doit1(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        N = len(grid)
        dp = [[[-1]*N for _ in range(N)] for _ in range(2)]
        dp[0][0][0] = grid[0][0]

        if N == 1: 
            return dp[0][0][0]

        # How many steps to go
        for step in range(1, 2*N-1):
            # 
            for x1 in range(max(0, step-(N-1)), min(N-1, step) + 1):

                y1 = step - x1
                for x2 in range(max(0, step-(N-1), x1), min(N-1, step) + 1):

                    y2 = step - x2
                    if grid[x1][y1] == -1 or grid[x2][y2] == -1:
                        dp[step % 2][x1][x2] = -1
                        continue

                    r1 = -1 if x1 == 0 or y2 == 0 else dp[(step + 1) % 2][x1 - 1][x2]
                    r2 = -1 if x2 == 0 or y1 == 0 else dp[(step + 1) % 2][x1][x2 - 1]
                    r3 = -1 if x1 == 0 or x2 == 0 else dp[(step + 1) % 2][x1 - 1][x2 - 1]
                    r4 = -1 if y1 == 0 or y2 == 0 else dp[(step + 1) % 2][x1][x2]

                    maxv = max(r1, r2, r3, r4)

                    if maxv == -1:
                        dp[step % 2][x1][x2] = -1
                    else:
                        dp[step % 2][x1][x2] = maxv + grid[x1][y1] + grid[x2][y2] - (0 if x1 != x2 or grid[x1][y1] != 1 else 1)

        res = dp[step % 2][N-1][N-1]
        return 0 if res == -1 else res



if __name__ == "__main__":

    res = CherryPickup().doit( [[0, 1, -1],
                               [1, 0, -1],
                               [1, 1,  1]])
    

    pass