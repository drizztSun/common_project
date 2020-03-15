/*
 
 
 # 956. Tallest Billboard

 # You are installing a billboard and want it to have the largest height.
 # The billboard will have two steel supports, one on each side.  Each steel support must be an equal height.

 # You have a collection of rods which can be welded together.
 # For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.

 # Return the largest possible height of your billboard installation.  If you cannot support the billboard, return 0.


 # Example 1:

 # Input: [1, 2, 3, 6]
 # Output: 6
 # Explanation: We have two disjoint subsets {1, 2, 3} and {6}, which have the same sum = 6.

 # Example 2:

 # Input: [1, 2, 3, 4, 5, 6]
 # Output: 10
 # Explanation: We have two disjoint subsets {2, 3, 5} and {4, 6}, which have the same sum = 10.

 # Example 3:

 # Input: [1, 2]
 # Output: 0
 # Explanation: The billboard cannot be supported, so we return 0.

 
 
 */
#include <algorithm>
#include <numeric>

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

class TallestBillboard {
    
public:
    
    int doit(vector<int>&& rods) {
        
        unordered_map<int, int> dp;
        dp[0] = 0;
        
        for (auto c : rods) {
            
            unordered_map<int, int> newdp(dp);
            for (auto& item : dp) {
                
                int k = item.first, v = item.second;
                
                // put it on left
                dp[k+c] = std::max(newdp.count(k+c) ? newdp[k+c] : 0, c + v);
                
                // discard it
                dp[k] = std::max(newdp.count(k) ? newdp[k] : 0, v);
                
                // put it on right
                dp[k-c] = std::max(newdp.count(k-c) ? newdp[k-c] : 0, v);
            }
            
        }
        
        return dp[0];
    }
    
    /*
     Explanation:
     dp[d] mean the maximum pair of sum we can get with pair difference d
     
     For example, if have a pair of sum (a, b) with a > b, then dp[a - b] = b
     If we have dp[diff] = a, it means we have a pair of sum (a, a + diff).
     And this is the biggest pair with difference = a

     dp is initializes with dp[0] = 0;

     Assume we have an init state like this
     ------- y ------|----- d -----|
     ------- y ------|

     case 1
     If put x to tall side
     ------- y ------|----- d -----|----- x -----|
     ------- y ------|

     We update dp[d + x] = max(dp[d + x], y )

     case 2.1
     Put x to low side and d >= x:
     -------y------|----- d -----|
     -------y------|--- x ---|

     We update dp[d-x] = max( dp[d - x], y + x)

     case 2.2
     Put x to low side and d < x:
     ------- y ------|----- d -----|
     ------- y ------|------- x -------|
     We update dp[x - d] = max(dp[x - d], y + d)

     case 2.1 and case2.2 can merge into dp[abs(x - d)] = max(dp[abs(x - d)], y + min(d, x))


     Time Complexity:
     O(NM), where we have
     N = rod.length <= 20
     S = sum(rods) <= 5000
     M = all possible sum = min(3^N, S)

     There are 3 ways to arrange a number: in the first group, in the second, not used.
     The number of difference will be less than 3^N.
     The only case to reach 3^N is when rod = [1,3,9,27,81...]
     */
    int doit1(vector<int>&& rods) {
        
        int s = std::accumulate(rods.begin(), rods.end(), 0);
        
        // dp: K is differernce, V is min(left, right)
        vector<int> dp(s+1, -1);
        dp[0] = 0;
        
        for (int h : rods) {
        
            vector<int> cur(dp);
            for (int i=0; i<=s; ++i) {
            
                if (cur[i] < 0)
                    continue;
                
                if (i+h <= s)
                    // put it on long side,
                    dp[i+h] = std::max(dp[i+h], cur[i]);
                
                // put it on short side,
                dp[abs(i-h)] = std::max(dp[abs(i-h)], cur[i] + std::min(i, h));
            }
        }
        
        return dp[0];
    }
    
    int doit11(vector<int>& rods) {
        unordered_map<int, int> dp;
        dp[0] = 0;
        for (int x : rods) {
            unordered_map<int, int> cur(dp);
            for (auto it: cur) {
                int d = it.first;
                dp[d + x] = std::max(dp[d + x],cur[d]);
                dp[abs(d - x)] = std::max(dp[abs(d - x)], int(cur[d] + std::min(d, x)));
            }
        }
        return dp[0];
    }
    
    int doit2(vector<int>&& rods) {
        int s = 0;
        for (auto it : rods){
            s += it;
        }
        
        vector<vector<int>> dp(2, vector<int>((s + 1) << 1, -1));
        dp[0][s] = 0;
        for (int i = 0; i < rods.size(); i++){
            
            int now = i & 1, next = (i & 1) ^ 1;
            for (int j = 0; j < dp[now].size(); j++){
            
                if (dp[now][j] == -1)
                    continue;
                
                dp[next][j] = std::max(dp[now][j], dp[next][j]);
                dp[next][j + rods[i]] = std::max(dp[next][j + rods[i]], dp[now][j] + rods[i]);
                dp[next][j - rods[i]] = std::max(dp[next][j - rods[i]], dp[now][j] + rods[i]);
            }
        }
        return dp[rods.size() & 1][s] >> 1;
    }
    
};

void test_956_Tallest_Billboards() {
    
    auto res1 = TallestBillboard().doit(vector<int>{1, 2, 3, 6});
    
    auto res2 = TallestBillboard().doit(vector<int>{1, 2, 3, 4, 5, 6});
    
    auto res3 = TallestBillboard().doit(vector<int>{1, 2});
    
    return;
}
