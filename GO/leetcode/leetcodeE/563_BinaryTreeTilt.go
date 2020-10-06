package leetcodeE

/*
563. Binary Tree Tilt

Given a binary tree, return the tilt of the whole tree.

The tilt of a tree node is defined as the absolute difference between the sum of all left subtree node values and the sum of all right subtree node values. Null node has tilt 0.

The tilt of the whole tree is defined as the sum of all nodes' tilt.

Example:
Input: 
         1
       /   \
      2     3
Output: 1
Explanation: 
Tilt of node 2 : 0
Tilt of node 3 : 0
Tilt of node 1 : |2-3| = 1
Tilt of binary tree : 0 + 0 + 1 = 1
*/

func abs(a int) int {
    if a < 0 {
        return -a
    }
    return a
}

func search(node *TreeNode) (int, int) {
    
    if node == nil {
        return 0, 0
    }
    
    ltilt, lsum := search(node.Left)
    rtilt, rsum := search(node.Right)
    
    return ltilt + rtilt + abs(lsum - rsum), lsum + rsum + node.Val
}

func findTilt_2(root *TreeNode) int {
    tilt, _ := search(root)
    return tilt
}


unc findTilt_1(root *TreeNode) int {
	result := 0
	itterate(root, &result)
	return result
}

func itterate(node *TreeNode, result *int) int {
	if node == nil {
		return 0
	}

	left, right := itterate(node.Left, result), itterate(node.Right, result)
	*result += absDiff(left, right)
	return left + right + node.Val
}

func absDiff(a, b int) int {
	diff := a - b
	if diff < 0 {
		diff = -diff
	}

	return diff
}