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
      
    typedef vector<int> VI;  // {h,x,y}

    /*
        407.Trapping-Rain-Water-II
        注意此题和一维的版本不一样，无法使用DP的思想。

        我们将矩阵所有的边界格子加入一个优先队列，里面的格子按照海拔从低到高排列。这些边界格子相当于闭合的堤岸，围了中间的区域。

        我们想象一下海平面逐渐上涨的过程，当海平面cur上涨到优先队列里最矮的那个元素时，就相当于从那里冲破了堤岸，拓展进了内陆、同时会有新的堤岸格子加入队列。
        如果加入队列的这一系列新格子高度都小于cur，那么它们其实也被淹没了，洪水可以基于它们的位置继续向四周扩展。这个“泛滥”的过程直到队列里面的所有元素高度（也就是首元素）都大于cur为止。在上面的过程中，所有被“淹没”的格子(i,j)，计算cur-h(i,j)就是该点的储水量。

        然后重复上述的过程，再次想象海平面cur上涨到队列最矮元素的高度，这样就再一次“决堤”，这个泛滥的过程依然是在各地“储水”的机会，直至队列里面的堤岸都高于海平面cur位置，“泛滥”结束。

        以上过程中，所有被“决堤”或者被“淹没”的格子，都要做标记，不用重复入队列。直至队列为空停止。
    */
    int doit_heap_dijkstra(vector<vector<int>>& heightMap) 
    {
        int m = heightMap.size();
        int n = heightMap[0].size();
        
        priority_queue<VI, vector<VI>, greater<>>pq;
        auto visited = vector<vector<int>>(m, vector<int>(n,0));
        auto dir = vector<std::pair<int,int>>({{1,0},{-1,0},{0,1},{0,-1}});
        
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
                if (i==0||i==m-1||j==0||j==n-1)
                {
                    pq.push({heightMap[i][j],i,j});
                    visited[i][j] = 1;
                }
                    
        
        int ret = 0;
        int cur = INT_MIN;
        while (!pq.empty())
        {
            int h = pq.top()[0];
            int x = pq.top()[1];
            int y = pq.top()[2];
            pq.pop();
                        
            if (h>cur) cur = h;
            ret += cur - h;
            for (int k=0; k<4; k++)
            {
                int i = x+dir[k].first;
                int j = y+dir[k].second;
                if (i<0||i>=m||j<0||j>=n) continue;
                if (visited[i][j]) continue;
                visited[i][j] = 1;
                pq.push({heightMap[i][j],i,j});                
            }            
        }
        
        return ret;
    }

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
    
    int doit_minheap(vector<vector<int>>& heightMap) {
        
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