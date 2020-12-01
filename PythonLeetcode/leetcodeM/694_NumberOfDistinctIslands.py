"""
694. Number of Distinct Islands

Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.)
You may assume all four edges of the grid are surrounded by water.

Count the number of distinct islands. An island is considered to be the same as another if and only if
one island can be translated (and not rotated or reflected) to equal the other.

Example 1:
11000
11000
00011
00011
Given the above grid map, return 1.
Example 2:
11011
10000
00001
11011
Given the above grid map, return 3.

Notice that:
11
1
and
 1
11
are considered different island shapes, because we do not consider reflection / rotation.
Note: The length of each dimension in the given grid does not exceed 50.
"""


class NumDistinctIslands:

    """
    Approach #1: Hash By Local Coordinates [Accepted]
    Intuition and Algorithm

    At the beginning, we need to find every island, which we can do using a straightforward depth-first search. The hard part is deciding whether two islands are the same.

    Since two islands are the same if one can be translated to match another, let's translate every island so the top-left corner is (0, 0)
    For example, if an island is made from squares [(2, 3), (2, 4), (3, 4)], we can think of this shape as [(0, 0), (0, 1), (1, 1)] when anchored at the top-left corner.

    From there, we only need to check how many unique shapes there ignoring permutations (so [(0, 0), (0, 1)] is the same as [(0, 1), (1, 0)]).
    We use sets directly as we have showcased below, but we could have also sorted each list and put those sorted lists in our set structure shapes.

    In the Java solution, we converted our tuples (r - r0, c - c0) to integers. We multiplied the number of rows by 2 * grid[0].length instead of grid[0].length
    because our local row-coordinate could be negative.

    Complexity Analysis

    Time Complexity: O(R∗C), where RR is the number of rows in the given grid, and CC is the number of columns. We visit every square once.
    Space complexity: O(R∗C), the space used by seen to keep track of visited squares, and shapes.
    """

    def doit_(self, grid: list) -> int:

        seen = {}
        sharps = {}

        def execute(x, y, memo, c0, c1):
            if 0 <= x < len(grid) and 0 <= y < len(grid[0]) and grid[x][y] and (x, y) not in seen:
                seen.add((x, y))
                memo.add((x-c0, y-c1))
                execute(x-1, y, memo, c0, c1)
                execute(x+1, y, memo, c0, c1)
                execute(x, y-1, memo, c0, c1)
                execute(x, y+1, memo, c0, c1)

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if (i, j) not in seen:
                    sharp = {}
                    execute(i, j, sharp, i, j)
                    if sharp:
                        sharps.add(frozenset(sharp))

        return len(sharps)

    """
    Approach #2: Hash By Path Signature [Accepted]
    Intuition and Algorithm
    
    When we start a depth-first search on the top-left square of some island, the path taken by our depth-first search will be the same 
    if and only if the shape is the same. We can exploit this by recording the path we take as our shape - keeping in mind to record both when we enter and when we exit the function. 
    The rest of the code remains as in Approach #1.
    
    Complexity Analysis

    Time Complexity: O(R∗C), where RR is the number of rows in the given grid, and CC is the number of columns. We visit every square once.
    Space complexity: O(R∗C), the space used by seen to keep track of visited squares, and shapes.
    """
    def doit_1(self, grid):

        seen = set()

        def explore(r, c, di = 0):
            if 0 <= r < len(grid) and 0 <= c < len(grid[0]) and grid[r][c] and (r, c) not in seen:
                seen.add((r, c))
                shape.append(di)
                explore(r+1, c, 1)
                explore(r-1, c, 2)
                explore(r, c+1, 3)
                explore(r, c-1, 4)
                shape.append(0)

        shapes = set()
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                shape = []
                explore(r, c)
                if shape:
                    shapes.add(tuple(shape))

        return len(shapes)
