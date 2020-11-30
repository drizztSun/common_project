"""
1522. Diameter of N-Ary Tree

Given a root of an N-ary tree, you need to compute the length of the diameter of the tree.

The diameter of an N-ary tree is the length of the longest path between any two nodes in the tree. This path may or may not pass through the root.

(Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value.)



Example 1:



Input: root = [1,null,3,2,4,null,5,6]
Output: 3
Explanation: Diameter is shown in red color.
Example 2:



Input: root = [1,null,2,null,3,4,null,5,null,6]
Output: 4
Example 3:



Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: 7


Constraints:

The depth of the n-ary tree is less than or equal to 1000.
The total number of nodes is between [0, 10^4].

"""


# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = []


class DiameterOfNAryTree:

    def doit_search(self, root: 'Node') -> int:
        """
        :type root: 'Node'
        :rtype: int
        """
        ans = 0

        def search(node):

            nonlocal ans
            l1, l2 = 0, 0

            for c in node.children:

                r = search(c)

                if r > l1:
                    l1 = r
                    l2 = l1
                elif r > l2:
                    l2 = r

            ans = max(ans, l1 + l2)
            return l1 + 1

        search(root)
        return ans

    def doit_search_1(self, root: 'Node') -> int:
        diameter = 0

        def height(node):
            """ return the height of the node """
            nonlocal diameter

            if len(node.children) == 0:
                return 0

            # select the top two heights
            max_height_1, max_height_2 = 0, 0
            for child in node.children:
                parent_height = height(child) + 1
                if parent_height > max_height_1:
                    max_height_1, max_height_2 = parent_height, max_height_1
                elif parent_height > max_height_2:
                    max_height_2 = parent_height

            # calculate the distance between the two farthest leaves nodes.
            distance = max_height_1 + max_height_2
            diameter = max(diameter, distance)

            return max_height_1

        height(root)
        return diameter

    """
    Approach 2: Distance with Depth
    Intuition
    
    The depth of a node is the length of the path to the root node.
    
    Still, we would like to know the longest path between two leaves nodes bridged by a non-leaf node. But this time we could calculate it with the concept of depth, rather than height.
    
    If we know the top two largest depths among two leaves nodes starting from the node, namely depth(node.leaf_m) and depth(node.leaf_n), then this longest path could be calculated as the sum of top two largest depths minus the depth of the parent node, namely
    
    Algorithm

    Let us define a function called maxDepth(node) which returns the maximum depth of the leaves nodes starting from the node.
    
    Again, we could implement it with recursion, with the following formula:
    
    \text{maxDepth(node)} = \max\big(\text{maxDepth(node.child)}\big), \space \forall \text{child} \in \text{node.children}maxDepth(node)=max(maxDepth(node.child)), ∀child∈node.children
    
    Similarly, within the function, we will also select the top two largest depths. With these top two largest depths, we will update the diameter accordingly.
    
    Complexity Analysis

    Let NN be the number of nodes in the tree.
    
    Time Complexity: O(N)
    
    We enumerate each node in the tree once and only once via recursion.
    Space Complexity: O(N)
    
    We employed only constant-sized variables in the algorithm.
    
    On the other hand, we used recursion which will incur additional memory consumption in the function call stack. In the worst case where all the nodes are chained up in a single path, the recursion will pile up NN times.
    
    As a result, the overall space complexity of the algorithm is O(N).
    """
    def doit_search_3(self, root: 'Node') -> int:
        """
        :type root: 'Node'
        :rtype: int
        """
        diameter = 0

        def maxDepth(node, curr_depth):
            """ return the maximum depth of leaves nodes
                 descending from the current node```123456788999990
            """
            nonlocal diameter

            if len(node.children) == 0:
                return curr_depth

            # select the top 2 depths from its children
            max_depth_1, max_depth_2 = curr_depth, 0
            for child in node.children:
                depth = maxDepth(child, curr_depth + 1)
                if depth > max_depth_1:
                    max_depth_1, max_depth_2 = depth, max_depth_1
                elif depth > max_depth_2:
                    max_depth_2 = depth

            # calculate the distance between the two farthest leaves nodes
            distance = max_depth_1 + max_depth_2 - 2 * curr_depth
            diameter = max(diameter, distance)

            return max_depth_1

        maxDepth(root, 0)
        return diameter


if __name__ == '__main__':

    node3 = Node(3)
    node3.children = [Node(5), Node(6)]

    root = Node(1)
    root.children = [node3, Node(2), Node(4)]

    DiameterOfNAryTree().doit_search(root)
