package leetcode

/*
654. Maximum Binary Tree

Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
Construct the maximum tree by the given array and output the root node of this tree.

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    /
     2  0
       \
        1
Note:
The size of the given array will be in the range [1,1000].
*/

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

type constructMaximumBinaryTree int8

// doit
func build(nums []int, s, e int) *TreeNode {
	z := s
	for i := s; i < e; i++ {
		if nums[i] > nums[z] {
			z = i
		}
	}

	c := &TreeNode{nums[z], nil, nil}
	if z > s {
		c.Left = build(nums, s, z)
	}

	if z < e-1 {
		c.Right = build(nums, z+1, e)
	}

	return c
}

func (i *constructMaximumBinaryTree) doit(nums []int) *TreeNode {

	return build(nums, 0, len(nums))
}

// doit1
func (i *constructMaximumBinaryTree) doit1(nums []int) *TreeNode {

	return nil
}

// doit2
func (i *constructMaximumBinaryTree) doit2(nums []int) *TreeNode {
	if len(nums) == 0 {
		return nil
	}

	maxIndex := 0
	for i := range nums {
		if nums[i] > nums[maxIndex] {
			maxIndex = i
		}
	}

	return &TreeNode{nums[maxIndex], i.doit2(nums[:maxIndex]), i.doit2(nums[maxIndex+1:])}
}
