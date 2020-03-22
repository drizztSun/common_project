# 980. Unique Paths III

# On a 2-dimensional grid, there are 4 types of squares:

# 1 represents the starting square.  There is exactly one starting square.
# 2 represents the ending square.  There is exactly one ending square.
# 0 represents empty squares we can walk over.
# -1 represents obstacles that we cannot walk over.
# Return the number of 4-directional walks from the starting square to the ending square,
# that walk over every non-obstacle square exactly once.


# Example 1:

# Input: [[1,0,0,0],
#         [0,0,0,0],
#         [0,0,2,-1]]
# Output: 2
# Explanation: We have the following two paths:
# 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
# 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

# Example 2:

# Input: [[1,0,0,0],
#         [0,0,0,0],
#         [0,0,0,2]]
# Output: 4
# Explanation: We have the following four paths:
# 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
# 2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
# 3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
# 4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

# Example 3:

# Input: [[0,1],[2,0]]
# Output: 0
# Explanation:
# There is no path that walks over every empty square exactly once.
# Note that the starting and ending square can be anywhere in the grid.


class UniquePathsIII:
    def doit(self, grid):

        start = (0, 0)
        zeros = 0
        end = (0, 0)
        self.ans = 0

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 0:
                    zeros += 1
                elif grid[i][j] == 1:
                    start = (i, j)
                elif grid[i][j] == 2:
                    end = (i, j)

        self.seen = [[0 for _ in range(len(grid[0]))] for _ in range(len(grid))]


        def search(i, j, num):

            if (i, j) == end:
                self.ans += 1 if num == 0 else 0
                return

            for c in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                x, y = i + c[0], j + c[1]
                base = x * len(grid[0]) + y
                if (0 <= x < len(grid) and 0 <= y < len(grid[0]) and grid[x][y] != -1 and self.seen[x][y] == 0):
                    self.seen[x][y] = 1
                    search(x, y, num - 1)
                    self.seen[x][y] = 0

        self.seen[start[0]][start[1]] = 1
        search(start[0], start[1], zeros + 1)
        return self.ans


if __name__ == "__main__":

    res = UniquePathsIII().doit([[1, 0, 0, 0], [0, 0, 0, 0], [0, 0, 2, -1]])

    res = UniquePathsIII().doit([[1, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 2]])

    res = UniquePathsIII().doit([[0,1],[2,0]])

    pass
