/*
1567. Maximum Length of Subarray With Positive Product


Given an array of integers nums, find the maximum length of a subarray where the product of all its elements is positive.

A subarray of an array is a consecutive sequence of zero or more values taken out of that array.

Return the maximum length of a subarray with positive product.

 

Example 1:

Input: nums = [1,-2,-3,4]
Output: 4
Explanation: The array nums already has a positive product of 24.
Example 2:

Input: nums = [0,1,-2,-3,-4]
Output: 3
Explanation: The longest subarray with positive product is [1,-2,-3] which has a product of 6.
Notice that we cannot include 0 in the subarray since that'll make the product 0 which is not positive.
Example 3:

Input: nums = [-1,-2,-3,0,1]
Output: 2
Explanation: The longest subarray with positive product is [-1,-2] or [-2,-3].
Example 4:

Input: nums = [-1,2]
Output: 1
Example 5:

Input: nums = [1,2,3,5,-6,4,0,10]
Output: 4
 

Constraints:

1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

*/


#include <vector>
using std::vector;

class MaximumLengthOfSubarry {

    /*
        1567.Maximum-Length-of-Subarray-With-Positive-Product
        首先，这个subarray里面不能含有0元素。因此我们会将整个数组分拆为若干个被0间隔的区域，每个区域单独处理。

        接下来在每一个区域里，我们想要找一段最长的subarray，使得里面包含的负数的个数必须是偶数（可以为0）。假设我们从区域的起点i开始遍历到j的位置，经过的负数有偶数个，那么[i:j]这个subarray就是符合条件的。
        反之，如果从起点i开始遍历到j的位置时，经过的负数有奇数个，那么我们必然会寻找第一次出现负数的位置（记做k），那么[k+1:j]这个subarray就是符合条件的。总之，如果以j为subarray的右边界，那么左边界只有两种情况：要么就是i，要么就是k+1，取决于到j为止时总共出现了多少次负数。

        因为根据j来确定左边界可以用o(1)时间完成，所以本题的时间复杂度是o(N).
    */
    int doit_greedy(vector<int>& nums) 
    {
        int ret = 0;

        for (int i=0; i<nums.size(); i++)
        {
            if (nums[i]==0) continue;
            int j = i;
            int count = 0;
            int firstNeg = -1;

            while (j<nums.size() && nums[j]!=0)
            {
                count += (nums[j]<0);
                if (count % 2 ==0)
                    ret = std::max(ret, j-i+1);
                else if (firstNeg!=-1)
                    ret = std::max(ret, j-firstNeg);

                if (firstNeg==-1 && nums[j]<0)
                    firstNeg = j;
                j++;
            }
            i = j;
        }
        return ret;
    }

public:

    int doit_greedy_slidingwindow_twopointer(vector<int>& nums) {
        
        int total = 1, res = 0;
        int pos = -1, neg = INT_MAX;
        
        for (int i = 0; i < nums.size(); i++) {
            
            if (nums[i] == 0) {
                total = 1;
                pos = i;
                neg = INT_MAX;
                continue;
            }
            
            total *= nums[i] > 0 ? 1 : -1;
            
            if (total < 0) {
                if (neg == INT_MAX) {
                    neg = i;
                }
                res = std::max(res, i - neg);
            } else {
                res = std::max(res, i - pos);
            }
        }
        
        return res;
    }
};