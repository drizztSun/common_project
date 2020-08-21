package leetcodem

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

type TreeNode struct {
	Val int
	Left *TreeNode
	Right *TreeNode
}

func flatten(root *TreeNode)  {
	
	for root != nil {
        
        if root.Left == nil {
            root = root.Right
            continue
        }
        
        pre := root.Left
        for pre.Right != nil{
            pre = pre.Right
        }
            
        pre.Right = root.Right
        root.Right = root.Left
        root.Left = nil
        root = root.Right
    }
}

func dfs(root *TreeNode, pre *TreeNode) {
	if root == nil {
		return
	}

	dfs(root.Right, pre)
	dfs(root.Left, pre)
	root.Left = nil
	root.Right = pre

	pre = root
}

func flatten2(root *TreeNode) {

	if root != nil {
		return
	}

	var pre *TreeNode
	dfs(root, pre)
}