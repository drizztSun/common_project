# 1001. Grid Illumination

# On a N x N grid of cells, each cell (x, y) with 0 <= x < N and 0 <= y < N has a lamp.

# Initially, some number of lamps are on.  lamps[i] tells us the location of the i-th lamp that is on.
# Each lamp that is on illuminates every square on its x-axis, y-axis, and both diagonals (similar to a Queen in chess).

# For the i-th query queries[i] = (x, y), the answer to the query is 1 if the cell (x, y) is illuminated, else 0.

# After each query (x, y) [in the order given by queries], we turn off any lamps that are at cell (x, y)
# or are adjacent 8-directionally (ie., share a corner or edge with cell (x, y).)

# Return an array of answers.  Each value answer[i] should be equal to the answer of the i-th query queries[i].


# Example 1:

# Input: N = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
# Output: [1,0]
# Explanation:
# Before performing the first query we have both lamps [0,0] and [4,4] on.
# The grid representing which cells are lit looks like this, where [0,0] is the top left corner, and [4,4] is the bottom right corner:
# 1 1 1 1 1
# 1 1 0 0 1
# 1 0 1 0 1
# 1 0 0 1 1
# 1 1 1 1 1
# Then the query at [1, 1] returns 1 because the cell is lit.  After this query, the lamp at [0, 0] turns off, and the grid now looks like this:
# 1 0 0 0 1
# 0 1 0 0 1
# 0 0 1 0 1
# 0 0 0 1 1
# 1 1 1 1 1
# Before performing the second query we have only the lamp [4,4] on.  Now the query at [1,0] returns 0, because the cell is no longer lit.


# Note:

# 1 <= N <= 10^9
# 0 <= lamps.length <= 20000
# 0 <= queries.length <= 20000
# lamps[i].length == queries[i].length == 2

from collections import Counter


class GridIllumination:
    def doit(self, N, lamps, queries):
        """
        :type N: int
        :type lamps: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        lamps = {(light[0], light[1]) for light in lamps}
        rows = collections.defaultdict(int)
        cols = collections.defaultdict(int)
        diag1 = collections.defaultdict(int)
        diag2 = collections.defaultdict(int)

        for i, j in lamps:
            rows[i] += 1
            cols[j] += 1
            diag1[i - j] += 1
            diag2[i + j] += 1

        res = []

        for i, j in queries:
            # print(i,j)
            lit = rows[i] + cols[j] + diag1[i - j] + diag2[i + j]
            if lit > 0:
                res.append(1)
                # we turn off any lamps that are at cell (x, y) or are adjacent 8-directionally, row (i-1 to i+1), col (j-1 to j+1)
                for x in range(i - 1, i + 2):
                    for y in range(j - 1, j + 2):
                        if (x, y) in lamps:
                            lamps.remove((x, y))
                            rows[x] -= 1
                            cols[y] -= 1
                            diag1[x - y] -= 1
                            diag2[x + y] -= 1
            else:
                res.append(0)

        return res

    def doit(self, N, lamps, queries):
        def p(x, y, N):
            return (x - min(x, y), y - min(x, y))

        def q(x, y, N):
            return (x - min(x, N - 1 - y), y + min(x, N - 1 - y))

        def process(x, y):
            res = 1 if any([row[x], col[y], ld[p(x, y, N)], rd[q(x, y, N)]]) else 0

            for d1 in (-1, 0, 1):
                for d2 in (-1, 0, 1):
                    x0, y0 = x + d1, y + d1
                    if [x0, y0] in lamps:
                        lamps.remove([x0, y0])
                        row[x0] -= 1
                        col[y0] -= 1
                        ld[p(x0, y0, N)] -= 1
                        rd[q(x0, y0, N)] -= 1

            return res

        col, row, ld, rd = Counter(), Counter(), Counter(), Counter()

        for (x, y) in lamps:
            col[x] += 1
            row[y] += 1
            ld[p(x, y, N)] += 1
            rd[q(x, y, N)] += 1

        return [process(x, y) for x, y in queries]

    def doit(self, N, lamps, queries):

        rows, cols = [0 for _ in range(N)], [0 for _ in range(N)]
        dd, rd = [0 for _ in range(N * 2 - 1)], [0 for _ in range(N * 2 - 1)]

        index_dd = lambda x, y: N - 1 - y + x
        index_rd = lambda x, y: x + y

        for x, y in lamps:

            rows[x] += 1
            cols[y] += 1
            dd[index_dd(x, y)] += 1
            rd[index_rd(x, y)] += 1

        res = []

        for x, y in queries:

            if rows[x] + cols[y] + dd[index_dd(x, y)] + rd[index_rd(x, y)] == 1:
                res.append(0)
                continue

            for d1 in (-1, 0, 1):
                for d2 in (-1, 0, 1):
                    x0, y0 = x + d1, y + d2
                    if [x0, y0] in lamps:
                        lamps.remove([x0, y0])
                        rows[x0] -= 1
                        cols[y0] -= 1
                        dd[index_dd(x0, y0)] -= 1
                        rd[index_rd(x0, y0)] -= 1

            res.append(1)

        return res


if __name__ == "__main__":

    res = GridIllumination().doit(
        N=5, lamps=[[0, 0], [4, 4]], queries=[[1, 1], [1, 0]]
    )  # [1, 0]

    res = GridIllumination().doit(
        5, [[0, 0], [0, 4]], [[0, 4], [0, 1], [1, 4]]
    )  # [1,1,0]

    pass
