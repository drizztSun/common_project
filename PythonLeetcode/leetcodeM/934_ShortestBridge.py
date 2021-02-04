"""
934. Shortest Bridge

# In a given 2D binary array A, there are two islands.  (An island is a 4-directionally connected group of 1s not connected to any other 1s.)

# Now, we may change 0s to 1s so as to connect the two islands together to form 1 island.

# Return the smallest number of 0s that must be flipped.  (It is guaranteed that the answer is at least 1.)


# Example 1:

# Input: [[0,1],[1,0]]
# Output: 1
# Example 2:

# Input: [[0,1,0],[0,0,0],[0,0,1]]
# Output: 2

# Example 3:

# Input: [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
# Output: 1


# Note:

# 1 <= A.length = A[0].length <= 100
# A[i][j] == 0 or A[i][j] == 1

"""


class ShortestBridge:

    """
    Approach 1: Find and Grow
    Intuition

    Conceptually, our method is very straightforward: find both islands, then for one of the islands, keep "growing" it by 1 until we touch the second island.

    We can use a depth-first search to find the islands, and a breadth-first search to "grow" one of them. This leads to a verbose but correct solution.

    Algorithm

    To find both islands, look for a square with a 1 we haven't visited, and dfs to get the component of that region. Do this twice. After, we have two components source and target.

    To find the shortest bridge, do a BFS from the nodes source. When we reach any node in target, we will have found the shortest distance.

    Please see the code for more implementation details.

    Complexity Analysis

    Time Complexity: O(A), where {A}A is the content of A.

    Space Complexity: O(A).
    """
    def doit_bfs(self, A):

        def get_n(x, y):
            r = []
            for dx, dy in [[1, 0], [-1, 0], [0, 1], [0, -1]]:
                a = x + dx
                b = y + dy
                if 0 <= a < len(A) and 0 <= b < len(A[0]):
                    r.append([a, b])
            return r

        q = []
        b = []

        # Find 1st island and its boundary region 'b'.
        for i in range(len(A)):
            for j in range(len(A[0])):
                if A[i][j] == 1:
                    q = [[i, j]]
                    break

        while q:
            x, y = q.pop(0)
            if A[x][y] == 2:
                continue

            if A[x][y] == 0:
                b.append([x, y])
                continue

            if A[x][y] == 1:
                A[x][y] = 2
                q += get_n(x, y)

        # Grow boundary region 'b' until the 2nd island is discovered.
        dst = 0
        while len(b) > 0:
            size = len(b)
            for _ in range(size):
                x, y = b.pop(0)

                if A[x][y] == 1:
                    return dst

                if A[x][y] == 2:
                    continue

                if A[x][y] == 0:
                    A[x][y] = 2
                    b += get_n(x, y)
            dst += 1

        return dst


    def shortestBridge(self, A):
        from collections import deque
        R, C = len(A), len(A[0])

        def neighbors(r, c):
            for nr, nc in ((r-1,c),(r,c-1),(r+1,c),(r,c+1)):
                if 0 <= nr < R and 0 <= nc < C:
                    yield nr, nc

        def get_components():
            done = set()
            components = []
            for r, row in enumerate(A):
                for c, val in enumerate(row):
                    if val and (r, c) not in done:
                        # Start dfs
                        stack = [(r, c)]
                        seen = {(r, c)}
                        while stack:
                            node = stack.pop()
                            for nei in neighbors(*node):
                                if A[nei[0]][nei[1]] and nei not in seen:
                                    stack.append(nei)
                                    seen.add(nei)
                        done |= seen
                        components.append(seen)
            return components

        source, target = get_components()
        queue = deque([(node, 0) for node in source])
        done = set(source)

        while queue:
            node, d = queue.popleft()
            if node in target: 
                return d-1
            
            for nei in neighbors(*node):
                if nei not in done:
                    queue.append((nei, d+1))
                    done.add(nei)


if __name__ == '__main__':

    res = ShortestBridge().doit([[0, 1],
                                 [1, 0]])

    res = ShortestBridge().doit([[0, 1, 0],
                                 [0, 0, 0],
                                 [0, 0, 1]])

    res = ShortestBridge().doit([[1, 1, 1, 1, 1],
                                 [1, 0, 0, 0, 1],
                                 [1, 0, 1, 0, 1],
                                 [1, 0, 0, 0, 1],
                                 [1, 1, 1, 1, 1]])

    pass
