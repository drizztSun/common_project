# 714. Best Time to Buy and Sell Stock with Transaction Fee

# Your are given an array of integers prices, for which the i-th element is the price of a given stock on day i;
# and a non-negative integer fee representing a transaction fee.

# You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.
# You may not buy more than 1 share of a stock at a time (ie. you must sell the stock share before you buy again.)

# Return the maximum profit you can make.

# Example 1:
# Input: prices = [1, 3, 2, 8, 4, 9], fee = 2
# Output: 8
# Explanation: The maximum profit can be achieved by:
# Buying at prices[0] = 1
# Selling at prices[3] = 8
# Buying at prices[4] = 4
# Selling at prices[5] = 9
# The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

class maxProfit:

# track profit of holding and unholding at day i 
# for holding, the max profit at day i is the bigger number between at day i-1 (meaning do nothing at day i) 
# and selling at day i-1 and minus the prices at day i (meaning buying in at day i)
# for unholding, the max profit at day is the bigger number between at day i-1 
# (meaning do nothing at day i) and buying at day i-1 and plus the prices at day i and minus transaction fee (meaning selling at day i)

    def doit(self, prices, fee):
        """
        :type prices: List[int]
        :type fee: int
        :rtype: int
        """
        hold = [0] * len(prices)
        unhold = [0] * len(prices)
        hold[0] = -prices[0]
        unhold[0] = 0
        
        for i in range(1, len(prices)):
            hold[i] = max(hold[i-1], unhold[i-1]-prices[i])
            unhold[i] = max(unhold[i-1], hold[i-1]+prices[i]-fee)
        return unhold[-1]


# For this question you have nothing more than 2 states - hold and sell
# Note for initialization, hold has to be negative infinity because you cannot hold any stock before you iterate through stock prices (for each stage). 
# Then it's DP like everyone said, the code in for loop defines state transition and how to get optimal values. 
# We don't need O(n) space since we only need the optimal values for each state (but not stage).
    # <DP>        
    def doit(self, prices, fee):
        """
        :type prices: List[int]
        :type fee: int
        :rtype: int
        """
        hold, sell = -float('inf'), 0

        for p in prices:
            hold = max(hold, sell - p - fee)
            sell = max(sell, hold + p)

        return sell

# For all those who don't understand why '''minimum = prices[i] - fee''' just like me at first.
# Here's the explanation with an example:
# prices = [1, 3, 4, 5, 4, 8], fee = 2
# Do you take profit of day0 to day3 (prices[3] - prices[0] = 4) and day4 to day5(prices[5] - prices[4] = 4) ?
# Or do you take profit of day0 to day5(prices[5] - prices[0] = 7)?
# Because transaction fee = 2 , (7-2) > (4-2 + 4-2), 2nd option is better.
# So we need to avoid greedily setting 'minimum = day4' , because sell at $5 and buy again at $4 only give us $1 more profit yet costs $2 more transaction fee.
# Open a new transaction only if prices[today] < prices[yesterday] - fee. That's why we set 'minimum = prices[i] - fee'
    # <greedy>
    def doit2(self, prices, fee):
        """
        :type prices: List[int]
        :type fee: int
        :rtype: int
        """
        if len(prices) < 2:
            return 0
        
        ans, minv = 0, prices[0]

        for i in range(1, len(prices)):
            if prices[i] < minv:
                minv = prices[i]
            elif prices[i] > minv + fee:
                ans += prices[i] - minv - fee
                miv = prices[i] - fee
        return ans