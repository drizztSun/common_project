"""
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
"""


class CherryPickup:

    """
    Approach #3: Dynamic Programming (Bottom Up) [Accepted]
    Intuition

    Like in Approach #2, we have the idea of dynamic programming.

    Say r1 + c1 = t is the t-th layer. Since our recursion only references the next layer, we only need to keep two layers in memory at a time.

    Algorithm
    At time t, let dp[c1][c2] be the most cherries that we can pick up for two people going from (0, 0) to (r1, c1) and (0, 0) to (r2, c2),
    where r1 = t-c1, r2 = t-c2. Our dynamic program proceeds similarly to Approach #2.

    Complexity Analysis

    Time Complexity: O(N^3), where NN is the length of grid. We have three for-loops of size O(N)O(N).

    Space Complexity: O(N^2) the sizes of dp and dp2.
    """
    def doit_dp(self, grid):
        N = len(grid)
        dp = [[float('-inf')] * N for _ in range(N)]
        dp[0][0] = grid[0][0]
        for t in range(1, 2*N - 1):
            dp2 = [[float('-inf')] * N for _ in range(N)]
            for i in range(max(0, t-(N-1)), min(N-1, t) + 1):
                for j in range(max(0, t-(N-1)), min(N-1, t) + 1):
                    if grid[i][t-i] == -1 or grid[j][t-j] == -1:
                        continue
                    val = grid[i][t-i]
                    if i != j: val += grid[j][t-j]
                    dp2[i][j] = max(dp[pi][pj] + val
                                    for pi in (i-1, i) for pj in (j-1, j)
                                    if pi >= 0 and pj >= 0)
            dp = dp2
        return max(0, dp[N-1][N-1])

    """
    Approach #2: Dynamic Programming (Top Down) [Accepted]
    Intuition

    Instead of walking from end to beginning, let's reverse the second leg of the path, so we are only considering two paths from the beginning to the end.

    Notice after t steps, each position (r, c) we could be, is on the line r + c = t. So if we have two people at positions (r1, c1) and (r2, c2), then r2 = r1 + c1 - c2. That means the variables r1, c1, c2 uniquely determine 2 people who have walked the same r1 + c1 number of steps. This sets us up for dynamic programming quite nicely.

    Algorithm

    Let dp[r1][c1][c2] be the most number of cherries obtained by two people starting at (r1, c1) and (r2, c2) and walking towards (N-1, N-1) picking up cherries, where r2 = r1+c1-c2.

    If grid[r1][c1] and grid[r2][c2] are not thorns, then the value of dp[r1][c1][c2] is (grid[r1][c1] + grid[r2][c2]), plus the maximum of dp[r1+1][c1][c2], dp[r1][c1+1][c2], dp[r1+1][c1][c2+1], dp[r1][c1+1][c2+1] as appropriate. We should also be careful to not double count in case (r1, c1) == (r2, c2).

    Why did we say it was the maximum of dp[r+1][c1][c2] etc.? It corresponds to the 4 possibilities for person 1 and 2 moving down and right:

    Person 1 down and person 2 down: dp[r1+1][c1][c2];
    Person 1 right and person 2 down: dp[r1][c1+1][c2];
    Person 1 down and person 2 right: dp[r1+1][c1][c2+1];
    Person 1 right and person 2 right: dp[r1][c1+1][c2+1];
    Complexity Analysis

    Time Complexity: O(N^3), where NN is the length of grid. Our dynamic programming has O(N^3) states.
    Space Complexity: O(N^3), the size of memo.
    """
    def doit_dp(self, grid):
        N = len(grid)
        memo = [[[None] * N for _1 in range(N)] for _2 in range(N)]
        def dp(r1, c1, c2):
            r2 = r1 + c1 - c2
            if (N == r1 or N == r2 or N == c1 or N == c2 or
                    grid[r1][c1] == -1 or grid[r2][c2] == -1):
                return float('-inf')
            elif r1 == c1 == N-1:
                return grid[r1][c1]
            elif memo[r1][c1][c2] is not None:
                return memo[r1][c1][c2]
            else:
                ans = grid[r1][c1] + (c1 != c2) * grid[r2][c2]
                ans += max(dp(r1, c1+1, c2+1), dp(r1+1, c1, c2+1),
                           dp(r1, c1+1, c2), dp(r1+1, c1, c2))

            memo[r1][c1][c2] = ans
            return ans

        return max(0, dp(0, 0, 0))

    """
    # The idea is to use self.memo[(i1, j1, i2, j2)] to store the maximum number of cherries that can be collected starting from (i1, j1) to (N-1, N-1) then to(i2, j2).
    # Note that since I am taking a step at each end at the same time, i1+j1 is always equal to i2+j2, therefore there are only O(N^3) states
    # (and I am using the full quadruple to store the state for the sake of clearness).
    """
    # <DP> <O(N^3)>
    def doit_dp(self, grid):
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