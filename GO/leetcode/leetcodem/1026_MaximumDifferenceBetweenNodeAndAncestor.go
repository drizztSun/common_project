package leetcodem

/*
1026. Maximum Difference Between Node and Ancestor

Given the root of a binary tree, find the maximum value V for which there exists different nodes A and B
where V = |A.val - B.val| and A is an ancestor of B.

(A node A is an ancestor of B if either: any child of A is equal to B, or any child of A is an ancestor of B.)


Example 1:

Input: [8,3,10,1,6,null,14,null,null,4,7,13]
Output: 7
Explanation:
We have various ancestor-node differences, some of which are given below :
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.

*/

import (
	"math"
)

func maxInt(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func minInt(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func abs(a int) int {
	if a < 0 {
		return -a
	}
	return a
}

func search(node *TreeNode) (int, int, int) {

	if node.Left == nil && node.Right == nil {
		return node.Val, node.Val, 0
	}

	maxv, minv, r := 0, math.MaxInt32, 0
	if node.Left != nil {
		b, s, a := search(node.Left)

		a = maxInt(maxInt(a, abs(b-node.Val)), maxInt(a, abs(s-node.Val)))
		r = maxInt(r, a)
		maxv = maxInt(maxv, b)
		minv = minInt(minv, s)
	}

	if node.Right != nil {
		b, s, a := search(node.Right)

		a = maxInt(maxInt(a, abs(b-node.Val)), maxInt(a, abs(s-node.Val)))
		r = maxInt(r, a)
		maxv = maxInt(maxv, b)
		minv = minInt(minv, s)
	}

	return maxInt(maxv, node.Val), minInt(minv, node.Val), r
}

func maxAncestorDiff(root *TreeNode) int {

	_, _, ans := search(root)
	return ans
}
