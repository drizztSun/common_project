# 1030. Matrix Cells in Distance Order

# We are given a matrix with R rows and C columns has cells with integer coordinates (r, c),
# where 0 <= r < R and 0 <= c < C.

# Additionally, we are given a cell in that matrix with coordinates (r0, c0).

# Return the coordinates of all cells in the matrix, sorted by their distance from (r0, c0) from smallest distance to largest distance.
# Here, the distance between two cells (r1, c1) and (r2, c2) is the Manhattan distance, |r1 - r2| + |c1 - c2|.  (You may return the answer in any order that satisfies this condition.)


# Example 1:

# Input: R = 1, C = 2, r0 = 0, c0 = 0
# Output: [[0,0],[0,1]]
# Explanation: The distances from (r0, c0) to other cells are: [0,1]

# Example 2:

# Input: R = 2, C = 2, r0 = 0, c0 = 1
# Output: [[0,1],[0,0],[1,1],[1,0]]
# Explanation: The distances from (r0, c0) to other cells are: [0,1,1,2]
# The answer [[0,1],[1,1],[0,0],[1,0]] would also be accepted as correct.

# Example 3:

# Input: R = 2, C = 3, r0 = 1, c0 = 2
# Output: [[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
# Explanation: The distances from (r0, c0) to other cells are: [0,1,1,2,2,3]
# There are other answers that would also be accepted as correct, such as [[1,2],[1,1],[0,2],[1,0],[0,1],[0,0]].


# Note:

# 1 <= R <= 100
# 1 <= C <= 100
# 0 <= r0 < R
# 0 <= c0 < C

class AllCellsDistOrder:

    def doit(self, R: int, C: int, r0: int, c0: int):

        m = [[0 for _ in range(C)] for _ in range(R)]
        ans = []
        buff = [(r0, c0)]
        m[r0][c0] = 1

        while buff:

            tmp = []

            for x, y in buff:
                ans.append([x, y])

                for x1, y1 in [(x-1, y), (x+1, y), (x, y-1), (x, y+1)]:
                    if 0 <= x1 < R and 0 <= y1 < C and m[x1][y1] == 0:
                        tmp.append((x1, y1))
                        m[x1][y1] = 1

            buff = tmp

        return ans

    def doit(self, R, C, r0, c0):

        pos = [(i, j) for i in range(R) for j in range(C)]

        return sorted(pos, key=lambda x: abs(x[0]-r0) + abs(x[1]-c0))


if __name__ == '__main__':

    res = AllCellsDistOrder().doit(R=1, C=2, r0=0, c0=0)

    res = AllCellsDistOrder().doit(R=2, C=2, r0=0, c0=1)

    res = AllCellsDistOrder().doit(R=2, C=3, r0=1, c0=2)

    pass
