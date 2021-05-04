/*

322. Coin Change

You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

 

Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
Example 2:

Input: coins = [2], amount = 3
Output: -1
Example 3:

Input: coins = [1], amount = 0
Output: 0
Example 4:

Input: coins = [1], amount = 1
Output: 1
Example 5:

Input: coins = [1], amount = 2
Output: 2
 

Constraints:

1 <= coins.length <= 12
1 <= coins[i] <= 231 - 1
0 <= amount <= 104

*/

#include <vector>
#include <functional>
#include <algorithm>

using std::vector;

class CoinChange {

public:

    int doit_dp_bottomup(vector<int>& coins, int amount) {
        
        std::sort(begin(coins), end(coins));
        
        vector<int> dp(amount+1, amount+1);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; i++) {
            
            for (const auto c: coins) {
                
                if (i - c < 0) break;
                
                if (i - c == 0 || dp[i-c] > 0) {
                    dp[i] = std::min(dp[i], dp[i-c]+1);
                }
            }
        }
        
        return dp[amount] == amount + 1 ? -1 : dp[amount];
    }

    int doit_dp_topdown(vector<int>& coins, int amount) {
        
        int ans = amount+1;
        vector<int> dp(amount+1, 0);
        
        std::function<int(int)> dfs = [&](int cur) {
            
            if (cur == 0) return 0;
            
            if (dp[cur] != 0) return dp[cur];
            
            int res = amount+1;
            for (const auto c: coins) {
                if (cur >= c)
                    res = std::min(res, dfs(cur-c)+1);
            }
            
            return dp[cur] = res;
        };
        
        ans = dfs(amount);
        
        return ans == amount+1 ? - 1 : ans;
    }
};