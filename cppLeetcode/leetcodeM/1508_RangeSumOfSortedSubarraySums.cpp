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

using std::priority_queue;
using std::vector;

#define ll long long

class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
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