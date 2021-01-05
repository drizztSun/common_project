/*
494. Target Sum

You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. 
For each integer, you should choose one from + and - as its new symbol.

Find out how many ways to assign symbols to make sum of integers equal to target S.

Example 1:

Input: nums is [1, 1, 1, 1, 1], S is 3. 
Output: 5
Explanation: 

-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

There are 5 ways to assign symbols to make the sum of nums be target 3.
 

Constraints:

The length of the given array is positive and will not exceed 20.
The sum of elements in the given array will not exceed 1000.
Your output answer is guaranteed to be fitted in a 32-bit integer.

*/
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <numeric>

using std::vector;
using std::unordered_map;


class TargetSum {

public:


    int doit_dp_divide_conquer_best(vector<int>& nums, int target) {

        long total=0;
        for(auto &num:nums)
            total += num;
        
        if((total+target)%2==1 || total<target)
            return 0;
        /*
        Need to divide nums in 2 subsets (ss) such as
        sum(ss1) - sum(ss2) = target
        we know, sum(ss1) + sum(ss2) = total
        adding: 2*sum(ss1) = target+total
        sum(ss1) = (target+total)/2
        Problem turns to find no of ways having subset with sum(ss1)
        */
        long rows = nums.size(), cols = (total+target)/2+1;
        vector<long> curr(cols,0);
        curr[0] = 1;

        for(int num: nums) {
            for(int j = cols-1; j >= num; j--)
                curr[j] += curr[j-num];
        }
        return curr[cols-1];
    }

    /*
    Approach 3: 2D Dynamic Programming
    Algorithm

    The idea behind this approach is as follows. Suppose we can find out the number of times a particular sum, say sum_i
    is possible upto a particular index, say ii, in the given numsnums array, which is given by say count_i
    . Now, we can find out the number of times the sum sum_i + nums[i] can occur easily as count_i
    . Similarly, the number of times the sum sum_i - nums[i] occurs is also given by count_i
    */

    int doit_dp(vector<int>& nums, int S) {
        
        vector<unordered_map<int, int>> dp;
        dp.push_back({{0, 1}});

        for (auto c: nums) {
            unordered_map<int, int> tmp;
            auto lastResult = dp.back();

            for (auto it = begin(lastResult); it != end(lastResult); it++) {
                auto num = it->first, count = it->second;
                tmp[num - c] += count;
                tmp[num + c] += count;
            }

            dp.push_back(tmp);
        }

        return dp.back()[S];
    }

    int doit_dp_2(vector<int>& nums, int S) {
      const int n = nums.size();
      const int sum = std::accumulate(nums.begin(), nums.end(), 0);
      if (sum < std::abs(S)) 
        return 0;

      const int kOffset = sum;
      const int kMaxN = sum * 2 + 1;
      vector<int> ways(kMaxN, 0);      
      ways[kOffset] = 1;
      
      for (int num : nums) {
        vector<int> tmp(kMaxN, 0);
        for (int i = 0; i < kMaxN; ++i) {
          if (i + num < kMaxN) tmp[i] += ways[i + num];
          if (i - num >= 0)    tmp[i] += ways[i - num];
        }
        std::swap(ways, tmp);
      }

      return ways[S + kOffset];
    }

    /*
    Approach 4: 1D Dynamic Programming
    Algorithm

    If we look closely at the last solution, we can observe that for the evaluation of the current row of dpdp, only the values of the last row of dpdp are needed. 
    Thus, we can save some space by using a 1D DP array instead of a 2-D DP array. The only difference that needs to be made is that now the same dpdp array will be updated for every row traversed.

    Below code is inspired by @Chidong

    Complexity Analysis

    Time complexity : O(l.n). The entire numsnums array is traversed ll times. nn refers to the size of numsnums array. ll refers to the range of sumsum possible.
    Space complexity : O(n). dpdp array of size nn is used.
    */
    int doit_dp_best(vector<int>& nums, int S) {
        
        unordered_map<int, int> dp{{0, 1}};

        for (auto c: nums) {
            unordered_map<int, int> tmp;

            for (auto it = begin(dp); it != end(dp); it++) {
                auto num = it->first, count = it->second;
                tmp[num - c] += count;
                tmp[num + c] += count;
            }

            std::swap(dp, tmp);
        }

        return dp[S];
    }

    /*
        分析：

    这道题可以单纯的用暴力法解决，也就是对每个元素分别进行一次正负的累加，复杂度为2^n，因为n不超过20，故也就100w左右，但是在leetcode上同样的解法c++和java可以通过，python是无法通过的
    这里介绍discuss里一位大神提出来的超帅的数学解法，这道题中我们加正负号无非是将nums分为两个子集p,n，p中元素全部加正号，n中元素全部加负号，使得sum(p) - sum(n) = S，而本身又有sum(p) + sum(n) = sum(nums)，故两式相加化简得sum(p) = (sum(nums)+S) / 2
    
    那么这个式子直接给出了一个信息，也就是如果能找到p，则必有sum(nums)+S % 2 == 0这个条件，这个条件可以帮我们快速判断是否有解。
    那么此时题目就变成给定一个数组nums，求有多少组不同的p，使得sum(p) = target ((sum(nums) + S) / 2)，直接dp可解
    
    思路：

    建立dp，dp[i] = j代表数组nums中有j组子集的和为i，初始dp[0] = 1
    如nums = [1,1,1,1,1]，按照如下步骤分析
    对nums[0]分析，则得dp[1] = 1(因为dp[0] = 1)
    对nums[1]分析，则得dp[1] = 2,dp[2] = 1(因为dp[0] = 1,dp[1] = 1)
    对nums[2]分析，则得dp[1] = 3,dp[2] = 2,d[3] = 1,依次类推
    
    */
    int doit_(vector<int>& nums, int S) {
      S = std::abs(S);      
      const int sum = std::accumulate(nums.begin(), nums.end(), 0);
      if (sum < S || (S + sum) % 2 != 0) return 0;
      
      const int target = (S + sum) / 2;
      vector<int> dp(target + 1, 0);
      dp[0] = 1;
      
      for (int num : nums) {
        vector<int> tmp(dp);
        for (int j = 0; j <= target - num; ++j)
          tmp[j + num] += dp[j];
        std::swap(dp, tmp);
      }
      
      return dp[target];
    }

    int doit_2(vector<int>& nums, int S) {
      S = std::abs(S);
      const int n = nums.size();
      const int sum = std::accumulate(nums.begin(), nums.end(), 0);
      if (sum < S || (S + sum) % 2 != 0) return 0;
      const int target = (S + sum) / 2;
      vector<int> dp(target + 1, 0);
      dp[0] = 1;
      for (int num : nums)
        for (int j = target; j >= num; --j)
          dp[j] += dp[j - num];
      
      return dp[target];
    }
};