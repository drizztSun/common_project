/*
# leetcode 330. Patching Array

# Given a sorted positive integer array nums and an integer n, add / patch elements to the
# array such that any number in range[1, n] inclusive can be formed by the sum of some elements in the array.
# Return the minimum number of patches required.

# Example 1:
# nums = [1, 3], n = 6
# Return 1.

# Combinations of nums are[1], [3], [1, 3], which form possible sums of : 1, 3, 4.
# Now if we add / patch 2 to nums, the combinations are : [1], [2], [3], [1, 3], [2, 3], [1, 2, 3].
# Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range[1, 6].
# So we only need 1 patch.

# Example 2:
# nums = [1, 5, 10], n = 20
# Return 2.
# The two patches can be[2, 4].

# Example 3:
# nums = [1, 2, 2], n = 5
# Return 0.


class minPatches(object) :

	# Explanation

	# Let miss be the smallest sum in[0, n] that we might be missing.Meaning we already know we can build all sums in[0, miss).
	# Then if we have a number num <= miss in the given array, we can add it to those smaller sums to build all sums in[0, miss + num).
	# If we don’t, then we must add such a number to the array, and it’s best to add miss itself, to maximize the reach.

	# Example: Let’s say the input is nums = [1, 2, 4, 13, 43] and n = 100. We need to ensure that all sums in the range[1, 100] are possible.

	# Using the given numbers 1, 2 and 4, we can already build all sums from 0 to 7, i.e., the range[0, 8).
	# But we can’t build the sum 8, and the next given number(13) is too large.So we insert 8 into the array.
	# Then we can build all sums in[0, 16).

	# Do we need to insert 16 into the array ? No!We can already build the sum 3, and adding the given 13 gives us sum 16.
	# We can also add the 13 to the other sums, extending our range to[0, 29).

	# And so on.The given 43 is too large to help with sum 29, so we must insert 29 into our array.
	# This extends our range to[0, 58).But then the 43 becomes useful and expands our range to[0, 101).
	# At which point we’re done.


*/

#include <stdlib.h>
#include <vector>

using namespace std;

class MinPatches {


public:

	int doit(vector<int>& nums, int n) {

		long long maxV = 0, nextMax = 0;
		int i = 0;
		int cnt = 0;

		while (maxV < n) {

			nextMax = maxV + 1;

			if (i < nums.size() && nextMax >= nums[i]) {
				maxV += nums[i];
				i++;
			}
			else {
				maxV += nextMax;
				cnt++;
			}
		}
		return cnt;
	}

	int doit1(std::vector<int>& nums, int n) {

		int cnt = 0, i = 0;
		long long maxNum = 0;

		while (maxNum<n) {
		
			if (i<nums.size() && nums[i] <= maxNum + 1)
				maxNum += nums[i++];
			
			else {
				maxNum += maxNum + 1; 
				cnt++;
			}
		}
		return cnt;
	}
};

/*

show the algorithm with an example,

let nums=[1 2 5 6 20], n = 50.

Initial value: with 0 nums, we can only get 0 maximumly.

Then we need to get 1, since nums[0]=1, then we can get 1 using [1]. now the maximum number we can get is 1. (actually, we can get all number no greater than the maximum number)

number used [1], number added []
can achieve 1~1
Then we need to get 2 (maximum number +1). Since nums[1]=2, we can get 2. Now we can get all number between 1 ~ 3 (3=previous maximum value + the new number 2). and 3 is current maximum number we can get.

number used [1 2], number added []
can achieve 1~3
Then we need to get 4 (3+1). Since nums[2]=5>4; we need to add a new number to get 4. The optimal solution is to add 4 directly. In this case, we could achieve maximumly 7, using [1,2,4].

number used [1 2], number added [4]
can achieve 1~7
Then we need to get 8 (7+1). Since nums[2]=5<8, we can first try to use 5. Now the maximum number we can get is 7+5=12. Since 12>8, we successfully get 8.

number used [1 2 5], number added [4]
can achieve 1~12
Then we need to get 13 (12+1), Since nums[3]=6<13, we can first try to use 6. Now the maximum number we can get is 12+6=18. Since 18>13, we successfully get 13.

number used [1 2 5 6], number added [4]
can achieve 1~18
Then we need to get 19 (18+1), Since nums[4]=20>19, we need to add a new number to get 19. The optimal solution is to add 19 directly. In this case, we could achieve maximumly 37.

number used [1 2 5 6], number added [4 19]
can achieve 1~37
Then we need to get 38(37+1), Since nums[4]=20<38, we can first try to use 20. Now the maximum number we can get is 37+20=57. Since 57>38, we successfully get 38.

number used [1 2 5 6 20], number added [4 19]
can achieve 1~57
Since 57>n=50, we can all number no greater than 50.

The extra number we added are 4 and 19, so we return 2.

The code is given as follows

*/

void Test_330_PatchingArray() {

	MinPatches a;

	std::vector<int> input = { 1, 3 };
	
	int res = 0;
	
	res = a.doit(input, 6);

	input = {1, 5, 10};

	res = a.doit(input, 20);

	input = { 1, 2, 2 };
	
	res = a.doit(input, 5);

	input = { 1, 2, 31, 33 };

	res = a.doit(input, 2147483647);

}