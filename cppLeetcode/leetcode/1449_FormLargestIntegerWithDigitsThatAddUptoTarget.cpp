/*
 1449. Form Largest Integer With Digits That Add up to Target
 
 Given an array of integers cost and an integer target. Return the maximum integer you can paint under the following rules:

 The cost of painting a digit (i+1) is given by cost[i] (0 indexed).
 The total cost used must be equal to target.
 Integer does not have digits 0.
 Since the answer may be too large, return it as string.

 If there is no way to paint any integer given the condition, return "0".



 Example 1:

 Input: cost = [4,3,2,5,6,7,2,5,5], target = 9
 Output: "7772"
 Explanation:  The cost to paint the digit '7' is 2, and the digit '2' is 3. Then cost("7772") = 2*3+ 3*1 = 9. You could also paint "977", but "7772" is the largest number.
 Digit    cost
   1  ->   4
   2  ->   3
   3  ->   2
   4  ->   5
   5  ->   6
   6  ->   7
   7  ->   2
   8  ->   5
   9  ->   5
 Example 2:

 Input: cost = [7,6,5,5,5,6,8,7,8], target = 12
 Output: "85"
 Explanation: The cost to paint the digit '8' is 7, and the digit '5' is 5. Then cost("85") = 7 + 5 = 12.
 Example 3:

 Input: cost = [2,4,6,2,4,6,4,4,4], target = 5
 Output: "0"
 Explanation: It's not possible to paint any integer with total cost equal to target.
 Example 4:

 Input: cost = [6,10,15,40,40,40,40,40,40], target = 47
 Output: "32211"


 Constraints:

 cost.length == 9
 1 <= cost[i] <= 5000
 1 <= target <= 5000
 
 
 */

#include <stdio.h>

#include <string>
#include <vector>

using std::vector;
using std::string;

class Solution {
    
public:
    
    /*
    Optimization
     
     To avoid string copying, we can store digit added (in order to back track the parent) and length of the optimal string.

     Time complexity: O(target)
     Space complexity: O(target)
     
    */
    string doit_dp_Bottoup_1(vector<int>&& cost, int target) {
        
        // dp[i] = {d, length} of the largest number that costs i.
        vector<std::pair<int, int>> dp(target + 1, {-1, -1});
        dp[0] = {0, 0};
        
        for (int t = 1; t <= target; ++t)
          for (int d = 1; d <= 9; ++d) { // we don't need to sort the cost by id, because same cost i < j. j always replace i res.
        
            const int s = t - cost[d - 1];
            if (s < 0 || dp[s].second == -1 || dp[s].second + 1 < dp[t].second) continue;
            dp[t] = {d, dp[s].second + 1};
          }
        
        if (dp[target].second == -1)
            return "0";
        
        string ans;
        while (target) {
          ans += dp[target].first + '0';
          target -= cost[dp[target].first - 1];
        }
        return ans;
    }
    
    string dpit_dp_Topdown_1(vector<int>&& cost, int target) {
        
        vector<std::pair<int, int>> cache(target + 1, {-1, -1});
        // dp[i] := {digit, length} of largestNumber that has cost i.
        std::function<std::pair<int, int>(int)> dp = [&](int t) -> std::pair<int, int> {
          if (t < 0)
              return {0, -1}; // Invalid.
          if (t == 0)
              return {0, 0}; // Found a solution.
          if (cache[t].first != -1)
              return cache[t];
          
          cache[t] = {0, -1}; // make as solved but invalid.
          for (int d = 1; d <= 9; ++d) {
            const int l = dp(t - cost[d - 1]).second;
            if (l != -1 && l + 1 >= cache[t].second)
              cache[t] = {d, l + 1};
          }
          return cache[t];
        };
        
        dp(target);
        if (cache[target].second <= 0)
            return "0";

        string ans;
        while (target) {
          ans += cache[target].first + '0';
          target -= cost[cache[target].first - 1];
        }
        return ans;
        
    }
    
    
    /*
     dp[t] := max number that costs[i]
     do[t] = max(d + dp[t-cost[d]) or "0"
     
     dp[t] = "0" if t < 0, invalid
     dp[t] = "" if t == 0
     
     ans = dp[target]
     */
    
    string doit_dp_Bottomup(vector<int>&& cost, int target) {
        
        vector<string> dp(target+1, "0");
        dp[0] = "";
        for (int t = 0; t <= target; t++) {
            for (int d = 1; d < 10; d++) {
                const int s = t - cost[d-1];
                if (s < 0 || dp[s] == "0" || dp[t].length() > dp[s].length()+1)
                    continue;
                dp[t] = std::to_string(d) + dp[s];
            }
        }
        return dp[target];
    }
    
    /*
     
     Time complexity: O(target^2)
     Space complexity: O(target^2)
     */
    
    string doit_dp_topdown(vector<int>&& cost, int target) {
        
        vector<string> cache(target + 1);
        
        std::function<string(int)> dp = [&](int n) -> string {
            
            if (n < 0)
                return "0"; // invalid
            if (n == 0)
                return ""; // found a solution
            
            if (!cache[n].empty())
                return cache[n];
            
            cache[n] = "0"; // Important
            
            for (int d = 1; d <= 9; d++) {
                const string& cur = dp(n - cost[d-1]);
                
                if (cur != "0" && cur.length() + 1 >= cache[n].length())
                    cache[n] = std::to_string(d) + cur;
                
            }
            
            return cache[n];
            
        };
        
        return dp(target);
    }
    
};
