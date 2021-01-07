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
    Approach 4: Search Space Reduction
    Intuition

    Because the rows and columns of the matrix are sorted (from left-to-right and top-to-bottom, respectively), we can prune \mathcal{O}(m)O(m) or \mathcal{O}(n)O(n) elements when looking at any particular value.

    Algorithm

    First, we initialize a (row, col)(row,col) pointer to the bottom-left of the matrix.[1] Then, until we find target and return true (or the pointer points to a (row, col)(row,col) 
    that lies outside of the dimensions of the matrix), we do the following: if the currently-pointed-to value is larger than target we can move one row "up". 
    
    Otherwise, if the currently-pointed-to value is smaller than target, we can move one column "right". It is not too tricky to see why doing this will never prune the correct answer; 
    because the rows are sorted from left-to-right, we know that every value to the right of the current value is larger. 
    Therefore, if the current value is already larger than target, we know that every value to its right will also be too large. 
    A very similar argument can be made for the columns, so this manner of search will always find target in the matrix (if it is present).

    Check out some sample runs of the algorithm in the animation below:

    Complexity Analysis

    Time complexity : \mathcal{O}(n+m)O(n+m)

    The key to the time complexity analysis is noticing that, on every iteration (during which we do not return true) either row or col is is decremented/incremented exactly once. 
    Because row can only be decremented mm times and col can only be incremented nn times before causing the while loop to terminate, the loop cannot run for more than n+mn+m iterations. 
    Because all other work is constant, the overall time complexity is linear in the sum of the dimensions of the matrix.

    Space complexity : \mathcal{O}(1)O(1)

    Because this approach only manipulates a few pointers, its memory footprint is constant.
    """
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        # an empty matrix obviously does not contain `target` (make this check
        # because we want to cache `width` for efficiency's sake)
        if len(matrix) == 0 or len(matrix[0]) == 0:
            return False

        # cache these, as they won't change.
        height = len(matrix)
        width = len(matrix[0])

        # start our "pointer" in the bottom-left
        row = height - 1
        col = 0

        while col < width and row >= 0:
            if matrix[row][col] > target:
                row -= 1
            elif matrix[row][col] < target:
                col += 1
            else: # found it
                return True
        
        return False

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
                return search(r1, c1, r-1, c2) or search(r, c1, r2, c-1)
            
            return search(r+1, c1, r2, c2) or search(r1, c+1, r, c2)
            
        return search(0, 0, len(matrix)-1, len(matrix[0])-1)