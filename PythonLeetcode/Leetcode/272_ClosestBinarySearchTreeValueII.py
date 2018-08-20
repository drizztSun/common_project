


# 272 Cloest Binary Search Tree Value II

# Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

# Note:

# Given target value is a floating point.
# You may assume k is always valid, that is: k ? total nodes.
# You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
 

# Follow up:
# Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

# Hint:

# Consider implement these two helper functions:
# getPredecessor(N), which returns the next smaller node to N.
# getSuccessor(N), which returns the next larger node to N.
# Try to assume that each node has a parent pointer, it makes the problem much easier.
# Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
# You would need two stacks to track the path in finding predecessor and successor node separately.

class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


import heapq
class CloestBinarySearchTreeValuII:

    # O(n) <inorder>
    def doit(self, root, val, k):
        """
        type: node
        typt: double
        rtype: list[int]
        """
        res = []
        def search(node):
            if not node:
                return

            search(node.left)
            if len(res) == k and abs(node.val - val) < abs(val + res[0]):
                heapq.heappop()
            else:
                return
            
            heapq.heappush(res, -node.val)
            search(node.right)

        return res

    # O(n) <preorder>
    def doit(self, root, val, k):
        """
        type: node
        typt: int
        rtype: list[int]
        """
        import heapq
        res = []
        def search(node, val):
            if not node:
                return

            if len(res) == k and abs(val - node.val) < -res[0][0]:
                heapq.heappush(res, (-abs(val - node.val), node.val))
                heapq.heappop()

            search(node.left, val)
            search(node.right, val)

            return

        search(root)
        return [ res[i][1] for i in range(len(res))]
    

    # O(logN)
    def doit(self, root, val, K):
        """
        type: node
        typt: int
        rtype: int
        """
        left, right = [], []
        res = []
        def search(node):

            if not node:
                return

            if len(res) == K:
                if abs(node.val - val) > abs(res[-1] - val):
                    heapq.heappop()
            heapq.heappush(res, node.val)

            
        

    # O(logN)
    def doit(self, root, val):
        """
        type: node
        typt: int
        rtype: int
        """
        import heapq
        res = []
        buff = []
        path = set()
        def search(node, val):

            if not node:
                return 

            if node in path:
                return

            path.add(node)

            if len(buff) < k:
                heapq.heappush(buff, (-abs(val - node.val), node))

                if node.left and node.right:
                    if abs(node.left.val - val) < abs(node.right.val - val):
                        search(node.left, val)
                        search(node.right, val)
                    else:
                        search(node.right, val)
                        search(node.left, val)
            else:
                if abs(val - node.val) < -buff[0][0]:
                    heapq.heappush(buff, (-abs(val - node.val), node))
                    heapq.heappop()
                    search(node.right, val)
                    search(node.left, val)
                else:
                    return

        search(root)

        return        