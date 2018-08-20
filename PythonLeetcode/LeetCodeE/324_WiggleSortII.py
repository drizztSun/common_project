
# Wiggle sort
# Given an unsorted array nums, reorder it in-place such that
# nums[0] <= nums[1] >= nums[2] <= nums[3]....

# Example
# Given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].

class wiggleSort:

    # O(nlong(n))    
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        nums.sort()
        for i in range(2, len(nums), 2):
            nums[i], nums[i-1] = nums[i-1], nums[i]

    # O(n)
    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        for i in range(1, len(nums)):
            if i % 2 == 1 and nums[i-1] > nums[i] or i % 2 == 0 and nums[i-1] < nums[i]:
                nums[i-1], nums[i] = nums[i-1], nums[i]




# 324. Wiggle Sort II
# Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

# Example:
# (1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is [1, 4, 1, 5, 1, 6]. 
# (2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is [2, 3, 1, 3, 1, 2].

# Note:
# You may assume all input has valid answer.

# Follow Up:
# Can you do it in O(n) time and/or in-place with O(1) extra space?


class wiggleSortII(object):

    # O(n*log(n))
    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        nums.sort()
        half = len(nums[::2])
        nums[::2], nums[1::2] = nums[:half][::-1], nums[half:][::-1]


    # O(n*log(n))
    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        nums.sort()
        half = len(nums[::2]) - 1
        nums[::2], nums[1::2] = nums[half::-1], nums[:half:-1]


    # O(n*log(n))
    def doit3(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        nums.sort(reverse = True)
        median = len(nums)/2
        larger = nums[0: median]
        smaller = nums[median: len(nums)]
        j, k = 0, 0

        for i in range(len(nums)):
            if i%2 == 0:
                nums[i] = smaller[j]
                j += 1
            else:
                nums[i] = larger[k]
                k += 1

           
    # O(n)
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        if len(nums) < 3:
            return

        

        
        
        
                


if __name__=="__main__":

    



    pass