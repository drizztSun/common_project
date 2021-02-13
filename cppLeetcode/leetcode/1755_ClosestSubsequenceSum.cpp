/*
1755. Closest Subsequence Sum

You are given an integer array nums and an integer goal.

You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal. That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).

Return the minimum possible value of abs(sum - goal).

Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.

 

Example 1:

Input: nums = [5,-7,3,5], goal = 6
Output: 0
Explanation: Choose the whole array as a subsequence, with a sum of 6.
This is equal to the goal, so the absolute difference is 0.
Example 2:

Input: nums = [7,-9,15,-2], goal = -5
Output: 1
Explanation: Choose the subsequence [7,-9,-2], with a sum of -4.
The absolute difference is abs(-4 - (-5)) = abs(1) = 1, which is the minimum.
Example 3:

Input: nums = [1,2,3], goal = -7
Output: 7
 

Constraints:

1 <= nums.length <= 40
-10^7 <= nums[i] <= 10^7
-10^9 <= goal <= 10^9

*/
#include <vector>

using std::vector;

class MinAbsDifference {

public:

    /*
        1755.Closest-Subsequence-Sum
        这道题的数据范围限定了解题方法。

        如果nums的元素不超过20个，那么我们可以穷举所有的subset sum，最多有2^20 = 1e6，时间复杂度是可以接受的。我们遍历一下这些subset，找到最接近goal的那个即可。

        如果nums的元素很多，但是值的范围很小，比如说限定了都是正数、所有的和不超过1000之类的，那么就可以当做动态规划来解。每处理一个新元素x，我们遍历所有subset sum的可能，更新dp[sum] = dp[sum-x].

        对于本题而言，以上两种方法都不适用。对于有经验的同学而言，nums的元素个数是40，提示了一种非常巧妙的解法：就是将nums平均拆成两个数组nums1和nums2来处理。
        对于每个数组，我们分别可以穷举所有的subset sum，时间复杂度是o(2^N/2)，然后各自排序得到sum1和sum2。然后对于sum1的每个元素x而言，我们要在sum2里面找到最接近goal-x的那个。
        反之对于sum2的每个元素x而言，我们要在sum1里面找到最接近goal-x的那个。最后找到全局最接近的abs diff即可。

        在上面的解法中，如果先求得所有的subset sum，然后排序，将会使得时间复杂度达到o(MlogM)，其中M=2^N/2. 有一种方法可以直接用o(2^N/2)得到有序的subset sum。
        假设nums的前i-1个元素已经得到了有序的subset sum的集合{a_k},那么加上第i个元素之后的subset sum的集合就是{a_k}和{a_k+nums[i]}的并集。我们发现这两个集合是各自有序的，这样我们可以用归并排序的方法将两者合并成一个更大的有序集合。
    
        No, this problem is NP-complete. It's basically https://en.wikipedia.org/wiki/Subset_sum_problem
        So there is a DP approach which has the complexity of O(n * goal), but goal can be up to 10^9, so it's too slow.
        Given n < 40 and goal < 10^9 the only possible exact approach is an optimised bruteforce (e.g. using meet in the middle technique).

        // vector<int> getSubSetsSum(vector<int>&nums)
        // {
        //     vector<int> sums;
        //     int m = nums.size();
        //     for (int state=0; state<(1<<m); state++)
        //     {
        //         int sum = 0;
        //         for (int i=0; i<32; i++)
        //         {
        //             if ((state>>i)&1)
        //                 sum += nums[i];
        //         }
        //         sums.push_back(sum);
        //     }
        //     sort(sums.begin(), sums.end());
        //     return sums;
        // }
    */
    int doit_brute_force(vector<int>& nums, int goal) 
    {
        int ret = 0;

        int m = nums.size()/2;
        int n = nums.size() - m;
        vector<int>nums1(nums.begin(), nums.begin() + m);
        vector<int>nums2(nums.begin() + m, nums.end());

        auto getSubSetsSum = [](vector<int>&nums) {

            vector<int> sums({0});

            for (int x: nums)
            {
                vector<int>temp;
                int i=0, j=0, n = sums.size();
                while (i<n && j<n)
                {
                    if (sums[i]+x < sums[j])
                    {
                        temp.push_back(sums[i]+x);
                        i++;
                    }
                    else
                    {
                        temp.push_back(sums[j]);
                        j++;
                    }
                }
                while (i<n)
                {
                    temp.push_back(sums[i]+x);
                    i++;
                }
                while (j<n)
                {
                    temp.push_back(sums[j]);
                    j++;
                }
                sums = temp;
            }
            return sums;
        };

        vector<int> a = getSubSetsSum(nums1);
        vector<int> b = getSubSetsSum(nums2);

        auto findAns = [&](vector<int>&a, vector<int>&b, int goal) {
            for (auto x: a)
            {
                // first bigger than goal
                auto iter = lower_bound(b.begin(), b.end(), goal-x);
                if (iter!=b.end())
                    ret = std::min(ret, abs(goal-x - *iter));

                // last smaller than goal
                if (iter!=b.begin())
                    ret = std::min(ret, abs(goal-x - *prev(iter)));
            }
        };

        findAns(a,b,goal);
        findAns(b,a,goal);
        return ret;
    }

    int doit_brute_force_1(vector<int>& nums, int goal) {
        int n = nums.size();
        if (n == 1) return abs(nums[0]-goal);

        vector<int> half1(1<<20);
        vector<int> half2(1<<20);
        vector<int> temp(1<<20);
        
        int n1 = n/2 + (n%2);
        int n2 = n/2;

        auto get = [&](vector<int> &half, vector<int>& nums, int n, int offset) {

            half[0] = 0;
            int p = 1;
            
            int a, b, x, y, pt;
            for (int i = 0; i < n; ++i) {
                a = b = pt = 0;
                while (a < p && b < p) {
                    x = half[a];
                    y = half[b] + nums[i+offset];
                    if (x < y) {
                        temp[pt++] = x;
                        ++a;
                    } else if (y < x) {
                        temp[pt++] = y;
                        ++b;
                    } else {
                        ++a; // skip one
                    }
                }
                while (a < p) {
                    temp[pt++] = half[a];
                    ++a;
                }
                while (b < p) {
                    temp[pt++] = half[b] + nums[i+offset];
                    ++b;
                }
                temp.swap(half);
                p = pt;
            }
            
            return p;
        };

        int half1size = get(half1, nums, n1, 0);
        int half2size = get(half2, nums, n2, n1);
        
        int j = half2size-1;

        int best = INT_MAX;
        for (int i = 0; i < half1size; ++i) {
            while (j > 0 && half1[i]+half2[j] > goal && abs(half1[i]+half2[j-1] - goal) <= abs(half1[i]+half2[j] - goal)) --j;

            best = std::min(best, abs(half1[i]+half2[j] - goal));
            if (best == 0) return 0;
        }
        return best;
    }
};
