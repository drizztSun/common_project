
# 121. Best Time to Buy and Sell Stock

class maxProfit_121:
    def doit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        diff, minv = 0, float('inf')
        for i in range(len(prices)):
            if i != 0:
                diff = max(diff, prices[i] - minv)
            minv = min(minv, prices[i])

        return diff

# 122. Best Time to Buy and Sell Stock II

class maxProfit_122:
    def doit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        maxV = 0
        for i in range(1, len(prices)):
            diff = prices[i] - prices[i-1]
            if diff > 0:
                maxV += diff
        return maxV
        

        
"""
123. Best Time to Buy and Sell Stock III

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
Example 2:

Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.
Example 3:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
Example 4:

Input: prices = [1]
Output: 0
 

Constraints:

1 <= prices.length <= 105
0 <= prices[i] <= 105
"""


class maxProfit:

    # <DP>
    def doit_dp(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        # f[k, ii] represents the max profit up until prices[ii] (Note: NOT ending with prices[ii]) using at most k transactions. 
        # f[k, ii] = max(f[k, ii-1], prices[ii] - prices[jj] + f[k-1, jj]) { jj in range of [0, ii-1] }
        #          = max(f[k, ii-1], prices[ii] + max(f[k-1, jj] - prices[jj]))
        # f[0, ii] = 0; 0 times transation makes 0 profit
        # f[k, 0] = 0; if there is only one price data point you can't make any money no matter how many times you can trade

        if not prices:
            return 0

        k, maxv = 2, 0
        DP = [[0] * len(prices) for _ in range(k+1)]

        for x in range(1, (k+1)):

            tmpMaxii = DP[k-1][0] - prices[0]

            for i in range(1, len(prices)):

                DP[x][i] = max(DP[x][i-1], prices[i] + tmpMaxii)
        
                tmpMaxii = max(tmpMaxii, DP[x-1][i] - prices[i])

                maxv = max(DP[x][i], maxv)

        return maxv

    def doit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        if not prices:
            return 0
        
        left, minv, = [0] * len(prices), float('inf')
        for i in range(len(prices)):
            if i != 0:
                left[i] = max(left[i-1], prices[i] - minv)
            minv = min(minv, prices[i])

        right, maxv = [0] * len(prices), float('-inf')
        for i in reversed(range(len(prices))):
            if i != len(prices)-1:
                right[i] = max(right[i+1], maxv - prices[i])
            maxv = max(maxv, prices[i])

        maxv = 0
        for i in range(len(prices)-1):
            maxv = max(maxv, left[i] + right[i+1])

        maxv = max(maxv, right[0]) # or left[-1]
        return maxv


if __name__ == "__main__":

    res = maxProfit().doit([2,1,2,0,1])
        
    res = maxProfit().doit([1, 2])

    res = maxProfit().doit([1, 2, 3, 4, 5, 6])

    res = maxProfit().doit([2, 3, 1, 6, 7, 9, 1, 3, 2, 6, 4, 7, 9, 10, 12, 1])

    res = maxProfit().doit([1])