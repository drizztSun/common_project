package leetcodeH

/*
652. Find Duplicate Subtrees

Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with same node values.

Example 1:

        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
The following are two duplicate subtrees:

      2
     /
    4
and

    4
Therefore, you need to return above trees' root in the form of a list.

*/

import (
	"strconv"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

type data struct {
	val  int
	node *TreeNode
}

func duplicate(node *TreeNode, buff *map[string]data) string {

	if node == nil {
		return "x "
	}

	key := strconv.Itoa(node.Val) + " " + duplicate(node.Left, buff) + duplicate(node.Right, buff)

	dpl := *buff
	if v, ok := dpl[key]; ok {
		v.val += 1
		dpl[key] = v
	} else {
		dpl[key] = data{1, node}
	}

	return key
}

func findDuplicateSubtrees(root *TreeNode) []*TreeNode {

	buff := make(map[string]data)
	duplicate(root, &buff)

	var res []*TreeNode
	for _, v := range buff {
		if v.val > 1 {
			res = append(res, v.node)
		}
	}

	return res
}
