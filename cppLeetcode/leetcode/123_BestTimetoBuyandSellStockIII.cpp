/*

123. Best Time to Buy and Sell Stock III

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note: You may not engage in multiple transactions at the same time 
(i.e., you must sell the stock before you buy again).

Example 1:

Input: [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

Example 2:

Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
engaging multiple transactions at the same time. You must sell before buying again.

Example 3:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.


*/

#include <vector>
#include <algorithm>
using namespace std;

class StockMaxProfit {

	/*
		123.Best-Time-to-Buy-and-Sell-Stock-III
		此题属于DP的范畴,但是不需要存储庞大的状态数组.本题中,每一天的决策,仅仅取决于之前一天的若干个状态.

		一天之内的状态,只有四种:已经买了一只股buy1,已经卖了一只股sold1,已经买了第二只股buy2,已经卖了第二只股sold2.那么显然每一天的状态更新是:

		buy1 = max(buy1,-p)
		sold1 = max(sold1, buy1+p)
		buy2 = max(buy2,sold1-p)
		sold2 = max(sold2, buy2+p)
		注意等号右边的变量都是前一天的状态. 另外需要考虑初始状态:buy1=-inf, sold1=0, buy2=-inf, sold2=0

		跟这一题类似的题目有:376,487,714,552
	*/

public:

	int doit_dp_bottomup(vector<int>&& prices) {
		if (prices.empty()) return 0;

		int k = 2, N = prices.size();
		vector<vector<int>> DP(k + 1, vector<int>(N+1, 0));
		int tmpMaxV = 0, maxV = 0;

		for (int x = 1; x < k + 1; x++) {

			tmpMaxV = DP[k - 1][0] - prices[0];
			for (int i = 1; i < N + 1; i++) {

				DP[x][i] = max(DP[x][i - 1], tmpMaxV + prices[i-1]);

				tmpMaxV = max(tmpMaxV, DP[x - 1][i] - prices[i-1]);

				maxV = max(maxV, DP[x][i]);
			}
		}

		return maxV;
	}

	/*
		O(1) Memory Solution
		Throughout the trading days, our balance changes as follows:

		Drops after we buy stock first time (- p1)
		Rises after we sell it (+ p2)
		Dips after we buy stock second time (- p3)
		Hikes after we sell it (+ p4)
		In the solution below, we just track the maximum balance after we perform each of the four operations:

		Complexity Analysis
		Runtime: O(n)
		Memory: O(1)
	*/
	int maxProfit(vector<int>& prices) {
		auto buy1 = INT_MIN, buy2 = INT_MIN, sell1 = 0, sell2 = 0;
		for (auto p : prices) {
			buy1 = max(buy1, -p);
			sell1 = max(sell1, buy1 + p);
			buy2 = max(buy2, sell1 - p);
			sell2 = max(sell2, buy2 + p);
		}
		return sell2;
	}

	/*
		This solution is based on the Best Time to Buy and Sell Stock where you track the global min price and max profit. It's easier to come up with, but requires extra memory.

		Go left to right, and store the best profit for each day individually in left
		left[i] shows the max profit for days [1, i]
		Go right to left, store best profit in right
		right[i] shows the max profit for days [i + 1, n]
		The maximum profit is the maximum of left[i] + right[i]

		Complexity Analysis
		Runtime: O(n)
		Memory: O(n)
	*/
	int doit_twopointer(vector<int>& prices) {
		
        if (prices.empty()) return 0;

        int n = prices.size();
        
		int minV = INT_MAX;
	    vector<int> left(n, 0);
		for (size_t i = 0; i < prices.size(); i++) {
			if (i > 0) left[i] = std::max(left[i - 1], prices[i] - minV);
			minV = std::min(minV, prices[i]);
		}

		int maxV = INT_MIN;
		vector<int> right(n, 0);
		for (int i = n - 1; i >= 0; i--) {
			if (i != n - 1) right[i] = std::max(right[i + 1], maxV - prices[i]);
			maxV = std::max(maxV, prices[i]);
		}

		int res = 0, minv = INT_MAX;
		for (int i = 0; i < n-1; i++) {
			res = max(res, left[i] + right[i + 1]);
		}
        
        return std::max(res, right[0]);
	}
};