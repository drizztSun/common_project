package leetcodeE

import (
	"math"
)

type Stones [2]int

// res := []int{math.MinInt32, math.MaxInt32}

func (s Stones) search(node *TreeNode) {

	if node == nil {
		return
	}

	s.search(node.Left)

	if node.Val-s[0] < s[1] {
		s[1] = node.Val - s[0]
	}

	s.search(node.Right)
}

func minDiffInBST1(root *TreeNode) int {

	s := Stones{math.MinInt32, math.MaxInt32}
	s.search(root)
	return s[1]
}

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

func minDiffInBST2(root *TreeNode) int {

	res = []int{math.MinInt32, math.MaxInt32}
	searchTree(root)
	return res[1]
}
