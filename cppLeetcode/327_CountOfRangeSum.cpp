

/*

# 327. Count of Range Sum

# Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
# Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ? j), inclusive.

# Note:
# A naive algorithm of O(n2) is trivial. You MUST do better than that.

# Example:
# Given nums = [-2, 5, -1], lower = -2, upper = 2,
# Return 3.
# The three ranges are : [0, 0], [2, 2], [0, 2] and their respective sums are: -2, -1, 2.


*/

#include <vector>
#include <algorithm>

class CountRangeSum {

public:

	int countSum(std::vector<int>& nums, int lower, int upper) {

		std::vector<int> sums;
		sums.push_back(0);

		for (auto i : nums) {
			sums.push_back(sums.back() + i);
		}

		return search(sums, 0, sums.size(), lower, upper);
	}

	int search(std::vector<int>& sums, int start, int end, int lower, int upper) {

		int mid = (start + end) / 2;
		if (mid == start)
			return 0;

		int count = search(sums, start, mid, lower, upper) + search(sums, mid, end, lower, upper);
		int i = mid, j = mid;

		for (auto left = start; left < mid; left++) {

			while (i < end && sums[i] - sums[left] < lower)
				i++;
			while (j < end && sums[j] - sums[left] <= upper)
				j++;

			count += j - i;
		}

		
		std::sort(sums.begin() + start, sums.begin() + end);

		return count;
	}


	int mergeSort(std::vector<long>& sum, int lower, int upper, int low, int high)
	{
		if (high - low <= 1) return 0;
		int mid = (low + high) / 2, m = mid, n = mid, count = 0;
		count = mergeSort(sum, lower, upper, low, mid) + mergeSort(sum, lower, upper, mid, high);
		for (int i = low; i< mid; i++)
		{
			while (m < high && sum[m] - sum[i] < lower) m++;
			while (n < high && sum[n] - sum[i] <= upper) n++;
			count += n - m;
		}
		inplace_merge(sum.begin() + low, sum.begin() + mid, sum.begin() + high);
		return count;
	}

	int countRangeSum(std::vector<int>& nums, int lower, int upper) {
		int len = nums.size();
		std::vector<long> sum(len + 1, 0);
		for (int i = 0; i< len; i++) sum[i + 1] = sum[i] + nums[i];
		return mergeSort(sum, lower, upper, 0, len + 1);
	}
};


void Test_327_CountOfRangeSum() {

	CountRangeSum A;

	std::vector<int> nums = {-2, 5, -1};
	int res = A.countSum(nums, -2, 2);


	nums = { 0, -3, -3, 1, 1, 2 };
	res = A.countSum(nums, 3, 5);

	res = A.countSum(std::vector<int>(), 0, 0);
}


