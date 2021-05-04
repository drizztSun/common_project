/*

45. Jump Game II

Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Your goal is to reach the last index in the minimum number of jumps.

Example:
Input: [2,3,1,1,4]
Output: 2

Explanation: The minimum number of jumps to reach the last index is 2.
Jump 1 step from index 0 to 1, then 3 steps to the last index.

*/

#include <vector>
#include <algorithm>
using namespace std;


class Jump {

public:

	int doit(vector<int>&& nums) {

		if (nums.size() < 2)
			return 0;

		int i = 1, scope = nums[0];
		int steps = 1;

		while (i < nums.size() && scope < nums.size() - 1) {

			int nextScope = scope;

			while (i <= scope) {
				nextScope = max(nextScope, i + nums[i]);
				i++;
			}

			if (scope == nextScope)
				break;

			steps++;
			scope = nextScope;
		}

		return steps;
	}

	int doit2(vector<int>& nums) {

		if (nums.size() < 2)
			return 0;

		int i = 0;
		int currentMax = 0, nextMax = 0;
		int levels = 0;

		while (currentMax - i + 1 > 0) {

			levels++;
			
			for (; i <= currentMax; i++) {
				nextMax = max(nextMax, i + nums[i]);
				if (nextMax >= nums.size() - 1)
					return levels;
			}

			currentMax = nextMax;
		}

		return 0;
	}


	// <TLE> because of it should be O(n)
	int doit1(vector<int>& nums) {

		vector<int> steps(nums.size(), INT_MAX);
		steps[0] = 0;

		for (auto i = 0; i < nums.size()-1; i++) {
			
			for (auto j = 1; j <= nums[i]; j++) {
				if (i + j < steps.size())
					steps[i + j] = std::min(steps[i + j], steps[i] + 1);
			}
		}

		return steps[nums.size() - 1];
	}
};