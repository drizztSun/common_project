# 674. Longest Continuous Increasing Subsequence

# Given an unsorted array of integers, find the length of longest continuous increasing subsequence (subarray).

# Example 1:
# Input: [1,3,5,4,7]
# Output: 3
# Explanation: The longest continuous increasing subsequence is [1,3,5], its length is 3. 
# Even though [1,3,5,7] is also an increasing subsequence, it's not a continuous one where 5 and 7 are separated by 4. 

# Example 2:
# Input: [2,2,2,2,2]
# Output: 1
# Explanation: The longest continuous increasing subsequence is [2], its length is 1. 
# Note: Length of the array will not exceed 10,000.

class FindLengthOfLCIS:
    def doit(self, nums: 'List[int]') -> 'int':
        
        s, maxv, pre = -1, 0, float('inf')

        for i in range(len(nums)):
            if i == 0 or nums[i] > pre:
                maxv = max(maxv, i - s)
            else:
                s = i - 1
                
            pre = nums[i]
            
        return maxv
        