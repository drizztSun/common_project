/*

41. First Missing Positive

Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

Input: [1,2,0]
Output: 3
Example 2:

Input: [3,4,-1,1]
Output: 2
Example 3:

Input: [7,8,9,11,12]
Output: 1

*/

#include <vector>
using namespace std;

class FirstMissingPositive {
public:
	int doit(vector<int>&& nums) {

		for (int i = 0; i < nums.size(); i++) {
			while (nums[i] > 0 && nums[i] <= nums.size() && nums[i] != i+1 && nums[i] != nums[nums[i]-1]) {
				int tmp = nums[i];
				nums[i] = nums[tmp - 1]; 
				nums[tmp-1] = tmp;
			}
		}

		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] - 1 != i)
				return i+1;
		}

		return nums.size() == 0 ? 1 : nums.size() + 1;
	}
};



//static const auto _____ = []()
//{
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr);
//	return nullptr;
//}();


class Solution {
public:
	int firstMissingPositive(vector<int>&& nums) {

		int size = nums.size();
		int result = size + 1;
		for (int i = 0; i < size; i++)
		{
			if (nums[i] > size)
				nums[i] = -1;
		}

		for (int i = 0; i < size; i++)
		{
			if (nums[i] > 0) {
				while (nums[(nums[i] - 1) % size] <= size)
				{
					if (nums[(nums[i] - 1) % size] <= 0)
						nums[(nums[i] - 1) % size] = nums[i] + size;
					else
						nums[(nums[i] - 1) % size] += size;
				}

			}
		}

		for (int i = 0; i < size; i++) {
			if (nums[i] <= size)
			{
				result = i + 1;
				break;
			}

		}

		return result;
	}
};


void Test_41_FirstMissingPositive() {

	int res1 = FirstMissingPositive().doit(vector<int>{1, 2, 0});

	int res2 = FirstMissingPositive().doit(vector<int>{3, 4, -1, 1});

	int res3 = FirstMissingPositive().doit(vector<int>{7, 8, 9, 11, 12});

	int res4 = FirstMissingPositive().doit(vector<int>{-10, -1, -1000, 1});

	int res5 = FirstMissingPositive().doit(vector<int>{1, 1});
}
