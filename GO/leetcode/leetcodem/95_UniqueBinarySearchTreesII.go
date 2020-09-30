package leetcodem

/*
95. Unique Binary Search Trees II


Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

Example:

Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

func find_generateNumTree(s, e int, memo [][][]*TreeNode) []*TreeNode {

	if memo[s][e] != nil {
		return memo[s][e]
	}

	res := make([]*TreeNode, 0)

	for i := s; i <= e; i++ {

		left := []*TreeNode{nil}
		if i != s {
			left = find_generateNumTree(s, i-1, memo)
		}

		right := []*TreeNode{nil}
		if i != e {
			right = find_generateNumTree(i+1, e, memo)
		}

		for _, l := range left {
			for _, r := range right {
				root := &TreeNode{Val: i, Left: nil, Right: nil}
				root.Left = l
				root.Right = r
				res = append(res, root)
			}
		}

	}

	if len(res) == 0 {
		res = []*TreeNode{nil}
	}

	memo[s][e] = res
	return res
}

func generateTrees_dp(n int) []*TreeNode {
	if n == 0 {
		return make([]*TreeNode, 0)
	}

	memo := make([][][]*TreeNode, n+1)
	for i := 0; i <= n; i++ {
		memo[i] = make([][]*TreeNode, n+1)
	}

	return find_generateNumTree(1, n, memo)
}

func Test_95_UniqueBinarySearchTreeII() {

	generateTrees_dp(3)
}
