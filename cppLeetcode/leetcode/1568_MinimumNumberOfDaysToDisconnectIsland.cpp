/*
 
 1568. Minimum Number of Days to Disconnect Island
 
 
 Given a 2D grid consisting of 1s (land) and 0s (water).  An island is a maximal 4-directionally (horizontal or vertical) connected group of 1s.

 The grid is said to be connected if we have exactly one island, otherwise is said disconnected.

 In one day, we are allowed to change any single land cell (1) into a water cell (0).

 Return the minimum number of days to disconnect the grid.

  

 Example 1:



 Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
 Output: 2
 Explanation: We need at least 2 days to get a disconnected grid.
 Change land grid[1][1] and grid[0][2] to water and get 2 disconnected island.
 Example 2:

 Input: grid = [[1,1]]
 Output: 2
 Explanation: Grid of full water is also disconnected ([[1,1]] -> [[0,0]]), 0 islands.
 Example 3:

 Input: grid = [[1,0,1,0]]
 Output: 0
 Example 4:

 Input: grid = [[1,1,0,1,1],
                [1,1,1,1,1],
                [1,1,0,1,1],
                [1,1,0,1,1]]
 Output: 1
 Example 5:

 Input: grid = [[1,1,0,1,1],
                [1,1,1,1,1],
                [1,1,0,1,1],
                [1,1,1,1,1]]
 Output: 2
  

 Constraints:

 1 <= grid.length, grid[i].length <= 30
 grid[i][j] is 0 or 1.
 
 */
#include <vector>


using std::vector;


class MinimumUNumberToDisconnectIsland {
    
public:
   const int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    int dfs(int x, int y, int px, int py) {
        int res = INT_MAX;
        for (int i = 0; i < 4; ++i) {
            int xx = x + dirs[i][0];
            int yy = y + dirs[i][1];
            if (xx < 0 || xx >= n || yy < 0 || yy >= m || g[xx][yy] != 1)
                continue;
            if (xx == px && yy == py)
                continue;
            if (depth[xx][yy] != -1) {
                res = std::min(res, depth[xx][yy]);
            } else {
                depth[xx][yy] = depth[x][y] + 1;
                int ret = dfs(xx, yy, x, y);
                if (ret == -1)
                    return -1;
                res = std::min(res, ret);
            }
        }
        return (res > depth[x][y]) ? -1 : std::min(depth[x][y], res);
    }
    
    int minDays(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();
        if (n == 1 && m == 1)
            return 0;
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        int ax, ay;
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (vis[i][j])
                    continue;
                if (grid[i][j] == 1) {
                    if (cnt)
                        return 0;
                    ax = i, ay = j;
                    vector<std::pair<int, int>> bfs = {{i, j}};
                    vis[i][j] = true;
                    ++cnt;
                    while (!bfs.empty()) {
                        int x = bfs.back().first;
                        int y = bfs.back().second;
                        bfs.pop_back();
                        for (int k = 0; k < 4; ++k) {
                            int xx = x + dirs[k][0];
                            int yy = y + dirs[k][1];
                            if (xx < 0 || xx >= n || yy < 0 || yy >= m || vis[xx][yy] || grid[xx][yy] != 1)
                                continue;
                            vis[xx][yy] = true;
                            ++cnt;
                            bfs.push_back({xx, yy});
                        }
                    }
                }
            }
        }
        if (cnt == 0)
            return 0;
        if (cnt == 2)
            return 2;
        g = grid;
        depth = vector<vector<int>>(n, vector<int>(m, -1));
        depth[ax][ay] = 0;
        if (dfs(ax, ay, -1, -1) == -1)
            return 1;
        return 2;
    }
    
    int n, m;
    vector<vector<int>> g;
    vector<vector<int>> depth;
};
