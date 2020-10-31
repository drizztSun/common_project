"""
# 305. Number of Islands II

# A 2d grid map of m rows and n columns is initially filled with water.
# We may perform an addLand operation which turns the water at position (row, col) into a land.
# Given a list of positions to operate, count the number of islands after each addLand operation.
# An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
# You may assume all four edges of the grid are all surrounded by water.

# Example:

# Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
# Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

# 0 0 0
# 0 0 0
# 0 0 0
# Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

# 1 0 0
# 0 0 0   Number of islands = 1
# 0 0 0
# Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

# 1 1 0
# 0 0 0   Number of islands = 1
# 0 0 0
# Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

# 1 1 0
# 0 0 1   Number of islands = 2
# 0 0 0
# Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

# 1 1 0
# 0 0 1   Number of islands = 3
# 0 1 0
# We return the result as an array: [1, 1, 2, 3]


# Challenge:

# Can you do it in time complexity O(k log mn), where k is the length of the positions?
"""


# <hard> <important>
class NumberOfIslandII(object):

    """
    Approach #3: Union Find (aka Disjoint Set) [Accepted]
    Intuition

    Treat the 2d grid map as an undirected graph (formatted as adjacency matrix) and there is an edge between two horizontally or vertically adjacent nodes of value 1,
    then the problem reduces to finding the number of connected components in the graph after each addLand operation.

    Algorithm

    Make use of a Union Find data structure of size m*n to store all the nodes in the graph and initially each node's parent value is set to -1 to represent an empty graph.
    Our goal is to update Union Find with lands added by addLand operation and union lands belong to the same island.

    For each addLand operation at position (row, col), union it with its adjacent neighbors if they belongs to some islands,
    if none of its neighbors belong to any islands, then initialize the new position as a new island (set parent value to itself) within Union Find.

    For detailed description of Union Find (implemented with path compression and union by rank), you can refer to this

    Complexity Analysis

    Time complexity : O(m×n+L) where LL is the number of operations, mm is the number of rows and nn is the number of columns.
    it takes O(m×n) to initialize UnionFind, and O(L)O(L) to process positions. Note that Union operation takes essentially constant time[1] when UnionFind is implemented with both path compression and union by rank.

    Space complexity : O(m \times n)O(m×n) as required by UnionFind data structure.
    """

    # <union-find>
    def doit(self, m, n, positions):
        """
        type: int
        type: int
        type: list[list[int]]
        rtype: list[int]
        """
        parent = [-1] * (m * n)
        lands = 0
        result = []

        def root(id):
            while parent[id] != id:
                # Path Suspress, child points to father's father
                parent[id] = parent[parent[id]]
                id = parent[id]
            return id

        for x, y in positions:
            id = x * n + y

            if parent[id] != -1:
                result.append(lands)
                continue

            parent[id] = id
            lands += 1
            nears = [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]

            for nx, ny in nears:
                nid = nx * n + ny
                if 0 <= nx < m and 0 <= ny < n and parent[nid] != -1:
                    rootid = root(nid)
                    if rootid != id:
                        parent[rootid] = id
                        lands -= 1

            result.append(lands)
        return result


if __name__ == "__main__":

    res = NumberOfIslandII().doit(
        3, 3, [[0, 0], [0, 1], [1, 2], [2, 1]])  # [1, 1, 2, 3]

    pass
