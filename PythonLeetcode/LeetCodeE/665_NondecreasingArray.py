# 665. Non-decreasing Array

# Given an array with n integers, your task is to check if it could become non-decreasing by modifying at most 1 element.

# We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).

# Example 1:
# Input: [4,2,3]
# Output: True
# Explanation: You could modify the first 4 to 1 to get a non-decreasing array.

# Example 2:
# Input: [4,2,1]
# Output: False
# Explanation: You can't get a non-decreasing array by modify at most one element.
# Note: The n belongs to [1, 10,000].

class CheckPossibility(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        count = 0
        for i in range(1, len(nums)):
            if nums[i-1] > nums[i] :
                count += 1
                if count == 2:
                    return False
                else:
                    if i == len(nums) - 1:
                        return True
                    elif nums[i-1] > nums[i+1] and i > 1 and nums[i-2] > nums[i]:
                        return False
        return True

if __name__ == "__main__":

    res = CheckPossibility().doit([4, 2, 1])