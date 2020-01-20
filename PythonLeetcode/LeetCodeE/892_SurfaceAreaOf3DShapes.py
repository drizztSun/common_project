# 892. Surface Area of 3D Shapes

# On a N * N grid, we place some 1 * 1 * 1 cubes.

# Each value v = grid[i][j] represents a tower of v cubes placed on top of grid cell (i, j).

# Return the total surface area of the resulting shapes.


# Example 1:

# Input: [[2]]
# Output: 10

# Example 2:

# Input: [[1,2],[3,4]]
# Output: 34

# Example 3:

# Input: [[1,0],[0,2]]
# Output: 16

# Example 4:

# Input: [[1,1,1],[1,0,1],[1,1,1]]
# Output: 32

# Example 5:

# Input: [[2,2,2],[2,1,2],[2,2,2]]
# Output: 46


# Note:

# 1 <= N <= 50
# 0 <= grid[i][j] <= 50

class SurfaceArea:

    def doit(self, grid):
        grid_rot = list(zip(*grid))
        area = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if i == 0:
                    area = area + grid[i][j] + grid_rot[i][j]
                else:
                    area = area + abs(grid[i][j] - grid[i-1][j]) + \
                        abs(grid_rot[i][j] - grid_rot[i-1][j])
                if grid[i][j] > 0:
                    area += 2
        area = area + sum(grid[-1]) + sum(grid_rot[-1])
        return area

    def doit(self, grid):
        row = len(grid)
        col = len(grid[0])
        res = 0
        for i in range(row):
            for j in range(col):
                if grid[i][j] > 0:
                    res += 4 * grid[i][j] + 2
                if i > 0:
                    res -= 2 * min(grid[i - 1][j], grid[i][j])
                if j > 0:
                    res -= 2 * min(grid[i][j - 1], grid[i][j])
        return res

    def doit(self, grid):

        M, N = len(grid), len(grid[0])
        ans = 0
        for i in range(M):
            for j in range(N):

                if grid[i][j] == 0:
                    continue

                ans += grid[i][j] * 6 - (grid[i][j] - 1) * 2

                for x, y in ((i - 1, j), (i + 1, j), (i, j-1), (i, j+1)):
                    if -1 < x < M and -1 < y < N:
                        ans -= min(grid[x][y], grid[i][j])

        return ans


if __name__ == '__main__':

    res = SurfaceArea().doit([[2]])

    res = SurfaceArea().doit([[1, 2], [3, 4]])

    res = SurfaceArea().doit([[1, 0], [0, 2]])

    res = SurfaceArea().doit([[1, 1, 1], [1, 0, 1], [1, 1, 1]])

    res = SurfaceArea().doit([[2, 2, 2], [2, 1, 2], [2, 2, 2]])

    pass
