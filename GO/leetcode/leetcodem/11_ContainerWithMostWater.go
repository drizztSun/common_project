package leetcodem

/*
11. Container With Most Water

Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai).
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0).
Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

Example:

Input: [1,8,6,2,5,4,8,3,7]
Output: 49
*/

func maxArea_dp(height []int) int {

	min := func(a, b int) int {
		if a < b {
			return a
		}
		return b
	}

	left, right := 0, len(height) - 1
	res := 0

	for left <= right {

		area := min(height[left], height[right]) * (right - left)
		if res < area {
			res = area
		}
		if height[left] < height[right] {
			left++
		} else {
			right--
		}

	}

	return res
}