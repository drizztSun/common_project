# 704. Binary Search

# Given a sorted (in ascending order) integer array nums of n elements and a target value, 
# write a function to search target in nums. If target exists, then return its index, otherwise return -1.


# Example 1:

# Input: nums = [-1,0,3,5,9,12], target = 9
# Output: 4
# Explanation: 9 exists in nums and its index is 4

# Example 2:

# Input: nums = [-1,0,3,5,9,12], target = 2
# Output: -1
# Explanation: 2 does not exist in nums so return -1


class BinarySearch(object):

    def doit(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        s, e = 0, len(nums) 
        
        while s < e:
            mid = int((s + e) // 2)
            
            print(mid)
            
            if nums[mid] == target:
                return mid
            elif nums[mid] > target:
                e = mid
            else :
                s = mid + 1
                
        return -1
            