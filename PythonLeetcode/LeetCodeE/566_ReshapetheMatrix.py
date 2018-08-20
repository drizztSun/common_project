# 566. Reshape the Matrix


# In MATLAB, there is a very useful function called 'reshape', which can reshape a matrix into a new one with different size but keep its original data.

# You're given a matrix represented by a two-dimensional array, and two positive integers r and c representing the row number and column number of the wanted reshaped matrix, respectively.

# The reshaped matrix need to be filled with all the elements of the original matrix in the same row-traversing order as they were.

# If the 'reshape' operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original matrix.

# Example 1:
# Input: 
# nums = 
# [[1,2],
#  [3,4]]
# r = 1, c = 4
# Output: 
# [[1,2,3,4]]

# Explanation:
# The row-traversing of nums is [1,2,3,4]. The new reshaped matrix is a 1 * 4 matrix, fill it row by row by using the previous list.

# Example 2:
# Input: 
# nums = 
# [[1,2],
#  [3,4]]
# r = 2, c = 4
# Output: 
# [[1,2],
#  [3,4]]

# Explanation:
# There is no way to reshape a 2 * 2 matrix to a 2 * 4 matrix. So output the original matrix.



class MatrixReshape:


    def doit(self, nums, r, c):
        """
        :type nums: List[List[int]]
        :type r: int
        :type c: int
        :rtype: List[List[int]]
        """
        if len(nums) * len(nums[0]) != r * c:
            return nums
            
        entries=[]
        for i in nums:
            entries += i
            
        return [entries[i * c : (i + 1) * c] for i in range(r)]

    def doit2(self, nums, r, c):
        """
        :type nums: List[List[int]]
        :type r: int
        :type c: int
        :rtype: List[List[int]]
        """
        if len(nums) * len(nums[0]) != r * c:
            return nums
    
        entities = []
        for c in nums:
            entities.extend(c)

        return [entities[i * c : (i + 1) * c] for i in range(r)]
            

    def doit1(self, nums, r, c):
        """
        :type nums: List[List[int]]
        :type r: int
        :type c: int
        :rtype: List[List[int]]
        """
        m, n = len(nums), len(nums[0])
        if m * n != r * c:
            return nums

        res = [[0] * c for _ in range(r)]
        total = 0

        for i in range(r):
            for j in range(c):
                x, y = divmod(total, n)
                res[i][j] = nums[x][y]
                total += 1

        return res
            
if __name__ == "__main__":

    res = MatrixReshape().doit2([[1, 2], [3, 4]], 1, 4)

    res = 1
        