/*
 
 410. Split Array Largest Sum
 
 Given an array nums which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays.

 Write an algorithm to minimize the largest sum among these m subarrays.

  

 Example 1:

 Input: nums = [7,2,5,10,8], m = 2
 Output: 18
 Explanation:
 There are four ways to split nums into two subarrays.
 The best way is to split it into [7,2,5] and [10,8],
 where the largest sum among the two subarrays is only 18.
 Example 2:

 Input: nums = [1,2,3,4,5], m = 2
 Output: 9
 Example 3:

 Input: nums = [1,4,4], m = 3
 Output: 4
  

 Constraints:

 1 <= nums.length <= 1000
 0 <= nums[i] <= 106
 1 <= m <= min(50, nums.length)
 */
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

using std::vector;

class SplitArray {
    
public:

    /*
        410.Split-Array-Largest-Sum
        解法1: DP
        大多数的数组问题都可以用动态规划解决。

        设计dp[i][k]表示元素1~i分成k份的最佳方案，即最大子区段的最小可能值。

        如何设计转移方程呢？无非就是考虑dp[i][k]和这些前态的关系：dp[i-？][k], dp[i][k-？]。
        可以发现，dp[i][k]和dp[i-1][k-1]有直接关系。遍历所有将前j个元素（j最小就是k-1）分成k-1份的方案，加上最后一份（就是 sum[i]-sum[j]）的影响。

        所以转移方程是： dp[i][k]=min{j} ( max(dp[j][k-1],sum[i]-sum[j]) )

        注意的细节是，sum[i]的计算可能会溢出。sum[i]-sum[j]可以转化为 dp[i][1]-dp[j][1].

        解法2: Binary Search
        进行k的二分搜索，k就是代表nums分成m份后最大自区段的和。 分析：k的最小值是nums里的最大值；k的最大值是数组元素的总和；对于任一个mid，另写函数用贪心法判断是否满足要求。满足要求的话，就继续缩小k来尝试。

        如何判断k是否可行呢？两个判据：

        如果任何nums[i]>k，则不可行。
        尽可能地合并元素，使得任何子区段的和都不超过k，并在遍历的过程中记录这些子区段的数目，超过m的话就说明不可行。
        此题和 1011. Capacity To Ship Packages Within D Days 几乎一模一样。
    
    */
    int doit_binary_search(vector<int>& nums, int m) 
    {
        long left = 0, right = INT_MAX;

        std::function<bool(int, long)> checkOK = [&](int m, long val) {

            int count = 0;
            for (int i=0; i<nums.size(); i++)
            {
                if (nums[i] > val) return false;
                
                int j = i;
                long sum = 0;
                while (j<nums.size() && sum+(long)nums[j]<=val)
                {
                    sum += (long)nums[j];
                    j++;
                }
                count++;
                i = j-1;
            }
            
            return count <= m;
        };

        
        while (left < right) {
            
            int mid = left + (right - left) / 2;
            if (checkOK(m, mid))
                right = mid;
            else
                left = mid + 1;
        }
        
        return left;
    }

    int doit_dp_1(vector<int>& nums, int m) {

        int N = nums.size();
        vector<vector<long>> dp(N+1,vector<long>(m+1, INT_MAX));
        nums.insert(nums.begin(),0);
        
        dp[0][0] = 0;
        
        for (int i = 1; i <= N; i++)
            for (int k=1; k <= std::min(m,i); k++)
            {
                long sum = 0;
                for (int j=i; j>=k; j--)
                {
                    sum += nums[j];
                    dp[i][k] = std::min(dp[i][k], std::max(dp[j-1][k-1], sum));
                }
            }
        
        return dp[N][m];
    }

    /*
     # The answer is between maximum value of input array numbers and sum of those numbers.
     # Use binary search to approach the correct answer.
     # We have l = max number of array; r = sum of all numbers in the array;
     # Every time we do mid = (l + r) / 2;
     # Use greedy to narrow down left and right boundaries in binary search.

     # 3.1 Cut the array from left.
     # 3.2 Try our best to make sure that the sum of numbers between each two cuts (inclusive) is large enough but still less than mid.
     # 3.3 We’ll end up with two results: either we can divide the array into more than m subarrays or we cannot.

     # If we can, it means that the mid value we pick is too small because we’ve already tried our best
     # to make sure each part holds as many non-negative numbers as we can but we still have numbers left.
     # So, it is impossible to cut the array into m parts and make sure each parts is no larger than mid. We should increase m. This leads to l = mid + 1;

     # If we can’t, it is either we successfully divide the array into m parts and the sum of each part is less than mid,
     # or we used up all numbers before we reach m.
     # Both of them mean that we should lower mid because we need to find the minimum one. This leads to r = mid - 1;
     
     **Complexity Analysis**

         Time complexity : O(n * log(sum of array)). The binary search costs O(log(sum of array)), where sum of array is the sum of elements in nums. For each computation of F(x), the time complexity is O(n)O(n)O(n) since we only need to go through the whole array.

         Space complexity : O(n)O(n)O(n). Same as the Brute Force approach. We only need the space to store the array.

     */
    
    int doit_binary_search_1(vector<int>& nums, int m) {
        
        /*
        int total = 0, maxv = 0;
        for (auto c : nums) {
            total += c;
            if (c > maxv) {
                maxv = c;
            }
        }*/

        int maxv = *std::max_element(begin(nums), end(nums));
        int total = std::accumulate(begin(nums), end(nums), 0);

        auto search = [](vector<int>& nums, int m, int target) {
            int cnt = 1, cur = 0;
            for (auto c : nums) {
                cur += c;
                if (cur > target) {
                    cur = c;
                    cnt++;
                    if (cnt > m)
                        return false;
                }
            }
            return true;
        };
    
        if (m == 1) return total;
        if (m == nums.size()) return maxv;

        int l = maxv, r = total;
        while (l <= r) {
            int mid = l + (r-l) / 2;
            if (search(nums, m, mid)) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    
        return l;
    }
    
    /*
     Approach #2 Dynamic Programming [Accepted]

     Intuition

     The problem satisfies the non-aftereffect property. We can try to use dynamic programming to solve it.

     The non-aftereffect property means, once the state of a certain stage is determined, it is not affected by the state in the future. In this problem, if we get the largest subarray sum for splitting nums[0..i] into j parts, this value will not be affected by how we split the remaining part of nums.

     To know more about non-aftereffect property, this link may be helpful : http://www.programering.com/a/MDOzUzMwATM.html

     Algorithm

     Let's define f[i][j] to be the minimum largest subarray sum for splitting nums[0..i] into j parts.

     Consider the jth subarray. We can split the array from a smaller index k to i to form it. Thus f[i][j] can be derived from max(f[k][j - 1], nums[k + 1] + ... + nums[i]). For all valid index k, f[i][j] should choose the minimum value of the above formula.

     The final answer should be f[n][m], where n is the size of the array.

     For corner situations, all the invalid f[i][j] should be assigned with INFINITY, and f[0][0] should be initialized with 0.
     */
    
    int doit_dp_1(vector<int>&nums, int m) {
        int n = nums.size();
        vector<vector<int>> f(n + 1, vector<int>(m + 1, INT_MAX));
        vector<int> sub(n + 1, 0);
        for (int i = 0; i < n; i++) {
            sub[i + 1] = sub[i] + nums[i];
        }

        f[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int k = 0; k < i; k++) {
                    f[i][j] = std::min(f[i][j], std::max(f[k][j - 1], sub[i] - sub[k]));
                }
            }
        }
        return f[n][m];
    }
};
