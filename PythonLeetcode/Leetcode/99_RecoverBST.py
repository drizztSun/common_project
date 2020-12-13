"""
99. Recover Binary Search Tree

You are given the root of a binary search tree (BST), where exactly two nodes of the tree were swapped by mistake.
Recover the tree without changing its structure.

Follow up: A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?



Example 1:


Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.
Example 2:


Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.


Constraints:

The number of nodes in the tree is in the range [2, 1000].
-231 <= Node.val <= 231 - 1

"""


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class RecoverTree(object):

    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """
        def inorder(root, res):
            if not root:
                return

            inorder(root.left, res)
            res.append(root)
            inorder(root.right, res)

        res = []
        inorder(root, res)
        iStart, iEnd = -1, -1
        for i in range(1, len(res)):
            if res[i].val <= res[i - 1].val:
                 if iStart == -1:
                    iStart = i -1
                    iEnd = i
                 else :
                    iEnd = i
                    break

        res[iStart].val, res[iEnd].val = res[iEnd].val, res[iStart].val       

    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """
        if not root:
            return 
                       
        buff, pt, left = [], root, []
        while pt:
            while pt.left:
                left.append(pt)
                pt = pt.left
            
            buff.append(pt)
            pt = pt.right
            while not pt and left:
                pt = left.pop()
                buff.append(pt)
                pt = pt.right
                
        iStart, iEnd = -1, -1        
        for i in range(1, len(buff)):
            if buff[i].val < buff[i-1].val:
                if iStart == -1:
                    iStart = i-1
                    iEnd = i
                else:
                    iEnd = i
                    break
                    
        buff[iStart].val, buff[iEnd].val = buff[iEnd].val, buff[iStart].val

    # 
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """
        nlist = []
        self.inorder_traverse(root, nlist)
        node1, node2 = self.find_node_to_swap(nlist)
        node1.val, node2.val = node2.val, node1.val
        # return root

        def find_node_to_swap(nlist):
            # assume nlist should be always sorted.
            # find nodes which are not sorted.
            i = j = None
            left = 0
            for right in range(1, len(nlist)):
                if nlist[left].val > nlist[right].val:
                    if i is None:
                        # first time, set i
                        i = left
                    else:
                        # second time set j
                        j = right
                        break
                left += 1
            if j is None:
                # means node is swapped with its parent
                j = i + 1
            return nlist[i], nlist[j]

        def inorder_traverse(root, nlist):
            if root is None:
                return
            self.inorder_traverse(root.left, nlist)
            nlist.append(root)
            self.inorder_traverse(root.right, nlist)


if __name__=="__main__":
    
    a = TreeNode(2)
    a.right = TreeNode(1)

    res = RecoverTree().doit1(a)

    a = TreeNode(0)
    a.left = TreeNode(1)

    res = RecoverTree().doit1(a)