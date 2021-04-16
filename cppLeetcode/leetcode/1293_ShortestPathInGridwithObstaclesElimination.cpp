/*
1293. Shortest Path in a Grid with Obstacles Elimination


Given a m * n grid, where each cell is either 0 (empty) or 1 (obstacle). In one step, you can move up, down, left or right from and to an empty cell.

Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m-1, n-1) given that you can eliminate at most k obstacles. 
If it is not possible to find such walk return -1.

 

Example 1:

Input: 
grid = 
[[0,0,0],
 [1,1,0],
 [0,0,0],
 [0,1,1],
 [0,0,0]], 
k = 1
Output: 6
Explanation: 
The shortest path without eliminating any obstacle is 10. 
The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
 

Example 2:

Input: 
grid = 
[[0,1,1],
 [1,1,1],
 [1,0,0]], 
k = 1
Output: -1
Explanation: 
We need to eliminate at least two obstacles to find such a walk.
 

Constraints:

grid.length == m
grid[0].length == n
1 <= m, n <= 40
1 <= k <= m*n
grid[i][j] == 0 or 1
grid[0][0] == grid[m-1][n-1] == 0

*/


#include <vector>
using std::vector;


class ShortestPathInGrid {

    /*
        1293.Shortest-Path-in-a-Grid-with-Obstacles-Elimination
        如果是不允许穿越障碍，那么我们用通常的BFS的做法，就可以记录到达每个位置(i,j)所需要的最短步数dp[i][j].但是现在允许穿越障碍，到达(i,j)的最短步数就要有所区分：

        O X O O
        O X O O
        O O O O
        在上面的例子中，如果不穿越障碍，从(0,0)到(0,2)需要6步；但是如果允许穿越障碍，那么只需要2步。那么到底选择哪个更好呢？答案是说不准。前者使用的elemination次数少（可以留着给之后的步骤用），后者的实际步数更少。
        所以这两种状态我们都要记录下来。因此我们使用dp[i][j][k]表示，从(0,0)走到(i,j)，并且使用了k次障碍消除，所需要的最短步数。

        因为本题是允许上下左右移动，没有“无后效性”，所以dp[i][j][k]无法使用动态规划来转移，只能用BFS的暴力搜索来前进。
        比如，我们知道dp[i][j][k]=step，那么如果向右走一步到空地，就有dp[i][j+1][k]=step+1；但是特别注意，如果向右走一步是障碍的话，那么需要使用一次障碍消除，即dp[i][j+1][k+1]=step+1

        直到我们第一次走到dp[m-1][n-1][k]，并且k不大于K的时候，dp值就是最少的步骤。如果BFS进行了K轮还没有走到右下角，那么说明无解。
    */
    int visited[40][40][1601];|
    int shortestPath(vector<vector<int>>& grid, int K) 
    {
        int m = grid.size();
        int n = grid[0].size();
        
        queue<vector<int>>q;
        q.push({0,0,0});
        if (m==1 && n==1) return 0;        
        auto dir = vector<pair<int,int>>({{1,0},{-1,0},{0,1},{0,-1}});
        
        int step = 0;
        while (!q.empty())
        {
            int len = q.size();
            while (len--)
            {
                int x = q.front()[0];
                int y = q.front()[1];
                int k = q.front()[2];
                q.pop();
            
                for (int t=0; t<4; t++)
                {
                    int i = x+dir[t].first;
                    int j = y+dir[t].second;
                    if (i<0||i>=m||j<0||j>=n) continue;
                    
                    if (i==m-1 && j==n-1) return step+1;
                
                    if (grid[i][j]==1)
                    {
                        if (k==K) continue;
                        if (visited[i][j][k+1]==1) continue;
                        visited[i][j][k+1] = 1;
                        q.push({i,j,k+1});
                    }
                    else
                    {
                        if (visited[i][j][k]==1) continue;
                        visited[i][j][k] = 1;
                        q.push({i,j,k});
                    }
                }
            }            
            step++;            
        }        
        return -1;
    }

public:

    int doit_bfs(vector<vector<int>>& grid, int k) {

        int m = grid.size(), n = grid[0].size();
        queue<vector<int>> qu;
        qu.push({0, 0, grid[0][0]==1});
        int steps = 0;
        vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(k+1, false)));
        visited[0][0] = vector<bool>(k+1, true);
        int dir[5] = {-1, 0, 1, 0, -1};
        
        while (!qu.empty()) {
            
            int sz = qu.size();
            
            while (sz--) {
                
                auto it = qu.front(); qu.pop();
                int x = it[0], y = it[1], r = it[2];
                
                if (x == m-1 && y == n-1) return steps;
                
                for (int i = 0; i < 4; i++) {
                    
                    int nx = x+dir[i], ny = y+dir[i+1];
                    
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n ) continue;
                    
                    int l = grid[nx][ny];
                    
                    if (r+l == k+1 || visited[nx][ny][r+l]) continue;
                    
                    visited[nx][ny][r+l] = true;
                    
                    qu.push({nx, ny, r+l});
                }
            }
            steps++;
        }
        
        return -1;
        
    }

    int shortestPath(vector<vector<int>>& grid, int k) {
        int rows=grid.size(), cols=grid[0].size();
        int minSteps = max(0,rows+cols-2), obstacles=minSteps-1, minStepsNextRound=minSteps;
        if(obstacles<=k) return minSteps; // take a shortcut if we can afford it

        vector<vector<int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};
        list<vector<int>> togo; togo.push_back({0,0,k}); // BFS: {row, col, remaining k}
        vector<int> visited(rows*cols, -1); // position -> k remaining
        visited[0]=k;
        int steps=0;
        
        while(togo.size()) {
            steps++;
			minSteps=minStepsNextRound;
            for(int sz=togo.size();sz>0;sz--) {
                int r=togo.front()[0], c=togo.front()[1], k=togo.front()[2];
                togo.pop_front();
                for(auto& d:dirs) {
                    int rr=r+d[0], cc=c+d[1];
                    if(rr<0 || rr>=rows || cc<0 || cc>=cols) continue;
                    int kk = k-grid[rr][cc];
                    if(visited[rr*cols+cc]>=kk) continue; // have been here passing less obstacles

                    // maybe we can take a shortcut and go straight to the goal
					// but jump only from the point closest to the target
                    int stepsToTarget = rows-rr-1+cols-cc-1;
                    if(stepsToTarget-1<=kk && stepsToTarget==minSteps-1) return steps+stepsToTarget;
                    togo.push_back({rr,cc,kk});
                    visited[rr*cols+cc]=kk;
					minStepsNextRound=min(minStepsNextRound,stepsToTarget);
                }
            }
        }
        return -1;
    }
};