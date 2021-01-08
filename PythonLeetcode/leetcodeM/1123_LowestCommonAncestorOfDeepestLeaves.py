"""
1123. Lowest Common Ancestor of Deepest Leaves


Given the root of a binary tree, return the lowest common ancestor of its deepest leaves.

Recall that:

The node of a binary tree is a leaf if and only if it has no children
The depth of the root of the tree is 0. if the depth of a node is d, the depth of each of its children is d + 1.
The lowest common ancestor of a set S of nodes, is the node A with the largest depth such that every node in S is in the subtree with root A.
Note: This question is the same as 865: https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation: We return the node with value 2, colored in yellow in the diagram.
The nodes coloured in blue are the deepest leaf-nodes of the tree.
Note that nodes 6, 0, and 8 are also leaf nodes, but the depth of them is 2, but the depth of nodes 7 and 4 is 3.
Example 2:

Input: root = [1]
Output: [1]
Explanation: The root is the deepest node in the tree, and it's the lca of itself.
Example 3:

Input: root = [0,1,3,null,2]
Output: [2]
Explanation: The deepest leaf node in the tree is 2, the lca of one node is itself.
 

Constraints:

The number of nodes in the tree will be in the range [1, 1000].
0 <= Node.val <= 1000
The values of the nodes in the tree are unique.

"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class LowestCommonAncestorDeepestLeaves:


    """
        Approach 2: One-pass Binary Search
        Instead of going through the input array in two passes, we could achieve the goal in one pass with an revised binary search.

        The idea is that we add some additional condition checks in the normal binary search in order to better narrow down the scope of the search.

        Algorithm

        As in the normal binary search, we keep two pointers (i.e. start and end) to track the search scope. 
        At each iteration, we reduce the search scope into half, by moving either the start or end pointer to the middle (i.e. mid) of the previous search scope.

        Here are the detailed breakdowns of the algorithm:

        Initiate the pointer start to 0, and the pointer end to n - 1.

        Perform standard binary search. While start <= end:

        Take an index in the middle mid as a pivot.

        If nums[mid] == target, the job is done, return mid.

        Now there could be two situations:

        Pivot element is larger than the first element in the array, i.e. the subarray from the first element to the pivot is non-rotated, as shown in the following graph.
    """
    def doit_(self, root: 'TreeNode') -> 'TreeNode':

        depth = 0
        res = None

        def search(node, length):

            nonlocal depth
            nonlocal res

            if not node:
                return length

            l = search(node.left, length + 1)
            r = search(node.right, length + 1)

            ans = max(l, r)
            if depth < ans:
                depth = ans
                res = node

            if l == r == depth:
                res = node

            return ans

        search(root, 0)
        return res
        