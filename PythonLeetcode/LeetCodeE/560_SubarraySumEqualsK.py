# 560. Subarray Sum Equals K

# Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

# Example 1:
# Input:nums = [1,1,1], k = 2
# Output: 2
# Note:
# The length of the array is in range [1, 20,000].
# The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].




class SubarraySum:
    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        total, ans = 0, 0
        sub = {0 : 1}
        for c in nums:
            total += c
            
            ans += sub.get(total - k, 0)

            sub[total] = sub.get(total, 0) + 1

        return ans



if __name__ == "__main__":

    res = SubarraySum().doit([1], 0)

    res = SubarraySum().doit([1, 1, 1], 2)

    res = 1