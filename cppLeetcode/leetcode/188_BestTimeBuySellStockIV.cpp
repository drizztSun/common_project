


/*

# 188. Best Time to Buy and Sell Stock IV

# Say you have an array for which the ith element is the price of a given stock on day i.

# Design an algorithm to find the maximum profit. You may complete at most k transactions.

# Note:
# You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).


*/

#include <vector>
#include <algorithm>

#include <queue>
#include <stack>
using namespace std;


class MaxProfit {

public:

	/*
	# f[k, ii] represents the max profit up until prices[ii] (Note: NOT ending with prices[ii]) using at most k transactions.
	# f[k, ii] = max(f[k, ii-1], prices[ii] - prices[jj] + f[k-1, jj]) { jj in range of [0, ii-1] }
	#          = max(f[k, ii-1], prices[ii] + max(f[k-1, jj] - prices[jj]))
	# f[0, ii] = 0; 0 times transation makes 0 profit
	# f[k, 0] = 0; if there is only one price data point you can't make any money no matter how many times you can trade
	*/
	// <DP>
	int doit(size_t k, vector<int>& prices) {

		if (prices.size() < 2)
			return 0;
		
		int res = 0;
		if (k >= prices.size() / 2) {
			for (size_t i = 1; i < prices.size(); i++)
				if (prices[i] > prices[i - 1])
					res += prices[i] - prices[i - 1];
			return res;
		}

		vector<vector<int>> DP(k + 1, vector<int>(prices.size()));
		int maxv = 0;

		for (size_t x = 1; x < k + 1; x++) {

			int tmp = DP[x - 1][0] - prices[0];
			for (size_t i = 1; i < prices.size(); i++) {

				DP[x][i] = max(DP[x][i - 1], prices[i] + tmp);
				tmp = std::max(tmp, DP[x - 1][i] - prices[i]);
				maxv = max(maxv, DP[x][i]);
			}

		}
		return maxv;
	}



	/*
	We can find all adjacent valley/peak pairs and calculate the profits easily.
	Instead of accumulating all these profits like Buy&Sell Stock II, we need the highest k ones.

	The key point is when there are two v/p pairs (v1, p1) and (v2, p2), satisfying v1 <= v2 and p1 <= p2,
	we can either make one transaction at [v1, p2], or make two at both [v1, p1] and [v2, p2]. The trick is to treat [v1, p2] as the first transaction, and [v2, p1] as the second. Then we can guarantee the right max profits in both situations, p2 - v1 for one transaction and p1 - v1 + p2 - v2 for two.

	Finding all v/p pairs and calculating the profits takes O(n) since there are up to n/2 such pairs.
	And extracting k maximums from the heap consumes another O(klgn).
	*/
	// <HEAP> 
	int doit1(int k, vector<int>& prices) {
		int length = prices.size();
		int v = 0, p = 0;

		priority_queue<int> profits;
		stack<pair<int, int>> vp_pairs;

		while (p < length) {

			for (v = p; v < length - 1 && prices[v] >= prices[v + 1]; v++);
			for (p = v + 1; p < length && prices[p] >= prices[p - 1]; p++);

			// if current low point is lower then last one, that means we can't combile those two profits to be one
			// Then we save last one (top one), and continue to compare (1) 
			// Until Top one' s low is lower then current one's
			while (!vp_pairs.empty() && prices[v] < prices[vp_pairs.top().first]) {
				profits.push(prices[vp_pairs.top().second - 1] - prices[vp_pairs.top().first]);
				vp_pairs.pop();
			}

			// so far, Top one's low is less than current one's
			// if Top one's high peak is less than current one's
			// That means there is a cross in projections (common projection).
			// we save the common part, and set 'v' to be the Top one's lower index
			// 'p' is still keeping current one's 
			// then right now the (v, p) cover both two profit's all projections.
			while (!vp_pairs.empty() && prices[p-1] >= prices[vp_pairs.top().second - 1]) {
				profits.push(prices[vp_pairs.top().second - 1] - prices[v]);
				v = vp_pairs.top().first;
				vp_pairs.pop();
			}

			vp_pairs.push(make_pair(v, p));
		}

		// Save the rest
		while (!vp_pairs.empty()) {
			profits.push(prices[vp_pairs.top().second - 1] - prices[vp_pairs.top().first]);
			vp_pairs.pop();
		}

		int ans = 0;
		while (k != 0 && !profits.empty()) {
			ans += profits.top();
			profits.pop();
			k -= 1;
		}

		return ans;
	}
};