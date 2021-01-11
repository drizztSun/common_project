"""
437. Path Sum III


You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11

"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class PathSumIII:
    
    def doit_dfs(self, root: 'TreeNode', sum: int) -> int:
        from collections import defaultdict

        def dfs(node, total, presum):

            if not node:
                return 0

            total += node.val
            ans = presum[total-sum] if total - sum in presum else 0

            presum[total] += 1
            if node.left:
                ans += dfs(node.left, total, presum)

            if node.right:
                ans += dfs(node.right, total, presum)
            presum[total] -= 1
        
            return ans

        presum = defaultdict(int)
        presum[0] = 1

        return dfs(root, 0, presum)
    
    """
        Approach 1: Prefix Sum
        Now let's reuse the same algorithm and the same code for the case of the binary tree.

        There is just one thing that is particular for the binary tree. There are two ways to go forward - to the left and to the right. To keep parent->child direction, we shouldn't blend prefix sums from the left and right subtrees in one hashmap.

        Algorithm

        Let's initialize tree paths counter count = 0, and the hashmap h "prefix sum -> how many times was it seen so far".

        One could parse the tree using recursive preorder traversal: node -> left -> right: preorder(node: TreeNode, curr_sum: int) -> None. This function takes two arguments: a tree node and a prefix sum before that node. To start the recursion chain, one should call preorder(root, 0).

        The first thing is to update the current prefix sum by adding the value of the current node: curr_sum += node.val.

        Now one could update the counter. One should consider two situations.

        In situation 1, the tree path with the target sum starts from the root. That means the current prefix sum is equal to the target sum curr_sum == k, so one should increase the counter by 1: count += 1.

        In situation 2, the tree path with the target sum starts somewhere downwards. That means we should add to the counter the number of times we have seen the prefix sum curr_sum - target so far: count += h[curr_sum - target].

        The logic is simple: the current prefix sum is curr_sum, and several elements before the prefix sum was curr_sum - target. All the elements in between sum up to curr_sum - (curr_sum - target) = target.

        Now it's time to update the hashmap: h[curr_sum] += 1.

        Let's parse left and right subtrees: preorder(node.left, curr_sum), preorder(node.right, curr_sum).

        Now the current subtree is processed. It's time to remove the current prefix sum from the hashmap, in order not to blend the parallel subtrees: h[curr_sum] -= 1.

        Now the preorder traversal is done, and the counter is updated. Return it.
    """
    def pathSum(self, root: 'TreeNode', sum: int) -> int:
        
        def preorder(node: 'TreeNode', curr_sum) -> None:
            nonlocal count
            if not node:
                return 
            
            # current prefix sum
            curr_sum += node.val
            
            # here is the sum we're looking for
            if curr_sum == k:
                count += 1
            
            # number of times the curr_sum − k has occurred already, 
            # determines the number of times a path with sum k 
            # has occurred up to the current node
            count += h[curr_sum - k]
            
            # add the current sum into hashmap
            # to use it during the child nodes processing
            h[curr_sum] += 1
            
            # process left subtree
            preorder(node.left, curr_sum)
            # process right subtree
            preorder(node.right, curr_sum)
            
            # remove the current sum from the hashmap
            # in order not to use it during 
            # the parallel subtree processing
            h[curr_sum] -= 1
            
        count, k = 0, sum
        h = defaultdict(int)
        preorder(root, 0)
        return count


            

        