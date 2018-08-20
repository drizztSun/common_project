# 749. Contain Virus

# A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.

# The world is modeled as a 2-D array of cells, where 0 represents uninfected cells,
# and 1 represents cells contaminated with the virus.
# A wall (and only one wall) can be installed between any two 4-directionally adjacent cells, on the shared boundary.

# Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall.
# Resources are limited. Each day, you can install walls around only one region
# -- the affected area (continuous block of infected cells)
# that threatens the most uninfected cells the following night. There will never be a tie. 

# Can you save the day? If so, what is the number of walls required?
#  If not, and the world becomes fully infected, return the number of walls used.

# Example 1:
# Input: grid = 
# [[0,1,0,0,0,0,0,1],
#  [0,1,0,0,0,0,0,1],
#  [0,0,0,0,0,0,0,1],
#  [0,0,0,0,0,0,0,0]]
# Output: 10
# Explanation:
# There are 2 contaminated regions.
# On the first day, add 5 walls to quarantine the viral region on the left. The board after the virus spreads is:


# [[0,1,0,0,0,0,1,1],
#  [0,1,0,0,0,0,1,1],
#  [0,0,0,0,0,0,1,1],
#  [0,0,0,0,0,0,0,1]]

# On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.

# Example 2:
# Input: grid = 
# [[1,1,1],
#  [1,0,1],
#  [1,1,1]]
# Output: 4
# Explanation: Even though there is only one cell saved, there are 4 walls built.

# Notice that walls are only built on the shared boundary of two different cells.
# Example 3:
# Input: grid = 
# [[1,1,1,0,0,0,0,0,0],
#  [1,0,1,0,1,1,1,1,1],
#  [1,1,1,0,0,0,0,0,0]]
# Output: 13
# Explanation: The region on the left only builds two new walls.


# Note:
# The number of rows and columns of grid will each be in the range [1, 50].
# Each grid[i][j] will be either 0 or 1.
# Throughout the described process, there is always a contiguous viral region
# that will infect strictly more uncontaminated squares in the next round.


import collections


class ContainVirus:
    def doit(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        M, N = len(grid), len(grid[0])
        ds = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        def getgroups():
            groups = []
            visited = set()

            for m in range(M):
                for n in range(N):
                    if grid[m][n] != 1 or (m, n) in visited:
                        continue

                    group = set()
                    q = [(m, n)]
                    while q:
                        x, y = q.pop()
                        group.add((x, y))
                        visited.add((x, y))

                        for dx, dy in ds:
                            xx, yy = x + dx, y + dy
                            if 0 <= xx < M and 0 <= yy < N and grid[xx][yy] == 1 and (xx, yy) not in visited:
                                q.append((xx, yy))
                                visited.add((xx, yy))

                    groups.append(group)
            return groups

        def expand(group):
            ct = collections.Counter()
            for (x, y) in group:
                for (dx, dy) in ds:
                    xx, yy = dx + x, dy + y
                    if 0 <= xx < M and 0 <= yy < N and grid[xx][yy] == 0:
                        ct[(xx, yy)] += 1
            return ct

        groups = getgroups()
        nwalls = 0

        while groups:

            if sum(len(p) for p in groups) == M * N:
                return nwalls

            walls = [expand(p) for p in groups]
            maxi, maxv = -1, 0

            for i in range(len(walls)):
                if len(walls[i]) > maxv:
                    maxi, maxv = i, len(walls[i])

            for (x, y) in groups[maxi]:
                grid[x][y] = 2

            nwalls += sum(walls[maxi].values())
            walls = walls[:maxi] + walls[maxi + 1:]

            for wall in walls:
                for (x, y) in wall:
                    grid[x][y] = 1

            groups = getgroups()

        return nwalls


if __name__ == "__main__":

    grid = [[1, 1, 1],
            [1, 0, 1],
            [1, 1, 1]]

    res = ContainVirus().doit(grid)

    grid = [[0,1,0,0,0,0,0,1],
            [0,1,0,0,0,0,0,1],
            [0,0,0,0,0,0,0,1],
            [0,0,0,0,0,0,0,0]]

    res = ContainVirus().doit(grid)

    grid = [[1,1,1,0,0,0,0,0,0],
            [1,0,1,0,1,1,1,1,1],
            [1,1,1,0,0,0,0,0,0]]

    res = ContainVirus().doit(grid)

    pass