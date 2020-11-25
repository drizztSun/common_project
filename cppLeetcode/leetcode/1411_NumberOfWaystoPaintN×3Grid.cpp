/*
 
 1411. Number of Ways to Paint N × 3 Grid
 
 
 You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colours: Red, Yellow or Green
 while making sure that no two adjacent cells have the same colour (i.e no two cells that share vertical or horizontal sides have the same colour).

 You are given n the number of rows of the grid.

 Return the number of ways you can paint this grid. As the answer may grow large, the answer must be computed modulo 10^9 + 7.

  

 Example 1:

 Input: n = 1
 Output: 12
 Explanation: There are 12 possible way to paint the grid as shown:

 Example 2:

 Input: n = 2
 Output: 54
 Example 3:

 Input: n = 3
 Output: 246
 Example 4:

 Input: n = 7
 Output: 106494
 Example 5:

 Input: n = 5000
 Output: 30228214
  

 Constraints:

 n == grid.length
 grid[i].length == 3
 1 <= n <= 5000

 
 */
#include <vector>


using std::vector;


class NumOfWays {
    
    
public:
    
    int doit_dp_1(int n) {
        
        int M = 1e9+7;
        int tmp1[3] = {0, 0, 0}, tmp2[3] = {0, 0, 0};
        
        auto self_dk = [](int p, int* tmp) ->bool {
            
            for (int i = 0; i < 3; i++) {
                tmp[i] = p%3;
                p /= 3;
            }
            
            return (tmp[0] != tmp[1] && tmp[1] != tmp[2]);
        };
        
        int dp[27] = {0};
        for (auto i = 0; i < 27; i++) {
            if (self_dk(i, tmp1))
                dp[i] = 1;
        }
            
        while (n > 1) {
            
            int nextdp[27];
            
            for (auto i = 0; i < 27; i++)
                nextdp[i] = dp[i];
            
            // each line, can has 27 possible result, but only 12 of them are valid.
            // last line can also have 27 possible result and 12 of them are valid.
            for (auto i = 0; i < 27; i++) {

                dp[i] = 0;
                if (!self_dk(i, tmp1))
                    continue;
                
                for (auto j = 0; j < 27; j++) {
                    
                    if (!self_dk(j, tmp2))
                        continue;
                    
                    if (tmp1[0] != tmp2[0] && tmp1[1] != tmp2[1] && tmp1[2] != tmp2[2])
                        dp[i] = (dp[i] + nextdp[j]) % M;
                }
            }
            
            n--;
        }
        
        int res = 0;
        for (auto i = 0; i < 27; i++) {
            res = (res + dp[i]) % M;
        }
        return res;
    }
    
    int doit_dp(int n) {
        
         /*
         i-1, 2 colors,   3 colors
         i,   2 colors,   3 colors
         
         ABA(2 colors) => CAC, BCB, BAB (2 colors) or BAC, CAB (3 colors)
         
         ABC(3 colors) => BAB, BCB, (2 colors) or BCA, CAB (3 colors)
         
         dp2[i] = 2 * dp3[i-1] + 3 * dp2[i-1]
         dp3[i] = 2 * dp2[i-1] + 2 * dp3[i-1]
         */
        
        int M = 1e9+7;
        int dp2 = 6, dp3 = 6;
        
        while (n > 1) {
            
            long last2 = dp2, last3 = dp3;
            
            dp2 = ((2 * last3) % M + (3 * last2) % M) % M;
            dp3 = ((2 * last2) % M + (2 * last3) % M) % M;
            
            n--;
        }
        
        return (dp2 + dp3) % M;
    }
    
    int doit_dp_fastpower(int n) {
        
        constexpr long kMod = 1e9 + 7;
        
        auto mul = [kMod] (const vector<vector<long>>& A, const vector<vector<long>>& B) {
            
            const auto m = A.size(), n = B.size();
            const auto p = B[0].size();
            
            vector<vector<long>> C(m, vector<long>(p));
            for (auto i = 0; i < m; i++) {
                for (auto j = 0; j < p; j++) {
                    for (auto k = 0; k < n; k++) {
                        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % kMod;
                    }
                }
            }
            return C;
        };
        
        vector<vector<long>> ans{{6, 6}};
        vector<vector<long>> M{{3, 2}, {2, 2}};
        
        --n;
        while (n) {
            
            if (n & 1)
                ans = mul(ans, M);
            M = mul(M, M);
            n >>= 1;
        }
        
        return (ans[0][0] + ans[0][1]) % kMod;
    }
};



void Test_1411_NumberOfWaysPaintGrid() {
    
    NumOfWays().doit_dp(2);
}
