


# 309. Best Time to Buy and Sell Stock with Cooldown

# Say you have an array for which the ith element is the price of a given stock on day i.

# Design an algorithm to find the maximum profit. You may complete as many transactions as you like
# (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

# You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
# After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
# Example:

# prices = [1, 2, 3, 0, 2]
# maxProfit = 3
# transactions = [buy, sell, cooldown, buy, sell]

class maxProfit(object):

    # <DP>
    def doit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        profit = [prices[i] - prices[i-1] for i in range(1, len(prices))]

        



if __name__=="__main__":

    res = maxProfit().doit([1, 2, 3, 0, 2])


    pass
        