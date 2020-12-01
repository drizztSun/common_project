"""
286. Walls and Gates

You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 2^31 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

Example:

Given the 2D grid:

INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
After running your function, the 2D grid should be:

  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4


"""


class WallsAndGates:


    """
    Approach #2 (Breadth-first Search) [Accepted]
    Instead of searching from an empty room to the gates, how about searching the other way round? In other words,
    we initiate breadth-first search (BFS) from all gates at the same time. Since BFS guarantees that we search
    all rooms of distance d before searching rooms of distance d + 1, the distance to an empty room must be the shortest.

    Complexity analysis

    Time complexity : O(mn)O(mn).

    If you are having difficulty to derive the time complexity, start simple.

    Let us start with the case with only one gate. The breadth-first search takes at most m \times nm×n steps to reach all rooms,
    therefore the time complexity is O(mn)O(mn). But what if you are doing breadth-first search from kk gates?

    Once we set a room's distance, we are basically marking it as visited, which means each room is visited at most once.
    Therefore, the time complexity does not depend on the number of gates and is O(mn)O(mn).

    Space complexity : O(mn)O(mn). The space complexity depends on the queue's size. We insert at most m \times nm×n points into the queue.
    """

    def doit_(self, rooms: list) -> None:

        from collections import deque
        if not rooms:
            return

        m, n = len(rooms), len(rooms[0])
        zeros = []
        for i in range(m):
            for j in range(n):
                if rooms[i][j] == 0:
                    zeros.append((i, j))

        queue = deque(zeros)
        inf = 2**31 - 1

        while queue:

            size = len(queue)
            for _ in range(size):

                r, l = queue.popleft()
                levels = rooms[r][l]
                for offset in ((-1, 0), (1, 0), (0, 1), (0, -1)):
                    x, y = r + offset[0], l + offset[1]
                    if 0 <= x < m and 0 <= y < n and rooms[x][y] == inf:
                        rooms[x][y] = levels + 1
                        queue.appendleft((x, y))


if __name__ == '__main__':

    WallsAndGates().doit_([[2147483647,-1,0,2147483647],[2147483647,2147483647,2147483647,-1],[2147483647,-1,2147483647,-1],[0,-1,2147483647,2147483647]])



