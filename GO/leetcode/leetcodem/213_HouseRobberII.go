package leetcodem

/*
213. House Robber II

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed.
All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one.
Meanwhile, adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2),
             because they are adjacent houses.
Example 2:

Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.
*/

func robII_dp(nums []int) int {

	maxint := func(a, b int) int {
		if a > b {
			return a
		}
		return b
	}

	rob, nonrob := 0, 0
	for i := 0; i < len(nums)-1; i++ {
		rob, nonrob = nonrob+nums[i], maxint(rob, nonrob)
	}

	res1 := maxint(rob, nonrob)

	rob, nonrob = 0, 0
	for i := 1; i < len(nums); i++ {
		rob, nonrob = nonrob+nums[i], maxint(rob, nonrob)
	}

	res2 := maxint(rob, nonrob)

	return maxint(res1, res2)
}
