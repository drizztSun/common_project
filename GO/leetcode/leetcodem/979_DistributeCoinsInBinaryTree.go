package leetcodem

/*

979. Distribute Coins in Binary Tree


*/

// Definition for a binary tree node.
type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func AbsInt(l int) int {
	if l < 0 {
		return -l
	}
	return l
}

func search(node *TreeNode, ans *int) int {

	if node == nil {
		return 0
	}

	l := search(node.Left, ans)
	r := search(node.Right, ans)

	*ans += AbsInt(l) + AbsInt(r)

	return r + l + node.Val - 1
}

func distributeCoins(root *TreeNode) int {

	ans := 0
	search(root, &ans)
	return ans
}
