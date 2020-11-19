"""
309. Best Time to Buy and Sell Stock with Cooldown

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

Input: [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]


"""


class BestTimeSellStockWithCooldown:

    def doit_dp(self, prices):
        n = len(prices)
        dp = [[0] * 3 for _ in range(n + 1)]
        # 0 sold, 1 held, 2 reset
        dp[0][0], dp[0][1], dp[0][2] = float('-inf'), float('-inf'), 0

        for i in range(1, n + 1):
            dp[i][0] = dp[i - 1][1] + prices[i - 1]
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][2] - prices[i - 1])
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][0])

        return max(dp[n][0], dp[n][2])

    def doit_dp_1(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        sold, held, reset = float('-inf'), float('-inf'), 0

        for price in prices:
            # Alternative: the calculation is done in parallel.
            # Therefore no need to keep temporary variables
            #sold, held, reset = held + price, max(held, reset-price), max(reset, sold)

            pre_sold = sold
            sold = held + price
            held = max(held, reset - price)
            reset = max(reset, pre_sold)

        return max(sold, reset)


if __name__ == '__main__':

    BestTimeSellStockWithCooldown().doit_dp_1([1,2,4])

    BestTimeSellStockWithCooldown().doit_dp([1, 2, 4])


