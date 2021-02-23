/*
502. IPO


Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the IPO. 
Since it has limited resources, it can only finish at most k distinct projects before the IPO. Help LeetCode design the best way to maximize its total capital after finishing at most k distinct projects.

You are given several projects. For each project i, it has a pure profit Pi and a minimum capital of Ci is needed to start the corresponding project. Initially, you have W capital. 
When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.

To sum up, pick a list of at most k distinct projects from given projects to maximize your final capital, and output your final maximized capital.

Example 1:
Input: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].

Output: 4

Explanation: Since your initial capital is 0, you can only start the project indexed 0.
             After finishing it you will obtain profit 1 and your capital becomes 1.
             With capital 1, you can either start the project indexed 1 or the project indexed 2.
             Since you can choose at most 2 projects, you need to finish the project indexed 2 to get the maximum capital.
             Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.
Note:
You may assume all numbers in the input are non-negative integers.
The length of Profits array and Capital array will not exceed 50,000.
The answer is guaranteed to fit in a 32-bit signed integer.
*/



#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class FindMaximizedCapital {
public:

	/*
		502.IPO
		
		将所有项目按照capital排序。在1~k轮中，每轮将所有capital小于当前W的项目都塞进一个pq里面，自动弹出利润最大的那个项目。就是当前的最优解。

		W更新后，之后再把capital小于当前W的项目入列。以此类推可以得到所需要的K个项目。

		需要注意的细节是：如果没有符合条件的K个项目，该什么时候判断退出？（答案是在pq为空的时候）
	*/
	int doit_heap_greedy(int k, int W, vector<int>& Profits, vector<int>& Capital) 
    {
        vector<pair<int,int>>proj;
        for (int i=0; i<Profits.size(); i++)
            proj.push_back({Capital[i], Profits[i]});

		// sort by capital	
        sort(proj.begin(),proj.end());
        
        priority_queue<int> pq;
        
        int count = 0, i = 0;

        while (count < k) {

            while (i < proj.size() && proj[i].first <= W)
            {
                pq.push(proj[i].second);
                i++;
            }

            if (pq.size() == 0) break;

            W += pq.top();
            count++;
            pq.pop();
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
	/*
		Key Observation:

		The more capital W you have now, the more maximum capital you will eventually earn.
		Working on any doable project with positive P[i] > 0 increases your capital W.
		Any project with P[i] = 0 is useless and should be filtered away immediately (note that the problem only guarantees all inputs non-negative).
		Therefore, always work on the most profitable project P[i] first as long as it is doable until we reach maximum k projects or all doable projects are done.

		The algorithm will be straightforward:

		At each stage, split projects into two categories:
		�doables�: ones with C[i] <= W (store P[i] in priority_queue<int> low)
		�undoables�: ones with C[i] > W (store (C[i], P[i]) in multiset<pair<int,int>> high)
		Work on most profitable project from low (low.top()) first, and update capital W += low.top().
		Move those previous undoables from high to doables low whose C[i] <= W.
		Repeat steps 2 and 3 until we reach maximum k projects or no more doable projects.
	*/
    int doit_heap_sort(int k, int W, vector<int>& Profits, vector<int>& Capital) {
        priority_queue<int> low;      // P[i]'s within current W
		multiset<std::pair<int, int>> high; // (C[i],P[i])'s' outside current W

		// initialize low and high
		for (int i = 0; i < Profits.size(); ++i) {
			if (Profits[i] > 0) 
				if (Capital[i] <= W) 
					low.push(Profits[i]); 
				else 
					high.emplace(Capital[i], Profits[i]);
		}

		while (k-- && low.size()) {
			// greedy to work on most profitable first
			W += low.top(); 
			low.pop();

			for (auto i = high.begin(); i != high.end() && i->first <= W; i = high.erase(i)) 
				low.push(i->second);
		}
		return W;
    }


	int doit1(int k, int W, vector<int>& Profits, vector<int>& Capital) {

		priority_queue<int> lowerThanCurrentW;
		multiset<std::pair<int, int>> HigherThanCurrentW;

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
};