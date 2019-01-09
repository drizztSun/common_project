

/*

354. Russian Doll Envelopes


*/

#include <vector>
#include <algorithm>
using namespace std;


class maxEnvelopes {
public:
	int doit(vector<pair<int, int>>& envelopes) {

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
};


struct Solution {
	int maxEnvelopes(vector<pair<int, int>>& envelopes) {
		if (envelopes.empty())
			return 0;

		sort(envelopes.begin(), envelopes.end());
		vector<int> dp(envelopes.size(), 1);

		for (int i = 0; i < envelopes.size(); ++i)
			for (int j = 0; j < i; ++j)
				if (envelopes[j].first < envelopes[i].first && envelopes[j].second < envelopes[i].second)
					dp[i] = max(dp[i], dp[j] + 1);

		return *max_element(dp.begin(), dp.end());
	}
};



void Test_354_Russian() {

}