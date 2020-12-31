"""
200. Number of Islands

Given an m x n 2d grid map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.



Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.

"""


class NumIslands:

    """
    Approach #1 DFS [Accepted]
    Intuition

    Treat the 2d grid map as an undirected graph and there is an edge between two horizontally or vertically adjacent nodes of value '1'.

    Algorithm

    Linear scan the 2d grid map, if a node contains a '1', then it is a root node that triggers a Depth First Search. During DFS, every visited node should be set as '0' to mark as visited node.
    Count the number of root nodes that trigger DFS, this number would be the number of islands since each DFS starting at some root identifies an island.

    Complexity Analysis

    Time complexity : O(M×N) where MM is the number of rows and NN is the number of columns.

    Space complexity : worst case O(M×N) in case that the grid map is filled with lands where DFS goes by M \times NM×N deep.
    """
    def doit_dfs(self, grid):
        def search(x, y):
            if 0 <= x < len(grid) and 0 <= y < len(grid[0]) and grid[x][y] == '1':
                grid[x][y] = '2'
                for c in zip((x + 1, x - 1, x, x), (y, y, y + 1, y - 1)):
                    search(c[0], c[1])

        res = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == '1':
                    res += 1
                    search(i, j)
        return res

    def doit_dfs(self, grid):

        if not grid:
            return 0

        m = len(grid)
        n = len(grid[0])
        count = 0

        def helper(grid, i, j):
            if i > m - 1 or i < 0 or j > n - 1 or j < 0 or grid[i][j] != "1":
                return

            grid[i][j] = "0"
            helper(grid, i + 1, j)
            helper(grid, i, j + 1)
            helper(grid, i - 1, j)
            helper(grid, i, j - 1)

        for i in range(m):
            for j in range(n):
                if grid[i][j] == "1":
                    count += 1
                    helper(grid, i, j)
        return count

    """
    Approach #2: BFS [Accepted]
    Algorithm
    
    Linear scan the 2d grid map, if a node contains a '1', then it is a root node that triggers a Breadth First Search. 
    Put it into a queue and set its value as '0' to mark as visited node. Iteratively search the neighbors of enqueued nodes until the queue becomes empty.
    
    Complexity Analysis

    Time complexity : O(M×N) where MM is the number of rows and NN is the number of columns.
    
    Space complexity : O(min(M,N)) because in worst case where the grid is filled with lands, the size of queue can grow up to min(M,NM,N).
    """
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