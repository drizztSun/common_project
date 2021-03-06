"""
# 778. Swim in Rising Water

# On an N x N grid, each square grid[i][j] represents the elevation at that point (i,j).

# Now rain starts to fall. At time t, the depth of the water everywhere is t.
# You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t.
# You can swim infinite distance in zero time. Of course, you must stay within the boundaries of the grid during your swim.

# You start at the top left square (0, 0). What is the least time until you can reach the bottom right square (N-1, N-1)?

# Example 1:

# Input: [[0,2],[1,3]]
# Output: 3
# Explanation:
# At time 0, you are in grid location (0, 0).
# You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.

# You cannot reach point (1, 1) until time 3.
# When the depth of water is 3, we can swim anywhere inside the grid.

# Example 2:

# Input: [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
# Output: 16
# Explanation:
#  0  1  2  3  4
#  24 23 22 21  5
#  12 13 14 15 16
#  11 17 18 19 20
#  10  9  8  7  6

# The final route is marked in bold.
# We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
# Note:

# 2 <= N <= 50.
# grid[i][j] is a permutation of [0, ..., N*N - 1].
"""
import heapq


class SwimInWater:

    # <heap>
    def doit_heap(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        st = [(grid[0][0], 0, 0)]
        highest = 0
        visited = set()
        visited.add((0, 0))

        while st:
            (v, x, y) = heapq.heappop(st)
            highest = max(highest, v)

            if x == m-1 and y == n-1:
                break

            for c in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                xx, yy = x + c[0], y + c[1]
                if 0 <= xx < m and 0 <= yy < n and (xx, yy) not in visited:
                    heapq.heappush(st, (grid[xx][yy], xx, yy))
                    visited.add((xx, yy))

        return highest

    # 
    def swimInWater(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        flag = []
        for i in range(n):
            flag.append([0] * n)

        flag[0][0] = 1
        pos = [0] * (n * n)
        for i in range(n):
            for j in range(n):
                pos[grid[i][j]] = (i, j)

                
        def search(x, y, n, grid, flag, k):
            if x < 0 or x >= n or y < 0 or y >= n or flag[x][y] == 2:
                return

            if grid[x][y] > k:
                flag[x][y] = 1
            else:
                flag[x][y] = 2
                search(x - 1, y, n, grid, flag, k)
                search(x + 1, y, n, grid, flag, k)
                search(x, y - 1, n, grid, flag, k)
                search(x, y + 1, n, grid, flag, k)

        for k in range(n * n):
            x, y = pos[k]

            if flag[x][y] == 1:
                search(x, y, n, grid, flag, k)

            if flag[n - 1][n - 1] == 2:
                return k


    # # <union-find>
    def doit_union_find(self, grid):

        def parent(x, y):
            if parent[x][y] == (x, y):
                return parent[x][y]
            parent[x][y] = parent(parent[x][y][0], parent[x][y][1])
            return parent[x][y]

        def union(a, b):
            a = parent(a[0], a[1])
            b = parent(b[0], b[1])
            if size[a[0]][a[1]] < size[b[0]][b[1]]:
                parent[a[0]][a[1]] = b
                size[b[0]][b[1]] += size[a[0]][a[1]]
            else:
                parent[b[0]][b[1]] = a
                size[a[0]][a[1]] += size[b[0]][b[1]]
            
        WAYS = [[-1, 0], [0, -1], [1, 0], [0, 1]]
        pos = {}
        m, n = len(grid), len(grid[0])

        for i in range(m):
            for j in range(n):
                pos[grid[i][j]] = (i, j)
                
        parent = []
        size = []
        for i in range(m):
            new_list = []
            for j in range(n):
                new_list.append((i, j))
            parent.append(new_list)
            size.append([1] * n)

        for i in range(m * n):
            x, y = pos[i]
            for w in WAYS:
                tx, ty = x + w[0], y + w[1]
                if tx >= 0 and tx < m and ty >= 0 and ty < n:
                    if grid[tx][ty] <= i:
                        union((x, y), (tx, ty))
                        if parent(0, 0) == parent(m - 1, n - 1):
                            return i


if __name__ == "__main__":

    res = SwimInWater().doit_heap([[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]])

    res = SwimInWater().doit_heap([[0, 2], [1, 3]])

    res = SwimInWater().doit_heap([[7,  34, 16, 12, 15, 0],
                                  [10, 26, 4,  30, 1,  20],
                                  [28, 27, 33, 35, 3,  8],
                                  [29, 9,  13, 14, 11, 32],
                                  [31, 21, 23, 24, 19, 18],
                                  [22, 6,  17, 5,  2,  25]])

