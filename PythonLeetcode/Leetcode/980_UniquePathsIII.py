# 980. Unique Paths III

# On a 2-dimensional grid, there are 4 types of squares:

# 1 represents the starting square.  There is exactly one starting square.
# 2 represents the ending square.  There is exactly one ending square.
# 0 represents empty squares we can walk over.
# -1 represents obstacles that we cannot walk over.
# Return the number of 4-directional walks from the starting square to the ending square,
# that walk over every non-obstacle square exactly once.


# Example 1:

# Input: [[1,0,0,0],
#         [0,0,0,0],
#         [0,0,2,-1]]
# Output: 2
# Explanation: We have the following two paths:
# 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
# 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

# Example 2:

# Input: [[1,0,0,0],
#         [0,0,0,0],
#         [0,0,0,2]]
# Output: 4
# Explanation: We have the following four paths:
# 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
# 2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
# 3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
# 4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

# Example 3:

# Input: [[0,1],[2,0]]
# Output: 0
# Explanation:
# There is no path that walks over every empty square exactly once.
# Note that the starting and ending square can be anywhere in the grid.


class UniquePathsIII:

    def findSols(self, grid, py: int, px: int, numEsq: int) -> int:

        sol = 0
        gyx = grid[py][px]
        grid[py][px] = 3
        numEsq -= 1

        if numEsq == 0:
            if px > 0 and grid[py][px - 1] == 2:
                sol = 1
            elif px < len(grid[0]) - 1 and grid[py][px + 1] == 2:
                sol = 1
            elif py > 0 and grid[py - 1][px] == 2:
                sol = 1
            elif py < len(grid) - 1 and grid[py + 1][px] == 2:
                sol = 1
        elif numEsq > 0:
            if px > 0 and grid[py][px - 1] == 0: sol += self.findSols(grid, py, px - 1, numEsq)
            if px < len(grid[0]) - 1 and grid[py][px + 1] == 0: sol += self.findSols(grid, py, px + 1, numEsq)
            if py > 0 and grid[py - 1][px] == 0: sol += self.findSols(grid, py - 1, px, numEsq)
            if py < len(grid) - 1 and grid[py + 1][px] == 0: sol += self.findSols(grid, py + 1, px, numEsq)

        grid[py][px] = gyx
        return sol

    def doit1(self, grid) -> int:
        numEsq = 0
        sx = -1
        sy = -1

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 0:
                    numEsq += 1
                elif grid[i][j] == 1:
                    sy = i
                    sx = j

        return self.findSols(grid, sy, sx, numEsq + 1)


    def doit(self, grid):

        start = (0, 0)
        zeros = 0
        end = (0, 0)
        self.ans = 0

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 0:
                    zeros += 1
                elif grid[i][j] == 1:
                    start = (i, j)
                elif grid[i][j] == 2:
                    end = (i, j)

        self.seen = [[0 for _ in range(len(grid[0]))] for _ in range(len(grid))]


        def search(i, j, num):

            if (i, j) == end:
                self.ans += 1 if num == 0 else 0
                return

            for c in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                x, y = i + c[0], j + c[1]
                base = x * len(grid[0]) + y
                if 0 <= x < len(grid) and 0 <= y < len(grid[0]) and grid[x][y] != -1 and self.seen[x][y] == 0:
                    self.seen[x][y] = 1
                    search(x, y, num - 1)
                    self.seen[x][y] = 0

        self.seen[start[0]][start[1]] = 1
        search(start[0], start[1], zeros + 1)
        return self.ans

