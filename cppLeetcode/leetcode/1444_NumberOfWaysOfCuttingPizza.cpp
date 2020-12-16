/*
 
 1444. Number of Ways of Cutting a Pizza
 
 Given a rectangular pizza represented as a rows x cols matrix containing the following characters: 'A' (an apple) and '.' (empty cell) and given the integer k. You have to cut the pizza into k pieces using k-1 cuts.

 For each cut you choose the direction: vertical or horizontal, then you choose a cut position at the cell boundary and cut the pizza into two pieces.
 If you cut the pizza vertically, give the left part of the pizza to a person. If you cut the pizza horizontally, give the upper part of the pizza to a person. Give the last piece of pizza to the last person.

 Return the number of ways of cutting the pizza such that each piece contains at least one apple. Since the answer can be a huge number, return this modulo 10^9 + 7.

  

 Example 1:

 Input: pizza = ["A..","AAA","..."], k = 3
 Output: 3
 Explanation: The figure above shows the three ways to cut the pizza. Note that pieces must contain at least one apple.
 Example 2:

 Input: pizza = ["A..","AA.","..."], k = 3
 Output: 1
 Example 3:

 Input: pizza = ["A..","A..","..."], k = 1
 Output: 1
  

 Constraints:

 1 <= rows, cols <= 50
 rows == pizza.length
 cols == pizza[i].length
 1 <= k <= 10
 pizza consists of characters 'A' and '.' only.

 */

#include <stdio.h>
#include <vector>
#include <string>

using std::vector;
using std::string;

class NumberOfCuttingPizza {
    
public:
    
    /*
     
     dp(n, m, k) := # of ways to cut pizza[n:N][m:M] with k cuts.

     dp(n, m, k) = sum(hasApples(n, m, N – 1, y) * dp(y + 1, n, k – 1) for y in range(n, M)) + sum(hasApples(n, m, x, M – 1) * dp(m, x + 1, k – 1) for x in range(n, M))

     Time complexity: O(M*N*(M+N)*K) = O(N^3 * K)
     Space complexity: O(M*N*K)
     
     */
    
    int doit_dp(vector<string>&& pizza, int K) {
        
        constexpr int kMod = 1e9 + 7;
        const int M = pizza.size();
        const int N = pizza[0].size();
        
        vector<vector<int>> A(M + 1, vector<int>(N + 1));
        for (int y = 0; y < M; ++y)
          for (int x = 0; x < N; ++x)
            A[y + 1][x + 1] = A[y + 1][x] + A[y][x + 1] + (pizza[y][x] == 'A') - A[y][x];
        
        auto hasApples = [&](int x1, int y1, int x2, int y2) {
          return (A[y2 + 1][x2 + 1] - A[y2 + 1][x1] - A[y1][x2 + 1] + A[y1][x1]) > 0;
        };
        
        vector<vector<vector<int>>> cache(M, vector<vector<int>>(N, vector<int>(K, -1)));
        
        // dp(m, n, k) := # of ways to cut pizza[m:M][n:N] with k cuts.
        std::function<int(int, int, int)> dp = [&](int m, int n, int k) -> int {
          if (k == 0)
              return hasApples(n, m, N - 1, M - 1);
          
          int& ans = cache[m][n][k];
          if (ans != -1) return ans;
          
          ans = 0;
          for (int y = m; y < M - 1; ++y)  // Cut horizontally.
            ans = (ans + hasApples(n, m, N - 1, y) * dp(y + 1, n, k - 1)) % kMod;
            
          for (int x = n; x < N - 1; ++x)  // Cut vertically.
            ans = (ans + hasApples(n, m, x, M - 1) * dp(m, x + 1, k - 1)) % kMod;
          return ans;
        };
        return dp(0, 0, K - 1);
    }
    
    
public:
    int m;
    int n;
    int dp[50][50][11];
    int count[50][50];
    int NUM = 1e9+7;
    
    int ways(vector<string>& pizza, int k) {
        m = pizza.size();
        n = pizza[0].size();
        for (int i = pizza.size()-1; i >= 0; --i) {
            for (int j = pizza[0].size()-1; j >= 0; --j) {
                count[i][j] = pizza[i][j] == 'A';
                
                if (j < n-1)
                    count[i][j] += count[i][j+1];
                if (i < m-1)
                    count[i][j] += count[i+1][j];
                
                if (j < n-1 && i < m-1) {
                    count[i][j] -= count[i+1][j+1];
                }
            }
        }
        
        memset(dp, -1, sizeof(dp));
        return ways(0, 0, k);
    }
    
    int ways(int r, int c, int k) {
        if (dp[r][c][k] != -1) return dp[r][c][k];
        if (count[r][c] < k) return dp[r][c][k] = 0;
        if (k == 1) return dp[r][c][k] = count[r][c] > 0;
        
        int ans = 0;
        for (int i = r; i < m - 1; ++i) {
            if (count[r][c] - count[i+1][c] > 0) {
                ans += ways(i+1, c, k-1);
                ans %= NUM;
            }
        }
        
        for (int i = c; i < n - 1; ++i) {
            if (count[r][c] - count[r][i+1] > 0) {
                ans += ways(r, i+1, k-1);
                ans %= NUM;
            }
        }
        
        return dp[r][c][k] = ans;
    }
};

void test_1444_number_of_cut_pizza() {
    
    int num = NumberOfCuttingPizza().doit_dp(vector<string>{"A..","AAA","..."}, 3);
    
    return;
}
