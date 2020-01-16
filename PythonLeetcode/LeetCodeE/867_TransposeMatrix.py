# 867. Transpose Matrix

# Given a matrix A, return the transpose of A.

# The transpose of a matrix is the matrix flipped over it's main diagonal, switching the row and column indices of the matrix.

# Example 1:

# Input: [[1,2,3],[4,5,6],[7,8,9]]
# Output: [[1,4,7],[2,5,8],[3,6,9]]

# Example 2:

# Input: [[1,2,3],[4,5,6]]
# Output: [[1,4],[2,5],[3,6]]


# Note:

# 1 <= A.length <= 1000
# 1 <= A[0].length <= 1000


class Transpose(object):

    def doit(self, A):
        """
        :type A: List[List[int]]
        :rtype: List[List[int]]
        """
        return [[ A[j][i] for j in range(len(A)) ] for i in range(len(A[0]))]

    def doit(self, A):
        """
        :type A: List[List[int]]
        :rtype: List[List[int]]
        """
        rows = len(A)
        columns = len(A[0])
        
        result = []
                 
        for i in range(columns):
            result = result + [[A[j][i] for j in range(rows)]]
            
        return result