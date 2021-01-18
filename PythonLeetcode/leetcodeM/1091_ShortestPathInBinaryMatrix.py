"""
1091. Shortest Path in Binary Matrix


In an N by N square grid, each cell is either empty (0) or blocked (1).

A clear path from top-left to bottom-right has length k if and only if it is composed of cells C_1, C_2, ..., C_k such that:

Adjacent cells C_i and C_{i+1} are connected 8-directionally (ie., they are different and share an edge or corner)
C_1 is at location (0, 0) (ie. has value grid[0][0])
C_k is at location (N-1, N-1) (ie. has value grid[N-1][N-1])
If C_i is located at (r, c), then grid[r][c] is empty (ie. grid[r][c] == 0).
Return the length of the shortest such clear path from top-left to bottom-right.  If such a path does not exist, return -1.



Example 1:

Input: [[0,1],[1,0]]


Output: 2

Example 2:

Input: [[0,0,0],[1,1,0],[1,1,0]]


Output: 4



Note:

1 <= grid.length == grid[0].length <= 100
grid[r][c] is 0 or 1


Solution
Overview
If an interviewer asks you this question in an interview, then their goal is probably to determine that:

You can recognize that this is a typical shortest path problem that can be solved with a Breadth-first search (BFS).
You can correctly implement a BFS to solve it.
For bonus points, you know that the solution could be optimized using the A* algorithm.
For this article, I'm going to assume that you already know the fundamentals of BFS and are at the stage of figuring out how to apply it to a wide range of problems, such as this one. 
If you aren't yet at this stage, then I recommend checking out our relevant Explore Card content on BFS before coming back to this problem.

We'll look at two BFS implementations in this article; one that overwrites the input and another that does not. We'll also take a look at how this problem could be solved using A*.

"""


