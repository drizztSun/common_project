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
 1 <= piles[i] <= 104
 
 */
#include <vector>
#include <numeric>


using std::vector;

class StoneGameII {
    
 
public:
    
    int doit_dp(vector<int>& piles) {
        
        int N = piles.size();
        vector<vector<int>> cache(N, vector<int>(N+1));
        
        std::function<int(int, int)> dp = [&](int i, int m) {
          
            if (i == N)
                return 0;
            
            m = std::min(m, N);
            if (cache[i][m] > 0)
                return cache[i][m];
            
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
        
        return (sums + dp(0, 1)) / 2;
    }
    
    
    vector<int>Sum;
    vector< vector<int>>dp;
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
