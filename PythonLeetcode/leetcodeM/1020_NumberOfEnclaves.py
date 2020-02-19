# 1020. Number of Enclaves

# Given a 2D array A, each cell is 0 (representing sea) or 1 (representing land)

# A move consists of walking from one land square 4-directionally to another land square, or off the boundary of the grid.

# Return the number of land squares in the grid for which we cannot walk off the boundary of the grid in any number of moves.


# Example 1:

# Input: [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
# Output: 3
# Explanation:
# There are three 1s that are enclosed by 0s, and one 1 that isn't enclosed because its on the boundary.

# Example 2:

# Input: [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
# Output: 0
# Explanation:
# All 1s are either on the boundary or can reach the boundary.


# Note:

# 1 <= A.length <= 500
# 1 <= A[i].length <= 500
# 0 <= A[i][j] <= 1
# All rows have the same size.

class NumEnclaves:
    def doit(self, A):

        self.Count = 0

        def dfs(A, i, j):
            if i < 0 or j < 0 or i > len(A)-1 or j > len(A[0])-1:
                return True
            if A[i][j] == 0:
                return False
            self.Count += 1
            A[i][j] = 0
            U = dfs(A, i-1, j)
            D = dfs(A, i+1, j)
            L = dfs(A, i, j-1)
            R = dfs(A, i, j+1)
            return U or D or L or R

        count = 0
        for i in range(len(A)):
            for j in range(len(A[0])):
                if A[i][j] == 1 and not dfs(A, i, j):
                    count += self.Count
                else:
                    self.Count = 0
        return count

    def doit(self, grid):

        if not grid or not grid[0]:
            return 0

        from collections import deque
        m, n = len(grid), len(grid[0])

        queue = deque()
        for i in range(m):
            if grid[i][0] == 1:
                queue.append((i, 0))
                grid[i][0] = 0
            if grid[i][n-1] == 1:
                queue.append((i, n - 1))
                grid[i][n-1] = 0

        for j in range(n):
            if grid[0][j] == 1:
                queue.append((0, j))
                grid[0][j] = 0
            if grid[m-1][j] == 1:
                queue.append((m - 1, j))
                grid[m-1][j] = 0

        while queue:
            i, j = queue.popleft()
            for p, q in ((i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)):
                if 0 <= p < m and 0 <= q < n and grid[p][q] == 1:
                    queue.append((p, q))
                    grid[p][q] = 0

        return sum(map(sum, grid))


if __name__ == '__main__':

    res = NumEnclaves().doit(
        [[0, 0, 0, 0],
         [1, 0, 1, 0],
         [0, 1, 1, 0],
         [0, 0, 0, 0]])

    res = NumEnclaves().doit(
        [[0, 1, 1, 0],
         [0, 0, 1, 0],
         [0, 0, 1, 0],
         [0, 0, 0, 0]])

    pass
