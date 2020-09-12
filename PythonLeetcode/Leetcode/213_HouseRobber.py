"""
198. House Robber

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you
from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.
Example 2:

Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.

"""


class Rob(object):

    def doit_dp(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        D = [0 for _ in range(len(nums) + 2)]
        D[0], D[1] = 0, 0

        for i in range(2, len(nums) + 2):
            D[i] = max(nums[i-2] + D[i-2], D[i-1])
        
        return D[len(nums)+1]

    def doit_dp_2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        l1, l2, = 0, 0
        for i in nums:
            l2, l1 = l1, max(l2 + i, l1)

        return l1

    def doit_dp_3(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        robbed, not_robbed = 0, 0

        for i in nums:
            robbed, not_robbed = not_robbed + i, max(not_robbed, robbed)

        return max(robbed, not_robbed)

    def doit4(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        def search(nums, i, D):
            if i == len(nums):
                return 0

            if i == len(nums) - 1:
                return nums[-1]

            if D[i] != 0:
                return D[i]

            res = max(search(nums, i + 1, D), search(nums, i + 2, D) + nums[i])

            if D[i] == 0:
                D[i] = res

            return res

        D = [0 for _ in range(len(nums))]
        return search(nums, 0, D)

"""
213. House Robber II

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. 
All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, 
adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2),
             because they are adjacent houses.
Example 2:

Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.

"""


class RobII(object):

    def doit_dp(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) == 1:
            return nums[0]

        robbed, not_robbed = 0, 0
        for i in range(1, len(nums)):
            robbed, not_robbed = not_robbed + nums[i], max(robbed, not_robbed)
        res1 = max(robbed, not_robbed)

        robbed, not_robbed = 0, 0
        for i in range(0, len(nums)-1):
            robbed, not_robbed = not_robbed + nums[i], max(robbed, not_robbed)

        return max(res1, robbed, not_robbed)

    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) == 1:
            return nums[0]

        def search(nums):
            robbed, not_robbed = 0, 0
            for i in nums:
                robbed, not_robbed = i + not_robbed, max(robbed, not_robbed)

            return max(robbed, not_robbed)     

        return max(search(nums[1:]), search(nums[:-1]))

# leetcode 337. House Robber III
# The thief has found himself a new place for his thievery again. 
# There is only one entrance to this area, called the "root." 
# Besides the root, each house has one and only one parent house. 
# After a tour, the smart thief realized that "all houses in this place forms a binary tree". 
# It will automatically contact the police if two directly-linked houses were broken into on the same night.

# Determine the maximum amount of money the thief can rob tonight without alerting the police.

#         3
#        / \
#       2   3
#      / \    \ 
#     1   3    1

"""
337. House Robber III

The thief has found himself a new place for his thievery again. There is only one entrance to this area, called the "root." 

Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that "all houses in this place forms a binary tree". 

It will automatically contact the police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:

Input: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \ 
     3   1

Output: 7 
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:

Input: [3,4,5,1,3,null,1]

     3
    / \
   4   5
  / \   \ 
 1   3   1

Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
"""

# Definition for a binary tree node.


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class RobIII:

    def doit_dfs(self, root):
        """
        :type nums: List[int]
        :rtype: int
        """
        def search(node):
            if not node:
                return 0, 0

            lw_l, lwo_l = search(node.left)
            rw_r, rwo_r = search(node.right)

            return node.val + lwo_l + rwo_r, max(lw_l, lwo_l) + max(rw_r, rwo_r)

        return max(search(root))

    def doit_dfs_1(self, root):
        """
        :type nums: List[int]
        :rtype: int
        """
        def search(node, D):
            if not node:
                return 0

            if node in D:
                return D[node]

            resl, resr = 0, 0
            resll, reslr, resrl, resrr = 0, 0, 0, 0
            if node.left:
                resl = search(node.left, D)
                resll = search(node.left.left, D)
                reslr = search(node.left.right, D)

            if node.right:
                resr = search(node.right, D)
                resrl = search(node.right.left, D)
                resrr = search(node.right.right, D)

            res = max(node.val + resll + reslr + resrl + resrr,
                       resl + resr)
            D[node] = res
            return res
            
        D = {}
        return search(root, D)


if __name__=="__main__":

    res = RobIII().doit2([1])
    
    res = RobIII().doit([1])

    pass