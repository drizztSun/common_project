/*
334. Increasing Triplet Subsequence


Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k].
If no such indices exists, return false.



Example 1:

Input: nums = [1,2,3,4,5]
Output: true
Explanation: Any triplet where i < j < k is valid.
Example 2:

Input: nums = [5,4,3,2,1]
Output: false
Explanation: No triplet exists.
Example 3:

Input: nums = [2,1,5,0,4,6]
Output: true
Explanation: The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.


Constraints:

1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1


Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space complexity?


Other LIC issue 340

*/
#include <vector>

using std::vector;



class IncreasingTriplet {

public:

    /*
        Approach 1: Linear Scan
        
        Intuition

        The idea is to keep track of the first two numbers in increasing order and find the last number which will be bigger than the first two numbers. 
        Here, the first and second smallest numbers can be updated with conditional checks while scanning nums.

        first_num = second_num = some very big number
        for n in nums:
            if n is smallest number:
                first_num = n
            else if n is second smallest number:
                second_num = n
            else n is bigger than both first_num and second_num:
                # We have found our triplet, return True

        # After loop has terminated
        # If we have reached this point, there is no increasing triplet, return False
        Let's take a look at two cases where nums is sorted:

        If nums is sorted in descending order, you will always end up in this first if block (and thus, repeatedly updating first_num). Finally, False will be returned after the loop has been terminated.
        If nums is sorted in ascending order, you will first update first_num as soon as you see the first number in nums and when you encounter another number in nums, you will update the second_nums since this new number would be bigger than the value stored in first_num. After these two variables have been populated, all you need to look for is another number which is bigger than first_num and second_num. As soon as you find that number, the first if and the second else if blocks will be skipped, and you will end up in the last else block and True will be returned immediately.
        This works not only for sorted cases described above but also for cases where the numbers are unsorted. First, find the smallest number and store it in first_num, and then find the second smallest number and store it in second_num. However, there is no guarantee that another number you encounter in nums will be greater than first_num and second_num. This new number can even be smaller than then first_num (in that case, you will have to update first_num with this new value) or second_num (in that case, you will have to update second_num with this new value). As long as you encounter those cases, you keep on updating your first_num and second_num. As soon as you encounter a number which is greater than both first_num and second_num, you have found your last number to complete the increasing triplet subsequence. At that point, you can immediately return True.

        However, there is an important logic that is quite important to grasp. Let's take nums = [10,20,3,2,1,1,2,0,4] for an example:

        Complexity Analysis

        Time complexity : O(N) where NN is the size of nums. We are updating first_num and second_num as we are scanning nums.

        Space complexity : O(1) since we are not consuming additional space other than variables for two numbers.
    
        It is like LIS, longest increasing sequence
    */

    bool doit_(vector<int>& nums) {

        int first = INT_MAX, second = INT_MAX;

        for (auto c : nums) {
            
            if (c <= first)
                first = c;
            else if (c <= second)
                second = c;
            else
                return true;
        }

        return false;
    }

    /*
        334.Increasing-Triplet-Subsequence
        
        解法1：
        从左往右，从右往左，各扫一遍数组，计算每个元素的LeftMin和RightMax。那么只要LeftMin[i]<nums[i]<RightMax[i]即可找到一对triplet

        这样的话，时间是o(3N),空间是o(2N)

        解法2：
        非常巧妙的思维，本题即是在这个数组里找到长度为3的increasing subsequence即可！

        用一个数组来记录当前的递增序列，长度达到3即可停下来。时间最差是nlog(3)，空间是o(3)。
    
    */

    bool doit_1(vector<int>& nums) 
    {
        int N = nums.size();
        if (N==0) return false;
        
        vector<int>LeftMin(N,0);
        LeftMin[0] = INT_MAX;
        for (int i=1; i<N; i++)
            LeftMin[i] = std::min(LeftMin[i-1],nums[i-1]);
        
        vector<int>RightMax(N,0);
        RightMax[N-1] = INT_MIN;
        for (int i=N-2; i>=0; i--)
            RightMax[i] = std::max(RightMax[i+1],nums[i+1]);
        
        for (int i=1; i<N-1; i++)
        {
            if (LeftMin[i]<nums[i] && RightMax[i]>nums[i])
                return true;
        }
        return false;
    }

    bool doit_2(vector<int>& nums) 
    {
        vector<int> q;
        for (auto x: nums)
        {
            if (q.empty() || q.back()<x)
                q.push_back(x);
            else
            {
                auto iter = lower_bound(q.begin(), q.end(), x);
                *iter = x;
            }
            if (q.size()==3)
                return true;
        }
        return false;
    }

}