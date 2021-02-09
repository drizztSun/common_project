"""
1730. Shortest Path to Get Food


You are starving and you want to eat food as quickly as possible. You want to find the shortest path to arrive at any food cell.

You are given an m x n character matrix, grid, of these different types of cells:

'*' is your location. There is exactly one '*' cell.
'#' is a food cell. There may be multiple food cells.
'O' is free space, and you can travel through these cells.
'X' is an obstacle, and you cannot travel through these cells.
You can travel to any adjacent cell north, east, south, or west of your current location if there is not an obstacle.

Return the length of the shortest path for you to reach any food cell. If there is no path for you to reach food, return -1.



Example 1:


Input: grid = [["X","X","X","X","X","X"],["X","*","O","O","O","X"],["X","O","O","#","O","X"],["X","X","X","X","X","X"]]
Output: 3
Explanation: It takes 3 steps to reach the food.
Example 2:


Input: grid = [["X","X","X","X","X"],["X","*","X","O","X"],["X","O","X","#","X"],["X","X","X","X","X"]]
Output: -1
Explanation: It is not possible to reach the food.
Example 3:


Input: grid = [["X","X","X","X","X","X","X","X"],["X","*","O","X","O","#","O","X"],["X","O","O","X","O","O","X","X"],["X","O","O","O","O","#","O","X"],["X","X","X","X","X","X","X","X"]]
Output: 6
Explanation: There can be multiple food cells. It only takes 6 steps to reach the bottom food.
Example 4:

Input: grid = [["O","*"],["#","O"]]
Output: 2
Example 5:

Input: grid = [["X","*"],["#","X"]]
Output: -1


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 200
grid[row][col] is '*', 'X', 'O', or '#'.
The grid contains exactly one '*'.


"""


class ShortestPathToGetFood:

    """



    """

    def doit_dfs(self, grid: list) -> int:
        from collections import deque

        foods, start = set(), None

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == '*':
                    start = (i, j)
                elif grid[i][j] == '#':
                    foods.add((i, j))

        queue = deque([start])
        step, direct = 0, (-1, 0, 1, 0, -1)
        m, n = len(grid), len(grid[0])
        grid[start[0]][start[1]] = 'X'

        while queue:

            size = len(queue)

            for _ in range(size):

                p = queue.popleft()

                if p in foods:
                    return step

                for i in range(4):
                    x, y = p[0] + direct[i], p[1] + direct[i + 1]

                    if 0 <= x < m and 0 <= y < n and grid[x][y] != 'X':
                        grid[x][y] = 'X'
                        queue.append((x, y))

            step += 1

        return -1

    def doit_dfs_1(self, grid: list) -> int:

        from collections import deque

        start = None

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == '*':
                    start = (i, j)

        queue = deque()
        step, direct = 0, (-1, 0, 1, 0, -1)
        m, n = len(grid), len(grid[0])
        grid[start[0]][start[1]] = 'X'
        queue.append((start[0], start[1], 0))

        while queue:

            x1, y1, d = queue.popleft()

            for i in range(4):
                x, y = x1 + direct[i], y1 + direct[i + 1]

                if 0 <= x < m and 0 <= y < n and grid[x][y] != 'X':
                    if grid[x][y] == '#':
                        return d + 1

                    grid[x][y] = 'X'
                    queue.append((x, y, d + 1))

        return -1