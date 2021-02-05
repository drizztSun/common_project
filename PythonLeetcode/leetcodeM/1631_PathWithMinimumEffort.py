"""
1631. Path With Minimum Effort


You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of cell (row, col). 
You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). 
You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.

A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.

Return the minimum effort required to travel from the top-left cell to the bottom-right cell.

 

Example 1:



Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
Output: 2
Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.
Example 2:



Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
Output: 1
Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in consecutive cells, which is better than route [1,3,5,3,5].
Example 3:


Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
Output: 0
Explanation: This route does not require any effort.
 

Constraints:

rows == heights.length
columns == heights[i].length
1 <= rows, columns <= 100
1 <= heights[i][j] <= 10^6

"""


class PathWithMinimumEffort:


    """
        Approach 2: Variations of Dijkstra's Algorithm
        Intuition

        The previous approach is exhaustive as it traverses all the paths. If we observe, the problem is similar to finding the shortest path from a source cell to a destination cell. Here, the shortest path is the one with minimum absolute difference between every adjacent cells in that path. Also, since there is height associated with each cell, simple BFS traversal won't be sufficient.

        The absolute difference between adjacent cells A and B can be perceived as the weight of an edge from cell A to cell B. Thus, we could use Dijkstra's Algorithm which is used to find the shortest path in a weighted graph with a slight modification of criteria for the shortest path.

        Let's look at the algorithm in detail.

        Algorithm

        We use a differenceMatrix of size \text{row} \cdot \text{col}row⋅col where each cell represents the minimum effort required to reach that cell from all the possible paths. Also, initialize we all the cells in the differenceMatrix to infinity \text{(MAX\_INT)}(MAX_INT) since none of the cells are reachable initially.

        As we start visiting each cell, all the adjacent cells are now reachable. We update the absolute difference between the current cell and adjacent cells in the differenceMatrix. At the same time, we also push all the adjacent cells in a priority queue. The priority queue holds all the reachable cells sorted by its value in differenceMatrix, i.e the cell with minimum absolute difference with its adjacent cells would be at the top of the queue.

        We begin by adding the source cell (x=0, y=0) in the queue. Now, until we have visited the destination cell or the queue is not empty, we visit each cell in the queue sorted in the order of priority. The less is the difference value(absolute difference with adjacent cell) of a cell, the higher is its priority.

        Get the cell from the top of the queue curr and visit the current cell.

        For each of the 4 cells adjacent to the current cell, calculate the maxDifference which is the maximum absolute difference to reach the adjacent cell (adjacentX, adjacentY) from current cell (curr.x, curr.y).

        If the current value of the adjacent cell (adjacentX, adjacentY) in the difference matrix is greater than the maxDifference, we must update that value with maxDifference. In other words, we have found that the path from the current cell to the adjacent cell takes lesser efforts than the other paths that have reached the adjacent cell so far. Also, we must add this updated difference value in the queue.

        Ideally, for updating the priority queue, we must delete the old value and reinsert with the new maxDifference value. But, as we know that the updated maximum value is always lesser than the old value and would be popped from the queue and visited before the old value, we could save time and avoid removing the old value from the queue.

        At the end, the value at differenceMatrix[row - 1][col - 1] is the minimum effort required to reach the destination cell (row-1,col-1).
        Current
        1 / 8
        Implementation


        Complexity Analysis

        Time Complexity : O(m⋅nlog(m⋅n)), where mm is the number of rows and nn is the number of columns in matrix \text{heights}heights. It will take \mathcal{O}(m \cdot n)O(m⋅n) time to visit every cell in the matrix. The priority queue will contain at most m \cdot nm⋅n cells, so it will take \mathcal{O}(\log (m \cdot n))O(log(m⋅n)) time to re-sort the queue after every adjacent cell is added to the queue. This given as total time complexiy as \mathcal{O}(m \cdot n \log(m \cdot n))O(m⋅nlog(m⋅n)).

        Space Complexity: O(m⋅n), where mm is the number of rows and nn is the number of columns in matrix \text{heights}heights. The maximum queue size is equal to the total number of cells in the matrix \text{height}height which is given by m \cdot nm⋅n. Also, we use a difference matrix of size m \cdot nm⋅n. This gives as time complexity as \mathcal{O}(m \cdot n + m \cdot n)O(m⋅n+m⋅n) = \mathcal{O}(m \cdot n)O(m⋅n)

    """

    def doit_bfs_dijstra(self, heights: list) -> int:

        from collections import deque
        from heapq import heapify, heappush, heappop

        m, n = len(heights), len(heights[0])
        heap = [(float('-inf'), 0, 0)]
        heapify(heap)
        direct = (-1, 0, 1, 0, -1)
        visited = [[float('inf') for _ in range(n)] for _ in range(m)]
        visited[0][0] = 0

        while heap:

            val, r, c = heappop(heap)

            if r == m - 1 and c == n - 1:
                return val

            for i in range(4):

                x1 = r + direct[i]
                y1 = c + direct[i+1]

                if 0 <= x1 < m and 0 <= y1 < n:
                    nval = max(val, abs(heights[x1][y1] - heights[r][c]))    
                    if nval < visited[x1][y1]:
                        visited[x1][y1] = nval
                        heappush(heap, (nval, x1, y1))

        return -1

    """
        Approach 3: Union Find - Disjoint Set
        Intuition

        Using Disjoint Set is another intuitive way to solve the problem. Each cell in the matrix is a single node/component in a graph. The path from the current cell to adjacent cells is an edge connecting the 2 cells. Using this intuition, we could use Union Find algorithm to form a connected component from the source cell to the destination cell.

        Initially, every cell is a disconnected component and we aim to form a single connected component that connects the source cell to the destination cell. Each connected component connects multiple cells and is identified by a parent. We must continue connecting components until the source cell and destination cell shares the same parent.

        The union find algorithm performs 2 operations,

        Find(x): Returns the parent of the connected component to which x belongs.

        Union(x, y): Merges the two disconnected components to which x and y belongs.

        To efficiently implement the above operations, we could use Union By Rank and Path Compression strategy.

        Algorithm

        Initially, each cell is a disconnected component, so we initialize each cell as a parent of itself. Also we flatten a 2D matrix into a 1D matrix of size row * col and each cell (currentRow, currentCol) in a 2D matrix can be stored at (currentRow * col + currentCol) in a 1D matrix. The below figure illustrates this idea.
        img

        We also build an edgeList which consists of the absolute difference between every adjacent cell in the matrix. We also sort the edge list in non-decreasing order of difference. The below example illustrates the edge list of given heights matrix [[1,2,2],[3,8,2],[5,3,5]] sorted by difference.
        img

        Start iterating over the sorted edge list and connect each edge to form a connected component using Union Find Algorithm.

        After every union, check if the source cell (0) and destination cell (row * col - 1) are connected. If yes, the absolute difference between the current edge is our result. Since we access the edges in increasing order of difference, and the current edge connected the source and destination cell, we are sure that the current difference is the maximum absolute difference in our path with minimum efforts.

        Implementation


        Complexity Analysis

        Let mm be the number of rows and nn be the number of columns of the matrix \text{height}height.

        Time Complexity : O(m⋅n(log(m⋅n))). We iterate each edge in the matrix. From the above example, it is evident that for a matrix of size 3 \cdot33⋅3, the total number of edges are 1212. Thus, for a m \cdot nm⋅n matrix, the total number of edges could be given by (m\cdot n \cdot 2)-(m+n)(m⋅n⋅2)−(m+n) (3*3*2) - (3+3)), which is roughly equivalent to m \cdot nm⋅n.
        For every edge, we find the parent of each cell and perform the union (Union Find). For nn elements, the time complexity of Union Find is \log nlogn. (Refer Proof Of Time Complexity Of Union Find). Thus for m \cdot nm⋅n cells, the time taken to perform Union Find would be \log m \cdot nlogm⋅n. This gives us total time complexity as, \mathcal{O}(m\cdot n(\log(m\cdot n)))O(m⋅n(log(m⋅n))).

        Space Complexity : O(m⋅n) , we use arrays edgeList, parent, and rank of size m \cdot nm⋅n.
    """
    def doit_disjoint(self, heights: list) -> int:
            class UnionFind:
                def __init__(self, size):
                    self.parent = [x for x in range(size)]
                    self.rank = [0]*(size)

                def find(self, i):
                    if self.parent[i] != i:
                        self.parent[i] = self.find(self.parent[i])
                    return self.parent[i]

                def union(self, x, y):
                    parent_x = self.find(x)
                    parent_y = self.find(y)
                    if parent_x != parent_y:
                        if self.rank[parent_x] > self.rank[parent_y]:
                            self.parent[parent_y] = parent_x
                        elif self.rank[parent_x] < self.rank[parent_y]:
                            self.parent[parent_x] = parent_y
                        else:
                            self.parent[parent_y] = parent_x
                            self.rank[parent_x] += 1

            row = len(heights)
            col = len(heights[0])
            if row == 1 and col == 1:
                return 0

            edge_list = []
            for current_row in range(row):
                for current_col in range(col):
                    if current_row > 0:
                        difference = abs(heights[current_row][current_col] - heights[current_row - 1][current_col])
                        edge_list.append((difference, current_row * col + current_col, (current_row - 1) * col + current_col))

                    if current_col > 0:
                        difference = abs(heights[current_row][current_col] - heights[current_row][current_col - 1])
                        edge_list.append((difference, current_row * col + current_col, current_row * col + current_col - 1))

            edge_list.sort()
            union_find = UnionFind(row*col)

            for difference, x, y in edge_list:
                union_find.union(x, y)
                if union_find.find(0) == union_find.find(row*col-1):
                    return difference
            return -1

    """
        Approach 4: Binary Search Using BFS
        Intuition

        Our aim to find the minimum effort required to travel from source cell to destination cell. We know from the given constraints that the maximum height could be 10^6 (1000000)10 
        6
        (1000000). So we know that our required absolute difference values would between 00 and 10^610 
        6
        . We could use Binary Search and reduce our search space by half.

        Given the lower bound as 00 and upper bound as 10^610 
        6
        , we could repeatedly calculate the middle value. Let this middle value be mid. We could divide our search space based on the following condition,

        If there exists a path from the source cell to the destination cell with the effort less than the value mid, we know that the required minimum effort value lies between lower bound 00 and mid.
        Similarly, if there doesn't exist any path from a source cell to destination cell with the effort less than the value mid, we know that the required minimum effort value lies between mid and upper bound 10^610 
        6
        .
        To find if there exists a path from the source cell to the destination cell for a given mid value, we could use simple graph traversal. In this approach, we use Breath First Search traversal.

        Algorithm

        Intialize the lower bound left as 00 and upper bound right as 10^610 
        6
        . Calculate the middle value mid of the left and right value.

        Using Breath First Search, check if there exists a path from source cell (x=0, y=0) to destination cell (x=row-1, y=column-1) with effort less than or equal to mid using method canReachDestination which returns a boolean value.

        If there exists a path from the source cell to the destination cell, we must update the result value as a minimum of the current result and mid and continue the search in the range between left and mid-1. For this, we must update the value of right to mid-1.

        Otherwise, we must search in the range between mid+1 and right and update left to mid+1.

        Implementation


        Complexity Analysis

        Let mm be the number of rows and nn be the number of columns for the matrix \text{height}height.

        Time Complexity : O(m⋅n). We do a binary search to calculate the mid values and then do Breadth First Search on the matrix for each of those values.

        Binary Search: To perform Binary search on numbers in range (0.. 10^{6}), the time taken would be O(log10^6).

        Breath First Search: The time complexity for the Breadth First Search for vertices V and edges E is O(V+E) (Refer) Thus, in the matrix of size m \cdot nm⋅n, 
        with m \cdot nm⋅n vertices and m \cdot nm⋅n edges (Refer time complexity of Approach 3), the time complexity to perform Breath First Search would be \mathcal{O}(m \cdot n + m \cdot n)O(m⋅n+m⋅n) = \mathcal{O}(m \cdot n)O(m⋅n).

        This gives us total time complexity as O(log10^6 ⋅(m⋅n)) which is equivalent to O(m⋅n).

        Space Complexity: O(m⋅n), as we use a queue and visited array of size m⋅n
    """
    def doit_bfs_binary_search(self, heights: list) -> int:
        row = len(heights)
        col = len(heights[0])

        def canReachDestinaton(mid):
            visited = [[False]*col for _ in range(row)]
            queue = [(0, 0)]  # x, y
            while queue:
                x, y = queue.pop(0)
                if x == row-1 and y == col-1:
                    return True
                visited[x][y] = True
                for dx, dy in [[0, 1], [1, 0], [0, -1], [-1, 0]]:
                    adjacent_x = x + dx
                    adjacent_y = y + dy
                    if 0 <= adjacent_x < row and 0 <= adjacent_y < col and not visited[adjacent_x][adjacent_y]:
                        current_difference = abs(heights[adjacent_x][adjacent_y] - heights[x][y])
                        if current_difference <= mid:
                            visited[adjacent_x][adjacent_y] = True
                            queue.append((adjacent_x, adjacent_y))

        left = 0
        right = 10000000
        while left < right:
            mid = (left + right)//2
            if canReachDestinaton(mid):
                right = mid
            else:
                left = mid + 1
        return left

    """
        Approach 5: Binary Search Using DFS
        Intuition and Algorithm

        The solution is similar to Approach 4. Except that, here, we use a Depth First Search traversal to find if there exists a path from the source cell to destination cell for a given value middle value mid.

        Implementation


        Complexity Analysis

        Time Complexity : O(m⋅n). As in Approach 4. The only difference is that we are using Depth First Search instead of Breadth First Search and have similar time complexity.

        Space Complexity: O(m⋅n), As in Approach 4. In Depth First Search, we use the internal call stack (instead of the queue in Breadth First Search).


    """
    def minimumEffortPath(self, heights: list) -> int:
        row = len(heights)
        col = len(heights[0])

        def canReachDestinaton(x, y, mid):
            if x == row-1 and y == col-1:
                return True
            visited[x][y] = True
            for dx, dy in [[0, 1], [1, 0], [0, -1], [-1, 0]]:
                adjacent_x = x + dx
                adjacent_y = y + dy
                if 0 <= adjacent_x < row and 0 <= adjacent_y < col and not visited[adjacent_x][adjacent_y]:
                    current_difference = abs(heights[adjacent_x][adjacent_y] - heights[x][y])
                    if current_difference <= mid:
                        visited[adjacent_x][adjacent_y] = True
                        if canReachDestinaton(adjacent_x, adjacent_y, mid):
                            return True
        left = 0
        right = 10000000
        while left < right:
            mid = (left + right)//2
            visited = [[False]*col for _ in range(row)]
            if canReachDestinaton(0, 0, mid):
                right = mid
            else:
                left = mid + 1
        return left
    

if __name__ == '__main__':

    # PathWithMinimumEffort().doit_bfs([[1,2,2],[3,8,2],[5,3,5]])

    PathWithMinimumEffort().doit_bfs([[1,10,6,7,9,10,4,9]])
