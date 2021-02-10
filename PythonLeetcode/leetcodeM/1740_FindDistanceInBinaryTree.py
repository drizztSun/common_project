"""
1740. Find Distance in a Binary Tree


Given the root of a binary tree and two integers p and q, return the distance between the nodes of value p and value q in the tree.

The distance between two nodes is the number of edges on the path from one to the other.



Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 0
Output: 3
Explanation: There are 3 edges between 5 and 0: 5-3-1-0.
Example 2:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 7
Output: 2
Explanation: There are 2 edges between 5 and 7: 5-2-7.
Example 3:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 5
Output: 0
Explanation: The distance between a node and itself is 0.


Constraints:

The number of nodes in the tree is in the range [1, 104].
0 <= Node.val <= 109
All Node.val are unique.
p and q are values in the tree.

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class FindDistance:

    def doit_recursive(self, root: 'TreeNode', p: int, q: int) -> int:

        ans = 0

        def search(node):
            nonlocal ans
            if not node: return 0

            l, r = search(node.left), search(node.right)

            if l != 0 and r != 0:
                ans = l + r

            elif (l != 0 or r != 0) and node.val in (p, q):
                ans = l + r

            return l + r + 1 if l + r != 0 or node.val in (p, q) else 0

        search(root)
        return ans

    def doit_bfs(self, root: 'TreeNode', p: int, q: int) -> int:

        from collections import deque
        if not root:
            return -1

        node_map = {}

        def preorder(node, parent):
            if not node:
                return
            node_map[node.val] = node
            node.parent = parent
            preorder(node.left, node)
            preorder(node.right, node)

        preorder(root, None)

        queue = deque([(node_map[p], 0)])
        visited = set()
        while queue:
            node, level = queue.popleft()
            if node in visited:
                continue
            visited.add(node)
            if node == node_map[q]:
                return level

            neighbors = [node.left, node.right, node.parent]
            for neighbor in neighbors:
                if neighbor and not neighbor in visited:
                    queue.append((neighbor, level + 1))

    def doit_(self, root, p, q):
        from collections import defaultdict, deque
        d = defaultdict(list)
        queue = deque()
        queue.appendleft(root)
        visited = defaultdict()

        while queue:
            top = queue.pop()
            visited[top.val] = False
            if top.left:
                queue.appendleft(top.left)
                d[top.val].append(top.left.val)
                d[top.left.val].append(top.val)
            if top.right:
                queue.appendleft(top.right)
                d[top.val].append(top.right.val)
                d[top.right.val].append(top.val)

        queue = deque()
        queue.appendleft(p)
        visited[p] = True
        h = 0
        while queue:
            for i in range(len(queue)):
                top = queue.pop()
                if top == q: return h
                for neigh in d[top]:
                    if not visited[neigh]:
                        queue.appendleft(neigh)
                        visited[neigh] = True
            h += 1