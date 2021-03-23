/*
1799. Maximize Score After N Operations


You are given nums, an array of positive integers of size 2 * n. You must perform n operations on this array.

In the ith operation (1-indexed), you will:

    . Choose two elements, x and y.
    . Receive a score of i * gcd(x, y).
    . Remove x and y from nums.
Return the maximum score you can receive after performing n operations.

The function gcd(x, y) is the greatest common divisor of x and y.

 

Example 1:

Input: nums = [1,2]
Output: 1
Explanation: The optimal choice of operations is:
(1 * gcd(1, 2)) = 1
Example 2:

Input: nums = [3,4,6,8]
Output: 11
Explanation: The optimal choice of operations is:
(1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11
Example 3:

Input: nums = [1,2,3,4,5,6]
Output: 14
Explanation: The optimal choice of operations is:
(1 * gcd(1, 5)) + (2 * gcd(2, 4)) + (3 * gcd(3, 6)) = 1 + 4 + 9 = 14
 

Constraints:

    .1 <= n <= 7
    .nums.length == 2 * n
    .1 <= nums[i] <= 10^6

*/

#include <functional>
#include <vector>
#include <cmath>

using std::vector;

class MaximizeScoreAfterNOps {

public:
    
    /*
        Recursion with Memorization:

        State: numbers, k-th operation.
        Space complexity (states): O(n*(2^2n))
        Each state, we try all pairs: O((2n)^2)

        dp([1, 2, 3, 4, 5, 6], 1) = max(
            gcd(1, 2) + dp[3, 4, 5, 6], 2),
            gcd(1, 3) + dp[2, 4, 5, 6], 2)
            ... )

        dp([3, 6], 3) = max(3*gcd(3, 6) + dp([], 4)) = 9;



        dp(mask, i) := max score of numbers (represented by a binary mask) at the i-th operations.
        ans = dp(1, mask)
        base case: dp = 0 if mask == 0
        Transition: dp(mask, i) = max(dp(new_mask, i + 1) + i * gcd(nums[m], nums[n]))

    
        Time complexity: O(n^2 * 2^(2n)). if n == 7, so it is O(2*2*10^7)
        Space complexity: O(2^(2n))
    */
    int doit_dp_bitmask_topdown(vector<int>& nums) {
        const int l = nums.size();
        vector<int> cache(1 << l);

        std::function<int(int)> dp = [&](int mask) {      
            if (mask == 0) return 0;
            int& ans = cache[mask];

            if (ans > 0) return ans;
            const int k = (l - __builtin_popcount(mask)) / 2 + 1;
            
            for (int i = 0; i < l; ++i)
                for (int j = i + 1; j < l; ++j)

                if ((mask & (1 << i)) && (mask & (1 << j)))
                    ans = std::max(ans, k * std::gcd(nums[i], nums[j]) + dp(mask ^ (1 << i) ^ (1 << j)));
            
            return ans;
        };
        return dp((1 << l) - 1);
    }

    int doit_dp_bitmask_bottomup(vector<int>& nums) {

        const int l = nums.size();
        vector<int> dp(1 << l);    
        for (int mask = 0; mask < 1 << l; ++mask) {
            int c = __builtin_popcount(mask);
            if (c & 1) continue; // only do in pairs
            int k = c / 2 + 1;

            for (int i = 0; i < l; ++i)
                for (int j = i + 1; j < l; ++j)
            
                if ((mask & (1 << i)) + (mask & (1 << j)) == 0) {            
                    int new_mask = mask | (1 << i) | (1 << j);            
                    dp[new_mask] = std::max(dp[new_mask], k * gcd(nums[i], nums[j]) + dp[mask]);
                }
        }
        return dp[(1 << l) - 1];
    }
};