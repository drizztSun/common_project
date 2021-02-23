/*
    632. Smallest Range Covering Elements from K Lists
	
	You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.

	We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.

	

	Example 1:

	Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
	Output: [20,24]
	Explanation: 
	List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
	List 2: [0, 9, 12, 20], 20 is in range [20,24].
	List 3: [5, 18, 22, 30], 22 is in range [20,24].
	Example 2:

	Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
	Output: [1,1]
	Example 3:

	Input: nums = [[10,10],[11,11]]
	Output: [10,11]
	Example 4:

	Input: nums = [[10],[11]]
	Output: [10,11]
	Example 5:

	Input: nums = [[1],[2],[3],[4],[5],[6],[7]]
	Output: [1,7]
	

	Constraints:

	nums.length == k
	1 <= k <= 3500
	1 <= nums[i].length <= 50
	-105 <= nums[i][j] <= 105
	nums[i] is sorted in non-decreasing order.
*/


#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using std::set;
using std::priority_queue;
using std::vector;


class SmallestRange {

public:

	/*
		632.Smallest-Range
		本题的想法是：从小到大遍历所有的元素a，考虑如果以a为最小值，那么符合条件的最大值b是多少？

		我们第一个考察的a必然是全局的最小值，假设它是nums[0]的第一个元素。那么我们如何找range的其他元素呢？显然为了使得range的范围最小、并且每个nums都被覆盖到，我们必然选取的都是每个nums[i]的第一个元素。
		我们把这个n个数放进一个有序容器里，自动排序后就知道最大值b是多少。因此b-a就可以确定下来了。

		那么第二个考察的a就是全局的次小值。怎么找到这个次小值呢？我们只要把原来的a从有序容器里弹出去，再加进来nums[0]的第二个元素。此时有序容器里面的最小元素必然就是此时全局的次小值a。
		而且我们发现，现在容器里面的n个元素恰好覆盖了每个nums，并且都是各个nums里面的最小值（刨去已经弹走的不计）。所以我们用此时容器里面的最大值和最小值，就对应这当前range。

		依次类推，我们每弹出一个当前容器里的最小值，为了保证每个nums都被覆盖到，必然就从那个数组里再补进一个最小值。此时容器里面的所有元素，就是当前全局最小值所对应的range（即恰好覆盖每个nums。
		直至某次弹出最小值后，发现无法再从它的nums里补进新元素，说明再无法用剩下的元素取覆盖所有nums，即推出。
	*/
	vector<int> smallestRange(vector<vector<int>>& nums) 
    {
        set<std::pair<int,int>>Set;
        int n = nums.size();
        vector<int>pointers;
        for (int i=0; i<n; i++)
        {
            pointers.push_back(0);
            Set.insert({nums[i][0],i});
        }

        int range = INT_MAX;
        vector<int>ret;
        while (1)
        {
            if (Set.rbegin()->first - Set.begin()->first < range)
            {
                range = Set.rbegin()->first - Set.begin()->first;
                ret = {Set.begin()->first, Set.rbegin()->first};
            }            
            int i = Set.begin()->second;
            pointers[i]++;
            if (pointers[i]==nums[i].size()) break;
            Set.erase(Set.begin());
            Set.insert({nums[i][pointers[i]],i});
        }

        return ret;
    }

	vector<int> doit_heap(vector<vector<int>>& nums) {

		typedef vector<int>::iterator vi;

		struct cmp {
			bool operator()(pair<vi, vi>& a, pair<vi, vi>& b) {
				return *a.first > *b.first;
			}
		};

		std::priority_queue<pair<vi, vi>, vector<pair<vi, vi>>, cmp> pq;
		int lo = INT_MAX, hi = INT_MIN;

		for (const auto& num: nums) {
			lo = std::min(lo, num[0]);
			hi = std::max(hi, num[0]);
			pq.push({ num.begin(), num.end() });
		}

		vector<int> ans{lo, hi};

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
				ans = {lo, hi};
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


	auto res = SmallestRange().doit_heap(input);

	return;
}
