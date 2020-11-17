/*
 
 1655. Distribute Repeating Integers
 
 You are given an array of n integers, nums, where there are at most 50 unique values in the array. You are also given an array of m customer order quantities, quantity, where quantity[i] is the amount of integers the ith customer ordered. Determine if it is possible to distribute nums such that:

 The ith customer gets exactly quantity[i] integers,
 The integers the ith customer gets are all equal, and
 Every customer is satisfied.
 Return true if it is possible to distribute nums according to the above conditions.

  

 Example 1:

 Input: nums = [1,2,3,4], quantity = [2]
 Output: false
 Explanation: The 0th customer cannot be given two different integers.
 Example 2:

 Input: nums = [1,2,3,3], quantity = [2]
 Output: true
 Explanation: The 0th customer is given [3,3]. The integers [1,2] are not used.
 Example 3:

 Input: nums = [1,1,2,2], quantity = [2,2]
 Output: true
 Explanation: The 0th customer is given [1,1], and the 1st customer is given [2,2].
 Example 4:

 Input: nums = [1,1,2,3], quantity = [2,2]
 Output: false
 Explanation: Although the 0th customer could be given [1,1], the 1st customer cannot be satisfied.
 Example 5:

 Input: nums = [1,1,1,1,1], quantity = [2,3]
 Output: true
 Explanation: The 0th customer is given [1,1], and the 1st customer is given [1,1,1].
  

 Constraints:

 n == nums.length
 1 <= n <= 105
 1 <= nums[i] <= 1000
 m == quantity.length
 1 <= m <= 10
 1 <= quantity[i] <= 105
 There are at most 50 unique values in nums.
 
 
 */
#include <unordered_map>
#include <vector>


using std::vector;
using std::unordered_map;


class CanDistribute {

public:
    
    bool doit_backtracking_dfs(vector<int>& nums, vector<int>& quantity) {
        std::unordered_map<int, int> cnt;
        for (auto c : nums)
            cnt[c]++;
        
        vector<int> amounts;
        for (auto [k, v] : cnt)
            amounts.push_back(v);
        
        int m = quantity.size();
        int n = amounts.size();
        
        std::function<bool(int)> dp = [&](int d) {
            
            if (d == m)
                return true;
            
            for (auto i = 0; i < amounts.size(); i++) {
                if (amounts[i] >= quantity[d]) {
                    amounts[i] -= quantity[d];
                    if (dp(d+1))
                        return true;
                    amounts[i] += quantity[d];
                }
            }
            
            return false;
        };
        
        std::sort(rbegin(amounts), rend(amounts));
        std::sort(rbegin(quantity), rend(quantity));
        
        return dp(0);
    }
    
    
    bool res = false;
    
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        unordered_map<int, int> conter;
        for (auto n : nums) {
            conter[n] += 1;
        }
        
        vector<int> counts;
        for (auto& e : conter) counts.push_back(e.second);
        
        sort(quantity.rbegin(), quantity.rend());
        
        dfs(quantity, counts, 0);
        
        return res;
    }
    
    void dfs(vector<int>& quantity, vector<int>& counts, int i) {
        if (i == quantity.size() || res) {
            res = true;
            return;
        }
        
        for (int j = 0; j < counts.size(); j++) {
            int n = counts[j];
            
            if (n >= quantity[i]) {
                counts[j] -= quantity[i];
                dfs(quantity, counts, i + 1);
                counts[j] += quantity[i];
            }
        }
    }
    
    /*
     Bitmask + subsets
     dp(mask, i) := whether we can distribute to a subset of customers represented as a bit mask, using the i-th to (n-1)-th numbers.

     Time complexity: O(2^m * m * |vals|) = O(2^10 * 10 * 50)
     Space complexity: O(2^m * |vals|)
     
     key: assign i-th number to a subset of customers exclusively.
     dp[mask][i] = anu(sums(subset) <= freq[i] and dp[mask^subset][i-1])
     
     Subproblem: can the rest of the group be satisfied by the first i-1 numbers?
     
     Time O(3m * |f|) = O(50 * 3**10)
     
     */
    bool doit_dp_bitmask(vector<int>& nums, vector<int>& quantity) {
    
        unordered_map<int, int> cnts;
        for (auto i : nums) {
            cnts[i]++;
        }
        vector<int> values;
        for (auto c: cnts) {
            values.push_back(c.second);
        }
        
        auto m = quantity.size();
        auto n = values.size();
        vector<int> sums(1<<m);
        for (auto mask = 0; mask < (1<<m); mask++) {
            for (auto i = 0; i < m; i++) {
                if (mask & (1 << i))
                    sums[mask] += quantity[i];
            }
        }
        
        vector<vector<int>> dp(1<<m, vector<int>(n+1));
        dp[0][0] = 1;
        
        for (auto mask = 0; mask < 1<<m; mask ++) {
            
            for (int i = 0; i < n; i++) {
                
                dp[mask][i+1] |= dp[mask][i];
                
                auto cur = mask;
                while (cur) {
                    if (sums[cur] <= values[i] && dp[mask ^ cur][i]) {
                        dp[mask][i+1] = 1;
                    }
                    cur = (cur-1) & mask;
                }
            }
        }
        
        return dp[(1<<m)-1][n];
    }
};
