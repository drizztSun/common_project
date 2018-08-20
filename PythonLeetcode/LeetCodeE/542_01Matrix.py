# 542. 01 Matrix

# Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.

# The distance between two adjacent cells is 1.
# Example 1: 
# Input:

# 0 0 0
# 0 1 0
# 0 0 0
# Output:
# 0 0 0
# 0 1 0
# 0 0 0
# Example 2: 
# Input:

# 0 0 0
# 0 1 0
# 1 1 1
# Output:
# 0 0 0
# 0 1 0
# 1 2 1
# Note:
# The number of elements of the given matrix will not exceed 10,000.
# There are at least one 0 in the given matrix.
# The cells are adjacent in only four directions: up, down, left and right.

import collections
from collections import deque

class UpdateMatrix(object):


    def doit(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[List[int]]
        """
        M, N = len(matrix), len(matrix[0])
        amount = M * N
        res = [[-1 for _ in range(N)] for _ in range(M)]
        buff = collections.deque()
        
        for i in range(M):
            for j in range(N):
                if matrix[i][j] == 0:
                    res[i][j] = 0
                    buff.append((i, j))
                    amount -= 1

        while amount > 0:

            length = len(buff)
            for i in range(length):
                x, y = buff.popleft()

                for c in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                    xx, yy = x + c[0], y + c[1]
                    if 0 <= xx < M and 0 <= yy < N and res[xx][yy] == -1:
                        res[xx][yy] = res[x][y] + 1
                        buff.append((xx, yy))
                        amount -= 1

        return res

    def doit1(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[List[int]]
        """
        m,n = len(matrix),len(matrix[0])
        import sys
        for i in range(m):
            for j in range(n):
                if matrix[i][j] != 0:
                    matrix[i][j] = sys.maxint
                    if i > 0 and matrix[i-1][j] + 1 < matrix[i][j]:
                        matrix[i][j] = matrix[i-1][j] + 1
                    if j > 0 and matrix[i][j-1] + 1 < matrix[i][j]:
                        matrix[i][j] = matrix[i][j-1] + 1
                        
 
        #print(matrix)
        for i in range(m-1,-1,-1):
            for j in range(n-1,-1,-1):
                if matrix[i][j] != 0:
                    if i + 1 < m and matrix[i+1][j] + 1 < matrix[i][j]:
                        matrix[i][j] = matrix[i+1][j] + 1
                    if j + 1 < n and matrix[i][j+1] +1 < matrix[i][j]:
                        matrix[i][j] = matrix[i][j+1] + 1

        
        return(matrix)
                         


if __name__ == "__main__":

    res = UpdateMatrix().doit([[0, 0, 0], [0, 1, 0], [1, 1, 1]])

    pass
        
    

            

        