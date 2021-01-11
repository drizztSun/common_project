"""
48. Rotate Image

You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. 
DO NOT allocate another 2D matrix and do the rotation.

 

Example 1:


Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]
Example 2:


Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
Example 3:

Input: matrix = [[1]]
Output: [[1]]
Example 4:

Input: matrix = [[1,2],[3,4]]
Output: [[3,1],[4,2]]
 

Constraints:

matrix.length == n
matrix[i].length == n
1 <= n <= 20
-1000 <= matrix[i][j] <= 1000

"""

class Rotate(object):

    """
        Approach 1 : Transpose and then reverse
        The obvious idea would be to transpose the matrix first and then reverse each row. 
        This simple approach already demonstrates the best possible time complexity O(N 2). 
        Here is a visualization of why this approach works on a sample matrix.

        Time complexity : O(N ^ 2)
        Space complexity : O(1) since we do a rotation in place.
    """
    def rotate(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: void Do not return anything, modify matrix in-place instead.
        """
        n = len(matrix[0])
        # transpose matrix
        for i in range(n):
            for j in range(i, n):
                matrix[j][i], matrix[i][j] = matrix[i][j], matrix[j][i]

        # reverse each row
        for i in range(n):
            matrix[i].reverse()

    """
        Approach 3 : Rotate four rectangles in one single loop
        The idea is the same as in the approach 2, but everything is done in one single loop and hence it's a way more elegant (kudos go to @gxldragon).
        Time complexity : O(N^2) is a complexity given by two inserted loops.
        Space complexity : O(1) since we do a rotation in place.
    """
    def rotate(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: void Do not return anything, modify matrix in-place instead.
        """
        i, mid, n = 0, len(matrix) / 2, len(matrix)
        while i < mid:
            j = 0
            end = n - i - 1 - i
            while j < end:
                a = matrix[i][i + j]
                matrix[i][i + j] = matrix[n-i-1-j][i]
                matrix[n-i-1-j][i] = matrix[n-i-1][n-i-1-j]
                matrix[n-i-1][n-i-1-j] = matrix[i + j][n-i-1]
                matrix[i + j][n-i-1] = a
                j += 1
            i += 1
    
    """
        Approach 2 : Rotate four rectangles
        Intuition

        Approach 1 makes two passes through the matrix, though it's possible to make a rotation in one pass.

        To figure out how let's check how each element in the angle moves during the rotation.

        compute

        That gives us an idea to split a given matrix in four rectangles and reduce the initial problem to the rotation of these rectangles.

        compute

        Now the solution is quite straightforward - one could move across the elements in the first rectangle and rotate them using a temp list of 4 elements.

        Implementation

        Current
        1 / 6

        Complexity Analysis

        Time complexity : O(N^2) is a complexity given by two inserted loops.
        Space complexity : O(1) since we do a rotation in place and allocate only the list of 4 elements as a temporary helper.
    """
    def rotate(self, matrix: list) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        # (i, j) = (j, n-1-i)
        n = len(matrix)
        def rotate(i, j, v):
            tmp = matrix[j][n-1-i]
            matrix[j][n-1-i] = v
            return tmp, j, n-1-i
            
        for i in range(n // 2 + n%2):
            for j in range(n // 2):
                x, y, = i, j
                last = matrix[x][y]
                for _ in range(4):
                    last, x, y = rotate(x, y, last)


if __name__ == '__main__':

    Rotate().rotate([[1,2,3],[4,5,6],[7,8,9]])

    Rotate().rotate([[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]])

