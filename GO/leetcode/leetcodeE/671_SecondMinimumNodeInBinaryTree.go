package leetcodeE

import "sort"

/*
671. Second Minimum Node In a Binary Tree
Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes.

Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

Example 1:
Input:
    2
   / \
  2   5
     / \
    5   7

Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.
Example 2:
Input:
    2
   / \
  2   2

Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

type SecTreeNode struct {
	Val   int
	Left  *SecTreeNode
	Right *SecTreeNode
}

func search(node *SecTreeNode) []int {

	if node == nil {
		return nil
	}

	left := search(node.Left)
	right := search(node.Right)

	s := make(map[int]bool)
	for _, c := range left {
		s[c] = true
	}

	for _, c := range right {
		s[c] = true
	}

	s[node.Val] = true

	var res []int
	for k := range s {
		res = append(res, k)
	}

	sort.Ints(res)

	if len(s) >= 2 {
		return res[:2]
	}

	return res
}

func findSecondMinimumValue(root *SecTreeNode) int {

	ans := search(root)
	if len(ans) == 2 {
		return ans[1]
	} else {
		return -1
	}
}
