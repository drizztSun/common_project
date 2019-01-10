



#include <vector>
#include <algorithm>
using namespace std;

class KthSmallestPairDistance {

public:


// O(n*logN)
	int doit(vector<int>& nums, int k) {

		sort(nums.begin(), nums.end());
		int lo = 0, hi = nums.back() - nums[0];
		int N = nums.size();

		while (lo < hi) {

			int mid = lo + (hi - lo) / 2;
			int cnt = 0;
			for (int i = 0, j = 0; i < N; i++) {
				while (j < N && nums[j] - nums[i] <= mid)
					j++;

				cnt += j - i - 1;
			}

			if (cnt < k)
				lo = mid + 1;
			else
				hi = mid;
		}

		return lo;
	}


// O(n^2)
	int doit1(vector<int>& nums, int k) {
		int N = 10000000;
		vector<int> cnt(N, 0);
		int maxv = INT_MIN, minv = INT_MAX;
		for (int i = 0; i < nums.size(); i++) {
			for (int j = i + 1; j < nums.size(); j++) {
				int c = abs(nums[i] - nums[j]);
				cnt[c]++;
				maxv = max(maxv, c);
				minv = min(minv, c);
			}
		}

		int res = 0;
		for (auto i = minv; i < maxv; i++) {
			res += cnt[i];
			if (res >= k) {
				return i;
			}
		}
		return -1;
	}


};


