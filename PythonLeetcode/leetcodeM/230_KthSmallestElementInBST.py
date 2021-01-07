"""
230. Kth Smallest Element in a BST

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

 

Example 1:

Input: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
Output: 1
Example 2:

Input: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
Output: 3
Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

 

Constraints:

The number of elements of the BST is between 1 to 10^4.
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.


"""


class KthSmallestInBST:

    def doit_search(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: int
        """
        def search(node):
            if not node:
                return []
            res = search(node.left) + [node.val] + search(node.right)
            return res

        res = search(root)
        return None if len(res) < k else res[k-1]

    def doit_search(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: int
        """        
        cur, buff, res = root, [], []

        while cur or buff:

            if cur:
                buff.append(cur)
                cur = cur.left
            else:
                while not cur and buff:
                    cur = buff.pop()
                    k-=1
                    if k == 0:
                        return cur.val
                    
                    cur = cur.right
        return 0

    def doit_search(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: int
        """
        cur, buff, res = root, [], []

        while cur:

            if cur.left:
                buff.append(cur)
                cur = cur.left
            else :
                res.append(cur)
                while not cur.right and buff:
                    cur = buff.pop()
                    res.append(cur)

                cur = cur.right
                
            if len(res) >= k:
                return res[k-1].val

        return 0