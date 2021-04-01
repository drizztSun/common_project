/*
354. Russian Doll Envelopes

You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.

One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.

Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).

Note: You cannot rotate an envelope.

 

Example 1:

Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
Output: 3
Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
Example 2:

Input: envelopes = [[1,1],[1,1],[1,1]]
Output: 1
 

Constraints:

1 <= envelopes.length <= 5000
envelopes[i].length == 2
1 <= wi, hi <= 10^4

*/

#include <vector>
#include <algorithm>

using std::vector;

class maxEnvelopes {

	/*
		354. Russian-Doll-Envelopes
		解法1：
		我们将所有的信封按照长度从小到大排序之后，符合要求的信封嵌套序列一定是这个排序数组的一个subsequence（否则无法满足长度的递增要求）。

		我们可以用N^2的DP方法，在这个数组中找到宽度的最长递增子序列(LIS)。参考300. Longest Increasing Subsequence. 注意对于第i个元素，想寻找它在LIS中的前一个元素j，
		必须同时满足两个条件： width[j]<width[i] && length[j]<length[i]。否则会将长度相等、宽度不等的两个信封选入同一个LIS中。

		解法2：
		本题有一个技巧可以在求LIS的过程中不用再考虑长度的制约。那就是排序的时候，将长度相同的信封按照宽度降序排列。这样的好处是，相同长度的信封，不可能在宽度上是递增的。
		这样求宽度的LIS时，不可能选到两个长度相同的信封。于是，单纯求解宽度数组的LIS序列，就可以用o(NlogN)的贪心解法了。参考300. Longest Increasing Subsequence.
	*/
	int maxEnvelopes_dp(vector<vector<int>>& envelopes) 
    {
        int n = envelopes.size();
        sort(envelopes.begin(), envelopes.end());
        vector<int>dp(n,0);
        for (int i=0; i<n; i++)
        {
            dp[i] = 1;
            for (int j=0; j<i; j++)
            {
                if (envelopes[j][0]<envelopes[i][0] && envelopes[j][1]<envelopes[i][1])
                    dp[i] = std::max(dp[i], dp[j]+1);
            }
        }
        
        int ret = 0;
        for (int i=0; i<n; i++)
            ret = std::max(ret, dp[i]);
        return ret;
    }

	static bool cmp(vector<int>&a, vector<int>&b)
    {
        if (a[0]==b[0])
            return a[1]>b[1];
        else
            return a[0]<b[0];
    }

    int maxEnvelopes_greedy(vector<vector<int>>& envelopes) 
    {
        sort(envelopes.begin(), envelopes.end(), cmp);
        vector<int>q;
        for (auto x: envelopes)
        {
            if (q.empty() || x[1]>q.back())
                q.push_back(x[1]);
            else
            {
                auto iter = lower_bound(q.begin(), q.end(), x[1]);
                *iter = x[1];
            }
        }
        return q.size();
    }

public:

	int doit_greedy(vector<std::pair<int, int>>& envelopes) {

		std::sort(envelopes.begin(), envelopes.end(), [](auto a, auto b) {
			return a.first < b.first || (a.first == b.first && a.second > b.second); } );

		vector<int> tail;
		for (auto c : envelopes) {
			auto p = std::lower_bound(tail.begin(), tail.end(), c.second);
			if (p == tail.end()) {
				tail.push_back(c.second);
			}
			else {
				*p = c.second;
			}
		}
		return tail.size();
	}

	int doit_dp(vector<std::pair<int, int>>& envelopes) {

		if (envelopes.empty()) return 0;

		sort(envelopes.begin(), envelopes.end());
		vector<int> dp(envelopes.size(), 1);

		for (int i = 0; i < envelopes.size(); ++i)
			for (int j = 0; j < i; ++j)
				if (envelopes[j].first < envelopes[i].first && envelopes[j].second < envelopes[i].second)
					dp[i] = std::max(dp[i], dp[j] + 1);

		return *max_element(dp.begin(), dp.end());
	}
};