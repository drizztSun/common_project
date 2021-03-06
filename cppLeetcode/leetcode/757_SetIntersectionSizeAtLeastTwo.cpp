/*

# 757. Set Intersection Size At Least Two

# An integer interval [a, b] (for integers a < b) is a set of all consecutive integers from a to b, including a and b.

# Find the minimum size of a set S such that for every integer interval A in intervals,
# the intersection of S with A has size at least 2.

# Example 1:
# Input: intervals = [[1, 3], [1, 4], [2, 5], [3, 5]]
# Output: 3
# Explanation:
# Consider the set S = {2, 3, 4}.  For each interval, there are at least 2 elements from S in the interval.
# Also, there isn't a smaller size set that fulfills the above condition.
# Thus, we output the size of this set, which is 3.

# Example 2:
# Input: intervals = [[1, 2], [2, 3], [2, 4], [4, 5]]
# Output: 5
# Explanation:
# An example of a minimum sized set is {1, 2, 3, 4, 5}.

# Note:
# intervals will have length in range [1, 3000].
# intervals[i] will have length 2, representing some integer interval.
# intervals[i][j] will be an integer in [0, 10^8].


*/

#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class IntersectionSizeTwo {

	/*
		757.Set-Intersection-Size-At-Least-Two
		我们想象如果我们能找出一系列non-overlapping的区间，那么我们的答案必然需要在每个区间内至少采集两点。所以本题的答案至少是maximum number of non-overlapping intervals的两倍。所以借鉴435的思路，我们采用sort by ending points的方法去下手。这个突破口的想法和452.Minimum-Number-of-Arrows-to-Burst-Balloons很相似。

		如果我们将这些区间按照后边界从小到大排序后（相同后边界的情况下，显然只考虑区间跨度最短的，因为短区间能被S覆盖的话，那么相同右端点的长区间必然也能被覆盖），先考虑第一个区间。对于这个区间，我们肯定会选该区间的最后两点加入S，因为这两点是最有可能与后面的区间重合的，效率最高。

		然后我们再考虑下一个区间[x,y]，此时S应该如何更新呢？一个最明显的特点是，y一定大于等于S里的最大点。于是此时最有影响的其实就只是区间的前边界a。我们分类讨论x的位置查看对S的影响：

		如果[x,y]覆盖了S最后两个点，那么S就不用更新；
		如果[x,y]只覆盖了S最后一个点，那么这个点其实就一定是S的后边界，那么S需要再补一个点。这个点是什么呢?最好的选择就是[x,y]的最后一个点，即y。这种做法是最“贪心”的，因为它最可能会与[x,y]之后的区间重合。
		如果[x,y]没有覆盖S，那么S就要加上什么呢，是[x,y]的最后两个点即可，同理也是用贪心的策略。
		综上，我们其实只要每次关注集合S里的最大两个点a，b即可，不断与下一个区间[x,y]考察相对关系，更新S。
	*/
	static bool cmp(vector<int>&a, vector<int>&b)
    {
        if (a[1]==b[1])
            return a[0]>b[0];
        else
            return a[1]<b[1];
    }

    int intersectionSizeTwo(vector<vector<int>>& intervals) 
    {
        sort(intervals.begin(), intervals.end(), cmp);
        int a = intervals[0][1]-1, b = intervals[0][1];
        int count = 2;

        for (auto& interval: intervals)
        {
            if (interval[0]<=a)
                continue;
            else if (interval[0]<=b)
            {
                count++;
                a = b;
                b = interval[1];
            }
            else
            {
                count+=2;
                a = interval[1]-1;
                b = interval[1];
            }
        }
        return count;
    }

public:
	
	int doit1(vector<vector<int>>& intervals) {

		map<vector<int>, int> alive;
		set<int> event;
		unordered_map<int, vector<vector<int>>> start, end;

		for (auto c : intervals) {

			start[c[0]].push_back(c);
			start[c[1]].push_back(c);

			event.insert(c[0]);
			event.insert(c[1]);
		}

		int total = 0;

		for (auto t : event) {

			for (auto c : start[t])
				alive[c] = 2;

			int need = 0;
			for (auto c : end[t])
				need = max(need, alive[c]);

			total += need;

			for (auto it = alive.begin(); it != alive.end();) {

				it->second -= std::min(need, t - it->first[0] + 1);
				if (it->second < 0)
					it = alive.erase(it);
				else
					it++;
			}
		}

		return total;
	}

	int doit_greedy(vector<vector<int>>& intervals) {

		std::sort(intervals.begin(), intervals.end(), [](vector<int>& v1, vector<int>& v2) { 
			return v1[1] < v2[1] || (v1[1] == v2[1] && v1[0] > v2[0]); 
		});

		vector<int> pool{ -1, -1 }; // placeholder, so don't need to do more check in for-loop
		
		for (auto& c : intervals) {

			int sz = pool.size();
			if (c[0] <= pool[sz - 2])
				continue;

			if (c[0] > pool[sz - 1])
				pool.push_back(c[1] - 1);

			pool.push_back(c[1]);
		}

		return pool.size() - 2;
	}

};