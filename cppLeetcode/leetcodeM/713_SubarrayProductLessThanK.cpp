/*
713. Subarray Product Less Than K

Your are given an array of positive integers nums.

Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.

Example 1:
Input: nums = [10, 5, 2, 6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
Note:

0 < nums.length <= 50000.
0 < nums[i] < 1000.
0 <= k < 10^6.

*/

#include <vector>

using std::vector;


class NumSubarrayProductLessThanK {

    /*
        713.Subarray-Product-Less-Than-K
        本题有很明显的滑窗的特征，所以基本思路是用双指针。保证一个乘积小于k的最大窗口，这个窗口内可以构成subarray的数目就是j-i+1;

        本题需要注意的一点是，当nums[i]>k时，右指针动不了，而左指针依然会顺移，所以可能会出现j<i的情况，此时只需要重置这两个指针即可：

        if (j<i)
        {
            j = i;
            product = 1;
        }
    */
    int numSubarrayProductLessThanK(vector<int>& nums, int k) 
    {
        if (k<=1) return 0;
        int j=0;
        int prod = 1;
        int count = 0;
        for (int i=0; i<nums.size(); i++)
        {            
            if (j<i)
            {
                j = i;
                prod = 1;
            }
            
            while (j<nums.size() && prod*nums[j]<k)
            {
                prod = prod*nums[j];
                j++;
            }
            count += j-i;
            prod = prod/nums[i];
        }
        return count;
    }


public:


    /*
        Approach #2: Sliding Window [Accepted]
        Intuition
        For each right, call opt(right) the smallest left so that the product of the subarray nums[left] * nums[left + 1] * ... * nums[right] is less than k. opt is a monotone increasing function, so we can use a sliding window.

        Algorithm
        Our loop invariant is that left is the smallest value so that the product in the window prod = nums[left] * nums[left + 1] * ... * nums[right] is less than k.
        For every right, we update left and prod to maintain this invariant. Then, the number of intervals with subarray product less than k and with right-most coordinate right, is right - left + 1. We'll count all of these for each value of right.
        
        Complexity Analysis
        Time Complexity: O(N), where NN is the length of nums. left can only be incremented at most N times.
        Space Complexity: O(1), the space used by prod, left, and ans.
    */
    int doit_slidingwindow(vector<int>& nums, int k) {
        
        if (k <= 1) return 0;
        
        int total = 1, cnt = 0;

        for (int i = 0, j = 0; i < nums.size(); i++) {

            total *= nums[i];

            while (total >= k) total /= nums[j++];

            cnt += i - j + 1;
        }

        return cnt;
    }
};
