"""
# 200. Number of Islands

# Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
# An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
# You may assume all four edges of the grid are all surrounded by water.

# Example 1:

# 11110
# 11010
# 11000
# 00000
# Answer: 1

# Example 2:

# 11000
# 11000
# 00100
# 00011
# Answer: 3
"""


class NameOfIsland:

    """
    Approach #3: Union Find (aka Disjoint Set) [Accepted]
    Algorithm

    Traverse the 2d grid map and union adjacent lands horizontally or vertically, at the end, return the number of connected components maintained in the UnionFind data structure.

    For details regarding to Union Find, you can refer to this article.

    """
    def doit_disjoint(self, grid):

        m, n = len(grid), len(grid[0])
        parent = [i for i in range(n*m)]

        def find(x):
            if x == parent[x]:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            px = find(x)
            py = find(y)
            parent[px] = py

    # <bfs>
    def doit_bfs(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        from collections import deque
        res = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] != '1':
                    continue
                res += 1
                qu = deque([(i, j)])
                while qu:
                    x, y = qu.popleft()
                    if not (0 <= x < len(grid) and 0 <= y < len(grid[0]) and grid[x][y] == '1'):
                        continue
                    for c in zip((x + 1, x - 1, x, x), (y, y, y + 1, y - 1)):
                        qu.append((c[0], c[1]))
                    grid[x][y] = '2'
        return res

    # <dfs>
    def doit_dfs(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        def search(x, y):
            if 0 <= x < len(grid) and 0 <= y < len(grid[0]) and grid[x][y] == '1':
                grid[x][y] = '0'
                for c in zip((x+1, x-1, x, x), (y, y, y+1, y-1)):
                    search(c[0], c[1])

        res = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):

                if grid[i][j] == '1':
                    res += 1
                    search(i, j)
        return res

    def doit_dfs_1(self, grid):
        if not grid:
            return 0

        m = len(grid)
        n = len(grid[0])
        count = 0
        
        def helper(grid, i, j):
            if i > m-1 or i < 0 or j > n-1 or j < 0 or grid[i][j] != "1":
                return
        
            grid[i][j] = "0"
            helper(grid, i+1, j)
            helper(grid, i, j+1)
            helper(grid, i-1, j)
            helper(grid, i, j-1)
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] == "1":
                    count += 1
                    helper(grid,i,j)
        return count

    def doit_dfs_2(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        def island(x, y, grid, m, n):
            if x + 1 < m and grid[x + 1][y] == '1':
                grid[x + 1][y] = '2'
                island(x + 1, y, grid, m, n)
            if y + 1 < n and grid[x][y + 1] == '1':
                grid[x][y + 1] = '2'
                island(x, y + 1, grid, m, n)
            if x - 1 >= 0 and grid[x - 1][y] == '1':
                grid[x - 1][y] = '2'
                island(x - 1, y, grid, m, n)
            if y - 1 >= 0 and grid[x][y - 1] == '1':
                grid[x][y - 1] = '2'
                island(x, y - 1, grid, m, n)

        if len(grid) == 0:
            return 0

        m = len(grid)
        n = len(grid[0])
        res = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == '1':
                    res += 1
                    grid[i][j] = '2'
                    island(i, j, grid, m, n)
        return res
        

if __name__ == '__main__':

    NameOfIsland().doit_bfs([["1","1","1","1","0"],
                             ["1","1","0","1","0"],
                             ["1","1","0","0","0"],
                             ["0","0","0","0","0"]])

 