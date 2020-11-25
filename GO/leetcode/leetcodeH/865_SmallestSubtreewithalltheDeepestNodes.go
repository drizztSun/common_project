package leetcodeH

import "math"

/*
# 865. Smallest Subtree with all the Deepest Nodes

# Given a binary tree rooted at root, the depth of each node is the shortest distance to the root.

# A node is deepest if it has the largest depth possible among any node in the entire tree.

# The subtree of a node is that node, plus the set of all descendants of that node.

# Return the node with the largest depth such that it contains all the deepest nodes in its subtree.



# Example 1:

# Input: [3,5,1,6,2,0,8,null,null,7,4]
# Output: [2,7,4]
# Explanation:



# We return the node with value 2, colored in yellow in the diagram.
# The nodes colored in blue are the deepest nodes of the tree.
# The input "[3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]" is a serialization of the given tree.
# The output "[2, 7, 4]" is a serialization of the subtree rooted at the node with value 2.
# Both the input and output have TreeNode type.


# Note:

# The number of nodes in the tree will be between 1 and 500.
# The values of each node are unique.

*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

func search_deepernode(depth map[*TreeNode]int, node, parent *TreeNode) {

	if node == nil {
		return
	}

	depth[node] = depth[parent] + 1

	search_deepernode(depth, node.Left, node)
	search_deepernode(depth, node.Right, node)
}

func find(node *TreeNode, maxdepth int, depth map[*TreeNode]int) *TreeNode {

	if node == nil || depth[node] == maxdepth {
		return node
	}

	L, R := find(node.Left, maxdepth, depth), find(node.Right, maxdepth, depth)

	if L != nil && R != nil {
		return node
	} else if L != nil {
		return L
	} else {
		return R
	}
}

func subtreeWithAllDeepest1(root *TreeNode) *TreeNode {

	depth := make(map[*TreeNode]int)
	depth[nil] = -1

	search_deepernode(depth, root, nil)
	maxdepth := 0
	for _, v := range depth {
		if maxdepth < v {
			maxdepth = v
		}
	}

	return find(root, maxdepth, depth)
}

type res struct {
	Maxdepth int
	Ans      *TreeNode
}

func (obj *res) search_deepernode(node *TreeNode, depth int) int {
	if node == nil {
		return depth
	}

	L, R := obj.search_deepernode(node.Left, depth+1), obj.search_deepernode(node.Right, depth+1)

	lvl := int(math.Max(float64(L), float64(R)))

	if lvl > obj.Maxdepth {
		obj.Maxdepth = lvl
	}

	if L == R && L == obj.Maxdepth {
		obj.Ans = node
	}

	return lvl
}

func subtreeWithAllDeepest(root *TreeNode) *TreeNode {

	obj := res{-1, nil}

	obj.search_deepernode(root, 0)

	return obj.Ans
}
