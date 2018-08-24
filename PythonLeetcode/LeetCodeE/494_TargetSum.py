
# 494. Target Sum


# You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. 
# For each integer, you should choose one from + and - as its new symbol.

# Find out how many ways to assign symbols to make sum of integers equal to target S.

# Example 1:
# Input: nums is [1, 1, 1, 1, 1], S is 3. 
# Output: 5
# Explanation: 

# -1+1+1+1+1 = 3
# +1-1+1+1+1 = 3
# +1+1-1+1+1 = 3
# +1+1+1-1+1 = 3
# +1+1+1+1-1 = 3

# There are 5 ways to assign symbols to make the sum of nums be target 3.
# Note:
# The length of the given array is positive and will not exceed 20.
# The sum of elements in the given array will not exceed 1000.
# Your output answer is guaranteed to be fitted in a 32-bit integer.


class TargetSumWays(object):

    def doit(self, nums, S):
        """
        :type nums: List[int]
        :type S: int
        :rtype: int
        """
        ans = 0
        
        def search(nums, i, res, visited):
            if i == len(nums):
                return 1 if res == S else 0

            if (i, res) not in visited:
                visited[(i, res)] = search(nums, i + 1, res + nums[i], visited) + search(nums, i + 1, res - nums[i], visited)
    
            return visited[(i, res)]

        return search(nums, 0, 0, {})

    def doit1(self, nums, S):
        """
        :type nums: List[int]
        :type S: int
        :rtype: int
        """
        if not nums:
            return 0

        dic = {nums[0]: 1, -nums[0]: 1} if nums[0] != 0 else {0: 2}

        for i in range(1, len(nums)):
            tdic = {}
            
            for d in dic:
                tdic[d + nums[i]] = tdic.get(d + nums[i], 0) + dic.get(d, 0)
                tdic[d - nums[i]] = tdic.get(d - nums[i], 0) + dic.get(d, 0)
            
            dic = tdic

        return dic.get(S, 0)


    def doit2(self, nums, S):
        """
        :type nums: List[int]
        :type S: int
        :rtype: int
        """
        def sumSubset(nums, target):
            dp = [0 for i in range(target + 1)]
            dp[0] = 1
            for n in nums:
                for i in range(target, n - 1, -1):
                    dp[i] += dp[i - n]
            return dp[target]

        _sum = sum(nums)
        if _sum < S or (_sum + S) & 1 == 1:
            return 0
        
        target = (_sum + S) / 2
        
        return sumSubset(nums, target)


if __name__ == "__main__":
    
    res = TargetSumWays().doit([1, 1, 1, 1, 1], 3)

    res = TargetSumWays().doit([27,22,39,22,40,32,44,45,46,8,8,21,27,8,11,29,16,15,41,0], 10)

    res = 1
        