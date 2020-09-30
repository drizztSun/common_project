package leetcodeH

/*
312. Burst Balloons

Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums.
You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i.
After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:

You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
Example:

Input: [3,1,5,8]
Output: 167
Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
*/

func search_max_coins(nums []int, s, e int, dp [][]int) int {

	if dp[s][e] != -1 {
		return dp[s][e]
	}

	if s > e {
		return 0
	}

	maxv := 0
	for i := s; i <= e; i++ {

		res := nums[s-1]*nums[i]*nums[e+1] + search_max_coins(nums, s, i-1, dp) + search_max_coins(nums, i+1, e, dp)
		if res > maxv {
			maxv = res
		}
	}

	dp[s][e] = maxv
	return maxv
}

func maxCoins_dp_1(nums []int) int {

	if len(nums) == 0 {
		return 0
	}

	nums = append([]int{1}, nums...)
	nums = append(nums, 1)

	dp := make([][]int, len(nums))
	for i := range dp {
		dp[i] = make([]int, len(nums))
		for j := range dp {
			dp[i][j] = -1
		}
	}

	return search_max_coins(nums, 1, len(nums)-2, dp)
}

func maxCoins_dp_2(nums []int) int {

	nums = append(nums, 1)
	nums = append([]int{1}, nums...)

	dp := make([][]int, len(nums))
	for i := range dp {
		dp[i] = make([]int, len(nums))
	}

	for step := 1; step < len(nums)-1; step++ {

		for j := 1; j < len(nums)-step; j++ {

			for k := j; k < j+step; k++ {

				res := nums[j-1]*nums[k]*nums[j+step] + dp[j][k-1] + dp[k+1][j+step-1]

				if res > dp[j][j+step-1] {
					dp[j][j+step-1] = res
				}
			}
		}
	}

	return dp[1][len(nums)-2]
}
