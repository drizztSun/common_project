"""
1568. Minimum Number of Days to Disconnect Island

Given a 2D grid consisting of 1s (land) and 0s (water).  An island is a maximal 4-directionally (horizontal or vertical) connected group of 1s.

The grid is said to be connected if we have exactly one island, otherwise is said disconnected.

In one day, we are allowed to change any single land cell (1) into a water cell (0).

Return the minimum number of days to disconnect the grid.



Example 1:



Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
Output: 2
Explanation: We need at least 2 days to get a disconnected grid.
Change land grid[1][1] and grid[0][2] to water and get 2 disconnected island.
Example 2:

Input: grid = [[1,1]]
Output: 2
Explanation: Grid of full water is also disconnected ([[1,1]] -> [[0,0]]), 0 islands.
Example 3:

Input: grid = [[1,0,1,0]]
Output: 0
Example 4:

Input: grid = [[1,1,0,1,1],
               [1,1,1,1,1],
               [1,1,0,1,1],
               [1,1,0,1,1]]
Output: 1
Example 5:

Input: grid = [[1,1,0,1,1],
               [1,1,1,1,1],
               [1,1,0,1,1],
               [1,1,1,1,1]]
Output: 2


Constraints:

1 <= grid.length, grid[i].length <= 30
grid[i][j] is 0 or 1.

"""


class MinimumNumerOfDaysToDisconnectIsland:

    def doit_bfs(self, grid: list) -> int:

        cnt = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j]:
                    cnt += 1  # count the number of elements
                    root = (i, j)  # assign the root node for the graph

        if cnt <= 1:
            return cnt  # no elements in the map

        vis, low, res = {root}, {}, []

        # find whether articulation points are present in the matrix
        def articulation_points(curr, parent):
            low[curr] = base = len(vis)
            children = 0
            i, j = curr

            for x, y in [(i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)]:
                if (x, y) == parent:
                    continue

                if 0 <= x < len(grid) and 0 <= y < len(grid[0]) and grid[x][y]:
                    if (x, y) not in vis:
                        vis.add((x, y))
                        articulation_points((x, y), curr)
                        low[curr] = min(low[curr], low[(x, y)])
                        children += 1
                        if low[(x, y)] >= base and parent != (-1, -1):
                            res.append([i, j])
                    else:
                        low[curr] = min(low[curr], low[x, y])

                if parent == (-1, -1) and children > 1:
                    res.append([x, y])

        articulation_points(root, (-1, -1))

        if len(vis) != cnt:  # if the matrix is disconnected beforehand
            return 0
        elif res:  # if there are any articulation points
            return 1
        else:  # worst case, no articulation points
            return 2

    def doit_bfs_1(self, grid: list) -> int:
        import collections

        def islands_number():
            visited = set()
            m, n = len(grid), len(grid[0])
            ans = 0

            for i in range(m):
                for j in range(n):

                    if grid[i][j] == 1 and (i, j) not in visited:
                        ans += 1
                        queue = collections.deque([(i, j)])
                        visited.add((i, j))

                        while queue:

                            x, y = queue.popleft()
                            for x1, y1 in ((x + 1, y), (x, y + 1), (x - 1, y), (x, y - 1)):

                                if 0 <= x1 < m and 0 <= y1 < n and (x1, y1) not in visited and grid[x1][y1] == 1:
                                    queue.append((x1, y1))
                                    visited.add((x1, y1))

            return ans

        m, n = len(grid), len(grid[0])

        if islands_number() > 1:
            return 0

        for i in range(m):
            for j in range(n):

                if grid[i][j] == 1:
                    grid[i][j] = 0
                    cnt = islands_number()
                    if cnt > 1 or cnt == 0:
                        return 1
                    grid[i][j] = 1

        return 2