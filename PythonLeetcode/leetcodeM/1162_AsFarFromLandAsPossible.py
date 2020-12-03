"""
1162. As Far from Land as Possible

Given an n x n grid containing only values 0 and 1, where 0 represents water and 1 represents land, find a water cell
such that its distance to the nearest land cell is maximized, and return the distance. If no land or water exists in the grid, return -1.

The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.


Example 1:


Input: grid = [[1,0,1],[0,0,0],[1,0,1]]
Output: 2
Explanation: The cell (1, 1) is as far as possible from all the land with distance 2.
Example 2:


Input: grid = [[1,0,0],[0,0,0],[0,0,0]]
Output: 4
Explanation: The cell (2, 2) is as far as possible from all the land with distance 4.


Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 100
grid[i][j] is 0 or 1



"""


class MaxDistance:

    def doit_bfs(self, grid: list) -> int:
        from collections import deque
        q = deque([])
        m, n = len(grid), len(grid[0])

        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    q.append((i, j))

        if len(q) == 0 or len(q) == m * n:
            return 0

        d = -1
        while q:
            size = len(q)
            for c in range(size):
                i, j = q.popleft()
                for x, y in ((i-1, j), (i, j+1), (i + 1, j), (i. i-1)):
                    if 0 <= x < n and 0 <= y <= n and grid[x][y] == 0:
                        grid[x][y] = 1
                        q.append((x, y))
            d += 1

        return d

    def doit_bfs_1(self, grid: list) -> int:
        q, vis = [], set()
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 1:
                    q.append((i, j, 0))
                    vis.add((i, j))

        if len(q) == 0 or len(q) == len(grid) * len(grid[0]): return -1
        ans = 0
        while q:
            i, j, d = q.pop(0)
            for x, y in [(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)]:
                if 0 <= x < len(grid) and 0 <= y < len(grid[0]):
                    if (x, y) not in vis:
                        vis.add((x, y))
                        ans = max(ans, d + 1)
                        q.append((x, y, d + 1))

        return ans