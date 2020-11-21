"""
494. Target Sum

You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.

Find out how many ways to assign symbols to make sum of integers equal to target S.

Example 1:

Input: nums is [1, 1, 1, 1, 1], S is 3.
Output: 5
Explanation:

-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

There are 5 ways to assign symbols to make the sum of nums be target 3.


Constraints:

The length of the given array is positive and will not exceed 20.
The sum of elements in the given array will not exceed 1000.
Your output answer is guaranteed to be fitted in a 32-bit integer.
"""


class TargetSum:

    def doit_dp(self, nums: list, S: int) -> int:

        n = len(nums)
        dp = [{0: 1}]

        for i in range(n):
            newlevel = {}
            for k, v in dp[-1]:
                newlevel[k+nums[i]] = newlevel.get(k + nums[i], 0) + v
                newlevel[k-nums[i]] = newlevel.get(k - nums[i], 0) + v
            dp.append(newlevel)

        return dp[-1].get(S, 0)

    def doit_dp_1(self, nums: list, S: int) -> int:

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

    def doit_dfs(self, nums, S):
        """
        :type nums: List[int]
        :type S: int
        :rtype: int
        """
        def search(nums, i, res, visited):
            if i == len(nums):
                return 1 if res == S else 0

            if (i, res) not in visited:
                visited[(i, res)] = search(nums, i + 1, res + nums[i], visited) + search(nums, i + 1, res - nums[i], visited)

            return visited[(i, res)]

        return search(nums, 0, 0, {})