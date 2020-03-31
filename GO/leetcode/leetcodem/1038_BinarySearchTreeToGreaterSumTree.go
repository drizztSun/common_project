package leetcodem

/*

1038. Binary Search Tree to Greater Sum Tree

Given the root of a binary search tree with distinct values, modify it so that every node has a new value equal to the sum of the values of the original tree that are greater than or equal to node.val.

As a reminder, a binary search tree is a tree that satisfies these constraints:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.


Example 1:

Input: [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]

*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

import (
	"sort"
)

func bstToGst(root *TreeNode) *TreeNode {

	st := make([]*TreeNode, 0)
	st = append(st, root)

	for i := 0; i != len(st); i++ {

		if st[i].Left != nil {
			st = append(st, st[i].Left)
		}

		if st[i].Right != nil {
			st = append(st, st[i].Right)
		}
	}

	sort.Slice(st, func(i, j int) bool {
		return st[i].Val > st[j].Val
	})

	ans := 0
	for i := range st {
		ans += st[i].Val
		st[i].Val = ans
	}

	return root
}

func Test_1038_BinarySearchTreeToGreaterSumTree() {

}
