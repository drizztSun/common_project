# 581. Shortest Unsorted Continuous Subarray

# Given an integer array, you need to find one continuous subarray that if you only sort this subarray 
# in ascending order, then the whole array will be sorted in ascending order, too.

# You need to find the shortest such subarray and output its length.

# Example 1:
# Input: [2, 6, 4, 8, 10, 9, 15]
# Output: 5
# Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
# Note:
# Then length of the input array is in range [1, 10,000].
# The input array may contain duplicates, so ascending order here means <=.


class FindUnsortedSubarray:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # I use the variables beg and end to keep track of minimum subarray A[beg...end] which must be sorted for the entire 
        # array A to be sorted. If end < beg < 0 at the end of the for loop, then the array is already fully sorted.
        n = len(nums)
        maxv, minv = nums[0], nums[n-1]
        begin, end = -1, -2
        
        for i in range(1, n):
            
            maxv = max(maxv, nums[i])
            minv = min(minv, nums[n-1-i])
            
            if nums[i] < maxv:
                end = i
                
            if nums[n-1-i] > minv:
                begin = n - 1 - i
                
        return end - begin + 1
        


if __name__ == "__main__":

    res = FindUnsortedSubarraany().doit([2, 6, 4, 8, 10, 9, 15])
        