
# 654. Maximum Binary Tree

# Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

# The root is the maximum number in the array.
# The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
# The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
# Construct the maximum tree by the given array and output the root node of this tree.

# Example 1:
# Input: [3,2,1,6,0,5]
# Output: return the tree root node representing the following tree:

#      6
#    /   \
#   3     5
#    \    / 
#     2  0   
#       \
#        1
# Note:
# The size of the given array will be in the range [1,1000].

class TreeNode(object):

    def __init__(self, v):
        self.val = v
        self.left, self.right = None, None        

class MaxiumBinaryTree:

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: TreeNode
        """
        def build(nums, s, e):
            
            z = s
            for i in range(s, e):
                if nums[i] > nums[z]:
                    z = i

            c = TreeNode(nums[z])
            if z > s:
                c.left = build(nums, s, z)
            
            if z < e - 1:
                c.right = build(nums, z + 1, e)

            return c        

        return build(nums, 0, len(nums))

    # best one
    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: TreeNode
        """
        if not nums:
            return None

        stk = []
        for n in nums:

            curr = TreeNode(n)

            while stk and stk[-1].val < n:
                curr.left = stk.pop()

            # easier to come up with, now we must have stk[-1].val > n
            if stk:
                stk[-1].right = curr

            stk += curr,

        return stk[0]
                


if __name__ == "__main__":

    res = MaxiumBinaryTree().doit([3,2,1,6,0,5])

    None