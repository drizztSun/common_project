"""
1368. Minimum Cost to Make at Least One Valid Path in a Grid


Given a m x n grid. Each cell of the grid has a sign pointing to the next cell you should visit if you are currently in this cell. The sign of grid[i][j] can be:
1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])
Notice that there could be some invalid signs on the cells of the grid which points outside the grid.

You will initially start at the upper left cell (0,0). A valid path in the grid is a path which starts from the upper left cell (0,0) and ends at the bottom-right cell (m - 1, n - 1) following the signs on the grid. The valid path doesn't have to be the shortest.

You can modify the sign on a cell with cost = 1. You can modify the sign on a cell one time only.

Return the minimum cost to make the grid have at least one valid path.



Example 1:


Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
Output: 3
Explanation: You will start at point (0, 0).
The path to (3, 3) is as follows. (0, 0) --> (0, 1) --> (0, 2) --> (0, 3) change the arrow to down with cost = 1 --> (1, 3) --> (1, 2) --> (1, 1) --> (1, 0) change the arrow to down with cost = 1 --> (2, 0) --> (2, 1) --> (2, 2) --> (2, 3) change the arrow to down with cost = 1 --> (3, 3)
The total cost = 3.
Example 2:


Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
Output: 0
Explanation: You can follow the path from (0, 0) to (2, 2).
Example 3:


Input: grid = [[1,2],[4,3]]
Output: 1
Example 4:

Input: grid = [[2,2,2],[2,2,2]]
Output: 3
Example 5:

Input: grid = [[4]]
Output: 0


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 100


"""


class MinimumCostToMakeLeastStep:

    """
                1368.Minimum-Cost-to-Make-at-Least-One-Valid-Path-in-a-Grid
        解法1：BFS
        如果不给修改的机会，那么我们能遍历到哪些格子？显然就是从(0,0)顺着箭头走，假设能走到Set0 = {p1,p2,...pk}这些位置。

        然后考虑如果给一次修改的机会，我们能遍历到哪些格子？我们会从之前Set0集合里考察每一个格子，思考如果不按照当前的箭头走，而是可以修改成任意方向的话，下一步会到哪里？
        比如说p1原本的箭头指向p2，现在我们允许修改一次p1的箭头方向，那么p1可能可以走到上述集合之外的q1。同时我们顺着q1的箭头走，又可以遍历到q2,q3,q4...等一系列的位置。

        可见这一系列{qi}点集就是“给一次修改机会”所能到达的位置。同理，我们还可以修改p1的箭头指向r1，或者选择Set0中的其他格子修改箭头，这些操作都能得到“给一次修改机会”所能到达的位置，我们标记为Set1。

        我们看出来，从Set0到Set1，就是一个BFS的过程。同理从Set1到Set2，也是BFS的过程：不断从一个集合，扩展到下一个集合，伴随step+=1.直到发现经过若干步（即修改若干次箭头）之后，就可以遍历到右下角，那么就可以返回答案。

        需要注意的是，在上述过程中，从q1顺着原有的箭头扩展到q2,q3,q4...的过程也是遍历，这层遍历时的step都是保持不变的。对于这层遍历，我们也可以用dfs来实现。

        解法2：Dijkstra
        如果格子A的符号导向的是格子B，那么我们就认为AB之间的边权重是0；否则我们就认为AB之间的边权重是1. 于是本题就变成了求起点到终点的最短路径问题。因为图中任意两点之间的边权重不等，所以用Dijkstra是显而易见的方案
    """
    def doit_bfs(self, grid: list) -> int:
        from collections import deque
        m, n = len(grid), len(grid[0])
        visited = [[False for _ in range(n)] for _ in range(m)]
        direct = [(0, 1), (0, -1), (1, 0), (-1, 0)]

        def dfs(x, y, queue):
            if x < 0 or x >= m or y < 0 or y >= n or visited[x][y]:
                return
            queue.append((x, y))
            visited[x][y] = True
            dfs(x + direct[grid[x][y]-1][0], y + direct[grid[x][y]-1][1], queue)

        queue = deque()
        dfs(0, 0, queue)
        cost = 0
        while queue:

            size = len(queue)
            for _ in range(size):
                x, y = queue.popleft()
                if x == m-1 and y == n-1:
                    return cost

                for i in range(4):

                    x1, y1 = x + direct[i][0], y + direct[i][1]
                    if x1 < 0 or x1 >= m or y1 < 0 or y1 >= n or visited[x1][y1]: continue

                    dfs(x1, y1, queue)

            cost += 1

        return 0

    def doit_dijkstra(self, grid: list) -> int:

        from heapq import heappush, heappop
        m, n = len(grid), len(grid[0])
        visited = [[False for _ in range(n)] for _ in range(m)]
        heap = [(0, 0, 0)]
        direct = [(0, 1), (0, -1), (1, 0), (-1, 0)]

        while heap:

            cost, x, y = heappop(heap)

            if visited[x][y]: continue
            visited[x][y] = True

            if x == m-1 and y == n-1:
                return cost

            for i in range(4):
                x1, y1 = x + direct[i][0], y + direct[i][1]

                if x1 < 0 or x1 >= m or y1 < 0 or y1 >= n or visited[x1][y1]:
                    continue

                addon = 1 if grid[x][y] != i+1 else 0
                heappush(heap, (cost + addon, x1, y1))

        return 0





