package leetcodem

/*

Return the root node of a binary search tree that matches the given preorder traversal.

(Recall that a binary search tree is a binary tree where for every node, any descendant of node.left has a value < node.val, and any descendant of node.right has a value > node.val.
Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)


Example 1:

Input: [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]

*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

func bstFromPreorder(preorder []int) *TreeNode {

	buf := make([]*TreeNode, 0)
	var root *TreeNode = nil

	for _, v := range preorder {

		if len(buf) == 0 {
			n := &TreeNode{Val: v}
			buf = append(buf, n)

			if root == nil {
				root = n
			}
			continue
		}

		n := &TreeNode{Val: v}

		if v < buf[len(buf)-1].Val {
			buf[len(buf)-1].Left = n
		} else {
			i := len(buf) - 1
			for ; i > -1; i-- {
				if buf[i].Val > v {
					break
				}
			}

			if i+1 < len(buf) {
				buf[i+1].Right = n
			}

			buf = buf[:i+1]
		}

		buf = append(buf, n)
	}

	return root
}

func Test_1008_ConstructBinarySearchTreeFromPreorderTraversal() {

	bstFromPreorder([]int{8, 5, 1, 7, 10, 12})

}
