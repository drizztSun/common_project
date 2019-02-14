package leetcodeE

/*
669. Trim a Binary Search Tree

Given a binary search tree and the lowest and highest boundaries as L and R, trim the tree so that all its elements lies in [L, R] (R >= L). You might need to change the root of the tree, so the result should return the new root of the trimmed binary search tree.

Example 1:
Input:
    1
   / \
  0   2

  L = 1
  R = 2

Output:
    1
      \
       2
Example 2:
Input:
    3
   / \
  0   4
   \
    2
   /
  1

  L = 1
  R = 3

Output:
      3
     /
   2
  /
 1
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

func trim(node *TreeNode, L, R int) *TreeNode {

	if node == nil {
		return node
	} else if node.Val < L {
		return trim(node.Right, L, R)
	} else if node.Val > R {
		return trim(node.Left, L, R)
	} else {
		node.Left = trim(node.Left, L, R)
		node.Right = trim(node.Right, L, R)
		return node
	}

}

func trimBST(root *TreeNode, L int, R int) *TreeNode {

	return trim(root, L, R)
}
