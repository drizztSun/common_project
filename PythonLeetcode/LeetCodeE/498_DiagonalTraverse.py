# 498. Diagonal Traverse

# Given a matrix of M x N elements (M rows, N columns), return all elements of the matrix in diagonal order as shown in the below image.

# Example:
# Input:
#[
# [ 1, 2, 3 ],
# [ 4, 5, 6 ],
# [ 7, 8, 9 ]
#]
# Output:  [1,2,4,7,5,3,6,8,9]
# Explanation:

class DiagonalOrder:

    def doit1(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[int]
        """
        if not matrix:
            return []
        
        l, ll = len(matrix), len(matrix[0])
        if l == 1:
            return matrix[0]
        if ll == 1:
            return [matrix[x][0] for x in range(l)]
        
        total = l + ll - 2
        
        i, j = 0, 0
        res = [matrix[i][j]]
        for c in range(1, total+1):
            if c%2:
                if j < ll - 1:
                    i, j = i, j+1
                else:
                    i, j = i+1, j 
                while j >= 0 and i < l:
                    res.append(matrix[i][j])
                    i, j = i+1, j-1
                i, j = i-1, j+1
            else:
                if i < l-1:
                    i, j = i+1, j
                else:
                    i, j = i, j+1
                while j < ll and i >= 0:
                    res.append(matrix[i][j])
                    i, j = i-1, j+1
                i, j = i+1, j-1
            
        return res


    def doit(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[int]
        """
        if not matrix:
            return []

        M, N = len(matrix), len(matrix[0])
        ascend = True
        i, j = 0, 0
        res = []

        while len(res) < M * N:

            res.append(matrix[i][j])

            if ascend and (i == 0 or j == N - 1):
                if j == N - 1:
                    i += 1
                else:
                    j += 1

                ascend = not ascend

            elif not ascend and (j == 0 or i == M - 1):
                if i == M - 1:
                    j += 1
                else:
                    i += 1
                ascend = not ascend

            else:
                if not ascend:
                    i += 1
                    j -= 1
                else:
                    i -= 1
                    j += 1

        return res
                        

if __name__ == "__main__":

    res = DiagonalOrder().doit([
             [ 1, 2, 3 ],
             [ 4, 5, 6 ],
             [ 7, 8, 9 ]])