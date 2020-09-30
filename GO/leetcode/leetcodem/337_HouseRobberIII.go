package leetcodem

/*
337. House Robber III

The thief has found himself a new place for his thievery again. There is only one entrance to this area, called the "root."
Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that "all houses in this place forms a binary tree".
It will automatically contact the police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:

Input: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \
     3   1

Output: 7
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:

Input: [3,4,5,1,3,null,1]

     3
    / \
   4   5
  / \   \
 1   3   1

Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

func maxint(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func search_rob3(root *TreeNode) (int, int) {

	if root == nil {
		return 0, 0
	}

	lw, lnw := search_rob3(root.Left)
	rw, rnw := search_rob3(root.Right)

	return root.Val + lnw + rnw, maxint(lw, lnw) + maxint(rw, rnw)
}

func rob_recursive(root *TreeNode) int {

	return maxint(search_rob3(root))
}

// wrong way
func rob_bfs(root *TreeNode) int {

	buf := []*TreeNode{root}
	rob, nonrob := 0, 0

	for len(buf) > 0 {

		n, amount := len(buf), 0
		for i := 0; i < n; i++ {

			node := buf[0]
			buf = buf[1:]

			if node.Left != nil {
				buf = append(buf, node.Left)
			}

			if node.Right != nil {
				buf = append(buf, node.Right)
			}
		}

		rob, nonrob = nonrob+amount, maxint(rob, nonrob)
	}

	return maxint(rob, nonrob)
}
