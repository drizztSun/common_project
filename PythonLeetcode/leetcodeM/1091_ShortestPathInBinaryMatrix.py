"""
1091. Shortest Path in Binary Matrix


In an N by N square grid, each cell is either empty (0) or blocked (1).

A clear path from top-left to bottom-right has length k if and only if it is composed of cells C_1, C_2, ..., C_k such that:

Adjacent cells C_i and C_{i+1} are connected 8-directionally (ie., they are different and share an edge or corner)
C_1 is at location (0, 0) (ie. has value grid[0][0])
C_k is at location (N-1, N-1) (ie. has value grid[N-1][N-1])
If C_i is located at (r, c), then grid[r][c] is empty (ie. grid[r][c] == 0).
Return the length of the shortest such clear path from top-left to bottom-right.  If such a path does not exist, return -1.



Example 1:

Input: [[0,1],[1,0]]


Output: 2

Example 2:

Input: [[0,0,0],[1,1,0],[1,1,0]]


Output: 4



Note:

1 <= grid.length == grid[0].length <= 100
grid[r][c] is 0 or 1



"""


class ShortestPathBinaryMatrix:

    def doit_bfs(self, grid: list) -> int:

        from collections import deque
        m, n = len(grid), len(grid[0])
        qu = deque()
        if grid[0][0] == 0:
            qu.append((0, 0, 0))
        visited = set()

        while qu:

            path, r, c = qu.popleft()
            if (r, c) == (m - 1, n - 1):
                return path + 1

            for delta in ((-1, 0), (-1, -1), (0, -1), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1)):
                x, y = r + delta[0], c + delta[1]

                if 0 <= x < m and 0 <= y < n and grid[x][y] == 0 and (x, y) not in visited:
                    visited.add((x, y))
                    qu.append((path + 1, x, y))

        return -1

    def doit_bfs_1(self, grid):

        from heapq import heappush, heappop
        from itertools import product

        n = len(grid) - 1
        if grid[0][0] or grid[n][n]:
            return -1

        # use iterator to create 8 directions
        directions = [x for x in product((-1, 0, 1), repeat=2) if x != (0, 0)]

        q = [(n + 1, 1, n, n)]  # put (evaluation, step, i, j) into q
        grid[n][n] = -1  # the step of the start is 1

        while q:
            _, step, i, j = heappop(q)
            # arrive the end, return minimal step
            if (i, j) == (0, 0):
                return step

            for di, dj in directions:
                newI, newJ = i + di, j + dj
                # Except grid[i][j] = 1, we need to search and update
                if 0 <= newI <= n and 0 <= newJ <= n and grid[newI][newJ] < 1:
                    newStep = step + 1
                    # if we have new visit or can have fewer steps, update
                    if grid[newI][newJ] == 0 or grid[newI][newJ] < -newStep:
                        grid[newI][newJ] = -newStep  # store new minimal step
                        evaluation = max(newI, newJ) + newStep
                        heappush(q, (evaluation, newStep, newI, newJ))
        return -1