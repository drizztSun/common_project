# 661. Image Smoother

# Given a 2D integer matrix M representing the gray scale of an image, 
# you need to design a smoother to make the gray scale of each cell 
# becomes the average gray scale (rounding down) of all the 8 surrounding cells and itself.
# If a cell has less than 8 surrounding cells, then use as many as you can.

#Example 1:
#Input:
#[[1,1,1],
# [1,0,1],
# [1,1,1]]
#Output:
#[[0, 0, 0],
# [0, 0, 0],
# [0, 0, 0]]
#Explanation:
#For the point (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
#For the point (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
#For the point (1,1): floor(8/9) = floor(0.88888889) = 0
import math

class ImageSmoother:
    def doit(self, M):
        """
        :type M: List[List[int]]
        :rtype: List[List[int]]
        """
        row, col = len(M), len(M[0])
        res = [[0 for _ in range(col)] for _ in range(row)]
        
        for i in range(row):
            for j in range(col):
                amount, total = 0, 0
                
                for x in range(i-1, i+2):
                    for y in range(j-1, j+2):
                        if 0 <= x < row and 0 <= y < col:
                            total += M[x][y]
                            amount += 1
                            
                res[i][j] = math.floor(total // amount)
                
        return res
        

if __name__ == "__main__":

    M = [[1, 1, 1],
         [1, 0, 1],
         [1, 1, 1]]

    res = ImageSmoother().doit(M)

    N = [[2,3,4],
         [5,6,7],
         [8,9,10],
         [11,12,13],
         [14,15,16]]
    
    res = ImageSmoother().doit(N)

    pass