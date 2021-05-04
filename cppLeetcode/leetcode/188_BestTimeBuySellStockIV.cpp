


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

public:

	/*
		188.Best-Time-to-Buy-and-Sell-Stock-IV
		解法1：
		此题是对之前股票系列I，II，III的综合考察，并推广到任意k次交易的条件。

		基本思路还是从第i天的策略考虑起。第i天如果卖出的话，说明第i-1天必须手头有股票；如果是买入的话，说明第i-1天必须手头没有股票。因此我们可以粗略地写下：dp[i] = max{dp[i-1][yes]+sell, dp[i-1][no]+buy}这就提示我们dp其实有两个维度，dp[i][yes/no]，
		第二个维度代表了持有或不持有股票。这时候我们可以写出状态转移方程：

		for (int i=0; i<n; i++)
		{
			dp[i][yes] = max( dp[i-1][no]+buy, dp[i-1][yes]+hold );
			dp[i][no] =  max( dp[i-1][yes]+sell, dp[i-1][no]+hold );
		}
		return dp[n-1][no];
		但是这个状态转移方程并没有考虑到对于交易次数的约束。我们因此修改状态变量为dp[i][yes/no][j]，其中j表示经历过j次的股票买入。显然，第i天买入第j只股票，需要要求第i-1天已经卖出第j-1只股票；第i天卖出第j只股票，需要要求第i-1天已经入手第j只股票。因此类推，就可以把j写入状态转移方程中。

		for (int i=0; i<n; i++)
		{
			for (int j=0; j<=k; j++)
			{
			dp[i][yes][j] = max { dp[i-1][no][j-1]+buy, dp[i-1][yes][j]+hold };
			dp[i][no][j] = max {dp[i-1][yes][j]+sell, dp[i-1][no][j]+hold  };
			}
		}
		return dp[n-1][no];
		进一步，yes/no的状态维度可以拆分为两个dp变量：

		hold[i][j] = max { sold[i-1][j-1]+buy, hold[i-1][j] }
		sold[i][j] = max { hold[i-1][j]+sell, sold[i-1][j] }
		至此，写出最多k次交易的最大利润已经不难，返回的结果是sold[n-1][j]中的最大值。

		本题最有意思的一点是，k可以很大，远大于prices的天数。这样的话，题目就等效于无限次的操作，这样就可以用 122. Best Time to Buy and Sell Stock II 里面的技巧来解，时间复杂度反而从o(n*k)降到了o(n).

		解法2：
		上述的解法时间复杂度是o(NK)，在最近的评测中会TLE。这里介绍一个惊为天人的解法，时间复杂度是O(NlogP)，其中P是prices的最大值。

		我们令f(x)表示固定交易x次能收获的最大值。那么这个f(x)会长什么样子？它是一个上凸的函数。因为交易次数太少，赚的机会就少；交易次数太多，有些交易反而会亏钱。所以在某个位置xm的地方，交易这个次数可以使得利益最大化。
		如果k>=xm，那么我们必然选择交易xm次。如果k<xm，那么我们必然选择交易k次。对于前者，本质上就是没有约束，那么问题就转化为了122. Best Time to Buy and Sell Stock II. 所以这题的关键其实就是求后者的f(k).

		虽然知道了f(x)的形状，但直接求解f(x)我们其实没有什么特别好的办法。接下用来有个神奇的技巧。

		我们在令g(x)=f(x)-a*x，从形式上看，就是一个带有transaction fee的股票买卖问题，其中每买一次股票需要额外付出a。特别地，当a=0的时候，g(x)就是f(x)。
		我们此时考虑，当a=1的时候相比于a=0的时候，g(x)的函数图像有什么变化呢？首先对任何的交易次数x而言，交易费的引入都会让利润受损，所以g(x)整体会向下移动。另外，交易费的引入会让有些交易变得无利可图甚至亏损，最大利润所对应的股票交易次数一定会减少，所以g(x)的峰值会左移。

		可以想见，随着a的增大，g(x)的峰值会向下向左移动。注意，x的定义域是离散的，所以峰值也一定对应着某个整数的x。

		如果我们能找到某个a，使得g(x)的峰值恰好对应着x=k的时候，意味着f(k)-ak = g(x)_max. 如果g(x)_max和a都知道了，那么本题就得解。那么如何知道这样的a呢？
		事实上，我们已经知道，随着a的增大，g(x)的峰值位置是向左单调移动的。我们可以用二分法搜索出这个a来，满足峰值是的位置是k。此时交易费a确定了，那么问题就同714 Best Time to Buy and Sell Stock with Transaction Fee，可以知道最大利润，也就是g(x)的峰值。

		这个二分的过程中，a的最小值是0，最大值就是max{prices}。如果k>xm，那么我们二分搜索是不会搜到峰值位置是k的，但是会最终将a的选择收敛到0，这也就达到我们的目的了。
			
	*/
	int maxProfit(int k, vector<int>& prices) 
    {
        int n = prices.size();
        
        if (k>=n/2)
        {
            int result = 0;
            for (int i=1; i<prices.size(); i++)
                if (prices[i]>prices[i-1])
                    result+=prices[i]-prices[i-1];
            return result;
        }
        
        vector<int>hold(k+1, INT_MIN/2);
        vector<int>sold(k+1, INT_MIN/2);
        
        hold[0] = 0;
        sold[0] = 0;
        
        for (int i=0; i<n; i++)
        {
            auto hold_old = hold;
            auto sold_old = sold;
            
            for (int j=1; j<=k; j++)
            {
                hold[j] = max (sold_old[j-1]-prices[i], hold_old[j] );
                sold[j] = max (hold_old[j]+prices[i], sold_old[j] );
            }
            
        }
        
        int result = INT_MIN;
        for (int j=0; j<=k; j++)
            result = max(result, sold[j]);
        return result;
    }


	int n;
public:
    int maxProfit(int k, vector<int>& prices) 
    {
        n = prices.size();
        prices.insert(prices.begin(),0);
        int left = 0, right = *max_element(prices.begin(), prices.end());

        while (left<right)
        {
            int fee = left + (right-left)/2;
            if (helper(prices, fee)[1] > k)
                left = fee+1;
            else
                right = fee;
        }
        return helper(prices,left)[0] + left*k;
    }

    vector<int> helper(vector<int>& prices, int fee) 
    {
        vector<int>sold(n+1,0);
        vector<int>hold(n+1,0);
        sold[0] = 0;
        hold[0] = INT_MIN/2;
        int count0 = 0;
        int count1 = 0;

        for (int i=1; i<=n; i++)
        {
            if (hold[i-1]+prices[i]> sold[i-1])
            {
                sold[i] = hold[i-1] + prices[i];
                count0 = count1+1;
            }
            else
                sold[i] = sold[i-1];
            
            if (sold[i-1] - prices[i] - fee  > hold[i-1])
            {
                hold[i] = sold[i-1] - prices[i] - fee;
                count1 = count0;
            }
            else
                hold[i] = hold[i-1];
        }
        return {sold[n], count0};
    }


};