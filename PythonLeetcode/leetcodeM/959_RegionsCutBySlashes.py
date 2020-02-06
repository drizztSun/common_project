# 959. Regions Cut By Slashes

# In a N x N grid composed of 1 x 1 squares, each 1 x 1 square consists of a /, \, or blank space.
# These characters divide the square into contiguous regions.

# (Note that backslash characters are escaped, so a \ is represented as "\\".)

# Return the number of regions.

# Example 1:

# Input:
# [
#   " /",
#   "/ "
# ]
# Output: 2
# Explanation: The 2x2 grid is as follows:

# Example 2:

# Input:
# [
#   " /",
#   "  "
# ]
# Output: 1
# Explanation: The 2x2 grid is as follows:

# Example 3:

# Input:
# [
#   "\\/",
#   "/\\"
# ]

# Output: 4
# Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.)
# The 2x2 grid is as follows:

# Example 4:

# Input:
# [
#   "/\\",
#   "\\/"
# ]

# Output: 5
# Explanation: (Recall that because \ characters are escaped, "/\\" refers to /\, and "\\/" refers to \/.)
# The 2x2 grid is as follows:

# Example 5:

# Input:
# [
#   "//",
#   "/ "
# ]
# Output: 3
# Explanation: The 2x2 grid is as follows:


# Note:

# 1 <= grid.length == grid[0].length <= 30
# grid[i][j] is either '/', '\', or ' '.

class DSU:
    def __init__(self, N):
        self.p = range(N)

    def find(self, x):
        if self.p[x] != x:
            self.p[x] = self.find(self.p[x])
        return self.p[x]

    def union(self, x, y):
        xr = self.find(x)
        yr = self.find(y)
        self.p[xr] = yr


"""
Approach 1: Union-Find
Intuition

To find the number of components in a graph, we can use either depth-first search or union find.
The main difficulty with this problem is in specifying the graph.

One "brute force" way to specify the graph is to associate each grid square with 4 nodes (north, south, west, and east),
representing 4 triangles inside the square if it were to have both slashes.

Then, we can connect all 4 nodes if the grid square is " ",
and connect two pairs if the grid square is "/" or "". Finally, we can connect all neighboring nodes
(for example, the east node of the square at grid[0][0] connects with the west node of the square at grid[0][1]).

This is the most straightforward approach, but there are other approaches that use less nodes to represent the underlying information.

Algorithm

Create 4*N*N nodes, one for each grid square, and connect them as described above.
After, we use a union find structure to find the number of connected components.

We will skip the explanation of how a DSU structure is implemented.
Please refer to https://leetcode.com/problems/redundant-connection/solution/ for a tutorial on DSU.

Complexity Analysis

Time Complexity: O(N∗N∗α(N)), where N is the length of the grid, and α is the Inverse-Ackermann function (if we were to use union-find by rank.)

Space Complexity: O(N∗N).
"""


class RegionsBySlashes:

    def doit(self, grid):

        N = len(grid)
        dsu = DSU(4 * N * N)

        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                root = 4 * (r * N + c)
                if val in '/ ':
                    dsu.union(root + 0, root + 1)
                    dsu.union(root + 2, root + 3)
                if val in '\ ':
                    dsu.union(root + 0, root + 2)
                    dsu.union(root + 1, root + 3)

                # {north : 0, south : 3, east : 2, west : 1}
                # north/south
                if r + 1 < N:
                    dsu.union(root + 3, (root + 4 * N) + 0)
                if r - 1 >= 0:
                    dsu.union(root + 0, (root - 4 * N) + 3)
                # east/west
                if c + 1 < N:
                    dsu.union(root + 2, (root + 4) + 1)
                if c - 1 >= 0:
                    dsu.union(root + 1, (root - 4) + 2)

        return sum(dsu.find(x) == x for x in range(4 * N * N))

    # more and more fast
    def doit(self, grid)

     n = len(grid)
      ds = []

       def joint(ds, x, y):
            while ds[x] >= 0:
                x = ds[x]
            while ds[y] >= 0:
                y = ds[y]
            if x != y:
                if ds[x] == ds[y]:
                    ds[x] -= 1
                    ds[y] = x
                elif ds[x] > ds[y]:
                    ds[x] = y
                else:
                    ds[y] = x

        bottom = [[None] * n] * n
        right = [[None] * n] * n
        top_left = grid[0][0]
        ds += [-1]

        if top_left == ' ':
            bottom[0][0] = right[0][0] = 0
        elif top_left == '/':
            ds += [-1]
            bottom[0][0] = right[0][0] = 1
        else:
            ds += [-1]
            bottom[0][0] = 0
            right[0][0] = 1

        for i in range(1, n):
            left = right[0][i-1]
            x = grid[0][i]
            if x == ' ':
                bottom[0][i] = right[0][i] = left
            elif x == '/':
                bottom[0][i] = right[0][i] = len(ds)
                ds += [-1]
            else:
                bottom[0][i] = left
                right[0][i] = len(ds)
                ds += [-1]

        for i in range(1, n):
            for j in range(n):
                up = bottom[i-1][j]
                left = None
                if j > 0:
                    left = right[i][j-1]
                x = grid[i][j]

                if x == ' ':
                    bottom[i][j] = right[i][j] = up
                    if left != None and left != up:
                        joint(ds, left, up)
                elif x == '/':
                    if left != None and left != up:
                        joint(ds, left, up)
                    bottom[i][j] = right[i][j] = len(ds)
                    ds += [-1]
                else:
                    right[i][j] = up
                    if left == None:
                        left = len(ds)
                        ds += [-1]
                    bottom[i][j] = left

        return len([x for x in ds if x < 0])


if __name__ == '__main__':

    res = RegionsBySlashes().doit([
        " /",
        "/ "
    ])
