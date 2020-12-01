"""
311. Sparse Matrix Multiplication

Given two sparse matrices A and B, return the result of AB.

You may assume that A's column number is equal to B's row number.

Example:

Input:

A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]

B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]

Output:

     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |


Constraints:

1 <= A.length, B.length <= 100
1 <= A[i].length, B[i].length <= 100
-100 <= A[i][j], B[i][j] <= 100


"""


class SquareMatrixMultiply:

    def doit(self, A: list, B: list) -> list:

        def get_prod(A, B, r, c):
            cur = 0
            for x in range(0, len(A[0])):
                cur += A[r][x] * B[x][c]
            return cur

        res = [[0 for i in range(len(B[0]))] for j in range(len(A))]

        for r in range(0, len(A)):
            for c in range(0, len(B[0])):
                res[r][c] = get_prod(A, B, r, c)

        return res


