package leetcodem

/*

Given the root of a binary tree, return the inorder traversal of its nodes' values.


*/
func search_inorder(node *TreeNode) []int {

	if node == nil {
		return []int{}
	}

	left := search_inorder(node.Left)
	right := search_inorder(node.Right)

	return append(append(left, node.Val), right...)
}

func inorderTraversal_1(root *TreeNode) []int {

	return search_inorder(root)
}

func inorderTraversal_2(root *TreeNode) []int {

	node := root
	buf := make([]*TreeNode, 0)
	res := make([]int, 0)

	for node != nil || len(buf) > 0 {

		if node != nil {
			buf = append(buf, node)
			node = node.Left
		} else {
			res = append(res, buf[len(buf)-1].Val)
			node = buf[len(buf)-1].Right
			buf = buf[:len(buf)-1]
		}
	}

	return res
}
