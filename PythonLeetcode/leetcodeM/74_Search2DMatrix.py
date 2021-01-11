"""
74. Search a 2D Matrix

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
 

Example 1:


Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true
Example 2:


Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-104 <= matrix[i][j], target <= 104

"""

class Search2DMatrix:

    def searchMatrix(self, matrix, target):
        """
        :type matrix: List[List[int]]
        :type target: int
        :rtype: bool
        """
        m, n = len(matrix), 0
        if m == 0:
            return False
        
        n = len(matrix[0])
        if n == 0:
            return False
            
        start, end = 0, m * n - 1
        mid = (start + end) / 2
        
        while start < end:
            x, y = mid / n, mid % n
            if matrix[x][y] < target:
                start = mid + 1
            elif matrix[x][y] > target:
                end = mid
            else:
                return True
   
            mid = (start + end) / 2
        
        return matrix[mid/n][mid%n] == target