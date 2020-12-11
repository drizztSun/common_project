"""
1145. Binary Tree Coloring Game

Two players play a turn based game on a binary tree.  We are given the root of this binary tree, and the number of nodes n in the tree.  n is odd, and each node has a distinct value from 1 to n.

Initially, the first player names a value x with 1 <= x <= n, and the second player names a value y with 1 <= y <= n and y != x.  The first player colors the node with value x red, and the second player colors the node with value y blue.

Then, the players take turns starting with the first player.  In each turn, that player chooses a node of their color (red if player 1, blue if player 2) and colors an uncolored neighbor of the chosen node (either the left child, right child, or parent of the chosen node.)

If (and only if) a player cannot choose such a node in this way, they must pass their turn.  If both players pass their turn, the game ends, and the winner is the player that colored more nodes.

You are the second player.  If it is possible to choose such a y to ensure you win the game, return true.  If it is not possible, return false.



Example 1:


Input: root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
Output: true
Explanation: The second player can choose the node with value 2.


Constraints:

root is the root of a binary tree with n nodes and distinct node values from 1 to n.
n is odd.
1 <= x <= n <= 100

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class BtreeGameWinningMove:

    """
    We need to count tree sizes of children of x node.
    Then the tree size of the rest of the tree could be calculated directly from these findings.
    x_parent = n - x_left - x_right - 1
    If any of the tree sizes gets the majority, it's possible for us to win:
    capacity > n - capacity

    """
    def doit_search(self, root, n: int, x: int) -> bool:

        left_cnt, right_cnt = 0, 0

        def dfs(node):
            nonlocal left_cnt, right_cnt
            if not node:
                return 0

            l, r = dfs(node.left), dfs(node.right)

            if node.val == x:
                left_cnt, right_cnt = l, r

            return l + r + 1

        total = dfs(root)

        parent = total - left_cnt - right_cnt - 1

        for c in (left_cnt, right_cnt, parent):
            if c > total - c:
                return True

        return False