"""

Overview
Whenever we see the context of grid traversal, the technique of backtracking or DFS (Depth-First Search) should ring a bell.

In terms of this problem, it fits the bill perfectly, with a canonical setting, unlike another similar problem called robot room cleaner which has certain twists.

As a reminder, backtracking is a general algorithm for finding all (or some) solutions to some problems with constraints. It incrementally builds candidates to the solutions, 
and abandons a candidate as soon as it determines that the candidate cannot possibly lead to a solution.

In this article, we will showcase how to apply the backtracking algorithm to solve this problem.

Approach 1: Backtracking
Intuition

We can consider backtracking as a state machine, where we start off from an initial state, each action we take will move the state from one to another, and there should be some final state where we reach our goal.

As a result, let us first clarify the initial and the final states of the problem.

Initial State

There are different types of squares/cells in a grid.

There are an origin and a destination cell, which are not given explicitly.

Initially, all the cells are not visited.

Final State

We reach the destination cell, i.e. cell filled with the value 2.

We have visited all the non-obstacle cells, including the empty cells (i.e. filled with 0) and the initial cell (i.e. 1).

With the above definition, we can then translate the problem as finding all paths that can lead us from the initial state to the final state.

state machine

More specifically, we could summarise the steps to implement the backtracking algorithm for this problem in the following pseudo code.


    def backtrack(cell):
        1. if we arrive at the final state:
             path_count ++
             return

        2. mark the current cell as visited

        3. for next_cell in 4 directions:
             if next_cell is not visited and non-obstacle:
                 backtrack(next_cell)

        4. unmark the current cell
map

Algorithm

As one can see, backtracking is more of a methodology to solve a specific type of problems. For a backtracking problem, 
it would not be exaggerating to say that there are a thousand backtracking implementations in a thousand people's eyes, as one would find out in the implementation later.

Here we would simply show one example of implementation, following the pseudo code shown in the intuition section.

Here we would like to highlight some important design decisions we took in the above implementation. As one can imagine, with different decisions, one would have variations of backtracking implementations.

In-place Modification

This is an important technique that allows us to save some space in the algorithm.

In order to mark the cell as visited, often the case we use some matrix or hashtable with boolean values to keep track of the state of each cell, i.e. whether it is visited or not.

With the in-place technique, we simply assign a specific value to the cell in the grid, rather than creating an additional matrix or hashtable.

Boundary Check

There are several boundary conditions that we could check during the backtracking, namely whether the coordinate of a cell is valid or not and whether the current cell is visited or not.

We could do the checking right before we make the recursive call, or at the beginning of the backtrack function.

We decided to go with the former one, which could save us some recursive calls when the boundary check does not pass.

Complexity Analysis

Let NN be the total number of cells in the input grid.

Time Complexity: \mathcal{O}(3^N)O(3 
N
 )

Although technically we have 4 directions to explore at each step, we have at most 3 directions to try at any moment except the first step. The last direction is the direction where we came from, therefore we don't need to explore it, since we have been there before.

In the worst case where none of the cells is an obstacle, we have to explore each cell. Hence, the time complexity of the algorithm is \mathcal{O}(4 * 3 ^{(N-1)}) = \mathcal{O}(3^N)O(4∗3 
(N−1)
 )=O(3 
N
 ).

Space Complexity: \mathcal{O}(N)O(N)

Thanks to the in-place technique, we did not use any additional memory to keep track of the state.

On the other hand, we apply recursion in the algorithm, which could incur \mathcal{O}(N)O(N) space in the function call stack.

Hence, the overall space complexity of the algorithm is \mathcal{O}(N)O(N).

"""

    def doit2(self, grid):

        rows, cols = len(grid), len(grid[0])

        # step 1). initialize the conditions for backtracking
        #   i.e. initial state and final state
        non_obstacles = 0
        start_row, start_col = 0, 0
        for row in range(0, rows):
            for col in range(0, cols):
                cell = grid[row][col]
                if  cell >= 0:
                    non_obstacles += 1
                if cell == 1:
                    start_row, start_col = row, col

        # count of paths as the final result
        path_count = 0

        # step 2). backtrack on the grid
        def backtrack(row, col, remain):
            # we need to modify this external variable
            nonlocal path_count

            # base case for the termination of backtracking
            if grid[row][col] == 2 and remain == 1:
                # reach the destination
                path_count += 1
                return

            # mark the square as visited. case: 0, 1, 2
            temp = grid[row][col]
            grid[row][col] = -4
            remain -= 1   # we now have one less square to visit

            # explore the 4 potential directions around
            for ro, co in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                next_row, next_col = row + ro, col + co

                if not (0 <= next_row < rows and 0 <= next_col < cols):
                    # invalid coordinate
                    continue
                if grid[next_row][next_col] < 0:
                    # either obstacle or visited square
                    continue

                backtrack(next_row, next_col, remain)

            # unmark the square after the visit
            grid[row][col] = temp

        backtrack(start_row, start_col, non_obstacles)

        return path_count


if __name__ == "__main__":

    res = UniquePathsIII().doit([[1, 0, 0, 0], [0, 0, 0, 0], [0, 0, 2, -1]])

    res = UniquePathsIII().doit([[1, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 2]])

    res = UniquePathsIII().doit([[0,1],[2,0]])

    pass
