/*
 
 1681. Minimum Incompatibility
 
 You are given an integer array nums​​​ and an integer k. You are asked to distribute this array into k subsets of equal size
 such that there are no two equal elements in the same subset.

 A subset's incompatibility is the difference between the maximum and minimum elements in that array.

 Return the minimum possible sum of incompatibilities of the k subsets after distributing the array optimally, or return -1 if it is not possible.

 A subset is a group integers that appear in the array with no particular order.

  

 Example 1:

 Input: nums = [1,2,1,4], k = 2
 Output: 4
 Explanation: The optimal distribution of subsets is [1,2] and [1,4].
 The incompatibility is (2-1) + (4-1) = 4.
 Note that [1,1] and [2,4] would result in a smaller sum, but the first subset contains 2 equal elements.
 Example 2:

 Input: nums = [6,3,8,1,3,1,2,2], k = 4
 Output: 6
 Explanation: The optimal distribution of subsets is [1,2], [2,3], [6,8], and [1,3].
 The incompatibility is (2-1) + (3-2) + (8-6) + (3-1) = 6.
 Example 3:

 Input: nums = [5,3,3,6,3,3], k = 3
 Output: -1
 Explanation: It is impossible to distribute nums into 3 subsets where no two elements are equal in the same subset.
  

 Constraints:

 1 <= k <= nums.length <= 16
 nums.length is divisible by k
 1 <= nums[i] <= nums.length
 
 
 
 */
#include <vector>

using std::vector;

class MinimumIncompatibility {
    
    
    /*
     Solution -1: Seach
     let m = n/k
     C(n, m) * C(n-m, m) * ... * C(n-k*m, m) * c(m, m) => n!/m! => TLE
     
     n = 16, k = 4, m = 4 => 6306300
     
     */
    
    
public:
    
    /*
      Solution1 L Permutation -> Combination || Group numbers by their order
     (1 2 3 4) | (5 6 7 8) | (9 10 11 12) | (13 14 15 16) T(n) = O(n!) => TLE
     (7 5 8 6) | (11 12 9 10) | (4 1 3 2) | (13 ...
     However, if we have the optimal solution for a given set, the orders doesn't matter, we can convert it from permutation
     2^n( similar to TSP, LC 943/980/996/1125).
     
     dp[mask][i] := min cost to distribute numbers (as a binary mask) and the last number is i.
     
     Init: dp[1<<i][i] = 0 # cost of selecting a single number is zero.
     
     Transition:
     dp[mask | (1 << j)][j] = dp[mask][i]  # if we start a new group e.g. (1 2 3 4) | (5
     
     dp[mask | (1 << j)][j] = dp[mask][i] + nums[i] - nums[j] # if we extend the current group.
     e.g. (1 2 3 4) | (5 8 cost += 8  - 5 = 3
     
     Ans: min(dp[(1 << n) - 1]
     
     Q: How do we capture the max - min ? A: We require a group to be monotonically incresing.
     e.g. 4 8 12 19 => (8 - 5) + (12 - 8) + (19 - 12) => 19 - 5 = 14
     
     Time complexity: O(2^n * n^ 2) Space complexity: O(2^n)
     
     */
    
    int doit_(vector<int>& nums, int k) {
        const int n = nums.size();
        const int c = n / k;
        int dp[1 << 16][16];
        memset(dp, 0x7f, sizeof(dp));
        
        for (int i = 0; i < n; ++i) dp[1 << i][i] = 0;
        
        for (int s = 0; s < 1 << n; ++s)
          for (int i = 0; i < n; ++i) {
              
            if ((s & (1 << i)) == 0) continue;
              
            for (int j = 0; j < n; ++j) {
                
              if ((s & (1 << j))) continue;
                
              const int t = s | (1 << j);
              if (__builtin_popcount(s) % c == 0) {
                dp[t][j] = std::min(dp[t][j], dp[s][i]);
              } else if (nums[j] > nums[i]) {
                dp[t][j] = std::min(dp[t][j], dp[s][i] + nums[j] - nums[i]);
              }
            }
        }
        int ans = *std::min_element(std::begin(dp[(1 << n) - 1]), std::end(dp[(1 << n) - 1]));
        return ans > 1e9 ? - 1 : ans;
    }
    
    int doit_dp_bitmask_tsp(vector<int>& nums, int k) {
        
        const int size = nums.size();
        const int group = size / k;
        int N = (1 << size);
        vector<vector<int>> dp(N, vector<int>(size, 0x7F));
        
        for (int i = 0; i < size; i++) dp[1 << i][i] = 0;
        
        for (int s = 0; s < N; s++){
            
            for (int i = 0; i < size; i++) {
                
                if ((s & (1 << i)) == 0) continue;
                
                for (int j = 0; j < size; j++) {
                    if ((s & (1 << j)) == 1) continue;
                    
                    const int t = s | (1 << j);
                    
                    if (__builtin_popcount(s) % group == 0) {
                        dp[t][j] = std::min(dp[t][j], dp[s][i]);
                        
                    } else if (nums[j] > nums[i]) {
                        dp[t][j] = std::min(dp[t][j], dp[s][i] + nums[j] - nums[i]);
                    }
                }
            }
        }
        
        int ans = *min_element(begin(dp[N-1]), end(dp[N-1]));
        return ans > 1e9 ? -1 : ans;
    }
    
public:

    int ans = INT_MAX, n, m, k;
    
    int doit_backtracking(vector<int>& nums, int k) {
        n = nums.size(), m = n / k;
        this->k = k;
        if(m == 1){
            return 0;
        }
        sort(nums.begin(), nums.end());
        vector<vector<int>> subsets(k);
        backtrack(nums, 0, subsets, 0);
        return ans == INT_MAX ? -1 : ans;
    }

    void backtrack(const vector<int>& nums, int idx, vector<vector<int>>& subsets, int res){
        if(idx == n){
            ans = std::min(ans, res);
            return;
        }
        if(res >= ans){
            return;
        }
        
        for(int i = 0; i < subsets.size(); i++){
            if(subsets[i].size() == m || (!subsets[i].empty() && subsets[i].back() == nums[idx]) || (i > 0 && subsets[i] == subsets[i-1])){
                continue;
            }
            subsets[i].push_back(nums[idx]);
            int cur = 0;
            if(subsets[i].size() > 1){
                int t = subsets[i].size();
                cur = subsets[i][t-1] - subsets[i][t-2];
            }
            backtrack(nums, idx + 1, subsets, res + cur);
            subsets[i].pop_back();
        }
    }
};
