# 1028. Recover a Tree From Preorder Traversal

# We run a preorder depth first search on the root of a binary tree.

# At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  (If the depth of a node is D, the depth of its immediate child is D+1.  The depth of the root node is 0.)

# If a node has only one child, that child is guaranteed to be the left child.

# Given the output S of this traversal, recover the tree and return its root.


# Example 1:

# Input: "1-2--3--4-5--6--7"
# Output: [1,2,5,3,4,6,7]

# Example 2:

# Input: "1-2--3---4-5--6---7"
# Output: [1,2,5,3,null,6,null,4,null,7]

# Example 3:
# Input: "1-401--349---90--88"
# Output: [1,401,null,349,88,90]

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


from collections import defaultdict


class RecoverFromPreorder:
    def doit(self, S):

        stack = []
        for dashes, val in re.findall(r"(-*)(\d+)", S):
            level, node = len(dashes), TreeNode(int(val))
            while len(stack) > level:
                stack.pop()
            if stack:
                if stack[-1].left is None:
                    stack[-1].left = node
                else:
                    stack[-1].right = node
            stack.append(node)543
        return stack[0]

    def doit(self, S):

        buf = defaultdict(list)
        depth = 0
        i = 0

        while i < len(S):

            j = i
            while j < len(S) and S[j] == "-":
                j += 1

            depth = j - i
            i = j

            while j < len(S) and S[j].isdigit():
                j += 1

            c = int(S[i:j])
            i = j

            n = TreeNode(c)
            if depth - 1 in buf:
                if not buf[depth - 1][-1].left:
                    buf[depth - 1][-1].left = n
                else:
                    buf[depth - 1][-1].right = n

            buf[depth].append(n)
            depth = 0
            c = 0

        return buf[0][-1]


if __name__ == "__main__":

    res = RecoverFromPreorder().doit("1-2--3--4-5--6--7")

    res = RecoverFromPreorder().doit("1-2--3---4-5--6---7")

    res = RecoverFromPreorder().doit("1-401--349---90--88")

    pass
