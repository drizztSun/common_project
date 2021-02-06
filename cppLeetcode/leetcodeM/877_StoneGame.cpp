/*
 877. Stone Game
 
 Alex and Lee play a game with piles of stones.  There are an even number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].

 The objective of the game is to end with the most stones.  The total number of stones is odd, so there are no ties.

 Alex and Lee take turns, with Alex starting first.  Each turn, a player takes the entire pile of stones from either the beginning or the end of the row.
 This continues until there are no more piles left, at which point the person with the most stones wins.

 Assuming Alex and Lee play optimally, return True if and only if Alex wins the game.

  

 Example 1:

 Input: piles = [5,3,4,5]
 Output: true
 Explanation:
 Alex starts first, and can only take the first 5 or the last 5.
 Say he takes the first 5, so that the row becomes [3, 4, 5].
 If Lee takes 3, then the board is [4, 5], and Alex takes 5 to win with 10 points.
 If Lee takes the last 5, then the board is [3, 4], and Alex takes 4 to win with 9 points.
 This demonstrated that taking the first 5 was a winning move for Alex, so we return true.
  

 Constraints:

 2 <= piles.length <= 500
 piles.length is even.
 1 <= piles[i] <= 500
 sum(piles) is odd.
 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>

using std::vector;
using std::unordered_map;

class StoneGameI {

public:

    /*
        877.Stone-Game
        解法1：
        因为此题的N为偶数，且不会有平局。说明奇数堆的总和，必然与偶数堆的总和不一样。先手玩家可以总是取奇数堆（或者总是取偶数堆），因此可以必胜。

        解法2：
        当N为奇数时，就没有上述的巧解。对于这种策略型的题目，递归是比较常见的解法。我们设计递归函数int solve(a,b)表示先手玩家来当前面对[a,b]区间时可以得到的最大收益。因为这个游戏的得分是此消彼长的关系，所以先手玩家最终取得胜利的条件就是：

        solve(1,n) > total - solve(1,n);
        那么这个递归函数怎么往下拆解呢？无非就是遵循游戏规则，有两种决策：

        1. 如果我选择了最左边的石头堆（也就是a），那么对手面临也是同一个最优化的问题，只不过范围不同，即solve(a+1,b)，对手需要在[a+1,b]这个区间内最大化自己的收益。因此我方在[a,b]区间最终能够得到的收益就是sum[a:b] - solve(a+1,b).
        2. 如果我选择了最右边的石头堆（也就是b），那么对手面临也是同一个最优化的问题，只不过范围不同，即solve(a,b-1)，对手需要在[a,b-1]这个区间内最大化自己的收益。因此我方在[a,b]区间最终能够得到的收益就是sum[a:b] - solve(a,b-1).
        综上，我方必定会在这两个决策中选择一个能够在[a,b]区间收益更多的方案。这就实现了solve(a,b)的递归。无论是我方还是对方，递归的拆解思路总是相同的。递归的边界条件就是a==b时，这堆石头直接拿走。
    
    */



    

public:
    bool stoneGame(vector<int>& piles) 
    {
        int dp[501][501];
        std::function<int(int, int)> solve = [&](int a, int b) {
            if (a==b) 
                return piles[a];
            
            if (dp[a][b]!=0) 
                return dp[a][b];
            
            dp[a][b] = std::max(piles[a]+solve(a+1,b), piles[b]+solve(a,b-1));
            return dp[a][b];
        };

        int myBest = solve(0, piles.size()-1);
        int total = std::accumulate(piles.begin(), piles.end(), 0);
        return (myBest > total - myBest);
    }




    bool doit_dp_dfs(vector<int>& piles) {
        
        
        auto hash = [](const std::pair<int, int>& a) {
            return std::hash<int>()(a.first) ^ std::hash<int>()(a.second);
        };
        
        auto equal = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.first == b.first && a.second == b.second;
        };
        
        auto N = piles.size();
        // Must profit Alice can get from (a, b)
        unordered_map<std::pair<int, int>, int, decltype(hash), decltype(equal)> dp(0, hash, equal);
        
        std::function<int(int, int)> dfs = [&](int i, int j) {
            
            if (i > j)
              return 0;
            
            auto key = std::make_pair(i, j);
            
            if (dp.count(key) > 0)
                return dp[key];
           
            int turn = (j - i + 1) % 2;
            if (turn == 0) {
                // Alice turn, what profit is maximum profit at next range plus Bob gets
                dp[key] = std::max(piles[i] + dfs(i+1, j), piles[j] + dfs(i, j-1));
            } else {
                // Bob turn, what proit is maximum profit at next range minus Bob gets
                dp[key] = std::max(-piles[i] + dfs(i+1, j), -piles[j] + dfs(i, j-1));
            }
           
            return dp[key];
        };
                                   
        return dfs(0, piles.size() - 1) > 0;
    }
    
    bool doit_dp(vector<int>& piles) {
        
        int n = piles.size();
        vector<vector<std::pair<int,int>>> dp(n, vector<std::pair<int, int>>(n, {0,0}));
        
        for(int i = 0; i < n; i++)
            dp[i][i] = {piles[i], 0};
        
        for(int i = n-1; i >= 0; i--){
            for(int j = i+1; j < n; j++){
                int left = piles[i] + dp[i+1][j].second;
                int right = piles[j] + dp[i][j-1].second;
                if(left > right){
                    dp[i][j].first = left;
                    dp[i][j].second = dp[i+1][j].first;
                }
                else{
                    dp[i][j].first = right;
                    dp[i][j].second = dp[i][j-1].first;
                }
            }
        }
        return dp[0][n-1].first > dp[0][n-1].second;
    }
    
    bool doit_dp_2(vector<int>& piles) {
        
        auto n=piles.size();
        int sum=0;
        for(auto p:piles){
            sum+=p;
        }
        
        vector<vector<int> > dp(piles.size()+1,vector<int>(piles.size()+1));
        
        for(int i=0;i<n;i++){
            dp[i][i]=piles[i];
        }
        
        for(int i=0;i<n-1;i++){
            dp[i][i+1] = std::max(piles[i],piles[i+1]);
        }
        
        for(int len=3;len<=n;len++){
            int i=0,j=len-1;
            while(j<n){
                int ans1 = piles[i] + std::min(dp[i+2][j],dp[i+1][j-1]);
                int ans2 = piles[j] + std::min(dp[i][j-2],dp[i+1][j-1]);
                dp[i][j] = std::max(ans1,ans2);
                i++;
                j++;
            }
            
        }

        return dp[0][n-1]>(sum-dp[0][n-1]);
    }
};
