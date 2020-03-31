package leetcodem

/*

979. Distribute Coins in Binary Tree


*/

func AbsInt(l int) int {
	if l < 0 {
		return -l
	}
	return l
}

func distributeCoins_search(node *TreeNode, ans *int) int {

	if node == nil {
		return 0
	}

	l := distributeCoins_search(node.Left, ans)
	r := distributeCoins_search(node.Right, ans)

	*ans += AbsInt(l) + AbsInt(r)

	return r + l + node.Val - 1
}

func distributeCoins(root *TreeNode) int {

	ans := 0
	distributeCoins_search(root, &ans)
	return ans
}
