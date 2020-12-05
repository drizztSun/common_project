"""
199. Binary Tree Right Side View

Given a binary tree, imagine yourself standing on the right side of it,
return the values of the nodes you can see ordered from top to bottom.

Example:

Input: [1,2,3,null,5,null,4]
Output: [1, 3, 4]
Explanation:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class RightSideView:

    def doit_bfs_search(self, root) -> list:
        from collections import deque

        if not root:
            return []

        buff = deque([root])
        ans = []

        while buff:
            cnt = len(buff)
            first = -1
            for _ in range(cnt):
                node = buff.popleft()

                if first == -1:
                    first = node.val

                if node.right:
                    buff.append(node.right)
                if node.left:
                    buff.append(node.left)
            ans.append(first)

        return ans

    def doit_dfs_(self, root) -> list:

        def dfs(node):
            if not node:
                return []

            right_list = dfs(node.right)
            left_list = dfs(node.left)

            res = list()
            res.append(node.val)
            res.extend(right_list)

            if len(left_list) > len(right_list):
                res.extend(left_list[len(right_list):len(left_list)])

            return res

        return dfs(root)





