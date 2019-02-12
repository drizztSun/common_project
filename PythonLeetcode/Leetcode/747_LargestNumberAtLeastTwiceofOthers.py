# 747. Largest Number At Least Twice of Others


#In a given integer array nums, there is always exactly one largest element.

#Find whether the largest element in the array is at least twice as much as every other number in the array.

#If it is, return the index of the largest element, otherwise return -1.

#Example 1:

#Input: nums = [3, 6, 1, 0]
#Output: 1
#Explanation: 6 is the largest integer, and for every other number in the array x,
#6 is more than twice as big as x.  The index of value 6 is 1, so we return 1.
 

#Example 2:

#Input: nums = [1, 2, 3, 4]
#Output: -1
#Explanation: 4 isn't at least as big as twice the value of 3, so we return -1.

class DominantIndex:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        f1, f2, index = 0, 0, -1
        
        for i, n in enumerate(nums):
            
            if n > f1:
                f2 = f1
                f1 = n
                index = i
            elif n > f2:    
                f2 = n
                
        return index if f1 >= 2 * f2 else -1

    def doit1(self, nums: 'List[int]') -> 'int':
        largest = max(nums)
        second_largest = -1
        for x in nums:
            if x!=largest and x>second_largest:
                second_largest=x
        
        if largest>=second_largest*2:
            return nums.index(largest)
        else:
            return -1