# 1252. Cells with Odd Values in a Matrix

# Given n and m which are the dimensions of a matrix initialized by zeros and given an array indices where indices[i] = [ri, ci].
# For each pair of [ri, ci] you have to increment all cells in row ri and column ci by 1.

# Return the number of cells with odd values in the matrix after applying the increment to all indices.

# Example 1:
# Input: n = 2, m = 3, indices = [[0,1],[1,1]]
# Output: 6
# Explanation: Initial matrix = [[0,0,0],[0,0,0]].
# After applying first increment it becomes [[1,2,1],[0,1,0]].
# The final matrix will be [[1,3,1],[1,3,1]] which contains 6 odd numbers.

# Example 2:
# Input: n = 2, m = 2, indices = [[1,1],[0,0]]
# Output: 0
# Explanation: Final matrix = [[2,2],[2,2]]. There is no odd number in the final matrix.


# Constraints:

# 1 <= n <= 50
# 1 <= m <= 50
# 1 <= indices.length <= 100
# 0 <= indices[i][0] < n
# 0 <= indices[i][1] < m

class OddCells:

    def doit(self, n, m, indices):
        d1 = collections.Counter([i for i, j in indices])
        d2 = collections.Counter([j for i, j in indices])
        return sum([1 if (d1[i] + d2[j]) % 2 else 0 for i in range(n) for j in range(m)])

    def doit(self, n, m, indices):
        rows = [0] * n
        cols = [0] * m
        for x, y in indices:
            rows[x] += 1
            cols[y] += 1
        odd_rows = sum(row % 2 == 1 for row in rows)
        odd_cols = sum(col % 2 == 1 for col in cols)
        return odd_rows * (m - odd_cols) + odd_cols * (n - odd_rows)

    def doit(self, n, m, indices):
        matrix = [[0 for _ in range(m)] for _ in range(n)]
        odds = set()

        for c in indices:

            for i in range(m):
                matrix[c[0]][i] += 1
                if matrix[c[0]][i] % 2 != 0:
                    odds.add((c[0], i))
                else:
                    odds.remove((c[0], i))

            for i in range(n):
                matrix[i][c[1]] += 1
                if matrix[i][c[1]] % 2 != 0:
                    odds.add((i, c[1]))
                else:
                    odds.remove((i, c[1]))

        return len(odds)


if __name__ == '__main__':

    res = OddCells().doit(n=2, m=3, indices=[[0, 1], [1, 1]])  # 6

    res = OddCells().doit(n=2, m=2, indices=[[1, 1], [0, 0]])  # 0

    pass
