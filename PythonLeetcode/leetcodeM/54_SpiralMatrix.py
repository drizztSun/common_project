"""
54. Spiral Matrix

Given an m x n matrix, return all elements of the matrix in spiral order.

 

Example 1:


Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:


Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100
"""

class SpiralMatrix:

    def doit_(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[int]
        """
        m = len(matrix)
        if m == 0:
            return []
            
        result, n = [], len(matrix[0])
        rowBen, rowEnd, colBen, colEnd = 0, m-1, 0, n-1

        while rowBen <= rowEnd and colBen <= colEnd:
            j = colBen
            while j <= colEnd:
                result.append(matrix[rowBen][j])
                j += 1    
            rowBen += 1

            i = rowBen
            while i <= rowEnd:
                result.append(matrix[i][colEnd])
                i += 1
            colEnd -= 1

            if rowBen <= rowEnd :
                j = colEnd
                while j >= colBen:
                    result.append(matrix[rowEnd][j])
                    j -= 1
                rowEnd -= 1
            
            if colBen <= colEnd:
                i = rowEnd
                while i >= rowBen:
                    result.append(matrix[i][colBen])
                    i -= 1
                colBen += 1

        return result