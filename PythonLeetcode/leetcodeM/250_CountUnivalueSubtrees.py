"""
250. Count Univalue Subtrees

Given the root of a binary tree, return the number of uni-value subtrees.

A uni-value subtree means all nodes of the subtree have the same value.

 

Example 1:


Input: root = [5,1,5,5,5,null,5]
Output: 4
Example 2:

Input: root = []
Output: 0
Example 3:

Input: root = [5,5,5,5,5,null,5]
Output: 6
 

Constraints:

The numbrt of the node in the tree will be in the range [0, 1000].
-1000 <= Node.val <= 1000


"""


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class CountUnivalSubtrees:

    """
        Approach 1: Depth First Search
        Intuition

        Given a node in our tree, we know that it is a univalue subtree if it meets one of the following criteria:

        The node has no children (base case)
        All of the node's children are univalue subtrees, and the node and its children all have the same value
        With this in mind we can perform a depth-first-search on our tree, and test if each subtree is uni-value in a bottom-up manner.

        Current
        1 / 7
        Algorithm


        Complexity Analysis

        Time complexity : O(n).

        Due to the algorithm's depth-first nature, the is_uni status of each node is computed from bottom up. When given the is_uni status of its children, computing the is_uni status of a node occurs in O(1)O(1)

        This gives us O(1) time for each node in the tree with O(N)O(N) total nodes for a time complexity of O(N)O(N)

        Space complexity : O(H), with H being the height of the tree. Each recursive call of is_uni requires stack space. Since we fully process is_uni(node.left) before calling is_uni(node.right), 
        the recursive stack is bound by the longest path from the root to a leaf - in other words the height of the tree.

        The above code is a commented version of the code here, originally written by Stefan Pochmann.

        Complexity Analysis

        Time complexity : O(N)O(N). Same as the previous approach.

        Space complexity : O(H)O(H), with H being the height of the tree. Same as the previous approach.
    """
    def countUnivalSubtrees(self, root):
        if root is None: return 0
        
        count = 0
        def is_uni(self, node):
            nonlocal count
            # base case - if the node has no children this is a univalue subtree
            if node.left is None and node.right is None:

                # found a univalue subtree - increment
                count += 1
                return True

            is_uni = True

            # check if all of the node's children are univalue subtrees and if they have the same value
            # also recursively call is_uni for children
            if node.left is not None:
                is_uni = is_uni(node.left) and is_uni and node.left.val == node.val

            if node.right is not None:
                is_uni = is_uni(node.right) and is_uni and node.right.val == node.val

            # increment self.res and return whether a univalue tree exists here
            count += is_uni
            return is_uni

        is_uni(root)
        return count

    def doit_search(self, root: TreeNode) -> int:
        
        from collections import defaultdict
        subtrees = defaultdict(int)
        
        if not root: return 0
        
        def search(node):

            if not node.left and not node.right:
                subtrees[node.val] += 1
                return True
            
            bres = True
            if node.left:
                bl = search(node.left)
                bres = bl and node.val == node.left.val
                    
            if node.right:
                br = search(node.right)
                bres = bres and br and node.val == node.right.val
                      
            if bres:
                subtrees[node.val] += 1
                
            return bres
        
        search(root)
        
        return sum(subtrees.values())

    """
        Approach 2: Depth First Search - Pass Parent Values
        Algorithm

        We can use the intuition from approach one to further simplify our algorithm. Instead of checking if a node has no children, we treat null values as univalue subtrees that we don't add to the count.

        In this manner, if a node has a null child, that child is automatically considered to a valid subtree, which results in the algorithm only checking if other children are invalid.

        Finally, the helper function checks if the current node is a valid subtree but returns a boolean indicating if it is a valid component for its parent. This is done by passing in the value of the parent node.
    """
    def countUnivalSubtrees(self, root):

        def is_valid_part(self, node, val):
            nonlocal count
            # considered a valid subtree
            if node is None: return True

            # check if node.left and node.right are univalue subtrees of value node.val
            if not all([is_valid_part(node.left, node.val),
                        is_valid_part(node.right, node.val)]):
                return False

            # if it passed the last step then this a valid subtree - increment
            count += 1

            # at this point we know that this node is a univalue subtree of value node.val
            # pass a boolean indicating if this is a valid subtree for the parent node
            return node.val == val

        count = 0
        is_valid_part(root, 0)
        return self.count


if __name__ == '__main__':

    obj = TreeNode(5)
    obj.left = TreeNode(1)
    obj.left.left = TreeNode(5)
    obj.left.right = TreeNode(5)

    obj.right = TreeNode(5)
    obj.right.right = TreeNode(5)

    CountUnivalSubtrees().doit_search(obj)
        