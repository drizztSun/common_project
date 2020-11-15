/*
 1463. Cherry Pickup II
 
 Given a rows x cols matrix grid representing a field of cherries. Each cell in grid represents the number of cherries that you can collect.

 You have two robots that can collect cherries for you, Robot #1 is located at the top-left corner (0,0) , and Robot #2 is located at the top-right corner (0, cols-1) of the grid.

 Return the maximum number of cherries collection using both robots  by following the rules below:

 From a cell (i,j), robots can move to cell (i+1, j-1) , (i+1, j) or (i+1, j+1).
 When any robot is passing through a cell, It picks it up all cherries, and the cell becomes an empty cell (0).
 When both robots stay on the same cell, only one of them takes the cherries.
 Both robots cannot move outside of the grid at any moment.
 Both robots should reach the bottom row in the grid.
  

 Example 1:



 Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
 Output: 24
 Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
 Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
 Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
 Total of cherries: 12 + 12 = 24.
 Example 2:



 Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
 Output: 28
 Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
 Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
 Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
 Total of cherries: 17 + 11 = 28.
 Example 3:

 Input: grid = [[1,0,0,3],[0,0,0,3],[0,0,3,3],[9,0,3,3]]
 Output: 22
 Example 4:

 Input: grid = [[1,1],[1,1]]
 Output: 4
  

 Constraints:

 rows == grid.length
 cols == grid[i].length
 2 <= rows, cols <= 70
 0 <= grid[i][j] <= 100
 
 */
#include <vector>

using std::vector;

class CherryPickupII {
    
public:
    
    int doit_dp(vector<vector<int>>& grid) {
        
        auto m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> cache(m, vector<vector<int>>(n, vector<int>(n, -1)));
        
        std::function<int(int, int, int)> dp = [&](int r, int c1, int c2) -> int {
            

            if (r == m)
                return 0;
            
            if (cache[r][c1][c2] != -1)
                return cache[r][c1][c2];
            
            auto maxv = 0;
            for (auto i = -1; i < 2; i++) {
                for (auto j = -1; j < 2; j++) {
                    int x = c1 + i, y = c2 + j;
                    if (x < 0 || y < 0 || x >= n || y >= n)
                        continue;
                    maxv = std::max(maxv, dp(r+1, x, y));
                }
            }
            
            maxv += c1 == c2 ? grid[r][c1] : (grid[r][c1] + grid[r][c2]);
            cache[r][c1][c2] = maxv;
            return maxv;
        };
        
        return dp(0, 0, n-1);
    }
    
    
    int dp1[70][70][70] = {};
    int doit_dp_1(vector<vector<int>>& grid) {
        memset(dp1, -1, sizeof(dp1));
        int m = grid.size(), n = grid[0].size();
        return dfs(grid, m, n, 0, 0, n - 1);
    }
    
    int dfs(vector<vector<int>>& grid, int m, int n, int r, int c1, int c2) {
        if (r == m)
            return 0; // Reach to bottom row
        if (dp1[r][c1][c2] != -1)
            return dp1[r][c1][c2];
        
        int ans = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int nc1 = c1 + i, nc2 = c2 + j;
                if (nc1 >= 0 && nc1 < n && nc2 >= 0 && nc2 < n) {
                    ans = std::max(ans, dfs(grid, m, n, r + 1, nc1, nc2));
                }
            }
        }
        int cherries = c1 == c2 ? grid[r][c1] : grid[r][c1] + grid[r][c2];
        return dp1[r][c1][c2] = ans + cherries;
    }
    
    int doit_dp_2(vector<vector<int>>& grid) {
        
        const int r = grid.size(), c = grid[0].size();
        vector<vector<vector<int>>> dp(r+2, vector<vector<int>>(c+2, vector<int>(c+2, 0)));
        
        for (auto i = r; i > 0; i--) {
            for (auto c1 = 1; c1 <= c; c1++) {
                for (auto c2 = 1; c2 <= c; c2++) {
                    
                    const int cur = grid[i-1][c1-1] + (c1 != c2) * grid[i-1][c2-1];
                    int& ans = dp[i][c1][c2];
                    
                    for (int d1 = -1; d1 < 2; d1++) {
                        for (int d2 = -1; d2 < 2; d2++) {
                            ans = std::max(ans, cur + dp[i+1][c1+d1][c2+d2]);
                        }
                    }
                }
            }
        }
        
        return dp[1][1][c];
    }

    int doit_dp_3(vector<vector<int>>&& grid) {
        
        const int r = grid.size(), c = grid[0].size();
        vector<vector<vector<int>>> dp(r+2, vector<vector<int>>(c+2, vector<int>(c+2, 0)));
        
        for (auto i = r; i > 0; i--) {
            for (auto c1 = 1; c1 <= std::min(i, c); c1++) {
                for (auto c2 = std::max(c-i, 1); c2 <= c; c2++) {
                    
                    const int cur = grid[i-1][c1-1] + (c1 != c2) * grid[i-1][c2-1];
                    int& ans = dp[i][c1][c2];
                    
                    for (int d1 = -1; d1 < 2; d1++) {
                        for (int d2 = -1; d2 < 2; d2++) {
                            ans = std::max(ans, cur + dp[i+1][c1+d1][c2+d2]);
                        }
                    }
                }
            }
        }
        
        return dp[1][1][c];
    }
};


void test_1463_cherry_pickupII() {
    
    CherryPickupII().doit_dp_3(vector<vector<int>>{{3,1,1}, {2,5,1}, {1,5,5}, {2,1,1}});
    
}
