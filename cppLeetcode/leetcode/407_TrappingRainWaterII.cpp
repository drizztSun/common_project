/*
 407. Trapping Rain Water II
 
 Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.

 Example:

 Given the following 3x6 height map:
 [
   [1,4,3,1,3,2],
   [3,2,1,3,2,4],
   [2,3,3,2,3,1]
 ]

 Return 4.
 
 */

#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>


using std::vector;
using std::priority_queue;
using std::greater;


class TrapRainWater {
public:
    int doit_heap(vector<vector<int>>&& heightMap) {
        
        if (heightMap.empty() || heightMap[0].empty())
            return 0;
        
        auto M = heightMap.size(), N = heightMap[0].size();
        vector<vector<bool>> seen(M, vector<bool>(N, false));
        priority_queue<std::pair<int, std::pair<int, int>>> heights;
        
        
        for (int i = 0; i < M; i++) {
            heights.push({-heightMap[i][0], {i, 0}});
            heights.push({-heightMap[i][N-1], {i, N-1}});
            seen[i][0] = true;
            seen[i][N-1] = true;
        }
        
        for (int j = 0; j < N; j++) {
            heights.push({-heightMap[0][j], {0, j}});
            heights.push({-heightMap[M-1][j], {M-1, j}});
            seen[0][j] = true;
            seen[M-1][j] = true;
        }
        
        int res = 0;
        vector<vector<int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!heights.empty()) {
            auto c = heights.top();
            int height = -c.first, i = c.second.first, j = c.second.second;
            heights.pop();
            for (auto& step : directions) {
                int x = i + step[0], y = j + step[1];
                if (x >= 0 && x < M && y >= 0 && y < N && !seen[x][y]) {
                    seen[x][y] = true;
                    res += height > heightMap[x][y] ? height - heightMap[x][y] : 0;
                    heights.push({-std::max(height, heightMap[x][y]), {x, y}});
                }
            }
        }
        
        return res;
    }
    
    int trapRainWater(vector<vector<int>>& heightMap) {
        
        typedef std::pair<int,int> pr;
        
        int n = heightMap.size();
        
        if(n==0) return 0;
        
        int m = heightMap[0].size();
        
        vector<vector<int>> vis(n, vector<int> (m,0));
        priority_queue<pr, vector<pr>, greater<pr>> q;
        
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(!(i==0 || i==n-1 || j==0 || j==m-1))
                    continue;
                q.push({heightMap[i][j],i*m+j});
                vis[i][j] = 1;
                
            }
        }
        
        int row[] = {0,-1,1,0};
        int col[] = {1,0,0,-1};
        
        int ans=0, maxm = 0;
        
        while(!q.empty()) {
            
            pr p = q.top();
            q.pop();
            
            int h = p.first, x = (p.second)/m, y = (p.second)%m;
            maxm = std::max(h, maxm);
            
            for(int i=0;i<4;i++){
                
                int nx = x+row[i], ny = y+col[i];
                if(nx>=0 && nx<n && ny>=0 && ny<m && (vis[nx][ny]==0)){
                        
                    if(heightMap[nx][ny]<maxm)
                        ans += maxm-heightMap[nx][ny];
                    q.push({heightMap[nx][ny],nx*m+ny});
                    vis[nx][ny] = 1;
                }
            }
            
        }
        
        return ans;
        
    }
};

void test_407_TrappingRainWaterII() {
    
    TrapRainWater().doit_heap(vector<vector<int>>{{1,4,3,1,3,2},{3,2,1,3,2,4},{2,3,3,2,3,1}});
}
