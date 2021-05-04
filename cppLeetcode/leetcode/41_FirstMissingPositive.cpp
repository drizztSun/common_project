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

	/*
		041.First-Missing-Positive
		首先，将nums数组之前添加一个零元素。于是本题的一个思路是：如果尝试把正整数1~N尽可能地按照顺序放入nums[1]~nums[N]后，那么从头到尾再遍历一遍nums，找到的第一个nums[i]!=i的数，就是所求的结果。

		那么如何尝试one pass就把正整数1~N尽可能地按照顺序放入nums[1]~nums[N]呢？这就是经典的array indexing的算法。遍历所有元素的时候，发现如果nums[i]!=i时，说明当前的nums[i]这个数没有被放置在合适的位置，根据对应的规则，它应该被放在nums[nums[i]]这个位置。

		于是我们持续交换nums[i]和nums[nums[i]]。每一次交换的结果是：把nums[i]送到了它应该在的位置；同时i位置的元素又有了新的值，可以再次进行交换。如果这样的步骤持续到 nums[i]==i（说明第i个元素的位置已经得到满足了）或者nums[nums[i]]==nums[i]（说明第nums[i]个元素的位置也已经得到了满足），就不需要交换了。

		当把所有的i都遍历一遍之后，就完成了“力所能及”的排序，意思就是nums里面所有处于1~N之间的数，都已经在它规定的位置上了。如前所述，此时从头到尾再遍历一遍nums，找到的第一个nums[i]!=i的数，就是原先nums里面1~N之间所缺失的数。

		和本题非常相似的还有:

		287.Find the Duplicate Number
		442.Find-All-Duplicates-in-an-Array 
		448.Find-All-Numbers-Disappeared-in-an-Array 
		645.Set Mismatch，
		也用到了array indexing.
	*/
	int doit_greedy_indexing(vector<int>&& nums) {

        nums.insert(nums.begin(),0);
        for (int i=0; i<nums.size(); i++)
        {
            while (nums[i] != i && nums[i] < nums.size() && nums[i] !=nums [nums[i]])
                swap(nums[i], nums[nums[i]]);
        }
        
		for (int i=1; i<nums.size(); i++)
            if (nums[i]!=i) return i;     
        
        return nums.size();
	}


public:

	int doit_greedy(vector<int>&& nums) {

		for (int i = 0; i < nums.size(); i++) {
			while (nums[i] > 0 && nums[i] <= nums.size() && nums[i] != i+1 && nums[i] != nums[nums[i]-1]) {
				std::swap(nums[i], nums[nums[i]-1]);
			}
		}

		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] - 1 != i)
				return i+1;
		}

		return nums.size() == 0 ? 1 : nums.size() + 1;
	}

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