"""
1254. Number of Closed Islands

Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of
0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.



Example 1:



Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
Output: 2
Explanation:
Islands in gray are closed because they are completely surrounded by water (group of 1s).
Example 2:



Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
Output: 1
Example 3:

Input: grid = [[1,1,1,1,1,1,1],
               [1,0,0,0,0,0,1],
               [1,0,1,1,1,0,1],
               [1,0,1,0,1,0,1],
               [1,0,1,1,1,0,1],
               [1,0,0,0,0,0,1],
               [1,1,1,1,1,1,1]]
Output: 2


Constraints:

1 <= grid.length, grid[0].length <= 100
0 <= grid[i][j] <=1
"""


class ClosedIsland:

    def doit_dfs(self, grid: list) -> int:

        m, n = len(grid), len(grid[0])
        visited = [[False for _ in range(n)] for _ in range(m)]
        res, notclosed = 0, False

        def dfs(i, j):
            nonlocal notclosed
            if i < 0 or i >= m or j < 0 or j >= n or visited[i][j] or grid[i][j] == 1:
                return

            if i == 0 or i == m - 1 or j == 0 or j == n - 1:
                notclosed = True

            visited[i][j] = True
            dfs(i - 1, j)
            dfs(i, j - 1)
            dfs(i + 1, j)
            dfs(i, j + 1)

        for i in range(m):
            for j in range(n):

                if grid[i][j] == 0 and not visited[i][j]:
                    dfs(i, j)
                    if not notclosed:
                        res += 1
                notclosed = False
        return res


if __name__ == '__main__':

    ClosedIsland().doit_dfs(grid = [[1,1,1,1,1,1,1,0],
                                    [1,0,0,0,0,1,1,0],
                                    [1,0,1,0,1,1,1,0],
                                    [1,0,0,0,0,1,0,1],
                                    [1,1,1,1,1,1,1,0]])

    ClosedIsland().doit_dfs(grid = [[0,0,1,0,0],
                                    [0,1,0,1,0],
                                    [0,1,1,1,0]])








