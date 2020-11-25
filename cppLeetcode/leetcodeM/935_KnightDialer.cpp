/*
 935. Knight Dialer
 
 
 The chess knight has a unique movement, it may move two squares vertically and one square horizontally, or two squares horizontally and one square vertically (with both forming the shape of an L).
 
 The possible movements of chess knight are shown in this diagaram:

 A chess knight can move as indicated in the chess diagram below:


 We have a chess knight and a phone pad as shown below, the knight can only stand on a numeric cell (i.e. blue cell).


 Given an integer n, return how many distinct phone numbers of length n we can dial.

 You are allowed to place the knight on any numeric cell initially and then you should perform n - 1 jumps to dial a number of length n. All jumps should be valid knight jumps.

 As the answer may be very large, return the answer modulo 109 + 7.

  

 Example 1:

 Input: n = 1
 Output: 10
 Explanation: We need to dial a number of length 1, so placing the knight over any numeric cell of the 10 cells is sufficient.
 Example 2:

 Input: n = 2
 Output: 20
 Explanation: All the valid number we can dial are [04, 06, 16, 18, 27, 29, 34, 38, 40, 43, 49, 60, 61, 67, 72, 76, 81, 83, 92, 94]
 Example 3:

 Input: n = 3
 Output: 46
 Example 4:

 Input: n = 4
 Output: 104
 Example 5:

 Input: n = 3131
 Output: 136006598
 Explanation: Please take care of the mod.
  

 Constraints:

 1 <= n <= 5000

 
 */
#include <vector>
#include <algorithm>
#include <numeric>

using std::vector;

class knightDialer {
    
public:
    
    int doit_dp(int n) {
        
        vector<vector<int>> jump{{4, 6}, {6, 8}, {7, 9}, {4, 8}, {0, 3, 9}, {}, {0, 1, 7}, {2, 6}, {1, 3}, {2, 4}};
        int mod = 1e9+7;
        vector<int> dp(10, 1);
        
        while (n>1) {
                
            vector<int> nextdp(10, 0);
            
            for (auto i = 0; i < dp.size(); i++) {
                for (auto j : jump[i])
                    nextdp[j] = (nextdp[j] + dp[i]) % mod;
            }
            nextdp.swap(dp);
            n--;
        }
        
        int res = 0;
        for (auto n : dp)
            res = (res + n) % mod;
        
        return res;
    }
    
    int doit_dp_fastpow(int n) {
        
        vector<vector<long>> ans(1, vector<long>(10, 1));
        
        vector<vector<long>> matrix{
            {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
            {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
            {0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 1, 0, 0, 0, 0, 0}
        };
        int mod = 1e9 + 7;
        
        auto mul = [mod](const vector<vector<long>>& A, const vector<vector<long>>& B) {
            
            const auto m = A.size(), n = B.size();
            const auto p = B[0].size();
            
            vector<vector<long>> C(m, vector<long>(p));
            for (auto i = 0; i < m; i++) {
                for (auto j = 0; j < p; j++) {
                    for (auto k = 0; k < n; k++) {
                        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
                    }
                }
            }
            return C;
        };
        
        n--;
        while (n) {
            if (n & 1)
                ans = mul(ans, matrix);
            
            matrix = mul(matrix, matrix);
            n >>= 1;
        }
        
        long res = 0;
        for (auto c : ans[0])
            res = (res + c) % mod;
        
        return res;
    }
};
