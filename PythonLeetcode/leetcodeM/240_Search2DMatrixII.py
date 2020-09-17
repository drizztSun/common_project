"""
240. Search a 2D Matrix II

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
Example:

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Given target = 5, return true.

Given target = 20, return false.

"""


class SearchMatrixII:

    """
    start from top right
    if the value equals target return 1
    if value less than target, increase i(index of row) by 1
    if value is greater than target, decrease j(index of column) by 1
    """
    def doit(self, matrix, target):
        """
        :type matrix: List[List[int]]
        :type target: int
        :rtype: bool
        """
        if len(matrix) < 1 or len(matrix[0]) < 1:
            return False

        m, n = len(matrix), len(matrix[0])
        row, col = 0, n - 1
        while row < m and col >= 0:
            if matrix[row][col] < target:
                row += 1
            elif matrix[row][col] > target:
                col -= 1
            else:
                return True

        return False

    def doit_divide_and_conquer(self, matrix, target):
        if not matrix:
            return False

        def search(r1, c1, r2, c2):
            if r1 > r2 or c1 > c2:
                return False
            r, c = (r2 + r1) // 2, (c2 + c1) // 2

            if matrix[r][c] == target:
                return True

            if matrix[r][c] > target:
                m1 = search(r1, c1, r - 1, c2)
                if m1:
                    return True
                m2 = search(r, c1, r2, c - 1)
            else:
                m1 = search(r1, c + 1, r, c2)
                if m1:
                    return True
                m2 = search(r + 1, c1, r2, c2)

            return m2

        return search(0, 0, len(matrix) - 1, len(matrix[0]) - 1)

    def doit_divide_and_conquer(self, matrix, target):
        """
        :type matrix: List[List[int]]
        :type target: int
        :rtype: bool
        """
        if len(matrix) == 0 or len(matrix[0]) == 0:
            return False

        def search(r1, c1, r2, c2):

            if r1 > r2 or c1 > c2:
                return False

            r, c = (r1 + r2) // 2, (c1 + c2) // 2

            if matrix[r][c] == target:
                return True

            if matrix[r][c] > target:
                return search(r1, c1, r - 1, c2) or search(r, c1, r2, c - 1)

            return search(r + 1, c1, r2, c2) or search(r1, c + 1, r, c2)

        return search(0, 0, len(matrix) - 1, len(matrix[0]) - 1)