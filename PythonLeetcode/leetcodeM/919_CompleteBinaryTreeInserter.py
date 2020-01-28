# 919. Complete Binary Tree Inserter

# A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled,
# and all nodes are as far left as possible.

# Write a data structure CBTInserter that is initialized with a complete binary tree and supports the following operations:

# CBTInserter(TreeNode root) initializes the data structure on a given tree with head node root;

# CBTInserter.insert(int v) will insert a TreeNode into the tree with value node.val = v
# so that the tree remains complete, and returns the value of the parent of the inserted TreeNode;

# CBTInserter.get_root() will return the head node of the tree.


# Example 1:

# Input: inputs = ["CBTInserter","insert","get_root"], inputs = [[[1]],[2],[]]
# Output: [null,1,[1,2]]

# Example 2:

# Input: inputs = ["CBTInserter","insert","insert","get_root"], inputs = [[[1,2,3,4,5,6]],[7],[8],[]]
# Output: [null,3,4,[1,2,3,4,5,6,7,8]]


# Note:

# The initial given tree is complete and contains between 1 and 1000 nodes.
# CBTInserter.insert is called at most 10000 times per test case.
# Every value of a given or inserted node is between 0 and 5000.


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class CBTInserter:

    def __init__(self, root):
        from collections import deque
        self._root = root
        self._leaves = deque()

        buff = deque([root])
        while buff:
            c = buff.popleft()

            if c.left:
                buff.append(c.left)

            if c.right:
                buff.append(c.right)

            if c.left and c.right:
                continue

            self._leaves.append(c)

    def insert(self, v):

        newleaf = TreeNode(v)
        res = 0
        if self._leaves[0].left == None:
            self._leaves[0].left = newleaf
            res = self._leaves[0].val
        else:
            self._leaves[0].right = newleaf
            res = self._leaves.popleft().val

        self._leaves.append(newleaf)
        return res

    def get_root(self):

        return self._root


"""
Approach 1: Deque
Intuition

Consider all the nodes numbered first by level and then left to right. Call this the "number order" of the nodes.

At each insertion step, we want to insert into the node with the lowest number (that still has 0 or 1 children).

By maintaining a deque (double ended queue) of these nodes in number order, we can solve the problem. After inserting a node, that node now has the highest number and no children, so it goes at the end of the deque. To get the node with the lowest number, we pop from the beginning of the deque.

Algorithm

First, perform a breadth-first search to populate the deque with nodes that have 0 or 1 children, in number order.

Now when inserting a node, the parent is the first element of deque, and we add this new node to our deque.

Complexity Analysis

Time Complexity: The preprocessing is O(N)O(N), where NN is the number of nodes in the tree. Each insertion operation thereafter is O(1)O(1).

Space Complexity: O(N_{\text{cur}})O(N 
cur
​	
 ) space complexity, when the size of the tree during the current insertion operation is N_{\text{cur}}N 
cur
​
"""


class CBTInserter1(object):

    def __init__(self, root):
        self.deque = collections.deque()
        self.root = root
        q = collections.deque([root])
        while q:
            node = q.popleft()
            if not node.left or not node.right:
                self.deque.append(node)
            if node.left:
                q.append(node.left)
            if node.right:
                q.append(node.right)

    def insert(self, v):
        node = self.deque[0]
        self.deque.append(TreeNode(v))
        if not node.left:
            node.left = self.deque[-1]
        else:
            node.right = self.deque[-1]
            self.deque.popleft()
        return node.val

    def get_root(self):
        return self.root


# Your CBTInserter object will be instantiated and called as such:
if __name__ == '__main__':

    root = TreeNode(1)

    obj = CBTInserter(root)

    param_1 = obj.insert(2)

    param_2 = obj.get_root()

    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.left.left = TreeNode(4)
    root.left.right = TreeNode(5)
    root.right.left = TreeNode(6)

    obj = CBTInserter(root)
    param_1 = obj.insert(7)
    param_2 = obj.insert(8)
