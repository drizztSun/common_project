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

    /*
        1568.Minimum-Number-of-Days-to-Disconnect-Island
        此题乍看没有头绪。但是考虑到这只是一个6分题，必然有巧解。

        首先想到的是，如果一个格子最多只会被四个邻接陆地包围，所以答案不会超过4.

        其次，想到肯定不会所有的格子都被四个邻接陆地包围，肯定会有“边缘”的格子，有一边是邻接水域或者边界。对于这个格子，我们只要断开另外三面陆地连接即可。所以答案不会超过3.

        再看一下例子，发现sample里的答案没有超过2的。细想一下，确实无论什么几何形状，都会有“角落”的格子。所谓的“角落”，指的是只有两个邻接点是与大陆相连。所以答案又可以缩小为不会超过2.

        如今答案的可能只有0，1，2。答案是否为零很好判断，扫一遍全局看是否只有一个岛。答案是否为1呢？如果只要删除一块陆地就能使得岛的数量大于等于2，那么我们就遍历每一块陆地，假设删除它，再查看一下剩下的地形的岛的数量即可。
        遍历一块“删除之地”大概是o(900)，然后每次搜索全局数一下剩余岛的个数也是o(900)，总共的时间复杂度是o(810000)，是可以接受的。如果答案不为1，那么答案就肯定是2了。

        所以本题的本质就是一个暴力枚举+BFS搜索判断岛数量。
    */
public:

    int doit_(vector<vector<int>>& grid) 
    {
        int m = grid.size(), n = grid[0].size();

        auto islands = [&]() -> int{

            auto dir = vector<pair<int,int>>({{1,0},{-1,0},{0,1},{0,-1}});
            auto visited = vector<vector<int>>(m, vector<int>(n,0));
            int count = 0;

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++)
                {
                    if (grid[i][j]==0) continue;
                    if (visited[i][j]==1) continue;
                    
                    queue<pair<int,int>> q;
                    q.push({i,j});
                    visited[i][j] = 1;
                                    
                    count++;
                    
                    while (!q.empty())
                    {
                        int x = q.front().first;
                        int y = q.front().second;
                        q.pop();
                        
                        for (int k=0; k<4; k++)
                        {
                            int a = x + dir[k].first;
                            int b = y + dir[k].second;
                            
                            if (a<0 || a>=m || b<0 || b>=n) continue;

                            if (grid[a][b] == 0) continue;
                            if (visited[a][b]==1) continue;

                            q.push({a,b});
                            visited[a][b] = 1;                        
                        }
                    }
                    
                    if (count == 2) return 2;
                }
            }
            return count;
        };
        
        int count = islands(grid);
        if (count > 1) return 0;
        
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                if (grid[i][j]==0) continue;
                grid[i][j] = 0;
                int count = islands(grid);
                if (count > 1) return 1;
                grid[i][j] = 1;
            }
        
        return 2;        
    }
    
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
