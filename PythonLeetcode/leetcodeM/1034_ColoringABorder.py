# 1034. Coloring A Border

# Given a 2-dimensional grid of integers, each value in the grid represents the color of the grid square at that location.

# Two squares belong to the same connected component if and only if they have the same color and are next to each other in any of the 4 directions.

# The border of a connected component is all the squares in the connected component that are either 4-directionally adjacent to a square not in the component, or on the boundary of the grid (the first or last row or column).

# Given a square at location (r0, c0) in the grid and a color, color the border of the connected component of that square with the given color, and return the final grid.


# Example 1:

# Input: grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
# Output: [[3, 3], [3, 2]]

# Example 2:

# Input: grid = [[1,2,2],[2,3,2]], r0 = 0, c0 = 1, color = 3
# Output: [[1, 3, 3], [2, 3, 3]]

# Example 3:

# Input: grid = [[1,1,1],[1,1,1],[1,1,1]], r0 = 1, c0 = 1, color = 2
# Output: [[2, 2, 2], [2, 1, 2], [2, 2, 2]]


# Note:

# 1 <= grid.length <= 50
# 1 <= grid[0].length <= 50
# 1 <= grid[i][j] <= 1000
# 0 <= r0 < grid.length
# 0 <= c0 < grid[0].length
# 1 <= color <= 1000


class ColorBorder:

    def doit(self, grid, r0, c0, color):

        t = grid[r0][c0]
        if t == color:
            return grid

        def dfs(i, j, val):

            if 0 <= i <= len(grid)-1 and 0 <= j <= len(grid[0])-1 and grid[i][j] == t:

                s.append((i, j))
                grid[i][j] = val

                dfs(i+1, j, color)
                dfs(i-1, j, color)
                dfs(i, j+1, color)
                dfs(i, j-1, color)

        s = []
        dfs(r0, c0, color)
        for item in s:
            i, j = item[0], item[1]
            if (i+1, j) in s and (i-1, j) in s and (i, j+1) in s and (i, j-1) in s:
                grid[i][j] = t
        return grid

    """
    BFS
    Let m = grid.length, n = grid[0].length, use the number
    from 0 to m * n - 1 to identify the cells to avoid duplicates;
    e.g., grid[x][y]'s cell number is x * n + y;
    put the initial cell [r0, c0] into the Queue then poll it out,
    then check if it is on the grid bounday; If yes, color the cell;

    Traverse the cell's 4 neighbors:
    a) if its neighbor is of different color, the cell is on the
    component border;
    b) if same color, put the neighbor into Queue;
    repeat the above 2 and 3 till Queue is empty.
    """

    """
    DFS
    Use DFS to explore the cell (r0, c0)'s component, and negate the visited cell, traverse its 4 neighbors.
    After the traversal, change back from the negative if the component cell is at inner part.
    """

    # BFS
    def doit(self, grid, r0, c0, color):
        m, n = len(grid), len(grid[0])
        bfs, component, border = [[r0, c0]], set([(r0, c0)]), set()
        for r0, c0 in bfs:
            for i, j in [[0, 1], [1, 0], [-1, 0], [0, -1]]:
                r, c = r0 + i, c0 + j
                if 0 <= r < m and 0 <= c < n and grid[r][c] == grid[r0][c0]:
                    if (r, c) not in component:
                        bfs.append([r, c])
                        component.add((r, c))
                else:
                    border.add((r0, c0))
        for x, y in border:
            grid[x][y] = color
        return grid

    # DFS
    def doit(self, grid, r0, c0, color):
        seen, m, n = set(), len(grid), len(grid[0])

        def dfs(x, y):
            if (x, y) in seen:
                return True
            if not (0 <= x < m and 0 <= y < n and grid[x][y] == grid[r0][c0]):
                return False
            seen.add((x, y))
            if dfs(x + 1, y) + dfs(x - 1, y) + dfs(x, y + 1) + dfs(x, y - 1) < 4:
                grid[x][y] = color
            return True
        dfs(r0, c0)
        return grid


if __name__ == '__main__':

    res = ColorBorder().doit(grid=[[1, 1], [1, 2]], r0=0, c0=0, color=3)

    res = ColorBorder().doit(grid=[[1, 2, 2], [2, 3, 2]], r0=0, c0=1, color=3)

    res = ColorBorder().doit(
        grid=[[1, 1, 1], [1, 1, 1], [1, 1, 1]], r0=1, c0=1, color=2)

    res = ColorBorder().doit([[1, 1], [1, 2]], 0, 0, 3)

    pass
