/*
 
 1140 Stone Game II
 
 Alice and Bob continue their games with piles of stones.  There are a number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].
 The objective of the game is to end with the most stones.

 Alice and Bob take turns, with Alice starting first.  Initially, M = 1.

 On each player's turn, that player can take all the stones in the first X remaining piles, where 1 <= X <= 2M.  Then, we set M = max(M, X).

 The game continues until all the stones have been taken.

 Assuming Alice and Bob play optimally, return the maximum number of stones Alice can get.

  

 Example 1:

 Input: piles = [2,7,9,4,4]
 Output: 10
 Explanation:  If Alice takes one pile at the beginning, Bob takes two piles, then Alice takes 2 piles again. Alice can get 2 + 4 + 4 = 10 piles in total.
 If Alice takes two piles at the beginning, then Bob can take all three piles left. In this case, Alice get 2 + 7 = 9 piles in total. So we return 10 since it's larger.
 Example 2:

 Input: piles = [1,2,3,4,5,100]
 Output: 104
  

 Constraints:

 1 <= piles.length <= 100
 1 <= piles[i] <= 10^4
 
 */
#include <vector>
#include <numeric>


using std::vector;

class StoneGameII {
    
 
public:

    /*
        1140.Stone-Game-II
        本题是典型的决策问题。设计solve(i,M)表示当前玩家可以从第i堆石头开始取、所取的堆数的上下限是[1,2M]，那么截止游戏结束所能得到的最大收益。

        假设当前玩家取X堆，那么对手在之后所能得到的最大收益就是solve(i+X, max(X,M))。
        这就说明，对于当前玩家而言，如果本回合取X堆，根据此消彼长的规则，意味着截止游戏时能得到的最大收益就是sufSum[i] - solve(i+X, max(X,M))。
        所以为了使solve(i,M)最大，我们必然会取能使sufSum[i] - solve(i+X, max(X,M))最大的X。

        递归的边界条件就是当i==n的时候，玩家不能再取石头，返回零。最终的答案就是solve(0,1)。
    */

public:
    int stoneGameII(vector<int>& piles)
    {

        int dp[101][101];    
        int sufsum[101];

        int n = piles.size();
        for (int i=0; i<=100; i++)
            for (int j=0; j<=100; j++)
                dp[i][j] = 0;

        sufsum[n] = 0;

        std::function<int(int, int)> solve = [&](int i, int M) {

            if (i==piles.size()) return 0;
            
            if (dp[i][M]!=0) return dp[i][M];

            for (int x=1; x<=2*M; x++)
            {
                if (i+x>piles.size()) break;
                dp[i][M] = max(dp[i][M], sufsum[i] - solve(i+x, max(x,M)));
            }
            return dp[i][M];
        }

        for (int i=n-1; i>=0; i--)
            sufsum[i] = sufsum[i+1]+piles[i];
        return solve(0, 1, piles);
    }



public:
    
    int doit_dp(vector<int>& piles) {
        
        int N = piles.size();
        vector<vector<int>> cache(N, vector<int>(N+1));
        
        // dp is profit of current turn, Alice or Bob, so one person needs calulate what he gets minus another person's profit 
        // also we need to cache dp(i, m), to minimize the calculation.
        std::function<int(int, int)> dp = [&](int i, int m) {
          
            if (i == N)
                return 0;
            
            m = std::min(m, N);

            if (cache[i][m] > 0) return cache[i][m];
            
            if (i + 2 * m >= N)
                return cache[i][m] = std::accumulate(begin(piles)+i, end(piles), 0);

            int total = 0, best = INT_MIN;
            for (auto j = 1; j <= 2*m; j++) {
                total += piles[i+j-1];
                best = std::max(best, total - dp(i+j, std::max(m, j)));
            }
            
            return cache[i][m] = best;
        };
        
        int sums = accumulate(begin(piles), end(piles), 0);
        
        // profit = A - B, A + b = total, so A = (sum + profit) / 2
        return (sums + dp(0, 1)) / 2;
    }
    
    
    vector<int>Sum;
    vector<vector<int>>dp;
public:
    
    int find_solution(vector<int>& arr, int index, int n, int X){
        if(index >= n)
            return 0;
        if(dp[index][X] != -1)
            return dp[index][X];
        
        int min_value = Sum[index];
        for(int k=index; k< index + 2 * X && k <n ; k++){
            min_value = std::min(min_value, find_solution(arr, k+1, n, std::max(k-index+1, X)));
        }
        dp[index][X] = Sum[index] - min_value;
        return dp[index][X];
    }

    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        Sum.resize(n);
        dp.resize(n);
        for(int i=0;i<n;i++)
            dp[i].resize(n);
        
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                dp[i][j] = -1;
        
        Sum[n-1] = piles[n-1];
        for(int i=n-2; i>=0; i--)
            Sum[i] = Sum[i+1] + piles[i];
        return find_solution(piles, 0, n, 1);
        
    }
};
