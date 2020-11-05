"""
711. Number of Distinct Islands II

Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.)
You may assume all four edges of the grid are surrounded by water.

Count the number of distinct islands. An island is considered to be the same as another if they have the same shape,
or have the same shape after rotation (90, 180, or 270 degrees only) or reflection (left/right direction or up/down direction).

Example 1:
11000
10000
00001
00011
Given the above grid map, return 1.

Notice that:
11
1
and
 1
11
are considered same island shapes. Because if we make a 180 degrees clockwise rotation on the first island, then two islands will have the same shapes.
Example 2:
11100
10001
01001
01110
Given the above grid map, return 2.

Here are the two distinct islands:
111
1
and
1
1

Notice that:
111
1
and
1
111
are considered same island shapes. Because if we flip the first array in the up/down direction, then they have the same shapes.
"""


class NumDistinctIslands2:

    def doit(self, grid: list) -> int:
        R = len(grid)
        if R == 0:
            return 0
        C = len(grid[0])
        if C == 0:
            return 0

        def dfs(r, c):
            shape = []
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                shape.append((r, c))
                if r - 1 >= 0 and grid[r - 1][c]:
                    grid[r - 1][c] = 0
                    stack.append((r - 1, c))
                if r + 1 < R and grid[r + 1][c]:
                    grid[r + 1][c] = 0
                    stack.append((r + 1, c))
                if c - 1 >= 0 and grid[r][c - 1]:
                    grid[r][c - 1] = 0
                    stack.append((r, c - 1))
                if c + 1 < C and grid[r][c + 1]:
                    grid[r][c + 1] = 0
                    stack.append((r, c + 1))
            return standarize(shape)

        def standarize(shape):
            shape = sorted(shape)
            min_r, min_c = shape[0]
            return tuple([(r - min_r, c - min_c) for r, c in shape])

        shapes = set()

        def addShape(shape):
            shapes.add(shape)
            shapes.add(standarize([(+r, -c) for r, c in shape]))
            shapes.add(standarize([(-r, +c) for r, c in shape]))
            shapes.add(standarize([(-r, -c) for r, c in shape]))
            shapes.add(standarize([(+c, -r) for r, c in shape]))
            shapes.add(standarize([(+c, +r) for r, c in shape]))
            shapes.add(standarize([(-c, -r) for r, c in shape]))
            shapes.add(standarize([(-c, +r) for r, c in shape]))

        ans = 0
        for r in range(R):
            for c in range(C):
                if grid[r][c]:
                    grid[r][c] = 0
                    shape = dfs(r, c)
                    if shape not in shapes:
                        ans += 1
                        addShape(shape)
        return ans

    """
    Approach #1: Canonical Hash [Accepted]
    Intuition

    As in Approach #1 to the sister problem Number of Distinct Islands, we determine local coordinates for each island.

    Afterwards, we will rotate and reflect the coordinates about the origin and translate the shape so that the bottom-left-most coordinate is (0, 0).
    At the end, the smallest of these lists coordinates will be the canonical representation of the shape.

    Algorithm

    We feature two different implementations, but the core idea is the same. We start with the code from the previous problem, Number of Distinct Islands.

    For each of 8 possible rotations and reflections of the shape, we will perform the transformation and then translate the shape so that the bottom-left-most coordinate is (0, 0).
    Afterwards, we will consider the canonical hash of the shape to be the maximum of these 8 intermediate hashes.

    In Python, the motivation to use complex numbers is that rotation by 90 degrees is the same as multiplying by the imaginary unit, 1j.
    In Java, we manipulate the coordinates directly. The 8 rotations and reflections of each point are (x, y), (-x, y), (x, -y), (-x, -y), (y, x), (-y, x), (y, -x), (-y, -x).

    """
    def doit_(self, grid: list) -> int:

        seen = set()
        def explore(r, c):
            if (0 <= r < len(grid) and 0 <= c < len(grid[0]) and
                    grid[r][c] and (r, c) not in seen):
                seen.add((r, c))
                shape.add(complex(r, c))
                explore(r+1, c)
                explore(r-1, c)
                explore(r, c+1)
                explore(r, c-1)

        def canonical(shape):
            def translate(shape):
                w = complex(min(z.real for z in shape),
                            min(z.imag for z in shape))
                return tuple(sorted(str(z-w) for z in shape))

            ans = tuple()
            for k in range(4):
                ans = max(ans, translate([z * (1j)**k for z in shape]))
                ans = max(ans,  translate([complex(z.imag, z.real) * (1j)**k
                                           for z in shape]))
            return ans

        shapes = set()
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                shape = set()
                explore(r, c)
                if shape:
                    shapes.add(canonical(shape))

        return len(shapes)