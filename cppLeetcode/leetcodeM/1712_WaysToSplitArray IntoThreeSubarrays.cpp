/*

1712. Ways to Split Array Into Three Subarrays

A split of an integer array is good if:

The array is split into three non-empty contiguous subarrays - named left, mid, right respectively from left to right.
The sum of the elements in left is less than or equal to the sum of the elements in mid, and the sum of the elements in mid is less than or equal to the sum of the elements in right.
Given nums, an array of non-negative integers, return the number of good ways to split nums. As the number may be too large, return it modulo 109 + 7.



Example 1:

Input: nums = [1,1,1]
Output: 1
Explanation: The only good way to split nums is [1] [1] [1].
Example 2:

Input: nums = [1,2,2,2,5,0]
Output: 3
Explanation: There are three good ways of splitting nums:
[1] [2] [2,2,5,0]
[1] [2,2] [2,5,0]
[1,2] [2,2] [5,0]
Example 3:

Input: nums = [3,2,1]
Output: 0
Explanation: There is no good way to split nums.


Constraints:

3 <= nums.length <= 10^5
0 <= nums[i] <= 10^4



*/
#include <vector>
#include <algorithm>

using std::vector;


class WaysToSplit{

public:

    /*
        1712.Ways-to-Split-Array-Into-Three-Subarrays
        我们遍历第一个subarray的位置，假设截止到i。那么第二个subarray的右端点必然有一个下限j，需要满足sum[i+1:j]恰好大于sum[0:i]。这样的j是可以用一个指针根据i单调地向右移动得到。

        确定了下限，那么接下来考虑第二个subarray的右端点最远可以到哪里？假设这个位置是k。k太远的话必然会挤占第三个subarray的元素和。所以k的极限需要满足sum[k+1:n-1]恰好大于sum[i+1:k]。对于区间和，我们必然会用前缀数组来实现，
        即presum[n-1]-presum[k] >= presum[k]-presum[i]，变化一下得到我们要求最大的k，使得presum[k] <= 0.5 *(presum[n-1]+presum[i])

        我们知道前缀数组presum是个单调序列。所以我们可以用二分法确定这个位置k，也就是用upper_bound找到第一个大于0.5 *(presum[n-1]+presum[i])的位置，再往前移动一个，就是最大的、小于等于
        0.5 *(presum[n-1]+presum[i])的位置。确定过了这个k，那么从j到k的所有位置，都可以是第二个区间的右端点，所以答案加上 j-i+1.

        特别注意的是，以上的二分法中可能得到的k是n-1. 这样的话，第三个区间的大小变成了0，这个是不可以的。所以如果得到k==n-1的话，我们需要把k往前再移动一位。


        [x x x] [x x x x ]  x x x } [x x x]
            i         j ------ k       n-1 
        
        sum[i+1: j] >= sum[0:i]
        ret += k - j + 1

        sum[i+1:k] <= sum[k+1:n-1]

        presum[k] - presum[i] <= presum[n-1] - presum[k]
        presum[k] <= 0.5 * (presum[i] + presum[n-1])
    */
    int doit_binary_search(vector<int>& nums) {
        
        int N = nums.size();
        vector<long long> presum(N, 0);
        for (int i = 0; i < N; i++)
            presum[i] = nums[i] + (i > 0 ? presum[i-1] : 0);  

        long long ans = 0;
        long long hmod = 1e9 + 7;
        
        for (int i = 0, j = 0; i < N; i++) {

            while (j <= i || j < N && presum[j] - presum[i] < presum[i]) j++;

            if (j == N) break;

            auto it = std::upper_bound(begin(presum), end(presum), 0.5 * (presum[N-1] + presum[i]));
            int k = it - begin(presum) -1;

            if (k == N-1) k--; // Third one needs room

            if (k < j) continue;

            ans = (ans + k - j + 1) % hmod;
        }

        return ans;
    }

    int doit_binary_search_best(vector<int>& nums) {
        const int MOD = 1000000007;
        int n = nums.size();
        vector<int> presum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            presum[i + 1] = presum[i] + nums[i];
        }

        long result = 0;
        for (int i = 0; i < n - 2; i++) {
            // nums[0],...,nums[i] | nums[i+1], nums[i+2], ...
            int leftSum = presum[i + 1];
            int remain = presum[n] - leftSum;
            if (remain < leftSum * 2) {
                break;
            }
            // search first & last in presum[i+2],..., presum[n-1]
            int first = (int)(std::lower_bound(presum.begin() + i + 2, presum.end() - 1, leftSum * 2) - presum.begin());

            // minus 1 since upper_bound finds the less one, not less or equal one
            int last = (int)(std::upper_bound(presum.begin() + i + 2, presum.end() - 1, leftSum + remain / 2) - presum.begin() - 1);

            result += std::max(last - first + 1, 0);
        }
        return result % MOD;
};