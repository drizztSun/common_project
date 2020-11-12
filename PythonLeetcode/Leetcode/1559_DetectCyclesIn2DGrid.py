"""
1559. Detect Cycles in 2D Grid

Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.

A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell,
you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.

Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1)
is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.

Return true if any cycle of the same value exists in grid, otherwise, return false.



Example 1:



Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
Output: true
Explanation: There are two valid cycles shown in different colors in the image below:

Example 2:



Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
Output: true
Explanation: There is only one valid cycle highlighted in the image below:

Example 3:



Input: grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
Output: false


Constraints:

m == grid.length
n == grid[i].length
1 <= m <= 500
1 <= n <= 500
grid consists only of lowercase English letters.

"""


class ContainsCycle:

    def doit_dfs(self, grid: list) -> bool:

        seen = set()

        def search(i, j, lasti, lastj):

            seen.add((i, j))

            for delta in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                x, y = i + delta[0], j + delta[1]
                if 0 <= x < len(grid) and 0 <= y < len(grid[0]) and grid[x][y] == grid[i][j] and (x, y) != (
                lasti, lastj):
                    if (x, y) in seen:
                        return True

                    if search(x, y, i, j):
                        return True

            return False

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if (i, j) not in seen and search(i, j, -1, -1):
                    return True

        return False

    def doit_disjoint(self, grid: list) -> bool:

        m, n = len(grid), len(grid[0])
        parent = [i for i in range(n*m+1)]

        def find(i):
            while parent[i] != i:
                parent[i] = parent[parent[i]]
                i = parent[i]
            return i

        def union(i, j):
            pa, pb = find(i), find(j)
            parent[pa] = pb
            return pa == pb

        for i in range(m):
            for j in range(n):
                base = i * n + j
                if i < m-1 and grid[i+1][j] == grid[i][j] and union(base, base+n):
                    return True

                if j < n-1 and grid[i][j+1] == grid[i][j] and union(base, base+1):
                    return True

        return False


if __name__ == '__main__':

    ContainsCycle().doit_dfs([["a","b","b"],["b","z","b"],["b","b","a"]])