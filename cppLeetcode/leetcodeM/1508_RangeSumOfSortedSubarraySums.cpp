/*
1508. Range Sum of Sorted Subarray Sums


Given the array nums consisting of n positive integers. You computed the sum of all non-empty continous subarrays from the array and then sort them in non-decreasing order, creating a new array of n * (n + 1) / 2 numbers.

Return the sum of the numbers from index left to index right (indexed from 1), inclusive, in the new array. Since the answer can be a huge number return it modulo 10^9 + 7.

 

Example 1:

Input: nums = [1,2,3,4], n = 4, left = 1, right = 5
Output: 13 
Explanation: All subarray sums are 1, 3, 6, 10, 2, 5, 9, 3, 7, 4. After sorting them in non-decreasing order we have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10]. The sum of the numbers from index le = 1 to ri = 5 is 1 + 2 + 3 + 3 + 4 = 13. 
Example 2:

Input: nums = [1,2,3,4], n = 4, left = 3, right = 4
Output: 6
Explanation: The given array is the same as example 1. We have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10]. The sum of the numbers from index le = 3 to ri = 4 is 3 + 3 = 6.
Example 3:

Input: nums = [1,2,3,4], n = 4, left = 1, right = 10
Output: 50
 

Constraints:

1 <= nums.length <= 10^3
nums.length == n
1 <= nums[i] <= 100
1 <= left <= right <= n * (n + 1) / 2


*/
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using std::priority_queue;
using std::vector;

class RangeSumsSortedSubarray {

    typedef long long ll;

    /*
        1508.Range-Sum-of-Sorted-Subarray-Sums
        暴力解法是将所有的subarray sum都计算出来。因此时间复杂度是o(N^2)。

        如果当left和right的区间范围比较窄时，二分搜值的效率更高。我们设计int kthSum(int k)表示第k大的subarray sum。
        方法是：我们猜测某个sum值，检查nums数组里有多少个smaller or equal to sum的subarray。如果个数小于k，那么sum就要往大猜（即left=mid+1）；反之如果大于等于k，那么sum可能需要往小猜（即right=mid）。

        int kthSum(int k)这个函数可以用快慢指针来实现，时间复杂度是o(N).

        所以总体的时间复杂度是(r-l)*n*log(Sum).

        本题还可以有时间复杂度更低的n*log(Sum)的解法，思想是：假想所有的subarray sum排序的话，令totalSum2为前right个subarray sum的sum，totalSum1前left-1个subarray sum的sum。答案就是totalSum2-totalSum1.
        但是写起来比较复杂。主要原因是：可能有重复的subarray sum都与第left个subarray sum的数值相同。同理，第right个subarray sum两边也会有若干个相同的值。
    */

public:
    int doit_binary_search(vector<int>& nums, int n, int left, int right) 
    {
        // not good way
        int totalSum;
        totalSum = accumulate(nums.begin(), nums.end(), 0);
        int ret = 0;
        int M = 1e9+7;

        auto smallerOrEqual = [&](int s)
        {
            int j = 0;
            int count = 0;
            int sum  = 0;
            for (int i=0; i<nums.size(); i++)
            {            
                while (j<nums.size() && sum+nums[j]<=s)
                {
                    sum+=nums[j];
                    j++;
                }                
                count += j-i;
                sum -= nums[i];
            }
            return count;
        };

        auto kthSum = [&](int k)
        {
            int left = 1, right = totalSum;
            while (left<right)
            {
                int mid = left+(right-left)/2;
                if (smallerOrEqual(mid) < k)  // how many ranges whose sum is smaller or equal to mid
                    left = mid+1;
                else
                    right = mid;
            }
            return left;
        };

        for (int k = left; k <= right; k++)
            ret = (ret + kthSum(k))%M;
        
        return ret;
    }


public:

    int doit_sort_quickselect(vector<int>& nums, int n, int left, int right) {

        vector<ll> sums;

        for (int i = 0; i < n; i++) {
            int tmp = 0;
            for (int j = i; j < n; j++) {
                tmp += nums[j];
                sums.push_back(tmp);
            }
        }

        std::nth_element(begin(sums), begin(sums) + right - 1, end(sums));
        std::nth_element(begin(sums), begin(sums) + left - 1, begin(sums) + right);
        
        
        auto it = begin(sums) + left - 1, end = begin(sums) + right;
        int res = 0, hmod = 1e9 + 7;
        while (it != end) {
            res = (res + *it) % hmod;
            it++;
        }

        return res;
    }
    
    int doit_heap(vector<int>& nums, int n, int left, int right) {
        // Use long long to avoid overflow
        priority_queue<ll, vector<ll>, std::greater<ll>> heap;
        ll res = 0;
        vector<ll> sum(n + 1, 0);
        
        // Create array such that sum[i] is the sum from 0th to ith element in nums
        for (int i = 1; i <= n; ++i)
        {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
        
        // Push each number into the heap, it takes O(nlog(n))
        // where n = (size of nums array) ^ 2
        for (int i = 0; i < n; ++i)
        {
            for (int j = i; j < n; ++j)
            {
                ll subSum = sum[j + 1] - sum[i];
                heap.push(subSum);
            }
        }
        
        // calculate the sum from left to right
        int popped = 0;
        while (popped < left - 1)
        {
            heap.pop();
            ++popped;
        }
        
        while (popped < right)
        {
            res += heap.top();
            heap.pop();
            ++popped;
        }
        
        return res % (ll)(1e9 + 7);
    }
};