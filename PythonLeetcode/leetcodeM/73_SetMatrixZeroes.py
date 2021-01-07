"""
73. Set Matrix Zeroes

Given an m x n matrix. If an element is 0, set its entire row and column to 0. Do it in-place.

Follow up:

A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?
 

Example 1:


Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]
Example 2:


Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 

Constraints:

m == matrix.length
n == matrix[0].length
1 <= m, n <= 200
-231 <= matrix[i][j] <= 231 - 1


"""

class MatrixSetZeroes:


    """
    The question seems to be pretty simple but the trick here is that we need to modify the given matrix in place i.e. our space complexity needs to O(1)O(1).

    We will go through two different approaches to the question. The first approach makes use of additional memory while the other does not.
    """

    """
        Approach 1: Additional Memory Approach
        Intuition

        If any cell of the matrix has a zero we can record its row and column number. All the cells of this recorded row and column can be marked zero in the next iteration.

        Algorithm

        We make a pass over our original array and look for zero entries.

        If we find that an entry at [i, j] is 0, then we need to record somewhere the row i and column j.

        So, we use two sets, one for the rows and one for the columns.

        if cell[i][j] == 0 {
            row_set.add(i)
            column_set.add(j)
        }
        Finally, we iterate over the original matrix. For every cell we check if the row r or column c had been marked earlier. If any of them was marked, we set the value in the cell to 0.

        if r in row_set or c in column_set {
            cell[r][c] = 0
        }

        Complexity Analysis

        Time Complexity: O(M×N) where M and N are the number of rows and columns respectively.

        Space Complexity: O(M+N).
    """ 

    def doit_(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: void Do not return anything, modify matrix in-place instead.
        """
        R = len(matrix)
        C = len(matrix[0])
        rows, cols = set(), set()

        # Essentially, we mark the rows and columns that are to be made zero
        for i in range(R):
            for j in range(C):
                if matrix[i][j] == 0:
                    rows.add(i)
                    cols.add(j)

        # Iterate over the array once again and using the rows and cols sets, update the elements
        for i in range(R):
            for j in range(C):
                if i in rows or j in cols:
                    matrix[i][j] = 0

    """
        Approach 2: O(1) Space, Efficient Solution
        Intuition

        Rather than using additional variables to keep track of rows and columns to be reset, we use the matrix itself as the indicators.

        The idea is that we can use the first cell of every row and column as a flag. This flag would determine whether a row or column has been set to zero. This means for every cell instead of going to M+NM+N cells and setting it to zero we just set the flag in two cells.

        if cell[i][j] == 0 {
            cell[i][0] = 0
            cell[0][j] = 0
        }
        These flags are used later to update the matrix. If the first cell of a row is set to zero this means the row should be marked zero. If the first cell of a column is set to zero this means the column should be marked zero.

        Algorithm

        We iterate over the matrix and we mark the first cell of a row i and first cell of a column j, if the condition in the pseudo code above is satisfied. i.e. if cell[i][j] == 0.

        The first cell of row and column for the first row and first column is the same i.e. cell[0][0]. Hence, we use an additional variable to tell us if the first column had been marked or not and the cell[0][0] would be used to tell the same for the first row.

        Now, we iterate over the original matrix starting from second row and second column i.e. matrix[1][1] onwards. For every cell we check if the row r or column c had been marked earlier by checking the respective first row cell or first column cell. If any of them was marked, we set the value in the cell to 0. Note the first row and first column serve as the row_set and column_set that we used in the first approach.

        We then check if cell[0][0] == 0, if this is the case, we mark the first row as zero.

        And finally, we check if the first column was marked, we make all entries in it as zeros.

        Complexity Analysis

        Time Complexity : O(M×N)
        Space Complexity : O(1)
    """
    def doit_(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: void Do not return anything, modify matrix in-place instead.
        """
        is_col = False
        R = len(matrix)
        C = len(matrix[0])
        for i in range(R):
            # Since first cell for both first row and first column is the same i.e. matrix[0][0]
            # We can use an additional variable for either the first row/column.
            # For this solution we are using an additional variable for the first column
            # and using matrix[0][0] for the first row. 
            if matrix[i][0] == 0:
                is_col = True
            for j in range(1, C):
                # If an element is zero, we set the first element of the corresponding row and column to 0
                if matrix[i][j]  == 0:
                    matrix[0][j] = 0
                    matrix[i][0] = 0

        # Iterate over the array once again and using the first row and first column, update the elements.
        for i in range(1, R):
            for j in range(1, C):
                if not matrix[i][0] or not matrix[0][j]:
                    matrix[i][j] = 0

        # See if the first row needs to be set to zero as well
        if matrix[0][0] == 0:
            for j in range(C):
                matrix[0][j] = 0

        # See if the first column needs to be set to zero as well        
        if is_col:
            for i in range(R):
                matrix[i][0] = 0