package leetcodeH

import "container/list"

/*
239. Sliding Window Maximum

You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.



Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation:
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]
Example 3:

Input: nums = [1,-1], k = 1
Output: [1,-1]
Example 4:

Input: nums = [9,11], k = 2
Output: [11]
Example 5:

Input: nums = [4,-2], k = 2
Output: [4]

*/

func maxSlidingWindow_array(nums []int, k int) []int {

	buf := []int{}
	res := make([]int, 0)

	for i := range nums {

		for len(buf) > 0 && nums[buf[len(buf)-1]] < nums[i] {
			buf = buf[:len(buf)-1]
		}

		buf = append(buf, i)

		if i-buf[0] >= k {
			buf = buf[1:]
		}

		if i >= k-1 {
			res = append(res, nums[buf[0]])
		}
	}

	return res
}

func maxSlidingWindow_array_2(nums []int, k int) []int {

	lis := list.New()
	var res []int
	for i, _ := range nums {
		for i > 0 && lis.Len() > 0 && nums[i] > nums[lis.Back().Value.(int)] {
			lis.Remove(lis.Back())
		}
		for lis.Len() > 0 && lis.Front().Value.(int) < i-k+1 {
			lis.Remove(lis.Front())
		}
		lis.PushBack(i)
		if i >= k-1 {
			res = append(res, nums[lis.Front().Value.(int)])
		}
	}
	return res
}

func maxSlidingWindow_array_1(nums []int, k int) []int {

	curMax := -(1 << 31)
	maxCnt := 0
	for i := 0; i < len(nums)-(k-1); i++ {
		if maxCnt == 0 {
			curMax = -(1 << 31)
			for c := i; c < i+k; c++ {
				if nums[c] > curMax {
					curMax = nums[c]
					maxCnt = 1
				} else if nums[c] == curMax {
					maxCnt++
				}
			}
		} else {
			c := i + (k - 1)
			if nums[c] > curMax {
				curMax = nums[c]
				maxCnt = 1
			} else if nums[c] == curMax {
				maxCnt++
			}
		}

		rv := nums[i]
		nums[i] = curMax

		if rv == curMax {
			maxCnt--
		}
	}

	return nums[:len(nums)-(k-1)]
}
