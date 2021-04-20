/*
1833. Maximum Ice Cream Bars

It is a sweltering summer day, and a boy wants to buy some ice cream bars.

At the store, there are n ice cream bars. You are given an array costs of length n, where costs[i] is the price of the ith ice cream bar in coins. 
The boy initially has coins coins to spend, and he wants to buy as many ice cream bars as possible. 

Return the maximum number of ice cream bars the boy can buy with coins coins.

Note: The boy can buy the ice cream bars in any order.

 

Example 1:

Input: costs = [1,3,2,4,1], coins = 7
Output: 4
Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3 + 2 + 1 = 7.
Example 2:

Input: costs = [10,6,8,7,7,8], coins = 5
Output: 0
Explanation: The boy cannot afford any of the ice cream bars.
Example 3:

Input: costs = [1,6,3,1,2,5], coins = 20
Output: 6
Explanation: The boy can buy all the ice cream bars for a total price of 1 + 6 + 3 + 1 + 2 + 5 = 18.
 

Constraints:

costs.length == n
1 <= n <= 105
1 <= costs[i] <= 105
1 <= coins <= 108

*/

#include <vector>
#include <map>
#include <algorithm>

using std::map;
using std::vector;

class MaxIceCream {

    /*
        Explanation
        Sort the cost array A.
        Iterate A[i] from the small to big,
        and update coins -= A[i].
        If coin < 0, we don't have enough for this ice cream bar,
        and we have bought i ice cream bars before this one,
        so we return the result i.

        If we finish the loop,
        it means we can buy all ice cream bars,
        return the lenght of A.


        Complexity
        Time O(sort)
        Space O(sort)
    */
    int doit_greedy(vector<int>& A, int coins) {
        sort(A.begin(), A.end());
        for (int i = 0; i < A.size(); ++i)
            if ((coins -= A[i]) < 0)
                return i;
        return A.size();
    }
    
public:

    int doit_dp_TLE(vector<int>& costs, int coins) {
        
        map<int, int> cnts;
        for (const auto c : costs) 
            cnts[c]++;
        
        vector<int> dp(coins+1, 0);
        
        for (const auto it: cnts) {
            
            int p = it.first, c = it.second;
            
            for (int i = coins; i >= 0; i--) {
                
                if (i == 0 || dp[i] != 0)
                    
                for (int j = i+p, k = 1; j <= std::min(coins, i + c*p) && k <= c; j += p, k++) {
                    
                    dp[j] = std::max(dp[j], dp[i] + k);
                }
            }
        }
        
        return *max_element(begin(dp), end(dp));
    }
};