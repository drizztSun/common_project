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
using std::vector;

class UniquePathsIII {
    
    void search(vector<vector<int>>& grid, int i, int j, int ex, int ey, int num, vector<vector<int>>& seen, int& res) {
        
        if (i == ex && j == ey) {
            res += num == 0 ? 1 : 0;
            return;
        }
        
        for (auto& c : vector<std::pair<int, int>>{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}) {
            int x0 = c.first + i, y0 = c.second + j;
            if (x0 >= 0 && x0 < grid.size() && y0 >= 0 && y0 < grid[0].size() && grid[x0][y0] != -1 && seen[x0][y0] == 0) {
                seen[x0][y0] = 1;
                search(grid, x0, y0, ex, ey, num - 1, seen, res);
                seen[x0][y0] = 0;
                
            }
        }
    }
    
public:
    int doit(vector<vector<int>>&& grid) {
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
        search(grid, sx, sy, ex, ey, zero + 1, seen, res);
        return res;
    }
};


class UniquePathsIII1 {
    int res = 0;
public:
    int doit(vector <vector<int>> &grid) {
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
        }
        backtracking(grid, m, n, start_i, start_j, 0, target);
        return res;
    }

    void
    backtracking(vector <vector<int>> &grid, int m, int n, int i, int j, int count, int target) {
        if (i < 0 || i == m || j <0 || j == n || grid[i][j] == -1) {
            return;
        }
        if (grid[i][j] == 2 && count + 1 == target) {
            res++;
            return;
        }
        int backup = grid[i][j];
        grid[i][j] = -1;
        backtracking(grid, m, n, i + 1, j, count + 1, target);
        backtracking(grid, m, n, i - 1, j, count + 1, target);
        backtracking(grid, m, n, i, j + 1, count + 1, target);
        backtracking(grid, m, n, i, j - 1, count + 1, target);
        grid[i][j] = backup;
    }
};

void test_978_longest_turbulent_subarrayIII() {
    
    auto res1 = UniquePathsIII().doit(vector<vector<int>>{{1,0,0,0}, {0,0,0,0}, {0,0,2,-1}});
    
    auto res2 = UniquePathsIII().doit(vector<vector<int>>{{1,0,0,0}, {0,0,0,0}, {0,0,0,2}});
    
    auto res3 = UniquePathsIII().doit(vector<vector<int>>{{0, 1}, {2, 0}});
    
    return;
}
