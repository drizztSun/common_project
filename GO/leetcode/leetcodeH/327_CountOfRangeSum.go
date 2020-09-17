package leetcodeH

/*
327. Count of Range Sum

Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

Note:
A naive algorithm of O(n2) is trivial. You MUST do better than that.

Example:

Input: nums = [-2,5,-1], lower = -2, upper = 2,
Output: 3
Explanation: The three ranges are : [0,0], [2,2], [0,2] and their respective sums are: -2, -1, 2.


Constraints:

0 <= nums.length <= 10^4
*/

import (
	"sort"
)

func LowBit(i int) int {
	return ((i - 1) ^ i) & i
}

type Bit struct {
	E   []int
	Org []int
}

func NewBit(nums []int) *Bit {

	org := make([]int, len(nums))
	for i := 0; i < len(nums); i++ {
		org[i] = nums[i]
	}

	e := make([]int, len(nums)+1)
	for i := 1; i < len(e); i++ {
		e[i] = nums[i-1]
	}

	b := Bit{
		E:   e,
		Org: org,
	}
	b.CalSum()
	return &b
}

func (t *Bit) CalSum() {

	for i := 1; i < len(t.E); i++ {
		parent := LowBit(i) + i
		if parent < len(t.E) {
			t.E[parent] += t.E[i]
		}
	}
}

func (t *Bit) GetSum(n int) int {

	n++
	res := 0

	for n > 0 {
		res += t.E[n]
		n -= LowBit(n)
	}

	return res
}

func (t *Bit) Update(i int, n int) {

	parent := i + 1
	delta := n - t.Org[parent]

	for parent < len(t.E) {
		t.E[parent] += delta
		parent += LowBit(parent)
	}
}

func search_range_sum(nums []int, s, e int, lower, upper int) int {

	m := (s + e) / 2
	if m == s {
		return 0
	}

	count := search_range_sum(nums, s, m, lower, upper) + search_range_sum(nums, m, e, lower, upper)

	i, j := m, m

	for _, left := range nums[s:m] {

		for i < e && nums[i]-left < lower {
			i++
		}

		for j < e && nums[j]-left <= upper {
			j++
		}

		count += j - i
	}

	// sort
	sort.SliceStable(nums[s:e], func(i, j int) bool {
		return nums[i] < nums[j]
	})

	return count
}

func countRangeSum_1(nums []int, lower int, upper int) int {

	sums := make([]int, len(nums)+1)
	for i := range sums {
		if i == 0 {
			sums[i] = 0
		} else {
			sums[i] = sums[i-1] + nums[i-1]
		}
	}

	return search_range_sum(sums, 0, len(sums), lower, upper)
}

func countRangeSum_2(nums []int, lower int, upper int) int {
	sums := make([]int64, len(nums)+1)
	for i := 0; i < len(nums); i++ {
		sums[i+1] = sums[i] + int64(nums[i])
	}

	return countRangeSumHelper(sums, 0, len(sums)-1, int64(lower), int64(upper))
}

func countRangeSumHelper(sums []int64, start, end int, lower, upper int64) int {
	if start >= end {
		return 0
	}

	mid := start + (end-start)/2
	count := countRangeSumHelper(sums, start, mid, lower, upper) + countRangeSumHelper(sums, mid+1, end, lower, upper)
	left, right := mid+1, end
	for i := mid; i >= start; i-- {
		if i == mid {
			for right >= mid+1 && sums[right]-sums[i] > upper {
				right--
			}

			for left <= end && sums[left]-sums[i] < lower {
				left++
			}
			count += right - left + 1
		} else {
			for right >= mid+1 && sums[right]-sums[i] > upper {
				right--
			}

			for left > end || (left >= mid+1 && sums[left]-sums[i] >= lower) {
				left--
			}
			count += right - left
		}
	}

	temp := make([]int64, end-start+1)
	x, y, z := start, mid+1, 0
	for x < mid+1 && y < end+1 {
		if sums[x] < sums[y] {
			temp[z] = sums[x]
			x++
		} else {
			temp[z] = sums[y]
			y++
		}

		z++
	}
	for x < mid+1 {
		temp[z] = sums[x]
		x++
		z++
	}
	for y < end+1 {
		temp[z] = sums[y]
		y++
		z++
	}

	for i := 0; i < len(temp); i++ {
		sums[start+i] = temp[i]
	}

	return count
}
