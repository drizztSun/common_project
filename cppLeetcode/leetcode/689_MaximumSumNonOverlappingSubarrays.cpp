/*

# 689. Maximum Sum of 3 Non-Overlapping Subarrays


In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.

Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.

Return the result as a list of indices representing the starting position of each interval (0-indexed). 
If there are multiple answers, return the lexicographically smallest one.

Example:
	Input: [1,2,1,2,6,7,5,1], 2
	Output: [0, 3, 5]
	Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
	We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.

Note:
	nums.length will be between 1 and 20000.
	nums[i] will be between 1 and 65535.
	k will be between 1 and floor(nums.length / 3).


*/

#include <vector>
using std::vector;

class MaxSumOfThreeSubarrays {

public:
	
	vector<int> doit(vector<int>&& nums, int k) {
		int N = nums.size();
		vector<int> sums(N + 1, 0);

		for (int i = 0; i < N; i++)
			sums[i + 1] = sums[i] + nums[i];

		int leftMax = sums[k] - sums[0];
		vector<int> left(N, 0);
		for (int i = k; i < N; i++) {
			if (sums[i + 1] - sums[i - k + 1] > leftMax) {
				left[i] = i - k + 1;
				leftMax = sums[i + 1] - sums[i - k + 1];
			}
			else {
				left[i] = left[i - 1];
			}
		}

		int rightMax = sums[N] - sums[N - k];
		vector<int> right(N, N - k);
		for (int i = N - k - 1; i > -1; i--) {
			if (sums[i + k] - sums[i] > rightMax) {
				right[i] = i;
				rightMax = sums[i + k] - sums[i];
			}
			else {
				right[i] = right[i + 1];
			}
		}

		vector<int> res(3, 0);
		int MaxV = 0;
		for (int i = k; i < N - 2 * k + 1; i++) {
			int l = left[i - 1], r = right[i + k];
			int total = sums[l + k] - sums[l] + sums[r + k] - sums[r] + sums[i + k] - sums[i];

			if (total > MaxV) {
				MaxV = total;
				res[0] = l, res[1] = i, res[2] = r;
			}
		}

		return res;
	}
};