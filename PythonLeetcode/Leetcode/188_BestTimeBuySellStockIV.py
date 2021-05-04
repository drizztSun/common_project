"""
188. Best Time to Buy and Sell Stock IV

You are given an integer array prices where prices[i] is the price of a given stock on the ith day.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Notice that you may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).



Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.


Constraints:

0 <= k <= 109
0 <= prices.length <= 1000
0 <= prices[i] <= 1000

"""


import heapq


class maxProfit:

    # <heap>
    def doit_heap(self, k, prices):
        """
        :type k: int
        :type prices: List[int]
        :rtype: int
        """
        length = len(prices)
        v = p = 0
        pairs, profits = [], []
        
        while p < length:
            
            v = p
            while v < length - 1 and prices[v] >= prices[v+1]:
                v += 1

            p = v+1
            while p < length and prices[p] >= prices[p-1]:
                p += 1

            
            while pairs and prices[v] < prices[pairs[-1][0]]:
                heapq.heappush(profits, prices[pairs[-1][0]] - prices[pairs[-1][1] - 1])
                pairs.pop()

            while pairs and prices[p-1] >= prices[pairs[-1][1] - 1]:
                heapq.heappush(profits, prices[v] - prices[pairs[-1][1] - 1])
                v = pairs[-1][0]
                pairs.pop()

            pairs.append((v, p))

        while pairs:
            heapq.heappush(profits, prices[pairs[-1][0]] - prices[pairs[-1][1] - 1])
            pairs.pop()


        ans = 0
        while k != 0 and profits:
            ans += -heapq.heappop(profits)
            k -= 1
        return ans

    # <DP>
    def doit_dp(self, k, prices):
        """
        :type k: int
        :type prices: List[int]
        :rtype: int
        """
        # f[k, ii] represents the max profit up until prices[ii] (Note: NOT ending with prices[ii]) using at most k transactions. 
        # f[k, ii] = max(f[k, ii-1], prices[ii] - prices[jj] + f[k-1, jj]) { jj in range of [0, ii-1] }
        #          = max(f[k, ii-1], prices[ii] + max(f[k-1, jj] - prices[jj]))
        # f[0, ii] = 0; 0 times transation makes 0 profit
        # f[k, 0] = 0; if there is only one price data point you can't make any money no matter how many times you can trade

        if len(prices) < 2:
            return 0
        
        if k >= len(prices) // 2:
            return sum([i - j for i, j in zip(prices[1:], prices[:-1]) if i - j > 0])

        DP = [ [0] * len(prices) for _ in range(k+1) ]
        maxv = 0
        
        for x in range(1, (k+1)):
            
            tmpMax = DP[x-1][0] - prices[0]
            
            for i in range(1, len(prices)):
                
                DP[x][i] = max(DP[x][i-1], prices[i] + tmpMax)
                
                tmpMax = max(tmpMax, DP[x-1][i] - prices[i])
                
                maxv = max(maxv, DP[x][i])
                
        return maxv

    # <DP>
    def doit_dp_2(self, k, prices):
        """
        :type k: int
        :type prices: List[int]
        :rtype: int
        """
        n = len(prices)
        if n < 2:
            return 0
        # k is big enougth to cover all ramps.
        if k >= n / 2:
            return sum(i - j for i, j in zip(prices[1:], prices[:-1]) if i - j > 0)

        globalMax = [[0] * n for _ in range(k + 1)]
        for i in range(1, k + 1):
            # The max profit with i transations and selling stock on day j.
            localMax = [0] * n
            for j in range(1, n):
                profit = prices[j] - prices[j - 1]
                localMax[j] = max(
                    # We have made max profit with (i - 1) transations in
                    # (j - 1) days.
                    # For the last transation, we buy stock on day (j - 1)
                    # and sell it on day j.
                    globalMax[i - 1][j - 1] + profit,
                    # We have made max profit with (i - 1) transations in
                    # (j - 1) days.
                    # For the last transation, we buy stock on day j and
                    # sell it on the same day, so we have 0 profit, apparently
                    # we do not have to add it.
                    globalMax[i - 1][j - 1],  # + 0,
                    # We have made profit in (j - 1) days.
                    # We want to cancel the day (j - 1) sale and sell it on
                    # day j.
                    localMax[j - 1] + profit)
                globalMax[i][j] = max(globalMax[i][j - 1], localMax[j])
        return globalMax[k][-1]
