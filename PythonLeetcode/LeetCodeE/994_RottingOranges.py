# 994. Rotting Oranges

# In a given grid, each cell can have one of three values:

# the value 0 representing an empty cell;
# the value 1 representing a fresh orange;
# the value 2 representing a rotten orange.
# Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.

# Return the minimum number of minutes that must elapse until no cell has a fresh orange.
# If this is impossible, return -1 instead.


# Example 1:

# Input: [[2,1,1],[1,1,0],[0,1,1]]
# Output: 4

# Example 2:

# Input: [[2,1,1],[0,1,1],[1,0,1]]
# Output: -1
# Explanation:  The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

# Example 3:

# Input: [[0,2]]
# Output: 0
# Explanation:  Since there are already no fresh oranges at minute 0, the answer is just 0.

class OrangesRotting:

    def doit(self, grid):

        rotten = set()
        fresh = set()
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 2:
                    rotten.add((i, j))
                elif grid[i][j] == 1:
                    fresh.add((i, j))

        ans = 0
        while fresh and rotten:
            ans += 1
            newrotten = set()
            for x, y in rotten:
                for c in [(x-1, y), (x+1, y), (x, y-1), (x, y+1)]:
                    if c in fresh:
                        fresh.remove(c)
                        newrotten.add(c)
            rotten = newrotten

        return ans if not fresh else -1

    """
    Approach 1: Breadth-First Search
    Intuition
    Every turn, the rotting spreads from each rotting orange to other adjacent oranges.
    Initially, the rotten oranges have 'depth' 0 [as in the spanning tree of a graph], and every time they rot a neighbor, the neighbors have 1 more depth. We want to know the largest possible depth.

    Algorithm
    We can use a breadth-first search to model this process.
    Because we always explore nodes (oranges) with the smallest depth first, we're guaranteed that each orange that becomes rotten does so with the lowest possible depth number.
    We should also check that at the end, there are no fresh oranges left.

    Complexity Analysis
    Time Complexity: O(N), where N is the number of cells in the grid.
    Space Complexity: O(N).
    """

    def doit(self, A):
        import collections
        R, C = len(A), len(A[0])

        # queue - all starting cells with rotting oranges
        queue = collections.deque()
        for r, row in enumerate():
            for c, val in enumerate(row):
                if val == 2:
                    queue.append((r, c, 0))

        def neighbors(r, c):
            for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                if 0 <= nr < R and 0 <= nc < C:
                    yield nr, nc

        d = 0
        while queue:
            r, c, d = queue.popleft()
            for nr, nc in neighbors(r, c):
                if A[nr][nc] == 1:
                    A[nr][nc] = 2
                    queue.append((nr, nc, d+1))

        if any(1 in row for row in A):
            return -1
        return d


if __name__ == '__main__':

    res = OrangesRotting().doit([[2, 1, 1],
                                 [1, 1, 0],
                                 [0, 1, 1]])  # 4

    res = OrangesRotting().doit([[2, 1, 1],
                                 [0, 1, 1],
                                 [1, 0, 1]])  # -1

    res = OrangesRotting().doit([[0, 2]])  # 0

    pass
