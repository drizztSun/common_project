"""
1391. Check if There is a Valid Path in a Grid


Given a m x n grid. Each cell of the grid represents a street. The street of grid[i][j] can be:
1 which means a street connecting the left cell and the right cell.
2 which means a street connecting the upper cell and the lower cell.
3 which means a street connecting the left cell and the lower cell.
4 which means a street connecting the right cell and the lower cell.
5 which means a street connecting the left cell and the upper cell.
6 which means a street connecting the right cell and the upper cell.


You will initially start at the street of the upper-left cell (0,0). A valid path in the grid is a path which starts from the upper left cell (0,0) 
and ends at the bottom-right cell (m - 1, n - 1). The path should only follow the streets.

Notice that you are not allowed to change any street.

Return true if there is a valid path in the grid or false otherwise.

 

Example 1:


Input: grid = [[2,4,3],[6,5,2]]
Output: true
Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
Example 2:


Input: grid = [[1,2,1],[1,2,1]]
Output: false
Explanation: As shown you the street at cell (0, 0) is not connected with any street of any other cell and you will get stuck at cell (0, 0)
Example 3:

Input: grid = [[1,1,2]]
Output: false
Explanation: You will get stuck at cell (0, 1) and you cannot reach cell (0, 2).
Example 4:

Input: grid = [[1,1,1,1,1,1,3]]
Output: true
Example 5:

Input: grid = [[2],[2],[2],[2],[2],[2],[6]]
Output: true
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
1 <= grid[i][j] <= 6


"""


class HasValidPath:

    """
        Explanation
        Reform the matrix to be 
        Assume we have input A[2][2]. (Thanks @Gad2017 for this diagram)
        diagram

        The center of A[0][0] has coordinates [0, 0]
        The center of A[i][j] has coordinates [2i, 2j]
        The top edge of A[i][j] has coordinates [2i-1, 2j]
        The left edge of A[i][j] has coordinates [2i, 2j-1]
        The bottom edge of A[i][j] has coordinates [2i+1, 2j]
        The right edge of A[i][j] has coordinates [2i, 2j+1]

        Then we apply Union Find:
        if A[i][j] in [2, 5, 6]: connect center and top
        if A[i][j] in [1, 3, 5]: connect center and left
        if A[i][j] in [2, 3, 4]: connect center and bottom
        if A[i][j] in [1, 4, 6]: connect center and right


        Complexity
        Time O(MN) * O(UF)
        Space O(MN)
    """
    def doit_disjoint(self, grid: list) -> bool:
        m, n = len(grid), len(grid[0])
        uf = {(i, j): (i, j) for i in range(-1, 2 * m) for j in range(-1, 2 * n)}

        def find(x):
            while (x) != uf[x]:
                uf[x] = uf[uf[x]]
                x = uf[x]
            return x

        def merge(x, y, dx, dy):
            uf[find((x, y))] = uf[find((x + dx, y + dy))]

        for i in range(m):
            for j in range(n):
                if grid[i][j] in (2, 5, 6): merge(i*2, j*2, -1, 0)
                if grid[i][j] in (2, 3, 4): merge(i*2, j*2, 1, 0)
                if grid[i][j] in (1, 3, 5): merge(i*2, j*2, 0, -1)
                if grid[i][j] in (1, 4, 6): merge(i*2, j*2, 0, 1)

        return find((0, 0)) == find((2*m - 2, 2*n-2))
 

    def doit_bfs(self, grid: list) -> bool:
        from collections import deque
        m, n = len(grid), len(grid[0])
        direct = {'L': (0, -1), 'U': (-1, 0), 'D': (1, 0), 'R': (0, 1)}
        neighbours = {
            1 : {
                'L': (1, 4, 6),
                'R': (1, 3, 5)
            },
            2: {
                'U': (2, 3, 4),
                'D': (2, 5, 6)
            },
            3: {
                'L': (1, 4, 6),
                'D': (2, 5, 6)
            },
            4: {
                'R': (1, 3, 5),
                'D': (2, 5, 6)
            },
            5: {
                'U': (2, 3, 4),
                'L': (1, 4, 6)
            },
            6: {
                'U': (2, 3, 4),
                'R': (1, 3, 5)
            }
        }

        queue = deque([(0, 0)])
        visited = set()
        visited.add((0, 0))
        while queue:

            x, y = queue.popleft()

            if (x, y) == (m-1, n-1):
                return True

            for dir, nxt in neighbours[grid[x][y]].items():

                x1, y1 = x + direct[dir][0], y + direct[dir][1]

                if 0 <= x1 < m and 0 <= y1 < n and (x1, y1) not in visited and grid[x1][y1] in nxt:
                    visited.add((x1, y1))
                    queue.append((x1, y1))

        return False