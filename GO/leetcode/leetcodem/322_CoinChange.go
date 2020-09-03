package leetcodem

/*

You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:

Input: coins = [1, 2, 5], amount = 11
Output: 3 
Explanation: 11 = 5 + 5 + 1
Example 2:

Input: coins = [2], amount = 3
Output: -1

*/

func coinChange_1(coins []int, amount int) int {

    dp := make([]int, amount + 1)
    dp[0] = 0
    
    for i := 1; i < amount + 1; i++ {
        res := amount
        
        for _, c := range coins {
            if i - c >= 0 && dp[i-c] < res {
                res = dp[i-c]
            }
        } 
        dp[i] = res + 1
    }

    if dp[amount] == amount + 1 {
        return -1
    }

    return dp[amount]
}