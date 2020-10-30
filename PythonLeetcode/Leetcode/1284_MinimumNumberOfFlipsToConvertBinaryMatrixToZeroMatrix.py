"""
 1284. Minimum Number of Flips to Convert Binary Matrix to Zero Matrix

 Given a m x n binary matrix mat. In one step, you can choose one cell and flip it and all the four neighbours of it
 if they exist (Flip is changing 1 to 0 and 0 to 1). A pair of cells are called neighboors if they share one edge.

 Return the minimum number of steps required to convert mat to a zero matrix or -1 if you cannot.

 Binary matrix is a matrix with all cells equal to 0 or 1 only.

 Zero matrix is a matrix with all cells equal to 0.



 Example 1:

 0 0      1 0       0 1     0 0
 0 1  ->  1 0  ->   1 1 ->  0 0


 Input: mat = [[0,0],[0,1]]
 Output: 3
 Explanation: One possible solution is to flip (1, 0) then (0, 1) and finally (1, 1) as shown.
 Example 2:

 Input: mat = [[0]]
 Output: 0
 Explanation: Given matrix is a zero matrix. We don't need to change it.
 Example 3:

 Input: mat = [[1,1,1],[1,0,1],[0,0,0]]
 Output: 6
 Example 4:

 Input: mat = [[1,0,0],[1,0,0]]
 Output: -1
 Explanation: Given matrix can't be a zero matrix

 Constraints:

 m == mat.length
 n == mat[0].length
 1 <= m <= 3
 1 <= n <= 3
 mat[i][j] is 0 or 1.

"""
from collections import deque


class MinFlips:

    def doit_bfs(self, mat: list) -> int:

        m, n = len(mat), len(mat[0])
        neighbors = [0, 1, 0, -1, 0, 0]

        def flip(status, i, j):
            for s in range(5):
                tx, ty = i + neighbors[s], j + neighbors[s+1]
                if 0 <= tx < m and 0 <= ty < n:
                    status ^= 1 << (tx * n + ty)
            return status

        start = 0
        for i in range(m):
            for j in range(n):
                if mat[i][j] == 1:
                    start ^= 1 << (i * n + j)

        visited = set()
        que = deque([start])
        visited.add(start)
        steps = 0

        while que:

            for _ in range(len(que)):

                c = que.popleft()
                if c == 0:
                    return steps

                for i in range(m):
                    for j in range(n):
                        nt = flip(c, i, j)
                        if nt not in visited:
                            visited.add(nt)
                            que.append(nt)
            steps += 1

        return -1