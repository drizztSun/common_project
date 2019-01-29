/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
package leetcodeE

import (
	"math"
	"strconv"
)

/*
655. Print Binary Tree

Print a binary tree in an m*n 2D string array following these rules:

The row number m should be equal to the height of the given binary tree.
The column number n should always be an odd number.
The root node's value (in string format) should be put in the exactly middle of the first row it can be put. The column and the row where the root node belongs will separate the rest space into two parts (left-bottom part and right-bottom part). You should print the left subtree in the left-bottom part and print the right subtree in the right-bottom part. The left-bottom part and the right-bottom part should have the same size. Even if one subtree is none while the other is not, you don't need to print anything for the none subtree but still need to leave the space as large as that for the other subtree. However, if two subtrees are none, then you don't need to leave space for both of them.
Each unused space should contain an empty string "".
Print the subtrees following the same rules.
Example 1:
Input:
     1
    /
   2
Output:
[["", "1", ""],
 ["2", "", ""]]
Example 2:
Input:
     1
    / \
   2   3
    \
     4
Output:
[["", "", "", "1", "", "", ""],
 ["", "2", "", "", "", "3", ""],
 ["", "", "4", "", "", "", ""]]
Example 3:
Input:
      1
     / \
    2   5
   /
  3
 /
4
Output:

[["",  "",  "", "",  "", "", "", "1", "",  "",  "",  "",  "", "", ""]
 ["",  "",  "", "2", "", "", "", "",  "",  "",  "",  "5", "", "", ""]
 ["",  "3", "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]
 ["4", "",  "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]]

*/

type treeNode struct {
	Val   int
	Left  *treeNode
	Right *treeNode
}

func depth(node *treeNode) int {

	if node == nil {
		return 0
	}

	if node.Left == nil && node.Right == nil {
		return 1
	}

	r := depth(node.Right)
	l := depth(node.Left)

	if r > l {
		return 1 + r
	} else {
		return 1 + l
	}

}

func fill(matrix [][]string, node *treeNode, i, start, end int) {
	if node == nil {
		return
	}

	mid := (start + end) / 2
	matrix[i][mid] = strconv.Itoa(node.Val)

	fill(matrix, node.Left, i+1, start, mid-1)
	fill(matrix, node.Right, i+1, mid+1, end)
}

func printTree(root *treeNode) [][]string {

	dep := depth(root)
	m, n := dep, int(math.Pow(2, float64(dep)))-1

	res := make([][]string, m)
	for i := range res {
		res[i] = make([]string, n)
		for j := range res[i] {
			res[i][j] = ""
		}
	}

	fill(res, root, 0, 0, n-1)
	return res
}
