package leetcodem

/*
343. Integer Break

Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.

Example 1:

Input: 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.
Example 2:

Input: 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
Note: You may assume that n is not less than 2 and not larger than 58.

*/

func integerBreak(n int) int {

	maxint := func(s []int) int {
		res := 0
		for _, c := range s {
			if res < c {
				res = c
			}
		}
		return res
	}

	dp := make([]int, n+1)
	dp[2] = 1

	for i := 3; i < n+1; i++ {

		for j := 1; j < i; j++ {

			dp[i] = maxint([]int{dp[i], j * (i - j), dp[j] * (i - j)})

		}
	}

	return dp[n]
}
