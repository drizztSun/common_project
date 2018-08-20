import os


#Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

#For example, given the following matrix:

    #1 0 1 0 0
    #1 0 1 1 1
    #1 1 1 1 1
    #1 0 0 1 0

# return 6

class maximalRectangle(object):

# The DP solution proceeds row by row, starting from the first row. 
# Let the maximal rectangle area at row i and column j be computed by [right(i,j) - left(i,j)]*height(i,j).
# All the 3 variables left, right, and height can be determined by the information from previous row, and also information from the current row.
# So it can be regarded as a DP solution. The transition equations are:

# left(i,j) = max(left(i-1,j), cur_left), cur_left can be determined from the current row
# right(i,j) = min(right(i-1,j), cur_right), cur_right can be determined from the current row
# height(i,j) = height(i-1,j) + 1, if matrix[i][j]=='1';
# height(i,j) = 0, if matrix[i][j]=='0'
  
  def doit(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        if not matrix or not matrix[0]:
            return 0
        
        rows, lines = len(matrix), len(matrix[0])
        high, left, right = [0] * lines, [0] * lines, [lines] * lines
        maxV = 0
        
        for i in range(rows):
            
            curleft, curright = 0, lines
            
            # scan high
            for j in range(lines):
                high[j] = high[j]+1 if matrix[i][j] == '1' else 0
                
            # scan left    
            for j in range(lines):
                if matrix[i][j] == '1':
                    left[j] = max(left[j], curleft)
                else:
                    left[j], curleft = 0, j+1
                    
            # scan right        
            for j in reversed(range(lines)):
                if matrix[i][j] == '1':
                    right[j] = min(right[j], curright)
                else:
                    right[j], curright = lines, j
                    
            for i in range(lines):
                maxV = max(maxV, (right[i]-left[i]) * high[i])
                
        return maxV

# The solution is based on largest rectangle in histogram solution. 
# Every row in the matrix is viewed as the ground with some buildings on it. 
# The building height is the count of consecutive 1s from that row to above rows. 
# The rest is then the same as this solution for largest rectangle in histogram
  def doit1(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        if not matrix or not matrix[0]:
            return 0

        n = len(matrix[0])
        height = [0] * (n + 1)
        ret = 0

        for row in matrix:

            for i in range(n):
                height[i] = height[i] + 1 if row[i] == '1' else 0

            stack = [-1]

            for i in range(n + 1):
                while height[i] < height[stack[-1]]:
                    h = height[stack.pop()]
                    w = i - 1 - stack[-1]
                    ret = max(ret, h * w)
                stack.append(i)

        return ret

        


if __name__=="__main__":
    pass
    
    a = [["1","0","1","0","0"],
         ["1","0","1","1","1"],
         ["1","1","1","1","1"],
         ["1","0","0","1","0"]]

    res = maximalRectangle().doit1(a)

    a = [["1","0","1","0","0","0","0"],
         ["1","0","1","0","0","1","1"],
         ["1","1","1","0","0","1","1"],
         ["1","0","0","0","0","1","0"]]

    res = maximalRectangle().doit1(a)

    pass