"""
1530. Number of Good Leaf Nodes Pairs

Given the root of a binary tree and an integer distance. A pair of two different leaf nodes of a binary tree is said to be good if the length of the shortest path between them is less than or equal to distance.

Return the number of good leaf node pairs in the tree.



Example 1:


Input: root = [1,2,3,null,4], distance = 3
Output: 1
Explanation: The leaf nodes of the tree are 3 and 4 and the length of the shortest path between them is 3. This is the only good pair.
Example 2:


Input: root = [1,2,3,4,5,6,7], distance = 3
Output: 2
Explanation: The good pairs are [4,5] and [6,7] with shortest path = 2. The pair [4,6] is not good because the length of ther shortest path between them is 4.
Example 3:

Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2], distance = 3
Output: 1
Explanation: The only good pair is [2,5].
Example 4:

Input: root = [100], distance = 1
Output: 0
Example 5:

Input: root = [1,1,1], distance = 2
Output: 1


Constraints:

The number of nodes in the tree is in the range [1, 2^10].
Each node's value is between [1, 100].
1 <= distance <= 10

"""


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class GoodLeafNodePairs:

    def doit_(self, root: 'TreeNode', distance: int) -> int:

        ans = 0

        def search(node):
            nonlocal ans

            if not node:
                return {}

            if not node.left and not node.right:
                return {1: 1}

            l, r = search(node.left), search(node.right)

            if l and r:
                tmp = 0
                for i in range(1, distance):
                    if i in l:
                        ans += sum(r[c] for c in r if c < distance - i)
                    #if i in r:
                    #    tmp += sum(l[c] for c in l if c <= distance - i)

               #for k1, v1 in l.items():
                #    for k2, v2 in r.items():
                #        if k1 + k2 <= distance:
                #            ans += v1 * v2

                return {i + 1: l.get(i, 0) + r.get(i, 0) for i in range(1, distance)}

            c = l if l else r
            return {i + 1: c[i] for i in range(1, distance) if i in c}

        search(root)
        return ans

    """
    For each node, compute the # of good leaf pair under itself.
    1. count the frequency of leaf node at distance 1, 2, …, d for both left and right child.
    2. ans += l[i] * r[j] (i + j <= distance) cartesian product
    3. increase the distance by 1 for each leaf node when pop
    Time complexity: O(n*D^2)
    Space complexity: O(n)
    """
    def doit_search(self, root: TreeNode, D: int) -> int:

        def dfs(node):
            f = [0] * (D + 1)
            if not node: return f, 0
            if not node.left and not node.right:
                f[0] = 1
                return f, 0

            fl, pl = dfs(node.left)
            fr, pr = dfs(node.right)

            pairs = 0
            for dl, cl in enumerate(fl):
                for dr, cr in enumerate(fr):
                    if dl + dr + 2 <= D:
                        pairs += cl * cr

            for i in range(D):
                f[i + 1] = fl[i] + fr[i]

            return f, pl + pr + pairs

        return dfs(root)[1]


if __name__ == '__main__':

    obj = TreeNode(1)
    obj.left = TreeNode(2)
    obj.right= TreeNode(3)
    obj.left.right = TreeNode(4)

    GoodLeafNodePairs().doit_(obj, 3)

    obj = TreeNode(1)
    obj.left = TreeNode(2)
    obj.right = TreeNode(3)

    obj.left.left = TreeNode(4)
    obj.left.right = TreeNode(5)

    obj.right.left = TreeNode(6)
    obj.right.right = TreeNode(7)

    GoodLeafNodePairs().doit_(obj, 3)

    obj = TreeNode(7)
    obj.left = TreeNode(1)
    obj.right = TreeNode(4)

    obj.left.left = TreeNode(6)
    obj.right.left = TreeNode(5)

    obj.right.right = TreeNode(3)
    obj.right.right.right = TreeNode(2)

    GoodLeafNodePairs().doit_(obj, 3)
