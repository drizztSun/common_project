# 766. Toeplitz Matrix

# A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same element.

# Now given an M x N matrix, return True if and only if the matrix is Toeplitz.
 

# Example 1:

# Input:
# matrix = [
#  [1,2,3,4],
#  [5,1,2,3],
#  [9,5,1,2]
#]
# Output: True

# Explanation:
# In the above grid, the diagonals are:
# "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
# In each diagonal all elements are the same, so the answer is True.

# Example 2:

# Input:
# matrix = [
#  [1,2],
#  [2,2]
# ]
# Output: False
# Explanation:
# The diagonal "[1, 2]" has different elements.

# Note:

# matrix will be a 2D array of integers.
# matrix will have a number of rows and columns in range [1, 20].
# matrix[i][j] will be integers in range [0, 99].

class isToeplitzMatrix:

    def doit(self, matrix: List[List[int]]) -> bool:

        n = len(matrix[0]) - 1
        for i in range(len(matrix) - 1):
            if matrix[i][0:n] != matrix[i+1][1:]:
                return False
        return True

    def doit2(self, matrix: 'List[List[int]]') -> 'bool':
        for i in range(len(matrix) - 1):
            if matrix[i][0:len(matrix[i]) - 1] != matrix[i+1][1:]:
                return False
        return True

    def doit1(self, matrix: List[List[int]]) -> bool:
        
        M, N = len(matrix), len(matrix[0])
        
        for j in range(N):
            c, t, l = matrix[0][j], 0, j
            while t < M and l < N:
                if matrix[t][l] != c:
                    return False
                t += 1
                l += 1
            
        for i in range(1, M):
            c, t, l = matrix[i][0], i, 0
            while t < M and l < N:
                if matrix[t][l] != c:
                    return False
                t += 1
                l += 1
        
        return True