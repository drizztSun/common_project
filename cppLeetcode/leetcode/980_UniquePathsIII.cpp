/*
 
 # 980. Unique Paths III

 # On a 2-dimensional grid, there are 4 types of squares:

 # 1 represents the starting square.  There is exactly one starting square.
 # 2 represents the ending square.  There is exactly one ending square.
 # 0 represents empty squares we can walk over.
 # -1 represents obstacles that we cannot walk over.
 # Return the number of 4-directional walks from the starting square to the ending square,
 # that walk over every non-obstacle square exactly once.


 # Example 1:

 # Input: [[1,0,0,0],
 #         [0,0,0,0],
 #         [0,0,2,-1]]
 # Output: 2
 # Explanation: We have the following two paths:
 # 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
 # 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

 # Example 2:

 # Input: [[1,0,0,0],
 #         [0,0,0,0],
 #         [0,0,0,2]]
 # Output: 4
 # Explanation: We have the following four paths:
 # 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
 # 2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
 # 3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
 # 4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

 # Example 3:

 # Input: [[0,1],[2,0]]
 # Output: 0
 # Explanation:
 # There is no path that walks over every empty square exactly once.
 # Note that the starting and ending square can be anywhere in the grid.

 */
#include <vector>
#include <functional>
using std::vector;

class UniquePathsIII {
    
public:

    /*
        Brute Force

        Time complexity: O(4^mn)
        Space complexity: O(m*n)
    */
    int doit_dfs(vector<vector<int>>&& grid) {
        int M = grid.size(), N = grid[0].size();
        int sx = 0, sy = 0;
        int ex = 0, ey = 0;
        int zero = 0;
        
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) {
                int v = grid[i][j];
                if (v == 1)
                    sx = i, sy = j;
                else if (v == 2)
                    ex = i, ey = j;
                else if (v == 0)
                    zero++;
            }
        
        int res = 0;
        vector<vector<int>> seen(grid.size(), vector<int>(grid[0].size(), 0));
        seen[sx][sy] = 1;

        std::function<void(int, int, int, int, int)> search = [&](int i, int j, int ex, int ey, int num) {
            
            if (i == ex && j == ey) {
                res += num == 0 ? 1 : 0;
                return;
            }
            
            for (auto& c : vector<std::pair<int, int>>{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}) {
                int x0 = c.first + i, y0 = c.second + j;
                if (x0 >= 0 && x0 < grid.size() && y0 >= 0 && y0 < grid[0].size() && grid[x0][y0] != -1 && seen[x0][y0] == 0) {
                    seen[x0][y0] = 1;
                    search(x0, y0, ex, ey, num - 1);
                    seen[x0][y0] = 0;
                }
            }
        };

        search(sx, sy, ex, ey, zero + 1);
        return res;
    }

    int doit_backtracking(vector <vector<int>> &grid) {
        int target = 0;
        int m = grid.size();
        int n = grid[0].size();
        int start_i = 0;
        int start_j = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != -1) {
                    target++;
                    if (grid[i][j] == 1) {
                        start_i = i;
                        start_j = j;
                    }
                }

            }
        };
        
        int res = 0;
        std::function<void(int, int, int, int, int, int)> backtracking = [&](int m, int n, int i, int j, int count, int target){
            if (i < 0 || i == m || j <0 || j == n || grid[i][j] == -1) return;

            if (grid[i][j] == 2 && count + 1 == target) {
                res++;
                return;
            }

            int backup = grid[i][j];
            grid[i][j] = -1;
            backtracking(m, n, i + 1, j, count + 1, target);
            backtracking(m, n, i - 1, j, count + 1, target);
            backtracking(m, n, i, j + 1, count + 1, target);
            backtracking(m, n, i, j - 1, count + 1, target);
            grid[i][j] = backup;
        };

        backtracking(m, n, start_i, start_j, 0, target);
        return res;
    }

    int doit_dfs_1(vector<vector<int>>&& grid) {    
        int sx = -1;
        int sy = -1;
        int n = 1;
        for (int i = 0; i < grid.size(); ++i)
        for (int j = 0; j < grid[0].size(); ++j)
            if (grid[i][j] == 0) ++n;
            else if (grid[i][j] == 1) { sx = j; sy = i; }

        std::function<int(int, int, int)> dfs = [&](int x, int y, int n) {
            if (x < 0 || x == grid[0].size() || 
                y < 0 || y == grid.size() || 
                grid[y][x] == -1) return 0;
            if (grid[y][x] == 2) return n == 0;    
            
            grid[y][x] = -1;
            int paths = dfs(x + 1, y, n - 1) + 
                        dfs(x - 1, y, n - 1) +
                        dfs(x, y + 1, n - 1) + 
                        dfs(x, y - 1, n - 1);
            grid[y][x] = 0;
            return paths;
        };
         
        return dfs(sx, sy, n);
    }

    /*
        Solution 2: DP

        Similar to 943. Find the Shortest Superstring

        dp[y][x][state] := # of path start from (x,y) with state

        state is a bit of map of modes to visit. 2^nm different states.

        for tx, ty in unvisited_neighbors(x, y, state):
            dp[y][x][state] += dp[y][x][state.unset(tx, ty)]
    
        Time complexity: O(m*n*2^nm) 400+ ms
        Space conplexity: O(m*n*2^mn)

        memory issues.
    */
    int doit_dp(vector<vector<int>>& grid) {
        const int n = grid.size();
        const int m = grid[0].size();
        const vector<int> dirs{-1, 0, 1, 0, -1};
        
        
        int sx = -1;
        int sy = -1;
        int state = 0;
        vector<vector<vector<short>>> cache(n, vector<vector<short>>(m, vector<short>(1 << n * m, -1)));
        auto key = [m](int x, int y) { return 1 << (y * m + x); };
        
        std::function<short(int, int, int)> dfs = [&](int x, int y, int state) {    
            if (cache[y][x][state] != -1) 
                return cache[y][x][state];

            if (grid[y][x] == 2) 
                return static_cast<short>(state == 0); 
            
            int paths = 0;
            for (int i = 0; i < 4; ++i) {
                const int tx = x + dirs[i];
                const int ty = y + dirs[i + 1];
                
                if (tx < 0 || tx == m || ty < 0 || ty == n || grid[ty][tx] == -1) continue;
                
                if (!(state & key(tx, ty))) continue;
                
                paths += dfs(tx, ty, state ^ key(tx, ty));
            }
            return cache[y][x][state] = paths;
        };
        
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < m; ++x)
                if (grid[y][x] == 0 || grid[y][x] == 2)
                    state |= key(x, y);
                else if (grid[y][x] == 1)
                    sx = x; sy = y;
        }
        return dfs(sx, sy, state);
  }
};

void test_978_longest_turbulent_subarrayIII() {
    
    auto res1 = UniquePathsIII().doit_dfs_1(vector<vector<int>>{{1,0,0,0}, {0,0,0,0}, {0,0,2,-1}});
    
    auto res2 = UniquePathsIII().doit_dfs_1(vector<vector<int>>{{1,0,0,0}, {0,0,0,0}, {0,0,0,2}});
    
    auto res3 = UniquePathsIII().doit_dfs_1(vector<vector<int>>{{0, 1}, {2, 0}});
    
    return;
}
