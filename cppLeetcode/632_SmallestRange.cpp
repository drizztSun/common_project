
/*
	You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists.

	We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.

	Example 1:
	Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
	Output: [20,24]
	Explanation:
	List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
	List 2: [0, 9, 12, 20], 20 is in range [20,24].
	List 3: [5, 18, 22, 30], 22 is in range [20,24].
	Note:
	The given list may contain duplicates, so ascending order means >= here.
	1 <= k <= 3500
	-105 <= value of elements <= 105.
	For Java users, please note that the input type has been changed to List<List<Integer>>. And after you reset the code template, you'll see this point.
*/


#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class SmallestRange {

public:

	vector<int> doit(vector<vector<int>>& nums) {

		typedef vector<int>::iterator vi;

		struct cmp {
			bool operator()(pair<vi, vi>& a, pair<vi, vi>& b) {
				return *a.first > *b.first;
			}
		};

		std::priority_queue<pair<vi, vi>, vector<pair<vi, vi>>, cmp> pq;
		int lo = INT_MAX, hi = INT_MIN;
		for (auto& num : nums) {
			lo = min(lo, num[0]);
			hi = max(hi, num[0]);
			pq.push({ num.begin(), num.end() });
		}

		vector<int> ans = { lo, hi };

		while (!pq.empty()) {

			auto A = pq.top();
			pq.pop();

			A.first++;
			if (A.first == A.second) 
				break;

			pq.push(A);

			lo = *pq.top().first;
			hi = std::max(hi, *A.first);

			if (hi - lo < ans[1] - ans[0]) {
				ans = { lo, hi };
			}
		}

		return ans;
	}

};



void Test_632_SmallestRange() {

	vector<vector<int>> input;
	input.push_back(vector<int>({ 4,10,15,24,26 }));
	input.push_back(vector<int>({ 0,9,12,20 }));
	input.push_back(vector<int>({ 5,18,22,30 }));


	auto res = SmallestRange().doit(input);

	return;
}