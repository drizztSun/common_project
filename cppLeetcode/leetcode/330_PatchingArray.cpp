/*

330. Patching Array


Given a sorted integer array nums and an integer n, add/patch elements to the array such that any number in the range [1, n] inclusive can be formed by the sum of some elements in the array.

Return the minimum number of patches required.

 

Example 1:

Input: nums = [1,3], n = 6
Output: 1
Explanation:
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.
Example 2:

Input: nums = [1,5,10], n = 20
Output: 2
Explanation: The two patches can be [2, 4].
Example 3:

Input: nums = [1,2,2], n = 5
Output: 0
 

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 10^4
nums is sorted in ascending order.
1 <= n <= 2^31 - 1

*/

#include <vector>

using std::vector;


class MinPatches {

	/*
		330.Patching-Array
		假设miss是当前无法通过nums[0]~nums[i-1]这i个数通过题述的加和规则得到的、最小的那个整数，那么我们考虑下一个nums[i]会带来什么影响？

		如果nums[i]>miss，说明它的加入对于我们试图得到miss没有任何帮助，因为nums[i]太大了；并且之后的nums元素更不会有帮助，只会更大。所以miss只能是我们必须人为补充的一个数，即我们手工补上miss。
		这时下一个无法得到的整数是什么呢？那就是miss*2.因为miss加入前，1~miss-1我们都可以得到，所以miss加入后最大能得到2*miss-1.

		如果nums[i]<=miss，说明它的加入可以将miss提升至miss+nums[i].因为nums[i]加入前，1~miss-1我们都可以得到，所以miss加入后最大能得到miss-1+nums[i].

		如此循环重复上述的过程，不断提升miss，直至miss>n. 注意这个过程中nums可以提前用完。

		另外，值得注意的是，miss的初始值是1，而不是0. 因为没有任何nums提供时，我们首先试图要填补的就是1.
	*/
	int minPatches(vector<int>& nums, int n) 
    {
        int count=0;
        long miss=1;
        int i=0;
        
        while (miss<=n)
        {
            if (i>=nums.size() || miss<nums[i])
            {
                count++;
                miss+=miss;
            }
            else
            {
                miss+=nums[i];
                i++;
            }
        }
        
        return count;
    }

public:

	int doit_greedy(vector<int>& nums, int n) {

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

	int doit_greedy(std::vector<int>& nums, int n) {

		int cnt = 0, i = 0;
		long long maxNum = 0;

		while (maxNum<n) {
			
			// maxNum is maximum value could be reach.
			if (i<nums.size() && nums[i] <= maxNum + 1)
				// nums[i] can help to get maxNum, and max it could each is nums[i] + maxNum
				maxNum += nums[i++];
			else {
				// more can reach is maxNUm, so maxNUm + 1 has to filled.
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