"""
491. Increasing Subsequences

Given an integer array, your task is to find all the different possible increasing subsequences of the given array, and the length of an increasing subsequence should be at least 2.

 

Example:

Input: [4, 6, 7, 7]
Output: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
 

Constraints:

The length of the given array will not exceed 15.
The range of integer in the given array is [-100,100].
The given array may contain duplicates, and two equal integers should also be considered as a special case of increasing sequence.


"""


class IncreasingSequence:

    def doit_dfs(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        def search(nums, i):

            if i == len(nums):
                return {()}

            res1 = search(nums, i + 1)
            res2 = { (nums[i],) + c for c in res1 if not c or c[0] >= nums[i] }

            return res2.union(res1)
        
        res = search(nums, 0)
        return [sub for sub in res if len(sub) > 1]