

import os



# leetcode 198. House Robber
# You are a professional robber planning to rob houses along a street. 
# Each house has a certain amount of money stashed, the only constraint stopping you from 
# robbing each of them is that adjacent houses have security system connected and 
# it will automatically contact the police if two adjacent houses were broken into on the same night.

# Given a list of non-negative integers representing the amount of money of each house, 
# determine the maximum amount of money you can rob tonight without alerting the police.
class rob(object):
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

            res = max(search(nums, i+1, D), search(nums, i+2, D) + nums[i])
                
            if D[i] == 0:
                D[i] = res

            return res


        D = [0 for _ in range(len(nums))]
        return search(nums, 0, D)

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        D = [0 for _ in range(len(nums) + 2)]
        D[0], D[1] = 0, 0

        for i in range(2, len(nums) + 2):
            D[i] = max(nums[i-2] + D[i-2], D[i-1])
        
        return D[len(nums)+1]


    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        l1, l2, = 0, 0
        for i in nums:
            l2, l1 = l1, max(l2 + i, l1)

        return l1


    def doit3(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        robbed, not_robbed = 0, 0

        for i in nums:
            robbed, not_robbed = not_robbed + i, max(not_robbed, robber)

        return max(robbed, not_robbed)
                    



# leetcode 213. House Robber II      
# After robbing those houses on that street, the thief has found himself a new place 
# for his thievery so that he will not get too much attention. 
# This time, all houses at this place are arranged in a circle. 
# That means the first house is the neighbor of the last one. Meanwhile, 
# the security system for these houses remain the same as for those in the previous street.

# Given a list of non-negative integers representing the amount of money of each house, 
# determine the maximum amount of money you can rob tonight without alerting the police.        
class robII(object):
    def doit(self, nums):
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


    def doit2(self, node):
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


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class robIII(object):
    def doit2(self, root):
        """
        :type nums: List[int]
        :rtype: int
        """
        buff = [root]
        robbed, not_robbed = 0, 0
        while buff:

            tmp, amount = [], 0
            for node in buff:
                amount +=  node.val
                if node.left:
                    tmp.push(node.left)
                if node.right:
                    tmp.push(node.right)
                
            robbed, not_robbed = not_robbed +amount, max(not_robbed, robbed)
            buff = tmp
        
        return max(robbed, not_robbed)


    def doit(self, root):
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


    def doit3(self, root):
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


    res = rob().doit2([1])
    
    res = robII().doit([1])

    pass