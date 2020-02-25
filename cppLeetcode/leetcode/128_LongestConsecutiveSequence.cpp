/*

128. Longest Consecutive Sequence

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

*/

#include <stdlib.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

class LongestConsecutiveSequence {

public:

	int doit1(vector<int>& nums) {
		
		std::unordered_set<int>  recorder(nums.begin(), nums.end());
		int best = 0;

		for (auto c : recorder) {
			
			if (recorder.find(c - 1) == recorder.end()) {
				int s = c + 1;
				while (recorder.find(s) != recorder.end())
					s += 1;

				best = std::max(best, s - c);
			}
		}
			
		return best;
	}

	int doit(vector<int>& nums) {

		unordered_map<int, int> keep;

		for (auto w : nums) {

			if (keep[w])
				continue;

			keep[w] = 1;
			int tmp_l = keep[w - 1];
			int tmp_r = keep[w + 1];

			keep[w + tmp_r] = keep[w - tmp_l] = 1 + tmp_l + tmp_r;
		}

		int res = 0;
		for (auto& c : keep) {
			res = std::max(res, c.second);
		}

		return res;
	}

	int doit3(vector<int>& nums) {
		sort(nums.begin(), nums.end());

		int max_sum = 0;
		int sum = 0;

		if (nums.size() <= 1)
			return nums.size();

		sum = 1;

		for (size_t i = 1; i < nums.size(); i++)
		{
			if ((nums[i] - nums[i - 1]) == 1 || (nums[i] - nums[i - 1]) == 0)
			{
				if ((nums[i] - nums[i - 1]) == 1)
					sum++;
			}
			else
			{
				max_sum = max(max_sum, sum);
				sum = 1;
			}
			// cout << sum << endl;
		}

		max_sum = max(max_sum, sum);
		return max_sum;
	}

	int doit2(vector<int>& nums) {

		if (nums.size() == 0)
			return 0;
		
		std::unordered_set<int> record(nums.begin(), nums.end());
		int best = 1;

		for (int c : nums) {

			if (record.find(c) == record.end())
				continue;

			record.erase(c);

			int prev = c - 1, next = c + 1;

			while (record.find(prev) != record.end()) 
				record.erase(prev--);
			
			while (record.find(next) != record.end())
				record.erase(next++);

			best = std::max(best, next - prev - 1);
		}

		return best;
	}

};
