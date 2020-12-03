/*
 1473. Paint House III
 
 There is a row of m houses in a small city, each house must be painted with one of the n colors (labeled from 1 to n),
 some houses that has been painted last summer should not be painted again.

 A neighborhood is a maximal group of continuous houses that are painted with the same color.
 (For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods  [{1}, {2,2}, {3,3}, {2}, {1,1}]).

 Given an array houses, an m * n matrix cost and an integer target where:

 houses[i]: is the color of the house i, 0 if the house is not painted yet.
 cost[i][j]: is the cost of paint the house i with the color j+1.
 Return the minimum cost of painting all the remaining houses in such a way that there are exactly target neighborhoods, if not possible return -1.

  

 Example 1:

 Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
 Output: 9
 Explanation: Paint houses of this way [1,2,2,1,1]
 This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
 Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.
 Example 2:

 Input: houses = [0,2,1,2,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
 Output: 11
 Explanation: Some houses are already painted, Paint the houses of this way [2,2,1,2,2]
 This array contains target = 3 neighborhoods, [{2,2}, {1}, {2,2}].
 Cost of paint the first and last house (10 + 1) = 11.
 Example 3:

 Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[1,10],[10,1],[1,10]], m = 5, n = 2, target = 5
 Output: 5
 Example 4:

 Input: houses = [3,1,2,3], cost = [[1,1,1],[1,1,1],[1,1,1],[1,1,1]], m = 4, n = 3, target = 3
 Output: -1
 Explanation: Houses are already painted with a total of 4 neighborhoods [{3},{1},{2},{3}] different of target = 3.
  

 Constraints:

 m == houses.length == cost.length
 n == cost[i].length
 1 <= m <= 100
 1 <= n <= 20
 1 <= target <= m
 0 <= houses[i] <= n
 1 <= cost[i][j] <= 10^4
 
 */
#include <vector>
#include <tuple>
#include <numeric>

using std::vector;
using std::tie;

class PaintHouseIII {
public:
    
    /*
     
        Solution: DP
     
     state:
     1) k: number of groups
     2) i: number of houses
     3) c: color if the last house / group
     
     Definition
     dp[k][i][c] := min cost of form k groups using first i houses and i-th is in color c.
     
     Init: dp[0][0][*] = 0, otherwise inf
     
     Transition:
     dp[k][i][c] = min(dp[k-(c!=cj)][j][cj]) + cost[i][c] if colors[i] == 0 else 0, j = i - 1
     
     Let ci = colors[i], dp[k][i][c!=ci] = inf
     
     ans: min(dp[target][m][*])
     
     Time complexity: O(T*M*N^2)
     Space complexity: O(T*M*N) -> O(MN)
     
     Cost to pait i-th house into color c.
     v = 0 if colors[i]  == c else cost[i][c]
    
    */
    
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        constexpr int kInf = 1e9 + 7, s = 1;
        // dp[k][i][c] := min cost to form k neighbors with first i houses and end with color c.
        vector<vector<vector<int>>> dp(target + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, kInf)));
        fill(begin(dp[0][0]), end(dp[0][0]), 0);
        
        for (int k = 1; k <= target; ++k)
          for (int i = k; i <= m; ++i) {
            
            const int hi = houses[i - 1];
            const int hj = i >= 2 ? houses[i - 2] : 0;
        
            const auto& [si, ei] = hi ? tie(hi, hi) : tie(s, n);
            const auto& [sj, ej] = hj ? tie(hj, hj) : tie(s, n);
            
            for (int ci = si; ci <= ei; ++ci) {
                const int v = ci == hi ? 0 : cost[i - 1][ci - 1];
                
                for (int cj = sj; cj <= ej; ++cj) {
                    dp[k][i][ci] = std::min(dp[k][i][ci], dp[k - (ci != cj)][i - 1][cj] + v);
                }
            }
          }
        
        const int ans = *min_element(begin(dp[target][m]), end(dp[target][m]));
        return ans >= kInf ? -1 : ans;
    }
  
    
    int n;
    int dp[100][101][20];
    int doit_dfs(vector<int>& houses, vector<vector<int>>& cost, int m, int N, int target) {
        n = N;
        memset(dp, -1, sizeof(dp));
        
        // normalize to -1 - no painting, otherwise color from 0 to n-1
        for (auto& h : houses) --h;
        
        int ans = INT_MAX;
        for (int i = 0; i < n; ++i)
            ans = std::min(ans, get(houses, cost, m-1, target, i));
        
        return ans == INT_MAX ? -1 : ans;
    }
    
    int get(vector<int>& houses, vector<vector<int>>& cost, int cur, int target, int color) {
        if (target > cur + 1) return INT_MAX;
        if (cur == -1) return target == 0 ? 0 : INT_MAX;
        if (target == 0) return INT_MAX;
        if (houses[cur] != -1 && houses[cur] != color) return INT_MAX;
        if (dp[cur][target][color] != -1) return dp[cur][target][color];
        
        long ans = INT_MAX;
        long val = houses[cur] == color ? 0 : cost[cur][color];
        for (int nc = 0; nc < n; ++nc) {
            if (nc != color) {
                ans = std::min(ans, val + get(houses, cost, cur-1, target-1, nc));
            } else {
                ans = std::min(ans, val + get(houses, cost, cur-1, target, nc));
            }
        }
        
        return dp[cur][target][color] = (ans > INT_MAX ? INT_MAX : ans);
    }
};
