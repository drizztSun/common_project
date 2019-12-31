
#include <stdlib.h>
#include <vector>
#include <set>

using namespace std;

class MedianSlidingWindow {
public:
	vector<double> doit(vector<int>& nums, int k) {

		vector<double> medians;
		multiset<int> window(nums.begin(), nums.begin() + k);
		auto mid = next(window.begin(), k / 2);

		for (auto i = k; i <= nums.size(); i++) {
			medians.push_back( (double(*mid) + *prev(mid, 1 - k % 2)) / 2);
			if (i == nums.size())
				break;

			window.erase(window.lower_bound(nums[i - k]));
			window.insert(nums[i]);
			mid = next(window.begin(), k / 2);
		}

		return medians;
	}



	vector<double> doit1(vector<int>& nums, int k) {

		vector<double> medians;
		multiset<int> window(nums.begin(), nums.begin() + k);
		auto median = next(window.begin(), k/2);

		for (auto i = k; i <= nums.size(); i++) {

			medians.push_back( (double(*median) + *prev(median, 1 - k%2)) / 2);

			if (i == nums.size())
				break;

			window.insert(nums[i]);

			// Brilliant solution.
			// Just a simple note : "in C++11, newly inserted elements follow their equivalents
			// already in the container."
			// Thus, when nums[i] == *mid, we do not need to decrease mid, since nums[i] will inserted after mid.

			// c++11 same value will be inserted after existing ones
			// mid always points to the leftmost one of them
		
			// StefanPochmann 21814  Jan 11, 2017, 6:14 PMLink CopiedShare
			//	@singku Like I said, I just keep it pointing to “index” k / 2. So when I insert something before it(i.e., something smaller),
			//	my pointer then points at “index” k / 2 + 1 and I’ll have to subtract 1 to fix that.Similar for erasing.
			//	And no, there won’t be an error, because I increase the iterator before erasing, which avoids erasing the element my iterator points to.
			if (nums[i] < *median)
				median--;

			if (nums[i - k] <= *median)
				median++;

			window.erase(window.lower_bound(nums[i - k]));
		}
        return medians;
	} 


	vector<double> doit2(vector<int>& nums, int k) {

		int size = nums.size(), median_pos = k - k / 2 - 1;
		vector<double> res(size - k + 1);
		multiset<int> s(nums.begin(), nums.begin() + k);
		auto it = next(s.begin(), median_pos);

		for (auto i = k; i <= size; ++i)
		{
			res[i - k] = ((double)*it + (k % 2 != 0 ? *it : *next(it))) / 2;
			if (i < size)
			{
				// magic numbers (instead of enum) for brevity. INT_MAX means to retrace the iterator from the beginning.
				int repos_it = INT_MAX;
				if (k > 2)
				{
					// if inserted or removed item equals to the current median, we need to retrace.
					// we do not know which exact element will be removed/inserted, and we cannot compare multiset iterators.
					// otherwise, we can keep or increment/decrement the current median iterator.
					if ((nums[i - k] < *it && nums[i] < *it) || (nums[i - k] > *it && nums[i] > *it)) repos_it = 0;
					else if (nums[i - k] < *it && nums[i] > *it) repos_it = 1; // advance forward.
					else if (nums[i - k] > *it && nums[i] < *it) repos_it = -1; // advance backward.
				}
				s.insert(nums[i]);
				s.erase(s.find(nums[i - k]));

				if (repos_it == INT_MAX) it = next(s.begin(), median_pos);
				else if (repos_it == 1) ++it;
				else if (repos_it == -1) --it;
			}
		}
		return res;
	}
};



void Test_480_SildingWIndowMedian() {

	MedianSlidingWindow A;
	vector<int> nums{ 1,3,-1,-3,5,3,6,7 };

	auto res = A.doit(nums, 3);


	nums = { 2147483647, 2147483647 };
	res = A.doit(nums, 2);

	nums = { 5, 5, 8, 1, 4, 7, 1, 3, 8, 4 };
	res = A.doit(nums, 8);

	return;

}
