"""
542. 01 Matrix

Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.

 

Example 1:

Input:
[[0,0,0],
 [0,1,0],
 [0,0,0]]

Output:
[[0,0,0],
 [0,1,0],
 [0,0,0]]
Example 2:

Input:
[[0,0,0],
 [0,1,0],
 [1,1,1]]

Output:
[[0,0,0],
 [0,1,0],
 [1,2,1]]
 

Note:

The number of elements of the given matrix will not exceed 10,000.
There are at least one 0 in the given matrix.
The cells are adjacent in only four directions: up, down, left and right.


"""


class Matrix01:

    def doit_bfs(self, matrix: list) -> list:
        from collections import deque
        m, n = len(matrix), len(matrix[0])

        ans = [[float('inf') for _ in range(n)] for _ in range(m)]
        queue = deque()

        for i in range(m):
            for j in range(n):
                if matrix[i][j] == 0:
                    ans[i][j] = 0
                    queue.append((i, j))

        direct = (-1, 0, 1, 0, -1)
        while queue:
            
            x, y = queue.popleft()
            for i in range(4):
                x1, y1 = x + direct[i], y + direct[i+1]

                if 0 <= x1 < m and 0 <= y1 < n and matrix[x1][y1] == 1 and ans[x1][y1] == float('inf'):
                    ans[x1][y1] = min(ans[x1][y1], ans[x][y]+1)
                    queue.append((x1, y1))

        return ans

    
    def doit_dp(self, matrix: list) -> list:

        from collections import deque
        m, n = len(matrix), len(matrix[0])

        ans = [[float('inf') for _ in range(n)] for _ in range(m)]

        # top-left

        for i in range(m):
            for j in range(n):
                if matrix[i][j] == 0:
                    ans[i][j] = 0
                else:
                    if i > 0:
                        ans[i][j] = min(ans[i][j], ans[i-1][j] + 1)
                    if j > 0:
                        ans[i][j] = min(ans[i][j], ans[i][j-1] + 1)

        for i in reversed(range(m)):
            for j in reversed(range(n)):
                if matrix[i][j] == 0:
                    ans[i][j] = 0
                else:
                    if i < m-1:
                        ans[i][j] = min(ans[i][j], ans[i+1][j] + 1)
                    if j < n-1:
                        ans[i][j] = min(ans[i][j], ans[i][j+1] + 1)

        return ans


if __name__ == '__main__':

    # Matrix01().doit_dp([[0,0,0],[0,1,0],[0,0,0]])

    Matrix01().doit_dp([[0],[1]])




        