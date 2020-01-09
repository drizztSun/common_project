# 840. Magic Squares In Grid

# A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9 such that each row, column, and both diagonals all have the same sum.

# Given an grid of integers, how many 3 x 3 "magic square" subgrids are there?  (Each subgrid is contiguous).


# Example 1:

# Input: [[4,3,8,4],
#         [9,5,1,9],
#         [2,7,6,2]]
# Output: 1
# Explanation:
# The following subgrid is a 3 x 3 magic square:
# 438
# 951
# 276

# while this one is not:
# 384
# 519
# 762

# In total, there is only one magic square inside the given grid.
# Note:

# 1 <= grid.length <= 10
# 1 <= grid[0].length <= 10
# 0 <= grid[i][j] <= 15


class NumMagicSquaresInside:

    def doit(self, grid):

        def magic(a, b, c, d, e, f, g, h, i):
            return (sorted([a, b, c, d, e, f, g, h, i]) == list(range(1, 10)) and
                    (a+b+c == d+e+f == g+h+i == a+d+g ==
                     b+e+h == c+f+i == a+e+i == c+e+g == 15))

        ans = 0
        for r in range(len(grid) - 2):
            for c in range(len(grid[0]) - 2):

                if grid[r+1][c+1] != 5:
                    continue

                if magic(grid[r][c], grid[r][c+1], grid[r][c+2],
                         grid[r+1][c], grid[r+1][c+1], grid[r+1][c+2],
                         grid[r+2][c], grid[r+2][c+1], grid[r+2][c+2]):
                    ans += 1

        return ans

    def doit__(self, grid):
        if len(grid) < 3 or len(grid[0]) < 3:
            return False

        buff = [0] * 10
        buff[0] = 1
        ans = 0

        for i in range(len(grid)-2):
            for j in range(len(grid[0])):

                if j >= 3:
                    buff[grid[i][j-3]] -= 1
                    buff[grid[i+1][j-3]] -= 1
                    buff[grid[i+2][j-3]] -= 1

                buff[grid[i][j]] += 1
                buff[grid[i+1][j]] += 1
                buff[grid[i+2][j]] += 1

                if buff == [1] * 10:
                    ans += 1

        return ans


if __name__ == '__main__':

    res = NumMagicSquaresInside().doit([[4, 3, 8, 4],
                                        [9, 5, 1, 9],
                                        [2, 7, 6, 2]])

    pass
