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

public:

	int doit(vector<int>& prices) {
		if (prices.empty())
			return 0;

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
	

	int doit1(vector<int>& prices) {
		
		if (prices.size() < 2)
			return 0;

		int minV = INT_MAX;
		vector<int> left(prices.size(), 0);
		for (int i = 0; i < prices.size(); i++) {
			if (i > 0)
				left[i] = std::max(left[i - 1], prices[i] - minV);
			minV = std::min(minV, prices[i]);
		}

		int maxV = 0;
		vector<int> right(prices.size(), 0);
		for (int i = prices.size() - 1; i >= 0; i--) {
			if (i != prices.size() - 1)
				right[i] = std::max(right[i + 1], maxV - prices[i]);

			maxV = std::max(maxV, prices[i]);
		}

		int res = 0;
		for (int i = 0; i < prices.size() - 1; i++) {
			res = max(res, left[i] + right[i + 1]);
		}

		res = max(res, right[0]);
		return res;
	}

};


void Test_123_BestTimetoBuyandSellStock() {

	auto res2 = StockMaxProfit().doit(vector<int>{});

	auto res1 = StockMaxProfit().doit(vector<int>{3, 3, 5, 0, 0, 3, 1, 4});

	auto res = StockMaxProfit().doit(vector<int>{2, 3, 1, 6, 7, 9, 1, 3, 2, 6, 4, 7, 9, 10, 12, 1});
}