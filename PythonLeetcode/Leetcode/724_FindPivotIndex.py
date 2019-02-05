# 724. Find Pivot Index

# Given an array of integers nums, write a method that returns the "pivot" index of this array.
# We define the pivot index as the index where the sum of the numbers to the left of the index is equal to the sum of the numbers to the right of the index.
# If no such index exists, we should return -1. If there are multiple pivot indexes, you should return the left-most pivot index.

# Example 1:

# Input: 
# nums = [1, 7, 3, 6, 5, 6]
# Output: 3
# Explanation: 
# The sum of the numbers to the left of index 3 (nums[3] = 6) is equal to the sum of numbers to the right of index 3.
# Also, 3 is the first index where this occurs.
 

# Example 2:

# Input: 
# nums = [1, 2, 3]
# Output: -1
# Explanation: 
# There is no index that satisfies the conditions in the problem statement.


class PivotIndex:

    def doit(self, nums: 'List[]int') -> 'int':
        
        total, left = sum(nums), 0

        for i in range(len(nums)):
            if left == total - left - nums[i]:
                return i
            
            left += nums[i]

        return -1

    def doit1(self, nums: 'List[int]') -> 'int':
        
        left = [0] * len(nums)
        right = [0] * len(nums)
        
        for i in range(1, len(nums)):
            left[i] = left[i-1] + nums[i-1]
            
        for i in reversed(range(0, len(nums)-1)):
            right[i] = right[i+1] + nums[i+1]
            
        for i in range(0, len(nums)):
            if left[i] == right[i]:
                return i
                
        return i


if __name__ == "__main__":

    res = PivotIndex().doit([-1, -1, 0, 0, -1, -1])

    res = 0