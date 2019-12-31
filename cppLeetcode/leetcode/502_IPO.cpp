



#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class FindMaximizedCapital {
public:

	/*
		Key Observation:

		The more capital W you have now, the more maximum capital you will eventually earn.
		Working on any doable project with positive P[i] > 0 increases your capital W.
		Any project with P[i] = 0 is useless and should be filtered away immediately (note that the problem only guarantees all inputs non-negative).
		Therefore, always work on the most profitable project P[i] first as long as it is doable until we reach maximum k projects or all doable projects are done.

		The algorithm will be straightforward:

		At each stage, split projects into two categories:
		“doables”: ones with C[i] <= W (store P[i] in priority_queue<int> low)
		“undoables”: ones with C[i] > W (store (C[i], P[i]) in multiset<pair<int,int>> high)
		Work on most profitable project from low (low.top()) first, and update capital W += low.top().
		Move those previous undoables from high to doables low whose C[i] <= W.
		Repeat steps 2 and 3 until we reach maximum k projects or no more doable projects.
	*/
	int doit(int k, int W, vector<int>&& P, vector<int>&& C) {
		priority_queue<int> low;      // P[i]'s within current W
		multiset<pair<int, int>> high; // (C[i],P[i])'s' outside current W

		for (int i = 0; i < P.size(); ++i) // initialize low and high
			if (P[i] > 0) if (C[i] <= W) low.push(P[i]); else high.emplace(C[i], P[i]);

		while (k-- && low.size()) {
			W += low.top(), low.pop(); // greedy to work on most profitable first
			for (auto i = high.begin(); high.size() && i->first <= W; i = high.erase(i)) 
				low.push(i->second);
		}
		return W;
	}


	int doit1(int k, int W, vector<int>& Profits, vector<int>& Capital) {

		priority_queue<int> lowerThanCurrentW;
		multiset<pair<int, int>> HigherThanCurrentW;

		for (auto i = 0; i < Profits.size(); i++) {
			if (Capital[i] <= W)
				lowerThanCurrentW.push(Profits[i]);
			else
				HigherThanCurrentW.emplace(Capital[i], Profits[i]);
		}

		while (k-- && !lowerThanCurrentW.empty()) {

			W += lowerThanCurrentW.top();
			lowerThanCurrentW.pop();

			while (!HigherThanCurrentW.empty() && HigherThanCurrentW.begin()->first <= W) {
				lowerThanCurrentW.push(HigherThanCurrentW.begin()->second);
				HigherThanCurrentW.erase(HigherThanCurrentW.begin());
			}
		}

		return W;
	}


	int doit2(int k, int W, vector<int>&& Profits, vector<int>&& Capital) {

		vector<std::pair<int, int>> buff;
		for (auto i = 0; i < Profits.size(); i++) {
			buff.push_back(make_pair(Capital[i], Profits[i]));
		}

		std::sort(buff.begin(), buff.end(), [](auto x, auto y) {
			return x > y;
		});

		priority_queue<int> comingProfits;

		while (k > 0) {

			while (!buff.empty() && buff.back().first <= W) {
				comingProfits.push(buff.back().second);
				buff.pop_back();
			}

			if (!comingProfits.empty()) {
				W += comingProfits.top();
				comingProfits.pop();
			}

			k--;
		}

		return W;
	}



};


void Test_502_IPO() {


	int res = FindMaximizedCapital().doit(2, 0, vector<int>({ 1, 2, 3 }), vector<int>({ 0, 1, 1 }));


}
