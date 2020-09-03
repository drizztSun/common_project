package leetcodem

import "fmt"

/*

518. Coin Change 2
Medium

2195

66

Add to List

Share
You are given coins of different denominations and a total amount of money. Write a function to compute the number of combinations that make up that amount. You may assume that you have infinite number of each kind of coin.



Example 1:

Input: amount = 5, coins = [1, 2, 5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
Example 2:

Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.
Example 3:

Input: amount = 10, coins = [10]
Output: 1


Note:

You can assume that

0 <= amount <= 5000
1 <= coin <= 5000
the number of coins is less than 500
the answer is guaranteed to fit into signed 32-bit integer

*/

func coin_change2_1(amount int, coins []int) int {

	dp := make([]int, amount+1)
	for i := range dp {
		dp[i] = 0
	}
	dp[0] = 1

	for _, c := range coins {
		for i := c; i < amount+1; i++ {
			if i-c >= 0 {
				dp[i] += dp[i-c]
			}
		}
	}

	fmt.Println(dp) // [1 1 2 2 3 4]

	return dp[amount]
}

// below has problem, it is gonna import duplicate resut {2, 1, 1}, {1, 1, 2} are the same one.
// so we have to feed coins{1, 2, 5} like above

func coin_change2_2(amount int, coins []int) int {

	dp := make([]int, amount+1)
	dp[0] = 1

	for i := 1; i < amount+1; i++ {
		dp[i] = 0

		for _, c := range coins {
			if i-c >= 0 {
				dp[i] += dp[i-c]
			}
		}
	}

	fmt.Println(dp) // [1 1 2 3 5 9]
	return dp[amount]
}
