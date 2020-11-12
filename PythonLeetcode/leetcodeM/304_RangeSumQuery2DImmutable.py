"""
304. Range Sum Query 2D - Immutable

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.

"""


class NumMatrixII:

    def __init__(self, matrix):
        """
        :type matrix: List[List[int]]
        """
        self._m = len(matrix)

        if self._m == 0:
            self._n = 0
            return

        self._n = len(matrix[0])
        self._mRec = [[0 for x in range(self._n)] for y in range(self._m)]

        self._mRec[0][0] = matrix[0][0]
        for j in range(1, self._n):
            self._mRec[0][j] = matrix[0][j] + self._mRec[0][j - 1]

        for i in range(1, self._m):
            sum = 0
            for j in range(self._n):
                sum += matrix[i][j]
                self._mRec[i][j] = sum + self._mRec[i - 1][j]

    def sumRegion(self, row1, col1, row2, col2):
        """
        :type row1: int
        :type col1: int
        :type row2: int
        :type col2: int
        :rtype: int
        """
        if row2 >= self._m and col2 >= self._n:
            return 0

        S3, S2, S1 = 0, 0, 0

        if row1 != 0:
            S2 = self._mRec[row1 - 1][col2]
        if col1 != 0:
            S3 = self._mRec[row2][col1 - 1]
        if row1 != 0 and col1 != 0:
            S1 = self._mRec[row1 - 1][col1 - 1]

        return self._mRec[row2][col2] - S3 - S2 + S1