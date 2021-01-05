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

    """
    分析：

    这道题可以单纯的用暴力法解决，也就是对每个元素分别进行一次正负的累加，复杂度为2^n，因为n不超过20，故也就100w左右，但是在leetcode上同样的解法c++和java可以通过，python是无法通过的
    这里介绍discuss里一位大神提出来的超帅的数学解法，这道题中我们加正负号无非是将nums分为两个子集p,n，p中元素全部加正号，n中元素全部加负号，使得sum(p) - sum(n) = S，而本身又有sum(p) + sum(n) = sum(nums)，故两式相加化简得sum(p) = (sum(nums)+S) / 2
    
    那么这个式子直接给出了一个信息，也就是如果能找到p，则必有sum(nums)+S % 2 == 0这个条件，这个条件可以帮我们快速判断是否有解。
    那么此时题目就变成给定一个数组nums，求有多少组不同的p，使得sum(p) = target ((sum(nums) + S) / 2)，直接dp可解
    
    思路：

    建立dp，dp[i] = j代表数组nums中有j组子集的和为i，初始dp[0] = 1
    如nums = [1,1,1,1,1]，按照如下步骤分析
    对nums[0]分析，则得dp[1] = 1(因为dp[0] = 1)
    对nums[1]分析，则得dp[1] = 2,dp[2] = 1(因为dp[0] = 1,dp[1] = 1)
    对nums[2]分析，则得dp[1] = 3,dp[2] = 2,d[3] = 1,依次类推
    """

    def doit_dp(self, nums, S):
        """
        :type nums: List[int]
        :type S: int
        :rtype: int
        """
        if sum(nums) < S: return 0
        if (sum(nums) + S) & 1: return 0

        target = (sum(nums) + S) / 2
        dp = [0] * (target+1)
        dp[0] = 1

        for i in range(len(nums)):
            for val in range(target, nums[i]-1, -1):
                if dp[val-nums[i]]:
                    dp[val] += dp[val-nums[i]]
        return dp[-1]

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
        def search(i, res, visited):
            if i == len(nums):
                return 1 if res == S else 0

            if (i, res) not in visited:
                visited[(i, res)] = search(i + 1, res + nums[i], visited) + search(i + 1, res - nums[i], visited)

            return visited[(i, res)]

        return search(0, 0, {})