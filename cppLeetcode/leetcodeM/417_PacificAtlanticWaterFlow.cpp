/*
417. Pacific Atlantic Water Flow

Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

Note:

The order of returned grid coordinates does not matter.
Both m and n are less than 150.
 

Example:

Given the following 5x5 matrix:

  Pacific ~   ~   ~   ~   ~ 
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic

Return:

[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).

*/

#include <vector>
#include <functional>

using std::vector;


class PacificAtlanticWaterFlow {

public:

    vector<vector<int>> doit_dfs(vector<vector<int>>& matrix) {
        
        int m = matrix.size(), n = matrix[0].size();

        vector<vector<bool>> pac_visible(m, vector<bool>(n, false));
        vector<vector<bool>> alt_visible(m, vector<bool>(n, false));

        int direct[5] = {-1, 0, 1, 0, -1};

        std::function<void(int, int, vector<vector<bool>>&)> dfs = [&](int i, int j, vector<vector<int>>& visited) {

            visited[i][j] = true;

            for (int k = 0; k < 4; k++) {
                int x = i + direct[k], y = j + direct[k+1];
                if (x < 0 || x == m || y < 0 || y == n || visited[x][y] || matrix[x][y] > matrix[i][j])
                    continue;
                dfs(x, y, visited);
            }
        };

        for (int i = 0; i < m; i++) {
            dfs(i, 0, pac_visible);
            dfs(i, n-1, alt_visible);
        }

        for (int j = 0; j < n; j++) {
            dfs(0, j, pac_visible);
            dfs(m-1, j, alt_visible);
        }

        vector<vector<int>> ans;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pac_visible[i][j] && alt_visible[i][j])
                    ans.push_back({i, j});
            }
        }

        return ans;
    }
};