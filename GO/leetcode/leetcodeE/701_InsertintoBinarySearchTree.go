package leetcodeE

/*
Given the root node of a binary search tree (BST) and a value to be inserted into the tree,
insert the value into the BST. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.

Note that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.

For example,

Given the tree:
        4
       / \
      2   7
     / \
    1   3
And the value to insert: 5
You can return this binary search tree:

         4
       /   \
      2     7
     / \   /
    1   3 5
This tree is also valid:

         5
       /   \
      2     7
     / \
    1   3
         \
          4
*/


/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func insertIntoBST(root *TreeNode, val int) *TreeNode {

    if root == nil {
        return &TreeNode{val, nil, nil}
    }

    node := root
    for ;node != nil; {

        if node.Val > val {
            if node.Left != nil {
                node.Left = &TreeNode{val, nil, nil}
                break
            } else {
                node = node.Left
            }

        } else {
            if node.Right != nil {
                node.Right = & TreeNode{val, nil, nil}
                break
            } else {
                node = node.Right
            }
        }

    }

    return root
}
