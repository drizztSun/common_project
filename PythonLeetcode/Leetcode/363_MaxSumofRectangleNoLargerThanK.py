"""

# 363. Max Sum of Rectangle No Larger Than K

# Given a non-empty 2D matrix matrix and an integer k, find the max sum of
# a rectangle in the matrix such that its sum is no larger than k.

# Example:
# Given matrix = [
#  [1,  0, 1],
#  [0, -2, 3]
# ]
# k = 2
# The answer is 2. Because the sum of rectangle [[0, 1], [-2, 3]] is
# 2 and 2 is the max number no larger than k (k = 2).

# Note:
# The rectangle inside the matrix must have an area > 0.
# What if the number of rows is much larger than the number of columns


"""
import bisect


class maxSumSubmatrix:

    """
    # using two pointers to scan the column, Space is O(col)
    # left and right both start from the 0, and move right first when it reaches the end then move left
    # record the sum of the value and find the max sum less than k
    # the following code can also be used to solve Max Sum of Sub-Matrix, only need to replace the maxSubArraylessK with Kadane's algorithm
    """
    def doit(self, matrix, k):

        def maxSubArraylessK(nums, k):
            """
            we need to find the sum[right]-sum[left]<=k
            since the bitsect return the index of the sorted value
            we can't directly pop the nums[idx] 
            we should use insort from the bisect
            """
            # python set() doesn't support indexing, using list instead
            # similar as the c++ or java set()
            cumset = []
            cumset.append(0)
            maxsum = -1<<32
            cursum = 0
            
            for i in range(len(nums)):
                cursum += nums[i]
                # find the lower bound of the index
                idx = bisect.bisect_left(cumset, cursum - k)
                # find max in sum[right]-sum[left]<=k
                if 0 <= idx < len(cumset):
                    maxsum = max(maxsum, cursum - cumset[idx])
                # using insort instead of append since bisect_left reason
                bisect.insort(cumset, cursum)
            
            return maxsum
        
        """
        The python solution hasn't a good time performance,
        since lack some of the datatype to do 
        I am trying to imitate the way solved in c++ or Java
        Ther related quesiton might be:
        1. #53. Maximum Subarray 
        2. Maximum Subarray sum less or equal than K
        3. maximun sum of rectangle 
        """
        if not matrix or not matrix[0]:
            return 0

        row, col = len(matrix), len(matrix[0])
        res=-(1<<32)
        
        # using two pointer to record the scan position
        for left in range(col):
            # reset mem to store the row data
            cursums = [0 for _ in range(row)]
            # since the rectange has area>0 
            right = left
            while right < col:
                # count one row
                for i in range(row):
                    cursums[i] += matrix[i][right]

                # find the max in this row
                curarrmax = maxSubArraylessK(cursums, k)

                res = max(res, curarrmax)

                right += 1
                
        return res

    def doit2(self, matrix, k):
        """
        :type matrix: List[List[int]]
        :type k: int
        :rtype: int
        """
        def maxSublessK(attr, k):
            sums, maxS = 0, float('-inf')
            f = [0]
            for c in attr:
                sums += c
                pos = bisect.bisect_left(f, sums - k)
                if 0 <= pos < len(l):
                    maxS = max(maxS, sums - f[pos])
                bisect.insort(f, sums)
            return maxS

        #######
        m, n = len(matrix), len(matrix[0])
        res = float('-inf')

        for i in range(n):
            maxV = [0] * m
            for j in range(i, n):
                for row in range(m):
                    maxV[row] += matrix[row][j]

                t = maxSublessK(maxV, k)
                if t == k:
                    return k

                if res < t < k:
                    res = t

        return res
    
    def doit1(self, matrix, k):
        """
        :type matrix: List[List[int]]
        :type k: int
        :rtype: int
        """

        def sum_of_parts(arr, k):
            sums, maxV = 0, float('-inf')
            for c in arr:
                sums += c
                maxV = max(maxV, sums)

                if sums == k:
                    return k

                if sums < 0:
                    sums = 0

            if maxV <= k:
                return maxV

            maxV, sums = float('-inf'), 0
            f = set()
            f.add(0)
            for c in arr:
                sums += c
                l = list(f)
                a = bisect.bisect_left(l, sums - k)
                if a != -1 and a < len(l):
                    maxV = max(maxV, sums - l[a])
                f.add(sums)

            return maxV

        # ##
        m, n = len(matrix), len(matrix[0])
        maxV = float('-inf')

        for i in range(n):
            sums = [0] * m
            for j in range(i, n):
                for row in range(m):
                    sums[row] += matrix[row][j]

                res = sum_of_parts(sums, k)

                if  res == k:
                    return k

                if maxV < res < k:
                    maxV = res
       
        return maxV


    def doit1(self, matrix, k):
        """
        :type matrix: List[List[int]]
        :type k: int
        :rtype: int
        """
        rows, columns = len(matrix), len(matrix[0])

        sumD = [ [0 for _ in range(columns)] for i in range(rows)]
        sumD[0][0] = matrix[0][0]

        for i in range(rows):
            accum = 0
            for j in range(columns):
                accum += matrix[i][j]
                sumD[i][j] = sumD[i][j-1] + accum

        
        
        pass



