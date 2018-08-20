# 594. Longest Harmonious Subsequence

# We define a harmonious array is an array where the difference between its maximum value and its minimum value is exactly 1.

# Now, given an integer array, you need to find the length of its longest harmonious subsequence among all its possible subsequences.

# Example 1:
# Input: [1,3,2,2,5,2,3,7]
# Output: 5

# Explanation: The longest harmonious subsequence is [3,2,2,2,3].
# Note: The length of the input array will not exceed 20,000.

class FindLHS:

    def wrong_understanding(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) == 0:
            return 0

        l, g = 0, 0
        s, e = -1, 0
        res = 0

        while e < len(nums):

            if e + 1 < len(nums) and (nums[e+1] == nums[g] or nums[e+1] == nums[l]):

                if nums[e+1] == nums[g]:
                    g = e + 1
                else:
                    l = e + 1
                e += 1

            elif nums[e+1] == nums[l] - 1: 
                s = g
                e += 1
            elif nums[e+1] == nums[g] + 1:
                s = l
                e += 1                                               
            else:
                s, e = e, e + 1
                l, g = e, e
            
            res = max(res, e - s)

        return res


    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import Counter
        
        cnts = Counter(nums)
        res = 0

        for c in nums:
            if c + 1 in cnts:
                res = max(res, cnts[c] + cnts[c + 1])

        return res


    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        cnts = {}
        res = 0

        for c in nums:
            cnts[c] = cnts.get(c, 0) + 1

        for c in nums:
            if c + 1 in cnts:
                res = max(res, cnts[c] + cnts[c+1])

        return res


if __name__ == "__main__":

    res = FindLHS().doit([1,3,2,2,5,2,3,7])