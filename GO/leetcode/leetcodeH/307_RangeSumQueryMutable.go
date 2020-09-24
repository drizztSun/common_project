package leetcodeH

import "fmt"

/*
	Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

	The update(i, val) function modifies nums by updating the element at index i to val.

	Example:

	Given nums = [1, 3, 5]

	sumRange(0, 2) -> 9
	update(1, 2)
	sumRange(0, 2) -> 8
*/

type NumArray struct {
	nums, e []int
}

func constructor(nums []int) NumArray {

	o := NumArray{}
	o.nums = make([]int, len(nums))
	for i := range o.nums {
		o.nums[i] = nums[i]
	}

	o.e = make([]int, len(nums)+1)
	for i := range nums {
		i++
		o.e[i] += nums[i-1]
		c := o.e[i]
		i += (-i) & i
		if i < len(o.e) {
			o.e[i] += c
		}
	}
	return o
}

func (this *NumArray) Update(i int, val int) {
	diff := val - this.nums[i]
	this.nums[i] = val
	i++

	for i < len(this.e) {
		this.e[i] += diff
		i += (-i) & i
	}
}

func (this *NumArray) SumRange(i int, j int) int {
	res := 0
	j++

	for j > 0 {
		res += this.e[j]
		j -= (-j) & j
	}

	for i > 0 {
		res -= this.e[i]
		i -= (-i) & i
	}

	return res
}

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

func Constructor(nums []int) NumArraySegment {

	return NumArraySegment{root: buildSegementTree(nums, 0, len(nums)-1)}
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

func (this *NumArraySegment) Update(i int, val int) {

	updateSegSum(this.root, i, val)
}

func searchSegSum(node *SegmentNode, s, e int) int {

	if s == node.S && e == node.E {
		return node.Total
	}

	mid := (node.S + node.E) / 2

	if mid >= e {
		return searchSegSum(node.Left, s, e)
	} else if mid < s {
		return searchSegSum(node.Right, s, e)
	} else {
		return searchSegSum(node.Left, s, mid) + searchSegSum(node.Right, mid+1, e)
	}
}

func (this *NumArraySegment) SumRange(i int, j int) int {
	return searchSegSum(this.root, i, j)
}

func testRangeSumQueryMutable() {

	o := constructor([]int{1, 3, 5})

	res := o.SumRange(0, 2)

	o.Update(1, 2)

	res = o.SumRange(0, 2)

	fmt.Println(res)

}
