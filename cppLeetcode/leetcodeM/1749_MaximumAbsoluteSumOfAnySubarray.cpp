/*
1749. Maximum Absolute Sum of Any Subarray


You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).

Return the maximum absolute sum of any (possibly empty) subarray of nums.

Note that abs(x) is defined as follows:

If x is a negative integer, then abs(x) = -x.
If x is a non-negative integer, then abs(x) = x.


Example 1:

Input: nums = [1,-3,2,3,-4]
Output: 5
Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.
Example 2:

Input: nums = [2,-5,1,-4,3,-2]
Output: 8
Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8) = 8.


Constraints:

1 <= nums.length <= 10^5
-104 <= nums[i] <= 10^4
*/

#include <vector>
using std::vector;

class MaximumAbsoluteSum {

    /*
    
        1749.Maximum-Absolute-Sum-of-Any-Subarray
        解法1
        最大的subarray sum的绝对值，肯定来自两个种可能：最大的正的subarray sum，或者最小的负的subarray sum，所以我们把这两个问题都解出来，取绝对值较大的那个就可以了。

        求max subarray sum是一个经典问题。我们令dp[i]表示截止到nums[i]的subarray的最大和（必须包括nums[i]本身），那么有dp[i]=max(dp[i-1],nums[i]). 全局的最优解就是所有dp[i]中的最大值。min subarray sum同理可得。

        解法2
        任何一个abs(sum[i:j])都可以写成两个前缀和之差abs(prefix[j]-prefix[i-1])的形式。显然最优解[i:j]就是对应全局最大前缀和prefix[j]、最小前缀和prefix[i-1]。特别注意，0也是前缀和。      
    */


public:
    
    int doit_(vector<int>& nums) 
    {
        int mx = 0, mn = 0;
        int ret = 0;
        for (int x: nums)
        {            
            mx = std::max(mx + x, x);
            mn = std::min(mn + x, x);
            ret = std::max(ret, abs(mx));
            ret = std::max(ret, abs(mn));
        }
        return ret;
    }

    int doit_(vector<int>& nums) 
    {
        int prefix_mx = 0, prefix_mn = 0;
        int prefix = 0;
        
        for (int x: nums)
        {
            prefix += x;
            prefix_mx = std::max(prefix_mx, prefix);
            prefix_mn = std::min(prefix_mn, prefix);            
        }

        return prefix_mx - prefix_mn;        
    }
};