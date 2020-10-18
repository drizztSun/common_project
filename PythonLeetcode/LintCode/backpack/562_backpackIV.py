"""
562 Backpack IV

Description
Given an integer array nums[] which contains n unique positive numbers, num[i] indicate the size of ith item.
An integer target denotes the size of backpack. Find the number of ways to fill the backpack.

Each item may be chosen unlimited number of times

Have you met this question in a real interview?
Example
Example1

Input: nums = [2,3,6,7] and target = 7
Output: 2
Explanation:
Solution sets are:
[7]
[2, 2, 3]
Example2

Input: nums = [2,3,4,5] and target = 7
Output: 3
Explanation:
Solution sets are:
[2, 5]
[3, 4]
[2, 2, 3]

"""


class BackPackIV:
    """
    @param nums: an integer array and all positive numbers, no duplicates
    @param target: An integer
    @return: An integer
    """
    def doit(self, nums, target):
        # write your code here
        dp = [0 for _ in range(target+1)]
        dp[0] = 1

        for c in nums:
            for i in range(c, target + 1):
                dp[i] += dp[i-c]

        return dp[-1]


if __name__ == "__main__":

    res = BackPackIV().doit([2, 3, 6, 7], 7)