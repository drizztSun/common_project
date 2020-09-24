package main

import (
	"fmt"
)

// Segment Tree
type SegmentNode struct {
	S, E        int
	Total       int
	Left, Right *SegmentNode
}

type NumArraySegment struct {
	root *SegmentNode
}

func buildSegementTree(nums []int, s, e int) *SegmentNode {

	a := SegmentNode{S: s, E: e}
	if s == e {
		a.Total = nums[s]
		return &a
	}

	mid := (s + e) / 2

	a.Left = buildSegementTree(nums, s, mid)
	a.Right = buildSegementTree(nums, mid+1, e)
	a.Total = a.Left.Total + a.Right.Total
	return &a
}

func updateSegSum(node *SegmentNode, i, val int) {
	if node.S == node.E && node.S == i {
		node.Total = val
		return
	}

	mid := (node.S + node.E) / 2

	if mid >= i {
		updateSegSum(node.Left, i, val)
	} else {
		updateSegSum(node.Right, i, val)
	}

	node.Total = node.Left.Total + node.Right.Total
	return
}

func searchSegSum(node *SegmentNode, s, e int) int {

	if s == node.S && e == node.E {
		return node.Total
	}

	mid := (node.S + node.E) / 2

	if mid >= e {
		return searchSegSum(node.Left, s, e)
	} else if mid <= s {
		return searchSegSum(node.Right, s, e)
	} else {
		return searchSegSum(node.Left, s, mid) + searchSegSum(node.Right, mid+1, e)
	}
}

type NumArray struct {
	root *SegmentNode
}

func Constructor(nums []int) NumArray {

	if len(nums) == 0 {
		return NumArray{}
	}

	return NumArray{root: buildSegementTree(nums, 0, len(nums)-1)}
}

func (this *NumArray) Update(i int, val int) {
	updateSegSum(this.root, i, val)
}

func (this *NumArray) SumRange(i int, j int) int {
	return searchSegSum(this.root, i, j)
}

func main() {
	fmt.Println("--- basic main function ---")

	num := Constructor([]int{0, 9, 5, 7, 3})

	num.SumRange(4, 4)

	num.SumRange(2, 4)

	num.SumRange(3, 3)

	num.Update(4, 5)

	num.Update(1, 7)

	num.Update(0, 8)

	num.SumRange(1, 2)

	num.Update(1, 9)

	num.SumRange(4, 4)

	num.Update(3, 4)

	// Test_null_interface()

	// Test_set()

	// test_hmac_hex()

	// basic()

	// test_closure()

	// test_json()

	// test_gzip()

	// test_sort()

	// test_struct()

	//Main_test_list()

	// test_array()

	//Test_str()

	//Test_strings()

	// test_uri()

	// test_time()

	// Test_io()

	// Test_strconver()

	// test_json()

	// test_reflect()

	// Test_os()

	// test_json()

	fmt.Println(" --- basic main function end --- ")
}
