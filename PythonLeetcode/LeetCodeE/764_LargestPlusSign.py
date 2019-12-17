# 764. Largest Plus Sign

# In a 2D grid from (0, 0) to (N-1, N-1), every cell contains a 1, except those cells in the given list mines which are 0.
# What is the largest axis-aligned plus sign of 1s contained in the grid? Return the order of the plus sign. If there is none, return 0.

# An "axis-aligned plus sign of 1s of order k" has some center grid[x][y] = 1 along with 4 arms of length k-1 going up, down, left, and right, and made of 1s.
# This is demonstrated in the diagrams below. Note that there could be 0s or 1s beyond the arms of the plus sign, only the relevant area of the plus sign is checked for 1s.

# Examples of Axis-Aligned Plus Signs of Order k:

# Order 1:
# 000
# 010
# 000

# Order 2:
# 00000
# 00100
# 01110
# 00100
# 00000

# Order 3:
# 0000000
# 0001000
# 0001000
# 0111110
# 0001000
# 0001000
# 0000000
#
# Example 1:

# Input: N = 5, mines = [[4, 2]]
# Output: 2

# Explanation:
# 11111
# 11111
# 11111
# 11111
# 11011
# In the above grid, the largest plus sign can only be order 2.  One of them is marked in bold.

# Example 2:

# Input: N = 2, mines = []
# Output: 1

# Explanation:
# There is no plus sign of order 2, but there is of order 1.

# Example 3:

# Input: N = 1, mines = [[0, 0]]
# Output: 0
# Explanation:
# There is no plus sign, so return 0.
# Note:

# N will be an integer in the range [1, 500].
# mines will have length at most 5000.
# mines[i] will be length 2 and consist of integers in the range [0, N-1].

from collections import defaultdict
import bisect


class OrderOfLargestPlusSign:

    # O(n*n*logn)
    def doit(self, N, mines):

        row, line = defaultdict(list), defaultdict(list)

        for c in mines:
            bisect.insort(row[c[0]], c[1])
            bisect.insort(line[c[1]], c[0])

        maxi = -1
        for x in range(N):
            for y in range(N):

                y_direct = [-1] + list(row[x]) + [N]
                i = bisect.bisect_left(y_direct, y)
                y_length = 0 if i == 0 or i == len(y_direct) - \
                    1 else min(y_direct[i] - y_direct[i-1], y_direct[i+1] - y_direct[i]) + 1

                x_direct = [-1] + list(line[y]) + [N]
                j = bisect.bisect_left(x_direct, x)
                x_length = 0 if j == 0 or j == len(x_direct) - \
                    1 else min(x_direct[i] - x_direct[i-1], x_direct[i+1] - x_direct[i]) + 1

                if maxi < min(x_length, y_length):
                    maxi = min(x_length, y_length)

        return maxi

    # O(n*n)
    # Algorithms:
    # For each position (i, j) of the grid matrix, we try to extend in each of the four directions (left, right, up, down) as long as possible,
    # then take the minimum length of 1's out of the four directions as the order of the largest axis-aligned plus sign centered at position (i, j).

    # Optimizations:
    # Normally we would need a total of five matrices to make the above idea work -- one matrix for the grid itself and four more matrices for each of the four directions.
    # However, these five matrices can be combined into one using two simple tricks:

    # For each position (i, j), we are only concerned with the minimum length of 1's out of the four directions.
    # This implies we may combine the four matrices into one by only keeping track of the minimum length.

    # For each position (i, j), the order of the largest axis-aligned plus sign centered at it will be 0 if and only if grid[i][j] == 0.
    # This implies we may further combine the grid matrix with the one obtained above.

    # Implementations:

    # Create an N-by-N matrix grid, with all elements initialized with value N.
    # Reset those elements to 0 whose positions are in the mines list.
    # For each position (i, j), find the maximum length of 1's in each of the four directions and set grid[i][j] to the minimum of these four lengths.
    # Note that there is a simple recurrence relation relating the maximum length of 1's at current position with previous position for each of the four directions (labeled as l, r, u, d).
    # Loop through the grid matrix and choose the maximum element which will be the largest axis-aligned plus sign of 1's contained in the grid.
    # Solutions: Here is a list of solutions for Java/C++/Python based on the above ideas. All solutions run at O(N^2) time with O(N^2) extra space.
    # Further optimizations are possible such as keeping track of the maximum plus sign currently available and terminating as early as possible if no larger plus sign can be found for current row/column.

    # Note: For those of you who got confused by the logic within the first nested for-loop, refer to andier's comment and my comment below for a more clear explanation.
    def doit(self, N, mines):
        """
        :type N: int
        :type mines: List[List[int]]
        :rtype: int
        """
        grid = [[N] * N for i in range(N)]

        for m in mines:
            grid[m[0]][m[1]] = 0

        for i in range(N):
            l, r, u, d = 0, 0, 0, 0

            for j, k in zip(range(N), reversed(range(N))):
                l = l + 1 if grid[i][j] != 0 else 0
                if l < grid[i][j]:
                    grid[i][j] = l

                r = r + 1 if grid[i][k] != 0 else 0
                if r < grid[i][k]:
                    grid[i][k] = r

                u = u + 1 if grid[j][i] != 0 else 0
                if u < grid[j][i]:
                    grid[j][i] = u

                d = d + 1 if grid[k][i] != 0 else 0
                if d < grid[k][i]:
                    grid[k][i] = d

        res = 0

        for i in range(N):
            for j in range(N):
                if res < grid[i][j]:
                    res = grid[i][j]

        return res

    def doit(self, N, mines):
        """
        :type N: int
        :type mines: List[List[int]]
        :rtype: int
        """
        if not mines:
            return (N+1) // 2

        maximum = -float('inf')
        mines = set([tuple(x) for x in mines])
        dp = [[(0, 0)]*N for _ in range(N)]

        for i in range(N):
            for j in range(N):
                if (i, j) in mines:
                    dp[i][j] = (0, 0)
                else:
                    x1 = dp[i][j-1][0]+1 if j > 0 else 1
                    y1 = dp[i-1][j][1]+1 if i > 0 else 1
                    dp[i][j] = (x1, y1)

        for i in range(N-1, -1, -1):
            for j in range(N-1, -1, -1):
                if (i, j) in mines:
                    dp[i][j] = (0, 0)
                else:
                    tmp1, tmp2 = dp[i][j][0], dp[i][j][1]
                    x2 = dp[i][j+1][0]+1 if j < N-1 else 1
                    y2 = dp[i+1][j][1]+1 if i < N-1 else 1
                    maximum = max(maximum, min(tmp1, tmp2, x2, y2))
                    dp[i][j] = (x2, y2)

        return maximum if maximum != -float('inf') else 0


if __name__ == "__main__":

    res = OrderOfLargestPlusSign().doit(5, [[4, 2]])

    res = OrderOfLargestPlusSign().doit(2, [])

    res = OrderOfLargestPlusSign().doit(1, [[0, 0]])

    pass
