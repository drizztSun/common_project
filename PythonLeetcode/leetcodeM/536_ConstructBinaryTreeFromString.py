"""
536. Construct Binary Tree from String


You need to construct a binary tree from a string consisting of parenthesis and integers.

The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis.
The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure.

You always start to construct the left child node of the parent first if it exists.



Example 1:


Input: s = "4(2(3)(1))(6(5))"
Output: [4,2,6,3,1,5]
Example 2:

Input: s = "4(2(3)(1))(6(5)(7))"
Output: [4,2,6,3,1,5,7]
Example 3:

Input: s = "-4(2(3)(1))(6(5)(7))"
Output: [-4,2,6,3,1,5,7]


Constraints:

0 <= s.length <= 3 * 104
s consists of digits, '(', ')', and '-' only.


"""


class ConstructBinaryTreeFromString:

    def doit_recursive(self, s: str) -> 'TreeNode':

        if not s: return None

        def search(i):

            num, sign, left, right = 0, 1, None, None
            while i < len(s):

                if s[i].isdigit():
                    num = num * 10 + int(s[i])
                elif s[i] == '-':
                    sign = -sign
                elif s[i] == '(':

                    i, child = search(i + 1)
                    if not left:
                        left = child
                    else:
                        right = child
                elif s[i] == ')':
                    break
                i += 1

            return i, TreeNode(sign * num, left, right)

        return search(0)[1]

    def doit_stack(self, s: str) -> 'TreeNode':
        if not s:
            return None

        stack, num = [], ''

        for ch in s:
            if ch in "()":
                if ch == '(' and num:
                    stack.append(TreeNode(num))
                    num = ''
                elif ch == ")":
                    if num:
                        node, parent = TreeNode(num), stack[-1]
                        num = ''
                    else:
                        node, parent = stack.pop(), stack[-1]

                    if parent.left:
                        parent.right = node
                    else:
                        parent.left = node
            else:
                num += ch

        if num:
            stack = [TreeNode(num)]
        return stack[0]