void Test_719_FindSmallestPairDistance() {

	auto res1 = KthSmallestPairDistance().doit(vector<int>({ 1, 3, 1 }), 1);

	auto res2 = KthSmallestPairDistance().doit(vector<int>({ 1, 6, 1 }), 3);

	auto res3 = KthSmallestPairDistance().doit(vector<int>({ 62, 100, 4 }), 2);

	auto res = KthSmallestPairDistance().doit(vector<int>({ 1,2,0,2,1,0,1,1,0,2,2,0,2,0,1,1,1,0,1,0,1,1,2,2,2,2,0,0,2,1,2,1,2,0,0,0,1,0,0,1,0,2,1,1,1,1,0,2,2,1,0,2,0,2,2,2,1,0,2,2,2,2,0,0,1,0,1,1,2,1,2,2,1,1,0,2,0,1,0,1,1,2,0,1,1,1,1,2,0,2,2,0,0,1,1,1,1,2,1,2,2,1,2,0,1,2,2,1,1,2,1,0,1,1,1,0,0,1,2,0,2,1,0,1,2,0,2,2,1,0,0,2,0,1,1,0,1,0,1,0,1,2,2,2,0,1,1,1,1,1,0,2,2,2,1,0,1,0,1,0,0,0,0,2,0,0,1,1,2,0,2,1,2,0,0,1,0,1,2,1,0,1,1,1,1,0,0,2,2,1,1,0,0,0,0,1,2,2,1,1,0,1,2,0,0,2,1,2,1,2,0,2,1,1,2,2,2,2,2,0,1,1,0,1,2,2,0,2,2,2,0,2,0,1,1,2,2,0,2,2,2,2,2,2,1,0,2,2,2,0,2,0,2,0,2,1,0,1,0,1,1,0,2,0,1,0,0,2,0,0,0,2,0,2,2,0,2,0,0,1,1,0,2,0,1,2,2,0,1,1,2,0,0,0,2,1,0,1,0,2,1,2,0,1,2,1,1,1,0,1,2,1,2,2,1,2,0,2,1,0,1,1,1,2,0,2,2,2,2,1,0,2,2,1,1,1,1,0,1,2,2,0,1,2,2,1,0,0,1,2,1,0,2,1,1,1,0,0,0,1,1,1,0,2,0,2,0,1,2,2,0,2,1,2,2,0,0,0,0,2,1,1,2,0,2,0,1,0,1,0,2,0,0,0,2,1,2,0,1,2,1,2,1,0,1,0,1,0,0,1,2,1,1,2,1,1,2,2,1,0,1,1,2,2,1,2,2,2,1,0,1,1,1,0,0,0,2,1,1,1,2,2,1,2,0,2,1,2,0,2,2,2,1,1,2,2,0,0,2,2,2,1,2,2,1,0,2,0,2,0,2,1,2,2,1,1,1,1,1,0,0,1,0,2,2,0,0,2,1,0,1,0,2,1,0,0,0,0,1,2,1,2,0,0,1,1,2,2,2,2,0,2,1,0,0,0,2,0,1,1,0,2,1,1,1,2,1,0,0,1,0,1,0,1,2,0,2,1,0,0,1,2,1,1,0,0,0,2,2,2,1,1,2,2,0,1,0,2,2,2,0,1,0,0,1,0,0,1,1,1,1,1,1,2,1,2,0,2,0,2,1,2,2,2,0,1,0,1,2,0,2,2,1,2,0,1,2,2,0,1,1,0,1,1,0,0,0,1,2,1,0,0,2,0,1,0,2,2,0,1,0,0,0,1,0,0,0,2,1,1,1,1,1,0,1,1,0,1,0,1,0,2,2,0,2,2,0,0,1,2,0,1,1,1,2,0,0,0,2,0,2,2,2,2,1,0,2,2,0,0,1,1,2,2,2,1,1,2,0,1,0,0,1,0,1,2,0,1,2,0,1,1,1,1,2,0,1,0,1,2,2,0,0,2,0,1,2,1,2,1,0,0,1,0,0,1,2,0,1,0,0,0,0,2,0,1,0,1,2,0,1,2,0,0,0,0,1,1,2,0,0,0,2,1,1,0,0,2,2,1,0,0,1,0,1,0,1,1,0,2,0,1,1,2,2,1,1,0,2,0,0,1,0,1,2,2,1,2,2,2,2,2,1,2,0,0,0,1,1,0,0,2,1,0,1,0,2,2,0,1,2,2,2,0,0,0,2,2,1,2,1,0,0,0,1,1,2,1,2,0,1,2,1,0,1,2,0,1,2,1,2,1,1,1,2,2,1,0,1,0,2,1,2,0,2,0,0,0,1,2,1,0,0,0,1,2,0,2,2,2,1,0,2,2,1,1,2,0,0,1,2,2,2,1,2,1,2,1,0,2,2,0,0,0,2,0,1,0,1,0,2,2,2,2,0,1,1,1,1,0,1,0,0,1,2,0,1,0,0,2,0,1,1,1,1,2,0,1,1,2,0,2,1,2,1,1,0,1,1,2,1,2,0,1,0,0,0,1,0,2,0,0,2,0,0,1,0,1,2,2,1,2,0,2,2,2,0,2,0,2,1,0,0,0,0,0,0,1,0,2,0,1,1,0,2,1,2,1,1,0,2,1,2,0,1,1,1,0,1,0,1,0,0,1,1,0,1,1,0,2,2,1,1,0,1,0,0,0,2,2,2,0,1,2,1,2,0,2,1,0,0,1,2,2,1,0,1,2,0,0,2,1,1,2,0,0,1,0,2,2,2,2,0,1,0,0,0,1,1,0,2,0,2,0,2,2,2,0,2,0,0,2,1,0,2,2,2,1,2,0,2,2,0,2,1,2,2,0,1,0,2,0,1,1,2,2,2,2,0,0,0,0,2,2,2,2,1,0,2,0,2,0,1,0,1,1,2,2,1,2,1,2,0,1,2,2,2,0,1,0,1,0,1,0,1,0,1,2,2,0,2,2,2,0,1,0,2,1,1,1,0,0,0,0,0,2,0,1,0,2,0,0,2,2,2,2,1,2,2,1,2,0,1,0,1,1,0,0,2,2,1,2,2,1,0,0,0,0,0,0,1,1,0,1,0,2,0,1,0,2,2,2,0,1,0,2,1,2,2,0,2,1,1,1,1,1,1,2,2,1,0,1,2,1,1,0,0,1,0,2,0,2,2,2,2,1,2,2,2,2,1,2,2,1,1,1,0,1,2,2,0,0,2,1,0,2,1,0,2,2,0,2,1,0,2,1,0,0,0,0,2,0,1,0,2,0,1,2,2,0,1,0,1,1,1,2,1,0,0,0,0,0,2,0,1,1,1,0,1,2,2,1,2,2,0,2,2,0,0,0,2,2,2,1,1,2,1,2,1,2,1,1,0,0,2,0,2,0,1,1,0,0,2,1,0,0,1,2,0,1,0,2,1,1,1,1,2,2,0,2,2,0,1,1,2,2,0,2,0,1,0,2,0,2,2,2,1,2,2,0,1,1,2,2,1,2,2,2,2,2,2,0,0,1,1,0,0,1,0,0,0,2,1,2,1,2,2,1,1,0,2,1,0,0,1,2,2,1,1,1,1,0,0,0,2,0,0,2,1,1,2,2,2,1,2,1,0,1,2,1,2,2,1,1,0,0,0,1,1,1,0,0,1,1,1,2,2,1,2,1,0,2,0,1,0,0,2,0,0,0,2,1,0,2,0,2,1,1,2,0,1,1,0,2,0,1,2,2,0,0,2,0,1,1,0,2,2,1,0,0,0,2,0,1,0,0,0,2,0,2,2,1,0,1,2,2,2,2,1,1,2,2,2,0,1,2,0,2,1,2,1,0,2,0,1,0,0,2,1,0,0,0,2,0,0,1,2,2,0,0,1,0,1,1,2,2,2,0,2,1,0,2,0,1,2,1,0,1,1,1,2,1,0,0,0,2,1,0,2,2,0,1,0,2,0,2,2,2,0,1,2,2,2,1,0,0,1,0,0,0,1,1,0,1,2,2,2,0,1,0,0,1,2,2,2,0,1,1,1,2,0,2,1,1,2,2,1,0,1,2,0,2,1,1,0,1,1,2,0,1,0,2,1,2,0,2,2,2,2,0,2,0,2,1,0,1,0,2,1,0,0,0,2,0,0,0,1,0,2,1,0,0,0,0,0,2,1,0,0,0,2,1,2,0,0,0,2,2,2,2,1,1,1,0,1,2,2,0,0,1,1,0,2,0,2,1,2,0,0,2,1,0,0,0,2,2,0,1,1,0,0,0,0,1,0,1,1,2,1,2,1,2,0,1,1,2,0,0,2,1,0,0,2,0,1,2,1,1,2,2,2,1,2,2,0,1,2,0,1,2,1,2,0,2,1,0,2,1,1,2,0,2,0,1,2,2,1,2,1,1,1,1,2,1,2,1,2,0,1,1,1,2,0,1,2,1,1,0,2,1,0,2,0,0,0,2,1,0,1,2,0,1,0,1,1,0,0,1,0,2,0,0,0,0,2,2,0,1,1,2,1,2,2,1,0,1,1,2,2,0,1,0,1,0,2,1,0,2,0,2,2,1,1,1,1,2,2,2,2,0,1,1,0,2,0,1,2,1,2,0,0,2,2,1,2,2,1,1,0,0,0,0,2,1,0,2,2,0,1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,0,0,1,2,2,0,2,0,1,2,2,1,0,2,2,0,0,0,2,0,0,0,1,2,1,0,2,2,1,2,0,0,2,2,2,1,1,1,2,0,0,2,0,0,2,1,2,2,2,1,0,0,1,1,1,0,0,2,0,1,1,0,0,0,1,0,2,0,0,1,1,2,0,2,0,2,0,1,0,0,1,1,0,1,0,1,1,0,2,1,0,1,0,1,2,0,0,1,2,0,2,1,0,1,1,2,0,2,2,1,1,2,2,1,1,0,2,2,2,2,1,2,0,2,0,2,2,1,1,0,1,0,0,1,2,2,1,1,1,0,1,0,1,2,0,2,1,2,2,0,2,2,0,1,1,0,0,1,1,1,1,1,0,1,2,0,2,2,0,1,2,2,1,1,2,0,1,1,1,2,0,2,1,1,2,1,1,1,1,2,1,0,1,2,0,1,1,1,0,2,1,2,0,0,2,1,0,1,0,2,2,2,1,1,1,2,2,0,2,1,0,2,2,2,2,2,2,0,0,1,2,2,2,0,0,2,0,2,2,2,2,2,2,2,0,2,1,1,2,0,2,2,0,2,1,0,0,1,1,1,1,2,1,2,0,2,0,0,0,2,2,0,0,2,1,2,1,0,1,0,2,0,1,2,0,1,2,0,1,1,1,1,0,2,2,1,0,2,1,0,2,0,1,0,0,2,1,0,1,0,2,2,2,1,2,2,0,2,1,0,2,0,2,1,1,2,0,1,2,0,0,1,1,1,0,2,0,0,2,2,0,0,2,2,1,0,1,2,1,1,2,1,0,0,1,0,0,0,0,0,1,2,2,2,1,1,2,0,1,2,1,2,1,1,1,1,1,0,2,1,1,1,0,2,0,0,0,2,1,0,1,2,0,1,1,2,1,1,2,2,0,2,0,2,0,2,0,2,2,0,0,1,0,2,0,0,0,0,0,1,0,2,1,1,0,1,2,2,1,0,2,2,1,2,0,1,2,2,2,0,1,0,0,1,0,2,1,0,1,1,1,1,2,1,2,0,1,2,2,2,2,2,0,1,0,2,2,0,0,0,0,1,2,1,1,1,1,0,1,0,0,0,0,2,2,2,0,0,0,1,2,2,2,2,2,2,2,1,2,1,1,1,2,0,1,1,2,0,0,1,2,0,2,0,2,2,1,2,2,2,2,2,1,1,2,1,1,1,2,0,1,2,2,1,1,0,2,1,2,1,1,1,0,2,1,0,0,2,2,2,1,0,1,2,1,2,1,1,0,0,0,2,1,0,1,0,0,1,2,0,0,2,0,0,0,1,0,1,0,1,0,1,0,1,1,1,0,2,2,0,0,0,1,2,0,1,1,1,1,2,1,1,0,1,1,1,0,1,1,2,1,2,2,1,2,2,2,1,1,0,2,1,0,2,0,1,1,0,1,2,1,1,0,2,0,0,1,0,0,1,0,0,1,2,2,0,1,2,1,2,2,2,2,0,2,1,1,0,0,0,1,1,2,2,0,0,0,1,2,0,1,2,0,1,2,1,1,2,1,2,2,0,1,2,2,1,2,0,1,1,0,0,0,0,1,2,2,2,0,1,0,1,0,2,1,1,0,2,1,2,1,2,0,2,0,0,1,2,0,1,0,0,0,1,1,1,2,1,1,1,0,1,2,0,0,0,1,0,2,0,2,0,1,1,1,0,0,0,2,0,1,2,0,1,0,1,1,0,1,0,1,1,2,1,1,2,2,1,1,1,0,1,0,1,1,2,1,2,2,1,1,2,2,2,1,1,1,1,1,1,2,1,1,0,2,1,0,0,1,1,1,0,2,2,0,0,1,1,2,2,1,2,2,2,0,0,2,2,2,0,1,0,2,1,0,0,2,0,0,1,2,1,2,1,2,0,0,1,0,2,0,0,2,0,1,1,2,2,0,1,0,1,1,1,2,2,1,1,1,2,0,1,2,0,1,1,1,0,1,0,2,2,0,2,1,0,0,1,2,0,0,1,0,1,0,2,2,1,0,1,2,2,0,2,2,0,0,1,1,1,2,1,2,2,2,0,1,0,0,0,1,0,0,0,1,1,0,2,1,0,2,1,2,0,2,0,2,2,0,2,2,0,1,0,0,2,0,2,2,1,0,2,0,2,2,1,1,2,2,2,1,0,0,1,2,1,0,1,0,2,2,1,2,1,2,0,1,0,1,2,2,1,0,2,0,2,1,0,1,2,0,0,2,2,1,1,0,0,1,2,0,2,2,1,2,1,0,1,1,0,0,2,2,2,2,2,0,1,0,1,1,1,0,1,2,1,0,2,2,0,1,1,2,0,2,2,0,2,1,1,2,2,2,1,1,0,1,0,2,2,2,2,0,2,2,1,0,0,1,1,0,1,2,1,0,0,0,2,2,0,2,0,1,2,2,1,1,1,2,0,2,0,0,1,2,0,1,1,0,1,1,1,2,0,0,0,2,1,0,2,1,2,1,0,1,1,2,2,0,1,0,2,2,2,1,1,0,1,2,1,2,0,0,0,0,1,1,1,1,0,2,1,0,0,2,0,2,0,1,1,0,0,1,2,0,2,2,2,1,1,0,0,0,0,1,0,1,2,2,2,0,1,0,1,1,0,0,1,0,0,1,1,2,2,0,0,2,2,0,0,0,2,2,2,2,1,1,2,2,2,0,0,2,0,1,2,2,2,2,0,0,2,0,2,2,2,0,2,1,1,1,1,0,2,0,2,0,0,1,2,2,1,0,2,0,1,2,2,1,2,0,0,2,0,0,1,1,1,0,2,0,2,2,2,2,1,2,2,0,1,2,2,2,0,0,0,1,0,1,2,0,0,0,0,1,2,0,0,2,2,0,1,1,2,2,2,2,0,0,0,1,0,1,0,1,1,0,0,0,2,2,0,0,1,1,0,2,2,1,1,0,2,0,2,1,0,1,2,1,1,2,1,0,0,1,2,1,1,2,2,0,1,2,0,0,0,1,1,2,0,2,1,2,0,1,0,0,0,2,0,1,1,2,2,2,0,0,0,2,2,1,0,2,1,0,0,2,1,1,2,0,2,0,2,0,1,2,2,0,0,0,2,2,1,1,1,0,0,1,1,0,0,0,2,1,1,0,1,0,2,0,1,0,2,0,2,1,0,1,2,0,0,2,1,1,0,0,1,0,2,1,1,1,2,1,2,2,0,2,2,1,2,2,2,1,0,1,1,1,2,1,1,1,1,0,0,1,1,0,2,2,0,1,1,1,1,2,1,1,0,0,2,2,0,2,1,1,1,1,2,0,2,2,2,0,1,0,1,0,0,1,0,2,0,0,0,2,1,1,2,2,0,1,1,0,0,1,0,2,0,2,2,0,2,2,0,0,1,2,0,1,0,0,0,0,1,2,0,1,1,0,0,2,0,0,2,0,1,1,2,2,1,0,1,0,0,2,2,2,0,0,1,0,2,0,1,2,1,0,1,1,2,2,2,2,0,0,0,2,1,1,2,0,1,1,1,0,0,0,1,0,2,0,2,0,2,0,0,1,0,0,2,0,2,2,2,2,2,1,0,2,0,0,0,0,0,0,2,0,2,0,1,0,2,2,2,1,1,1,0,1,0,1,1,0,2,0,0,1,2,2,1,2,0,0,0,2,2,0,1,1,0,2,0,1,2,1,0,0,0,1,1,1,2,0,1,1,1,2,1,0,2,1,0,1,0,1,2,0,1,2,0,2,0,0,0,2,0,2,2,2,0,1,1,2,0,0,1,1,0,1,1,0,2,0,1,1,2,2,1,0,2,1,2,0,0,0,2,2,2,0,1,1,0,0,1,1,1,1,0,0,2,0,2,2,0,1,0,0,1,1,1,1,1,0,0,2,0,0,2,0,2,2,2,2,1,1,1,2,0,2,1,1,0,0,1,2,1,2,2,2,2,0,0,0,1,1,0,1,0,1,1,1,2,0,2,2,2,0,1,0,1,2,2,0,0,2,0,0,1,0,0,1,2,1,0,1,2,2,1,2,2,1,1,0,2,1,0,1,1,2,1,2,1,0,2,0,1,1,0,0,1,0,2,1,1,1,2,1,0,2,2,1,2,2,1,2,2,2,2,1,1,2,1,0,0,2,2,1,1,2,1,1,1,0,0,0,0,0,0,2,2,1,0,1,0,1,1,2,2,0,1,1,2,2,1,0,2,1,1,1,2,1,2,0,0,2,0,2,0,0,0,0,2,2,2,0,0,0,2,0,2,1,0,2,1,1,0,1,0,0,2,2,1,1,2,0,0,0,1,1,1,1,1,0,2,2,2,2,1,0,0,0,1,0,1,1,0,1,2,2,1,0,1,1,0,2,0,2,2,1,1,1,1,0,0,2,2,1,2,0,0,2,1,0,2,1,2,1,2,1,0,2,2,2,0,0,1,1,0,0,1,1,1,1,2,2,2,1,0,2,0,2,2,2,1,1,1,0,0,1,1,0,1,0,0,2,1,2,0,0,0,1,2,0,1,2,0,1,0,0,0,1,0,1,2,2,1,2,0,1,0,2,1,0,1,2,1,1,1,2,1,0,0,2,1,1,1,0,2,1,2,2,2,2,2,1,1,2,1,2,1,0,1,1,0,1,2,0,1,2,2,2,2,2,1,0,2,2,2,2,0,1,2,1,2,0,0,2,0,0,0,0,0,0,2,0,0,2,0,2,1,1,2,0,1,1,2,0,0,2,2,0,0,2,0,2,2,1,0,1,0,2,0,0,0,0,2,0,1,2,1,0,1,2,0,2,0,2,1,0,0,0,1,2,0,1,1,2,1,1,1,0,0,0,0,0,2,2,0,2,2,2,1,2,1,1,1,2,0,2,1,0,0,0,2,2,1,0,2,0,2,0,1,0,1,0,2,0,1,1,1,1,0,2,0,1,2,1,2,0,2,1,2,1,2,2,2,2,1,2,0,0,2,0,2,2,2,0,1,2,1,0,2,0,2,2,2,0,1,1,0,2,2,2,2,0,1,2,1,2,2,1,2,0,1,2,0,0,0,2,2,1,1,0,0,2,1,1,1,0,1,2,0,1,2,0,0,1,2,0,2,0,0,2,0,2,0,1,1,1,1,1,0,2,1,1,2,2,0,0,1,2,1,2,2,1,0,2,2,2,2,2,0,1,0,0,1,1,2,0,1,2,1,2,0,0,0,2,2,2,1,2,1,1,2,0,0,0,0,1,1,1,0,1,0,2,0,1,1,2,2,0,0,1,2,0,2,2,1,2,0,0,1,0,1,2,2,0,1,2,1,2,1,2,1,2,0,1,1,1,1,1,2,0,2,2,1,2,2,1,1,0,0,1,0,2,0,1,1,1,1,2,2,0,0,1,0,1,0,2,2,2,1,0,2,2,2,0,0,2,2,1,2,2,0,2,0,2,1,0,2,0,0,1,1,1,0,2,0,0,0,1,0,2,1,2,1,2,1,0,1,2,0,2,0,1,2,2,1,0,1,2,1,2,1,0,2,2,2,1,1,1,0,0,1,1,1,1,1,1,2,1,1,1,0,0,2,0,1,2,2,0,1,2,2,2,2,0,2,1,1,2,2,2,2,1,0,1,0,2,2,0,1,0,2,2,0,0,0,0,2,0,2,1,0,1,1,2,2,1,1,2,1,2,2,0,1,1,2,0,0,0,0,2,0,0,1,2,1,2,2,2,1,0,1,1,1,1,0,0,2,0,2,1,0,2,2,1,0,0,2,1,2,2,2,1,0,2,1,0,1,2,2,0,1,2,2,0,0,2,1,2,0,1,0,1,2,1,1,0,1,1,0,0,1,2,0,1,2,2,0,1,0,0,2,2,2,2,2,0,2,0,1,1,2,2,0,0,2,0,0,2,0,1,1,0,1,0,1,2,1,1,2,0,0,0,1,1,1,1,1,2,2,1,0,1,2,2,0,1,2,2,1,1,1,2,1,1,1,2,2,2,0,0,0,0,1,1,0,0,2,2,1,2,0,2,2,0,0,1,1,0,2,1,1,1,0,2,0,0,0,0,0,1,2,1,0,0,0,0,2,2,1,0,2,2,0,1,0,0,1,2,0,0,0,1,0,2,0,2,0,0,2,2,1,1,0,0,2,0,0,2,1,0,2,1,0,1,2,2,1,0,2,0,0,0,0,2,2,2,2,0,1,1,0,1,2,0,0,0,2,0,1,1,1,1,0,0,1,2,1,1,2,2,1,0,1,1,1,1,0,2,0,1,2,2,0,2,0,2,1,1,0,1,0,2,2,2,2,1,1,2,1,1,2,0,0,2,0,0,1,0,0,2,2,0,2,1,2,2,2,2,1,0,1,2,2,1,1,1,1,1,0,1,2,0,0,2,0,0,2,2,1,1,1,0,0,0,2,0,2,0,1,2,2,0,2,2,2,0,1,0,1,2,2,2,1,0,2,1,1,2,0,1,2,2,1,0,2,2,1,2,0,1,2,1,0,2,0,0,2,2,1,1,0,2,0,0,2,2,0,1,0,1,2,0,1,0,1,2,0,0,1,1,1,0,1,1,0,2,2,2,0,1,0,1,1,0,2,1,0,1,0,0,2,0,0,1,2,0,2,1,0,1,0,0,0,0,1,0,1,0,0,2,0,2,0,0,1,1,0,0,2,0,0,2,1,2,1,2,2,1,2,1,0,1,2,0,2,0,1,2,2,0,2,2,1,1,0,0,0,0,1,0,0,1,0,0,2,1,0,1,0,1,0,2,2,2,2,2,1,2,0,1,2,2,1,0,1,2,0,1,1,0,1,2,0,1,2,0,0,2,0,0,2,2,0,0,1,2,2,0,0,1,2,2,1,1,1,2,0,2,0,2,2,1,2,1,1,2,1,1,2,2,2,2,2,0,0,1,2,1,2,0,0,2,0,0,2,1,1,1,2,0,1,2,0,1,1,0,1,1,2,0,2,2,0,1,2,2,2,0,1,2,0,2,2,0,0,1,0,0,0,0,2,0,1,0,0,2,0,0,0,2,1,0,2,0,1,1,1,0,2,0,0,1,0,2,2,1,0,0,1,1,0,1,2,1,1,2,2,2,0,1,0,2,2,2,1,1,2,2,0,1,2,0,0,1,1,2,0,1,2,1,2,1,2,2,1,2,2,0,1,1,2,0,1,0,0,2,0,0,1,0,0,0,2,1,2,2,2,0,0,1,2,0,0,2,1,1,2,0,0,2,1,1,0,0,1,2,2,0,1,2,0,1,0,2,2,1,1,1,0,0,2,2,2,2,0,1,0,2,2,1,2,1,1,1,0,2,2,1,1,2,2,0,2,1,2,2,2,1,1,2,1,0,0,1,1,0,2,1,0,2,2,2,2,0,0,0,1,0,0,0,1,1,1,0,1,0,0,0,2,1,0,2,1,0,0,2,0,2,2,1,2,0,2,1,2,2,1,2,0,0,2,2,0,0,1,0,1,2,1,1,0,2,1,0,1,2,2,2,1,1,2,0,1,1,2,1,2,0,2,1,0,2,1,2,0,0,0,0,0,2,0,2,1,0,0,0,1,2,0,0,2,1,2,0,2,1,2,0,1,1,2,0,0,1,1,0,0,2,0,1,2,1,1,0,1,0,2,2,2,2,1,2,0,2,1,2,2,1,1,1,0,1,2,2,1,2,0,0,0,2,1,1,1,0,2,0,1,0,2,0,0,2,0,2,1,1,1,2,0,1,0,0,2,2,1,0,0,0,2,2,0,2,1,1,0,1,1,2,1,2,2,0,0,1,2,2,2,2,2,1,2,0,1,2,1,0,2,2,2,2,2,1,2,1,2,0,0,1,1,2,2,1,0,1,2,0,2,0,1,2,2,1,2,1,0,0,1,2,0,1,1,0,2,2,2,0,1,2,2,1,0,1,2,1,0,2,2,2,2,0,1,0,2,0,0,0,1,1,2,2,2,0,2,2,2,0,2,1,0,2,1,2,1,2,2,1,0,1,1,2,2,0,1,2,1,2,1,2,2,0,2,0,1,1,0,2,2,2,2,1,0,1,0,0,1,1,2,1,2,1,1,2,1,1,0,2,2,1,1,2,2,1,1,2,2,1,2,2,1,2,1,2,0,1,2,1,0,2,0,2,0,0,0,2,0,0,0,1,2,2,2,2,1,0,2,0,0,1,1,0,0,0,1,0,1,2,2,0,2,1,2,1,2,2,1,0,1,0,2,2,0,2,2,1,1,0,0,1,1,0,2,2,2,0,1,0,1,0,0,1,0,2,1,2,2,0,0,2,0,0,2,0,2,1,1,1,1,0,0,1,0,1,0,1,0,2,2,1,1,2,1,2,0,2,1,0,2,2,0,2,2,0,2,2,2,0,1,2,0,2,2,2,0,1,0,0,2,2,1,1,2,1,2,2,0,2,2,2,2,0,0,0,1,0,2,0,0,2,1,2,0,2,2,2,2,2,2,1,2,0,2,2,2,2,1,1,0,0,1,2,0,2,0,2,0,2,2,0,1,2,1,2,0,2,2,1,2,1,0,0,1,2,1,0,2,2,1,1,1,2,1,1,2,1,0,2,2,0,0,0,2,1,2,2,0,1,0,0,2,1,1,1,0,1,1,2,2,1,1,0,0,1,1,0,2,0,2,1,0,0,1,2,2,1,0,2,2,1,1,0,1,0,0,0,0,1,1,1,1,1,0,2,1,0,2,2,0,2,1,1,0,2,1,1,1,2,2,2,2,2,2,1,1,1,2,0,2,2,2,1,1,1,0,2,1,2,1,0,1,1,0,0,0,2,1,2,2,1,1,2,0,1,0,2,0,0,2,2,1,0,2,1,2,0,2,2,2,2,0,0,0,1,0,2,1,1,0,2,1,2,2,1,2,2,1,0,1,2,2,0,1,0,1,2,2,1,1,1,0,0,0,1,2,2,1,2,2,0,2,2,1,0,0,2,0,1,1,2,1,0,0,0,1,2,0,0,0,0,1,1,1,2,1,2,2,1,2,2,2,1,1,2,2,2,2,1,2,0,0,0,2,0,2,1,2,0,1,1,1,0,0,2,2,1,1,0,1,0,0,1,0,1,0,2,0,2,0,1,2,2,1,2,1,1,1,0,1,0,0,2,0,1,1,2,2,2,1,1,0,1,2,2,2,0,2,2,0,1,1,1,1,1,2,0,0,2,2,2,0,0,0,1,1,2,0,2,1,0,1,1,2,1,1,2,2,2,2,2,2,0,0,2,1,2,2,2,1,2,0,0,2,1,1,0,1,0,2,0,1,2,2,0,0,0,2,0,1,0,1,2,1,0,1,2,2,1,0,0,1,1,0,2,2,0,1,2,1,1,0,1,1,2,1,2,2,1,0,2,0,2,1,0,0,2,2,1,1,0,0,1,1,0,0,2,0,0,2,0,2,0,2,1,1,2,1,0,0,0,0,2,0,0,1,1,2,0,0,2,1,1,2,0,2,1,1,1,2,1,2,1,2,0,1,2,2,2,1,2,2,1,1,2,0,2,1,0,1,2,1,1,0,2,1,2,0,1,1,0,0,0,2,1,0,1,0,0,0,1,2,0,0,1,0,0,2,2,0,2,1,0,0,1,1,2,2,2,0,1,1,0,1,0,2,0,0,0,2,0,1,0,0,0,1,0,2,2,0,1,1,1,1,0,0,2,1,2,0,0,0,1,1,2,2,0,0,0,1,2,1,0,1,1,2,1,1,0,0,2,2,2,0,1,0,0,2,1,0,1,0,0,0,2,1,2,1,0,2,0,0,1,2,2,1,2,1,2,0,0,1,1,0,1,1,1,1,2,2,1,2,0,2,1,0,0,0,2,2,2,0,1,2,1,1,0,1,2,1,0,0,0,2,0,0,1,2,2,0,0,1,0,0,1,0,2,1,0,2,2,2,0,2,1,1,2,0,1,1,1,1,1,1,1,1,0,2,0,2,2,2,2,2,0,2,1,1,0,1,0,0,1,0,0,0,2,1,2,2,2,1,0,1,0,2,2,0,0,0,1,2,0,2,2,1,1,1,0,2,2,0,2,2,0,1,2,2,0,1,1,1,1,2,2,0,2,2,2,2,1,1,0,2,1,0,0,1,1,0,0,0,0,1,0,2,1,2,0,1,0,2,1,2,2,2,2,0,2,1,0,2,0,2,0,2,2,0,0,2,0,2,1,2,2,0,0,1,2,0,1,1,2,0,0,2,0,1,0,0,2,0,1,2,2,1,0,2,2,1,0,1,1,0,1,1,1,0,0,1,0,2,0,2,2,2,2,1,0,2,2,0,2,0,0,0,2,0,0,2,0,2,1,1,2,1,1,0,1,0,1,1,2,0,2,1,0,0,0,2,0,2,0,0,2,1,0,0,0,0,0,1,0,1,1,1,1,1,1,2,0,1,2,1,0,1,0,2,2,2,2,0,2,0,0,0,1,1,0,1,1,0,2,0,2,2,1,0,1,0,1,0,0,1,1,1,1,1,2,1,0,1,2,1,2,2,0,1,0,1,2,0,1,1,2,0,0,2,0,2,0,0,1,2,2,2,0,0,2,0,1,1,2,2,0,0,2,1,1,0,1,1,0,2,0,0,2,2,0,0,2,0,1,2,1,2,0,2,1,1,1,0,2,0,0,2,2,2,2,2,1,2,0,2,1,1,2,2,2,0,0,1,0,0,2,2,2,1,1,1,2,1,2,2,2,0,1,0,0,1,1,0,1,1,2,0,2,1,1,0,1,1,1,0,0,1,1,1,0,1,1,2,0,0,0,2,2,0,0,0,0,2,1,2,1,1,1,2,1,1,0,0,0,0,2,1,2,1,0,1,2,2,0,0,0,2,2,0,0,1,0,0,1,1,2,1,2,1,0,1,1,1,1,2,1,1,2,0,1,2,1,0,2,2,2,0,0,2,2,0,0,2,1,0,0,2,2,1,2,0,0,0,0,2,1,0,1,1,0,2,1,2,1,2,1,2,1,2,2,1,2,0,2,2,2,1,1,1,2,1,2,2,2,1,1,2,1,1,2,1,2,1,2,2,0,2,2,1,2,1,2,2,2,0,0,0,1,1,0,2,1,0,1,1,2,1,0,2,1,0,1,0,0,2,2,1,2,1,0,1,1,0,1,1,2,2,0,0,2,0,0,0,2,0,2,1,1,2,2,1,0,0,2,1,0,2,2,1,1,2,1,2,2,2,2,0,1,1,1,2,0,2,0,0,1,2,0,2,2,0,2,2,0,0,2,1,2,1,1,0,2,2,2,1,2,2,0,0,0,0,2,0,1,1,2,1,1,1,2,2,1,0,1,1,1,1,0,1,1,2,1,0,2,0,2,0,1,2,2,0,1,1,2,1,2,0,2,1,0,1,0,1,2,1,2,0,2,1,2,1,0,1,1,1,0,1,0,0,2,0,0,2,2,0,0,2,0,2,2,0,0,2,2,0,2,1,2,0,1,0,2,1,1,2,1,2,0,2,1,2,1,1,2,2,1,0,1,0,1,1,1,1,0,0,0,2,0,0,0,0,0,2,1,2,0,1,1,2,0,2,2,0,2,0,1,1,1,0,0,2,1,1,2,0,1,2,0,0,2,0,0,2,0,1,2,2,2,2,2,0,1,0,2,2,1,1,2,2,2,1,0,2,2,2,2,1,0,0,2,2,1,1,1,1,1,1,2,2,0,2,2,1,1,2,0,1,0,1,2,2,0,2,2,2,0,2,1,1,1,2,0,0,0,1,2,0,1,0,1,0,1,1,2,2,1,0,0,2,0,1,2,0,0,1,2,1,1,2,2,1,0,0,0,0,2,2,0,2,0,0,1,0,2,0,2,1,1,1,0,2,2,0,0,0,1,0,1,0,1,0,2,1,2,0,1,2,2,0,0,0,0,0,0,2,0,2,1,0,2,1,1,1,2,0,1,1,2,1,0,1,2,0,2,1,2,0,0,1,1,0,1,1,2,0,2,2,0,2,1,0,0,2,2,0,2,1,2,1,1,1,1,2,2,0,1,2,2,0,2,1,1,1,2,0,0,1,0,0,0,2,1,1,0,0,0,1,0,0,2,2,0,1,1,0,2,1,2,2,0,0,2,2,0,0,2,2,0,0,1,1,1,0,0,0,1,2,0,0,0,1,0,1,2,2,2,1,1,1,1,0,2,2,1,1,1,0,2,0,2,0,2,1,2,2,1,2,1,0,1,1,2,1,2,2,1,0,1,1,0,1,2,1,0,0,0,0,0,2,1,2,0,2,0,1,0,2,1,0,0,2,0,1,2,0,2,2,1,1,1,0,0,2,0,1,1,1,1,2,0,1,1,0,0,2,0,0,1,1,0,0,0,0,1,1,1,0,1,2,1,2,1,1,2,2,2,1,1,0,2,2,0,2,2,2,0,2,0,1,1,0,1,2,1,2,1,1,2,0,0,1,2,1,1,0,1,2,1,2,2,1,2,1,1,0,2,2,1,0,2,0,1,2,1,1,2,0,1,2,2,1,2,0,1,2,1,1,2,0,2,1,1,0,2,2,2,0,2,0,1,1,0,0,1,0,1,2,2,1,1,0,1,1,1,1,1,2,2,0,2,1,1,1,1,0,1,0,1,1,0,0,1,0,1,2,2,1,2,0,1,2,1,0,0,0,1,0,0,1,2,1,1,0,2,0,0,0,0,0,1,0,1,2,1,2,2,2,0,2,1,1,2,2,1,0,1,0,0,1,1,2,1,2,0,1,2,2,2,0,2,2,0,0,2,1,2,1,2,1,0,2,2,0,0,1,0,1,1,0,0,0,0,0,2,2,2,0,1,2,0,1,1,2,1,0,1,2,0,2,2,2,1,2,2,1,1,2,0,2,1,1,0,2,1,1,1,2,1,2,1,1,2,1,2,2,1,0,0,2,0,0,1,0,2,0,2,0,2,1,0,1,2,1,0,1,2,1,1,0,2,2,1,2,1,1,0,2,2,2,2,0,2,1,0,2,1,2,2,0,1,1,1,0,1,2,1,2,0,1,2,2,0,2,2,2,0,1,1,0,2,1,0,0,2,1,0,1,0,0,1,1,1,1,2,0,1,0,1,1,2,2,2,0,0,2,1,1,1,2,2,0,0,0,0,2,0,1,1,1,2,0,0,1,1,1,2,0,0,1,0,2,0,0,2,2,1,2,1,1,2,2,2,2,1,2,2,1,2,1,1,0,1,1,1,1,2,1,1,2,2,2,1,1,1,0,0,0,0,0,1,1,2,1,1,0,1,1,2,2,0,1,2,2,1,2,1,0,1,2,1,0,2,1,1,1,2,2,1,1,0,0,0,1,1,2,1,0,2,1,0,1,2,1,1,1,1,2,2,0,2,1,1,1,1,2,0,0,1,1,2,1,2,0,2,1,0,0,0,0,1,2,0,1,2,0,0,1,1,1,2,2,2,2,2,1,2,0,0,1,0,0,2,0,1,0,2,0,1,2,1,1,1,1,2,0,2,0,2,0,0,1,2,2,1,1,1,1,1,2,1,2,0,0,2,1,2,1,1,1,2,2,2,1,2,0,2,1,2,1,2,1,2,1,2,2,2,2,1,1,2,0,0,0,2,0,2,2,0,1,0,1,2,1,1,0,0,1,1,2,2,0,1,1,2,2,1,2,0,1,2,1,0,2,2,1,0,1,0,1,1,0,2,2,2,1,2,0,2,2,2,2,2,1,0,1,1,2,1,2,1,2,0,0,0,0,2,0,2,2,1,1,1,1,2,2,0,0,0,2,0,2,1,0,0,1,0,1,2,1,0,1,0,2,0,2,0,0,2,2,0,0,1,2,1,0,1,0,2,1,0,2,2,2,2,2,2,0,0,1,2,2,2,2,0,1,0,2,1,2,2,2,0,2,2,2,1,1,2,2,1,0,0,1,1,2,1,0,0,0,0,0,2,0,0,0,1,0,2,0,2,2,1,2,2,2,0,0,2,1,1,2,1,2,2,0,0,2,2,2,2,0,0,0,0,0,0,2,0,2,2,1,0,0,1,0,2,2,1,0,2,2,0,1,0,2,1,0,0,2,0,0,2,1,2,2,2,0,0,1,0,0,2,0,2,1,2,2,2,1,1,1,2,1,2,2,2,2,0,1,0,2,1,2,0,2,1,0,2,0,1,1,0,1,1,2,2,0,0,2,1,0,2,0,2,1,2,2,1,2,1,2,1,2,2,2,0,2,1,2,2,1,0,2,0,0,1,0,2,0,1,1,1,2,2,2,2,2,0,1,1,1,1,2,1,0,0,2,2,1,2,2,2,0,1,2,1,1,1,2,2,0,1,1,2,2,0,0,0,0,0,2,1,0,1,0,0,0,0,1,2,1,1,0,2,1,2,1,0,0,0,0,1,2,1,0,0,0,0,1,2,0,0,1,2,2,1,2,2,2,2,0,0,0,2,0,0,2,0,2,1,1,1,0,0,0,2,1,0,2,1,0,2,0,2,2,0,0,0,0,2,1,1,1,0,1,2,2,1,0,0,0,1,1,0,0,1,0,2,1,2,1,1,2,2,2,2,2,2,1,0,2,2,2,1,2,1,2,1,0,2,1,0,1,1,1,1,0,0,2,1,0,1,0,1,0,1,1,1,1,1,2,0,0,2,0,1,1,0,1,1,1,2,1,0,0,1,2,0,1,1,0,2,1,1,2,1,0,1,2,0,1,1,0,1,1,0,2,2,1,0,1,1,0,0,0,2,2,2,1,0,2,0,1,0,2,2,1,2,0,0,1,2,1,0,1,0,1,2,2,2,2,1,2,1,0,2,1,2,2,2,2,2,0,2,2,0,1,1,2,2,2,0,2,2,2,0,0,2,1,1,1,0,0,1,0,0,2,1,1,1,0,1,0,0,0,2,0,0,1,1,1,2,0,1,1,0,1,2,0,1,2,0,2,2,2,1,0,2,2,2,1,0,0,2,2,2,0,2,0,2,1,1,0,1,0,0,1,2,1,1,2,1,1,0,2,0,0,1,1,0,2,1,2,1,1,1,2,0,2,1,0,1,0,1,0,1,0,1,2,0,1,0,0,2,2,1,2,0,0,2,1,2,1,2,2,0,1,1,0,1,1,2,0,0,1,2,0,0,0,2,0,2,2,0,0,2,1,2,2,2,0,0,1,1,2,2,0,1,0,1,0,0,0,0,0,1,0,0,0,1,1,0,2,2,1,0,1,1,1,1,2,0,0,1,0,2,1,0,2,1,1,0,1,1,0,1,2,2,0,0,1,1,2,0,2,1,0,2,2,0,2,1,0,0,1,0,0,1,0,2,0,2,0,0,1,0,0,1,2,0,1,1,1,2,0,0,0,0,2,2,2,0,1,0,1,1,0,0,2,2,0,2,0,1,2,1,1,1,0,1,0,2,0,1,2,0,2,2,0,1,1,1,2,1,1,0,1,2,2,0,1,0,1,0,1,2,1,1,0,0,2,1,2,2,2,0,1,2,0,2,1,1,0,2,1,2,1,2,0,2,0,0,1,0,1,0,1,1,0,1,0,0,1,2,2,2,2,2,2,2,1,2,2,1,2,0,1,0,0,0,1,0,2,2,1,0,1,1,0,2,2,1,0,2,2,1,1,0,0,0,1,2,2,1,2,0,2,0,1,0,2,2,0,0,2,0,1,2,2,1,1,2,2,1,1,1,2,0,0,0,0,2,0,0,1,1,2,1,1,1,1,0,0,1,1,1,0,2,0,0,1,1,2,2,2,0,0,1,0,0,2,1,2,1,2,0,1,2,2,0,2,1,1,0,0,0,2,0,2,0,1,2,0,1,2,1,0,1,1,0,0,0,1,2,1,0,2,0,2,0,0,1,1,0,0,0,1,1,0,1,2,1,0,2,1,1,0,1,1,2,1,1,1,0,2,2,2,1,0,1,0,1,2,1,2,1,2,0,0,2,2,1,0,2,2,2,2,2,0,1,0,1,1,2,1,1,2,1,1,1,2,1,1,2,1,0,0,2,2,0,0,1,1,2,1,1,0,0,0,2,0,2,2,1,0,2,0,0,1,2,1,2,2,1,2,0,0,2,0,0,0,2,2,1,0,1,2,2,1,1,1,1,1,1,1,1,2,1,0,2,0,0,0,0,1,0,0,1,2,1,2,2,2,0,2,2,0,1,2,0,1,0,2,0,2,1,1,1,0,2,1,2,1,2,0,1,0,2,2,2,0,1,1,1,2,2,2,0,1,0,2,2,2,2,0,0,0,2,1,2,2,1,2,0,1,1,1,0,0,1,1,1,2,1,1,2,2,2,0,0,0,2,2,1,1,0,2,1,2,1,1,2,1,1,2,0,1,1,1,1,2,2,2,2,2,1,1,0,0,2,1,2,0,2,2,1,1,1,2,2,0,1,2,0,0,0,0,0,2,0,2,2,1,2,0,2,1,0,1,2,2,2,0,2,2,2,2,1,2,1,2,2,0,0,2,2,0,1,2,0,2,1,0,2,1,1,2,1,2,2,1,2,2,2,0,1,1,0,0,1,0,2,2,0,1,2,1,0,2,2,0,1,0,2,2,1,1,0,2,1,1,2,2,1,2,2,1,0,1,2,0,1,1,1,0,2,0,0,2,2,0,2,1,0,2,0,1,0,0,1,0,1,0,2,2,1,1,0,1,0,1,0,1,2,2,2,2,1,2,1,0,0,2,1,0,0,0,1,2,2,0,1,1,2,2,0,1,0,0,1,0,1,1,1,2,0,2,0,0,1,1,1,0,1,1,2,2,2,1,0,0,2,2,0,2,2,1,2,0,0,2,2,0,0,2,2,0,0,1,0,2,1,0,1,1,0,2,0,0,0,0,2,1,1,2,0,0,2,1,0,0,1,2,1,1,0,0,0,2,2,2,1,2,1,0,1,1,1,0,1,0,0,2,0,0,1,0,2,2,2,2,2,1,1,0,0,0,1,1,0,2,1,1,1,2,1,0,0,1,0,2,2,2,0,1,1,0,1,1,2,0,1,2,1,0,2,1,0,0,2,1,0,2,1,2,2,1,2,0,2,2,0,0,1,0,2,2,1,2,1,2,2,1,1,0,0,2,2,1,1,2,2,1,2,0,0,0,2,2,2,0,1,0,2,1,2,2,2,2,2,1,0,1,0,1,0,0,0,1,1,0,2,1,2,0,1,0,1,1,0,0,1,1,0,2,0,0,1,1,2,0,2,1,0,0,2,0,1,2,0,0,0,1,1,0,2,0,2,0,2,0,0,1,1,0,0,0,2,0,2,1,0,1,0,1,0,1,2,1,1,0,0,1,2,1,0,2,0,1,1,1,2,2,2,2,0,1,0,0,1,2,2,2,2,1,0,0,0,2,2,1,1,1,2,0,1,0,0,1,1,1,1,1,2,0,2,1,1,2,2,1,1,2,2,2,0,2,2,2,1,1,2,1,1,0,1,2,0,1,2,0,2,0,2,2,0,2,1,0,2,0,1,1,0,2,1,1,2,0,1,1,1,2,1,2,1,2,2,1,1,0,0,2,2,1,2,0,1,1,2,1,1,1,1,0,1,0,2,0,1,1,1,0,0,0,1,1,1,1,0,0,2,1,2,2,1,1,2,1,0,1,2,1,1,1,1,0,0,1,0,0,0,0,0,1,0,1,1,0,2,0,2,1,1,0,2,2,2,0,2,1,2,2,1,1,1,1,1,0,0,0,1,2,2,2,0,0,0,0,2,1,0,1,0,2,1,0,1,0,1,2,0,1,0,2,1,1,1,0,2,1,2,0,1,1,1,0,0,0,0,2,0,0,2,0,2,1,0,1,0,0,0,1,1,0,2,1,2,1,2,2,0,1,2,0,2,1,1,0,1,1,1,2,0,0,1,2,1,2,0,1,2,1,2,0,1,2,1,0,1,2,1,0,1,1,1,0,1,1,2,0,1,0,0,1,1,1,1,1,0,2,2,0,2,2,0,1,1,2,1,2,0,2,1,0,2,1,1,1,2,0,0,2,1,2,2,2,2,2,1,0,2,2,0,1,1,0,2,2,1,1,0,2,1,2,0,0,2,1,1,2,0,0,0,0,2,2,0,1,1,0,2,2,1,2,1,1,0,2,2,0,1,2,1,2,1,0,1,1,0,0,2,2,2,0,0,2,2,0,0,0,0,0,0,1,1,0,2,0,0,2,0,2,0,0,0,2,1,2,2,1,0,2,2,1,2,2,0,2,0,1,0,0,1,2,1,0,1,0,0,1,0,0,0,1,1,1,2,2,2,1,0,2,2,2,0,2,1,2,1,2,0,1,1,0,0,0,2,2,1,1,1,2,0,2,1,1,1,0,0,1,2,2,0 }), 25000000);

	return;
}