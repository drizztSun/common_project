/*
309. Best Time to Buy and Sell Stock with Cooldown

You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:

After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
Example 2:

Input: prices = [1]
Output: 0
 

Constraints:

1 <= prices.length <= 5000
0 <= prices[i] <= 1000

*/
#include <vector>

using std::vector;


class StockProfitWithCoolDown {

    /*
        309.Best-Time-to-Buy-and-Sell-Stock-with-Cooldown
        此题和该系列的其他题目一样，用几个状态变量来做DP。此题比较特殊的情况是，仅有hold和sold两个状态是不够的。
        我们考虑hold表示手头有股票时候的收益，sold表示手头已经卖出了股票的收益，题目可知我们试图更新sold的时候不能用hold+price[i]，所以我们还需要sold_cd表示手头的股票已经出手了一天以上。

        我们不难分析出这三个状态的转移方程是：

        hold = max(hold, sold_cd-prices[i])
        sold = max(sold, hold+prices[i])
        sold_cd = sold
        注意所有等号右边的状态变量应该是上一轮的，所以会需要在更新前先缓存一下。
    */

    int doit_dp(vector<int>& prices) {
        
        int n = prices.size();
        
        int hold = INT_MIN/2, sell = 0, cooldown = 0;

        for (int i = 0; i < n; i++) {

            int lasthold = hold, lastsell = sell, lastcooldown = cooldown;
            hold = std::max(lasthold, lastcooldown - prices[i]);
            sell = std::max(lastsell, lasthold + prices[i]);
            cooldown = lastsell;
        }

        return sell;
    }
};
