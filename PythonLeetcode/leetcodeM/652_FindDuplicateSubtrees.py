"""
652. Find Duplicate Subtrees

Given the root of a binary tree, return all duplicate subtrees.

For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with the same node values.

 

Example 1:


Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]
Example 2:


Input: root = [2,1,1]
Output: [[1]]
Example 3:


Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]]
 

Constraints:

The number of the nodes in the tree will be in the range [1, 10^4]

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class FindDuplicateSubtrees:
    
    def doit_(self, root: 'TreeNode') -> 'List[TreeNode]':
        """
        :type root: TreeNode
        :rtype: List[TreeNode]
        """
        from collections import defaultdict
        buff = defaultdict(list)
        
        def duplicate(node):
            #global buff
            
            if not node:
                return 'x '
            
            key = str(node.val) + ' ' + duplicate(node.left) + duplicate(node.right)
            
            if key not in buff:
                buff[key] = [node, 1]
            else:
                buff[key][1] += 1
                
            return key
        
        duplicate(root)
        
        return [ v[0] for v in buff.values() if v[1] > 1]

    """
        Approach #1: Depth-First Search [Accepted]
        Intuition

        We can serialize each subtree. For example, the tree

        1
        / \
        2   3
            / \
        4   5
        can be represented as the serialization 1,2,#,#,3,4,#,#,5,#,#, which is a unique representation of the tree.

        Algorithm

        Perform a depth-first search, where the recursive function returns the serialization of the tree. At each node, record the result in a map, and analyze the map after to determine duplicate subtrees.

        Complexity Analysis

        Time Complexity: O(N^2), where NN is the number of nodes in the tree. We visit each node once, but each creation of serial may take O(N)O(N) work.

        Space Complexity: O(N^2), the size of count.
    """
    def doit_(self, root):
        import collections
        count = collections.Counter()
        ans = []
        def collect(node):
            if not node: return "#"
            serial = "{},{},{}".format(node.val, collect(node.left), collect(node.right))
            count[serial] += 1
            if count[serial] == 2:
                ans.append(node)
            return serial

        collect(root)
        return ans


    """
        Approach #2: Unique Identifier [Accepted]
        Intuition

        Suppose we have a unique identifier for subtrees: two subtrees are the same if and only if they have the same id.

        Then, for a node with left child id of x and right child id of y, (node.val, x, y) uniquely determines the tree.

        Algorithm

        If we have seen the triple (node.val, x, y) before, we can use the identifier we've remembered. Otherwise, we'll create a new one.

        Complexity Analysis

        Time Complexity: O(N), where NN is the number of nodes in the tree. We visit each node once.

        Space Complexity: O(N). Every structure we use is using O(1)O(1) storage per node.
    """
    def doit_(self, root):
        import collections
        
        trees = collections.defaultdict()
        trees.default_factory = trees.__len__
        count = collections.Counter()
        ans = []

        def lookup(node):
            if node:
                uid = trees[node.val, lookup(node.left), lookup(node.right)]
                count[uid] += 1
                if count[uid] == 2:
                    ans.append(node)
                return uid

        lookup(root)
        return ans