class ShortestPathBinaryMatrix:

    def doit_bfs(self, grid: list) -> int:

        from collections import deque
        m, n = len(grid), len(grid[0])
        qu = deque()
        if grid[0][0] == 0:
            qu.append((0, 0, 0))
        visited = set()

        while qu:

            path, r, c = qu.popleft()
            if (r, c) == (m - 1, n - 1):
                return path + 1

            for delta in ((-1, 0), (-1, -1), (0, -1), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1)):
                x, y = r + delta[0], c + delta[1]

                if 0 <= x < m and 0 <= y < n and grid[x][y] == 0 and (x, y) not in visited:
                    visited.add((x, y))
                    qu.append((path + 1, x, y))

        return -1

    def doit_bfs_1(self, grid):

        from heapq import heappush, heappop
        from itertools import product

        n = len(grid) - 1
        if grid[0][0] or grid[n][n]:
            return -1

        # use iterator to create 8 directions
        directions = [x for x in product((-1, 0, 1), repeat=2) if x != (0, 0)]

        q = [(n + 1, 1, n, n)]  # put (evaluation, step, i, j) into q
        grid[n][n] = -1  # the step of the start is 1

        while q:
            _, step, i, j = heappop(q)
            # arrive the end, return minimal step
            if (i, j) == (0, 0):
                return step

            for di, dj in directions:
                newI, newJ = i + di, j + dj
                # Except grid[i][j] = 1, we need to search and update
                if 0 <= newI <= n and 0 <= newJ <= n and grid[newI][newJ] < 1:
                    newStep = step + 1
                    # if we have new visit or can have fewer steps, update
                    if grid[newI][newJ] == 0 or grid[newI][newJ] < -newStep:
                        grid[newI][newJ] = -newStep  # store new minimal step
                        evaluation = max(newI, newJ) + newStep
                        heappush(q, (evaluation, newStep, newI, newJ))
        return -1


    """
        Algorithm

        Now that we've determined that this is a BFS problem, we need to fill in a few more details and figure out how it will all go together. Recall that BFS is implemented using a queue.

        A queue is what we refer to as a First-In-First-Out (FIFO) data structure, comparable to people queuing to go on a theme park ride. People enter the queue at the back and leave from the front. BFS works by putting the start node on the queue, and then while the queue is non-empty, it takes a node off the front of the queue and puts that node's neighbors on the back of the queue. In this way, the graph is progressively explored, starting with the nodes nearest to the start node and ending with the nodes farthest away.

        We commonly refer to putting a node on the queue as enqueuing and taking a node off the queue as dequeuing. We'll use this terminology for the remainder of the article.

        Applying BFS to this problem, we'll use the queue to keep track of cells that we have numbered but haven't yet numbered the * neighbors* of. While usually for BFS, we'd need a "visited" set to avoid infinite looping around cycles, we won't need one for this approach because we're going to overwrite the input, and so only unvisited cells will have a 0 in them.

        Here's the pseudocode for setting up the BFS. We identify cells with a (row, col) pair. The top-left cell is at row = 0 and col = 0 so is identified with the pair (0, 0).

        queue = a new queue
        enqueue cell (0, 0)
        set grid[0][0] to 1
        We enqueue the top-left cell as it's the first cell we'll be exploring. We also need to set its distance to be 1 in the grid (note that this will not cause confusion with the 1's that were used to represent blocked cells).

        Now that we've done the initialization, it's time to design the main BFS loop (again, this is fairly standard template stuff).

        While there are cells left on the queue, we should dequeue a cell, look up its distance (that has already been written into the input grid), and explore its neighbors. Exploring the cell's neighbors involves identifying all open cells adjacent to the current cell that still have a 0 in them. For each of these cells, we write the number distance + 1 into them. Finally, we need to enqueue the neighbor so that when we're ready, we can explore its neighbors too.

        Here is some pseudocode.

        while queue is not empty:

            cell = dequeue a cell
            look up distance at grid[cell row][cell col]

            for each open neighbour:
                if this neighbour is the bottom right cell (target):
                    return distance + 1
                set grid[neighbour row][neighbour col] = distance + 1
                enqueue neighbour
        return -1
        A few points to note:

        We return -1 if the loop terminates without returning, as this means we ran out of cells to explore before reaching the bottom-right cell.

        The reason we can simply do distance = grid[cell row][cell col] is because cells are only enqueued once a number has been written into them.

        We should only write numbers into cells that currently have a 0 in them. If, for example, a cell already had a 2 in it and you then change that to a 4, it would no longer have the number that represents the shortest distance from the top left to itself.

        It would be okay to do the check for the bottom-right cell in the outer loop. We would need to return distance instead of distance + 1.

        The final thing we need to consider is how to get all the neighbors of a cell. In traditional graph representations, this would be the equivalent of examining all the edges of a given node. For grids, we identify each neighbor by its row and column offset from the given cell.

        Offsets of a cell's neighbors.

        The most common pattern is to put these "offsets" into a list as follows.

        directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        We can then iterate over this list and use each offset to calculate a neighbor row and column. We need to be careful, though; while most cells have 8 neighbors, corner cells only have 3 neighbors, and edges cells have 5 neighbors. To handle this, we start by checking that the neighbors row and column actually are within the dimensions of the grid. If they are within the grid, we also check that the cell currently contains a 0 (in other words, it hasn't yet been numbered and is open). If the cell contains a 0, then we add it to a list of all the neighbors to be returned.

        Here is the pseudocode that puts all of this together. This function is reusable for many grid problems (usually without the 4 diagonal directions). You should be very familiar with this algorithm and be able to implement it in your programming language of choice very quickly.


        directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]

        define function get_neighbors(row, col):
        neighbors = a container to put the neighbors of (row, col) in
            for each (row_direction, col_direction) pair in directions:
                neighbor_row = row + row_direction
                neighbor_col = col + col_direction
                if (neighbor_row, neighbor_col) is NOT over the edge of the grid AND is 0:
                    add (neighbor_row, neighbor_col) to neighbors
            return neighbors
        Note that it is very important to check that the neighbor row and column are within the grid before checking the number in it. In most languages, getting this wrong will cause a crash. In Python, it will cause weird bugs due to Python's handling of negative indices.

        Code

        Here is the code for Java and Python.

    """
    def doit_bfs(self, grid: list) -> int:
        from collections import deque
        max_row = len(grid) - 1
        max_col = len(grid[0]) - 1
        directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        
        # Helper function to find the neighbors of a given cell.
        def get_neighbours(row, col):
            for row_difference, col_difference in directions:
                new_row = row + row_difference
                new_col = col + col_difference
                if not(0 <= new_row <= max_row and 0 <= new_col <= max_col):
                    continue
                if grid[new_row][new_col] != 0:
                    continue
                yield (new_row, new_col)
        
        # Check that the first and last cells are open. 
        if grid[0][0] != 0 or grid[max_row][max_col] != 0:
            return -1
        
        # Set up the BFS.
        queue = deque()
        queue.append((0, 0))
        grid[0][0] = 1 
        
        # Carry out the BFS.
        while queue:
            row, col = queue.popleft()
            distance = grid[row][col]
            if (row, col) == (max_row, max_col):
                return distance
            for neighbour_row, neighbour_col in get_neighbours(row, col):
                grid[neighbour_row][neighbour_col] = distance + 1
                queue.append((neighbour_row, neighbour_col))
        
        # There was no path.
        return -1


    def doit_bfs_2(self, grid: list) -> int:
        from collections import deque
        max_row = len(grid) - 1
        max_col = len(grid[0]) - 1
        directions = [
            (-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        
        # Helper function to find the neighbors of a given cell.
        def get_neighbours(row, col):
            for row_difference, col_difference in directions:
                new_row = row + row_difference
                new_col = col + col_difference
                if not(0 <= new_row <= max_row and 0 <= new_col <= max_col):
                    continue
                if grid[new_row][new_col] != 0:
                    continue
                yield (new_row, new_col)
        
        # Check that the first and last cells are open. 
        if grid[0][0] != 0 or grid[max_row][max_col] != 0:
            return -1
        
        # Set up the BFS.
        queue = deque([(0, 0, 1)])
        visited = {(0, 0)}
        
        # Do the BFS.
        while queue:
            row, col, distance = queue.popleft()
            if (row, col) == (max_row, max_col):
                return distance
            for neighbour in get_neighbours(row, col):
                if neighbour in visited:
                    continue
                visited.add(neighbour)
                # Note that the * splits neighbour into its values.
                queue.append((*neighbour, distance + 1))
                
        # There was no path.
        return -1


    def doit_bfs_2(self, grid: list) -> int:
        
        max_row = len(grid) - 1
        max_col = len(grid[0]) - 1
        directions = [
            (-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        
        # Helper function to find the neighbors of a given cell.
        def get_neighbours(row, col):
            for row_difference, col_difference in directions:
                new_row = row + row_difference
                new_col = col + col_difference
                if not(0 <= new_row <= max_row and 0 <= new_col <= max_col):
                    continue
                if grid[new_row][new_col] != 0:
                    continue
                yield (new_row, new_col)
        
        # Check that the first and last cells are open. 
        if grid[0][0] != 0 or grid[max_row][max_col] != 0:
            return -1
        
        # Set up the BFS.
        current_layer = [(0, 0)]
        next_layer = []
        visited = {(0, 0)}
        current_distance = 1
        
        while current_layer:
            
            # Process the current layer.
            for row, col in current_layer:
                if (row, col) == (max_row, max_col):
                    return current_distance
                for neighbour in get_neighbours(row, col):
                    if neighbour in visited:
                        continue
                    visited.add(neighbour)
                    next_layer.append(neighbour)
            
            # Set up for processing the next layer.
            current_distance += 1
            current_layer = next_layer
            next_layer = []
                
        # There was no path.
        return -1


    def doi_bfs_3(self, grid: list) -> int:  
        
        max_row = len(grid) - 1
        max_col = len(grid[0]) - 1
        directions = [
            (-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        
        # Helper function to find the neighbors of a given cell.
        def get_neighbours(row, col):
            for row_difference, col_difference in directions:
                new_row = row + row_difference
                new_col = col + col_difference
                if not(0 <= new_row <= max_row and 0 <= new_col <= max_col):
                    continue
                if grid[new_row][new_col] != 0:
                    continue
                yield (new_row, new_col)
        
        # Check that the first and last cells are open. 
        if grid[0][0] != 0 or grid[max_row][max_col] != 0:
            return -1
        
        # Set up the BFS.
        queue = deque([(0, 0)])
        visited = {(0, 0)}
        current_distance = 1
        
        # Do the BFS.
        while queue:
            # Process all nodes at current_distance from the top-left cell.
            nodes_of_current_distance = len(queue)
            for _ in range(nodes_of_current_distance):
                row, col = queue.popleft()
                if (row, col) == (max_row, max_col):
                    return current_distance
                for neighbour in get_neighbours(row, col):
                    if neighbour in visited:
                        continue
                    visited.add(neighbour)
                    queue.append(neighbour)
            # We'll now be processing all nodes at current_distance + 1
            current_distance += 1
                    
        # There was no path.
        return -1 