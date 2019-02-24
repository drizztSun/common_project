package leetcodeE

import (
	"math"
)

var res []int

func searchTree(node *TreeNode) {

	if node == nil {
		return
	}

	searchTree(node.Left)

	if node.Val-res[0] < res[1] {
		res[1] = node.Val - res[0]
	}
	res[0] = node.Val

	searchTree(node.Right)
}

func minDiffInBST(root *TreeNode) int {

	res = []int{math.MinInt32, math.MaxInt32}
	searchTree(root)
	return res[1]
}
