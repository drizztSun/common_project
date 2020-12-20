/*
# 719. Find K-th Smallest Pair Distance


# Given an integer array, return the k-th smallest distance among all the pairs.
# The distance of a pair (A, B) is defined as the absolute difference between A and B.

# Example 1:
# Input:
# nums = [1,3,1]
# k = 1
# Output: 0
# Explanation:
# Here are all the pairs:
# (1,3) -> 2
# (1,1) -> 0
# (3,1) -> 2
# Then the 1st smallest distance pair is (1,1), and its distance is 0.

# Note:
# 2 <= len(nums) <= 10000.
# 0 <= nums[i] < 1000000.
# 1 <= k <= len(nums) * (len(nums) - 1) / 2.
*/




#include <vector>
#include <algorithm>
using namespace std;

class KthSmallestPairDistance {

public:

	/*
    Approach #3: Binary Search + Sliding Window [Accepted]
    Intuition
    
    As in Approach #2, let's binary search for the answer, and we will focus on evaluating our possible function quickly.
    
    Algorithm
    
    We will use a sliding window approach to count the number of pairs with distance <= guess.
    
    For every possible right, we maintain the loop invariant: left is the smallest value such that nums[right] - nums[left] <= guess. 
    Then, the number of pairs with right as it's right-most endpoint is right - left, and we add all of these up.

	O(n*log(n))
	*/
	int doit(vector<int>&& nums, int k) {

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

	/*
	O(n^2)
	*/
	int doit1(vector<int>&& nums, int k) {
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