if __name__ == "__main__":


    matrix = [
      [1,  0, 1],
      [0, -2, 3]
    ]
        
    res = maxSumSubmatrix().doit(matrix, 2)

    matrix = [[5, -4, -3,  4],
              [-3,-4,  4,  5],
              [5,  1,  5, -4]]

    res = maxSumSubmatrix().doit(matrix, 8)



    matrix = [[5, -4, -3,  4],
              [-3,-4,  4,  5],
              [5,  1,  5,  -4]]

    res = maxSumSubmatrix().doit(matrix, 3)


    matrix = [[28,4,-19,18,-7,-10,27,19,1,16,0,10,-17,11,11,27,-1,10,12,-1],[-2,-19,17,4,25,-20,4,3,4,28,-10,7,16,-14,-3,-19,6,17,-4,-7],[2,8,18,-17,-2,10,-6,-5,11,10,22,-6,19,-16,6,-4,18,5,22,-17],[-14,-7,-20,13,-19,-20,-15,21,-11,-10,-8,-9,10,13,6,-10,15,9,-15,-2],[-18,26,12,8,2,16,-17,12,0,-5,9,-3,-12,-11,3,-6,-18,16,-7,-14],[5,29,25,22,11,-3,-2,-15,4,13,-17,-2,0,-2,20,10,-18,6,25,-20],[5,-7,8,5,15,22,8,-5,22,-18,-5,-14,23,2,-8,12,-16,-18,12,-12],[27,18,4,11,-3,12,-4,-8,-3,25,-9,24,-14,5,11,-9,-17,0,25,-15],[26,-7,18,4,4,18,-17,9,-19,-9,-19,-8,-4,-13,10,-11,6,-16,-12,12],[28,22,7,11,-6,13,8,22,7,-14,17,14,10,29,16,9,-3,18,-9,10],[27,19,-10,-9,1,3,14,1,7,3,-3,16,-2,9,14,-7,-19,-5,23,19],[-17,7,-20,8,-5,-6,-2,25,29,16,23,4,4,27,16,17,9,20,-6,22],[2,9,-13,1,-18,25,4,7,25,26,-4,8,-19,18,6,-7,-5,7,21,-8],[-2,11,1,29,6,-16,-8,3,7,11,10,-2,-1,-20,20,4,19,5,29,-7],[29,-12,-3,17,6,19,23,12,-19,13,19,5,27,22,-17,27,10,-12,12,23],[24,16,4,25,15,13,24,-19,1,-7,-19,13,-13,14,13,26,9,18,-9,-18],[-17,4,-18,-18,-19,3,-13,12,23,-17,-10,-20,14,2,18,21,-12,27,-3,4],[27,13,12,14,16,-9,-2,-15,-20,8,-2,24,18,15,26,21,27,17,-15,-3],[25,-8,17,-10,-16,13,26,-11,-15,6,-5,-13,23,2,24,-4,5,8,-15,-1],[15,-12,18,5,-3,7,5,11,-4,-13,28,20,0,-4,-13,-5,-13,-8,-16,3]]

    res = maxSumSubmatrix().doit(matrix, -123)


    matrix = [[2,2,-1]]
    
    res = maxSumSubmatrix().doit(matrix, -1)


    matrix = [[27, 5, -20, -9, 1, 26,  1, 12, 7, -4, 8, 7, -1, 5, 8],
              [16,28,8,3,16,28,-10,-7,-5,-13,7,9,20,-9,26],
              [24,-14,20,23,25,-16,-15,8,8,-6,-14,-6,12,-19,-13],
              [28,13,-17,20,-3,-18,12,5,1,25,25,-14,22,17,12],
              [7,29,-12,5,-5,26,-5,10,-5,24,-9,-19,20,0,18],
              [-7,-11,-8,12,19,18,-15,17,7,-1,-11,-10,-1,25,17],
              [-3,-20,-20,-7,14,-12,22,1,-9,11,14,-16,-5,-12,14],
              [-20,-4,-17,3,3,-18,22,-13,-1,16,-11,29,17,-2,22],
              [23,-15,24,26,28,-13,10,18,-6,29,27,-19,-19,-8,0],
              [5,9,23,11,-4,-20,18,29,-6,-4,-11,21,-6,24,12],
              [13,16,0,-20,22,21,26,-3,15,14,26,17,19,20,-5],
              [15,1,22,-6,1,-9,0,21,12,27,5,8,8,18,-1],
              [15,29,13,6,-11,7,-6,27,22,18,22,-3,-9,20,14],
              [26,-6,12,-10,0,26,10,1,11,-10,-16,-18,29,8,-8],
              [-19,14,15,18,-10,24,-9,-7,-19,-14,23,23,17,-5,6]]

    res = maxSumSubmatrix().doit(matrix, -100) #-101


    pass




