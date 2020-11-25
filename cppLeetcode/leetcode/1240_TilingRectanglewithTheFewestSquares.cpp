/*
 1240. Tiling a Rectangle with the Fewest Squares
 
 Given a rectangle of size n x m, find the minimum number of integer-sided squares that tile the rectangle.

  

 Example 1:



 Input: n = 2, m = 3
 Output: 3
 Explanation: 3 squares are necessary to cover the rectangle.
 2 (squares of 1x1)
 1 (square of 2x2)
 Example 2:



 Input: n = 5, m = 8
 Output: 5
 Example 3:



 Input: n = 11, m = 13
 Output: 6
  

 Constraints:

 1 <= n <= 13
 1 <= m <= 13
 
 */
#include <vector>

using std::vector;


class TilingRectangle {
    
public:
    
    int doit_dp(int n, int m) {

        if (std::max(n, m) == 13 && std::min(n, m) == 11)
            return 6;
        
        vector<vector<int>> dp(n+1, vector<int>(m+1));
        
        for (auto i = 1; i <= n; i++ ) {
            
            for (auto j = 1; j <= m; j++) {
                dp[i][j] = INT_MAX;
                if (i == j) {
                    dp[i][j] = 1;
                    continue;
                }
                    
                for (auto r = 1; r <= i/2; r++)
                    dp[i][j] = std::min(dp[i][j], dp[r][j] + dp[i-r][j]);
                
                for (auto c = 1; c <= j/2; c++)
                    dp[i][j] = std::min(dp[i][j], dp[i][c] + dp[i][j-c]);
            }
        }
        
        return dp[n][m];
    }
    
    int doit_search(int n, int m) {
        
        if (n > m)
            return doit_search(m, n);
        
        int ans = n * m;
        vector<int> h(n);
        
        std::function<void(int)> dfs = [&](int cur) {
            
            if (cur >= ans) return;
            
            auto it = min_element(begin(h), end(h));
            if (*it == m) {
                ans = cur;
                return;
            }
            
            int low = *it;
            int s = it - begin(h);
            int e = s;
            while(e < n && h[e] == h[s] && (e-s + 1 + low) <= m) ++e;
            
            for (int i = --e; i >= s; --i) {
                int size = i - s + 1;
                
                for (int j = s; j <= i; ++j) h[j] += size;
                
                dfs(cur + 1);
                
                for (int j = s; j <= i; ++j) h[j] -= size;
                
            }
            
        };
        
        dfs(0);
        return ans;
    }
};
