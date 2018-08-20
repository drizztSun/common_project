

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

	int doit(vector<vector<int>>& intervals) {

		std::sort(intervals.begin(), intervals.end(),
			[](vector<int>& v1, vector<int>& v2) { return v1[1] < v2[1] || (v1[1] == v2[1] && v1[0] > v2[0]); });

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


void Test_757_SetIntersectionsSizeAtLeastTwo() {


	IntersectionSizeTwo obj;

	vector<vector<int>> input{ {1, 3}, {1, 4}, {2, 5}, {3, 5} };

	int res1 = obj.doit(input);


	vector<vector<int>> input1{ {1, 2}, {2, 3}, {2, 4}, {4, 5} };

	int res2 = obj.doit(input1);

	vector<vector<int>> input2{ {1,2},{2,3},{2,4},{4,5} };

	int res3 = obj.doit(input2);

	vector<vector<int>> input3{ {2,10},{3,7},{3,15},{4,11},{6,12},{6,16},{7,8},{7,11},{7,15},{11,12}};

	int res4 = obj.doit(input3);

	return;
}