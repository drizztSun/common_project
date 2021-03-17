/*
1590. Make Sum Divisible by P

Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.

Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.

A subarray is defined as a contiguous block of elements in the array.

 

Example 1:

Input: nums = [3,1,4,2], p = 6
Output: 1
Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.
Example 2:

Input: nums = [6,3,5,2], p = 9
Output: 2
Explanation: We cannot remove a single element to get a sum divisible by 9. The best way is to remove the subarray [5,2], leaving us with [6,3] with sum 9.
Example 3:

Input: nums = [1,2,3], p = 3
Output: 0
Explanation: Here the sum is 6. which is already divisible by 3. Thus we do not need to remove anything.
Example 4:

Input: nums = [1,2,3], p = 7
Output: -1
Explanation: There is no way to remove a subarray in order to get a sum divisible by 7.
Example 5:

Input: nums = [1000000000,1000000000,1000000000], p = 3
Output: 0
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= p <= 10^9


*/
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <numeric>

using std::unordered_map;
using std::vector;

class MakeSumDivisible {

    /*
        1590.Make-Sum-Divisible-by-P
        假设整个数组的和除以P的余数是r0. 题目要求subarray的剩余数字和除以P于0，那么就意味着这个subarray sum除以P的余数就是r0. 于是本题就转化成了求最短的subarray，满足和是r0.

        假设我们探索这样的subarray，令其右边界是j，那么左边界i可以取在哪里呢？我们可以利用前缀和的思想。如果presum[j]%P==r，那么我们必然要求presum[i]%P==r-r0（当然如果r-r0<0，那么我们就要补上一个周期变成r-r0+P）.
        所以我们转化为了求与j最接近的索引i，满足presum[i]%P==r-r0。 显然，我们在遍历之前的presum的时候，可以每次都求一下它除以P的余数，然后存下余数->索引的映射关系。此时，我们就可以直接调用Map[r-r0]得到该余数对应的、最近的presum的索引值。

        本题要注意，计算totalSum和preSum的过程中，都有可能会溢出。但事实上，所有的操作都和取余有关，所以我们只需要每一步求和都取余就行了。
    */
    int minSubarray(vector<int>& nums, int p) 
    {
        using ll = long long;

        int n = nums.size();
        unordered_map<int,int>Map;
        Map[0] = -1;

        ll sum = 0;
        for (auto a: nums)
            sum = (sum+a)%p;
        ll r0 = sum % p;
        if (r0==0) return 0;
        
        ll presum = 0;
        int ret = INT_MAX;
        
        for (int i=0; i<n; i++)
        {
            presum += nums[i];
            presum %= p;
            ll r = presum % p;
            ll diff = (r+p-r0) % p;            
            
            if (Map.find(diff)!=Map.end())
                ret = std::min(ret, i-Map[diff]);
            Map[r] = i;
        }
        
        if (ret>=n)
            return -1;
        else 
            return ret;
    }


public:

    /*
        Intuition
        Calculate the need = sum(A) % p.
        Then one pass, record the prefix sum in a hashmap.


        Explanation
        Then the question become:
        Find the shortest array with sum % p = need.

        last[remainder] = index records the last index that
        (A[0] + A[1] + .. + A[i]) % p = remainder


        Complexity
        Time O(N)
        Space O(N)
    */
    int doit_(vector<int>& A, int p) {

        int n = A.size(), res = n, need = 0, cur = 0;
        for (auto a : A)
            need = (need + a) % p;

        unordered_map<int, int> last = {{0, -1}};
        for (int i = 0; i < n; ++i) {
            cur = (cur + A[i]) % p;
            last[cur] = i;
            int want = (cur - need + p) % p;
            if (last.count(want))
                res = std::min(res, i - last[want]);
        }
        
        return res < n ? res : -1;
    }
    int doit_1(vector<int>& nums, int p) {
        
        long long total = std::accumulate(begin(nums), end(nums), 0LL);
        if (total % p == 0) return 0;
        if (total / p < 1) return -1;
        
        int ans = INT_MAX;
        int target = total % p;
        unordered_map<int, int> lastpos{{0, -1}};
        int presum = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            
            presum = (presum + nums[i]) % p;
            int t = (presum - target + p) % p;
            if (lastpos.count(t) > 0) {
                ans = std::min(ans, i - lastpos[t]);
            }
            
            lastpos[presum] = i;
        }
        
        return ans >= nums.size() ? -1 : ans;
    }
};