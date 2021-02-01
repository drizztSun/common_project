/*
 
 1091. Shortest Path in Binary Matrix
 
 In an N by N square grid, each cell is either empty (0) or blocked (1).

 A clear path from top-left to bottom-right has length k if and only if it is composed of cells C_1, C_2, ..., C_k such that:

 Adjacent cells C_i and C_{i+1} are connected 8-directionally (ie., they are different and share an edge or corner)
 C_1 is at location (0, 0) (ie. has value grid[0][0])
 C_k is at location (N-1, N-1) (ie. has value grid[N-1][N-1])
 If C_i is located at (r, c), then grid[r][c] is empty (ie. grid[r][c] == 0).
 Return the length of the shortest such clear path from top-left to bottom-right.  If such a path does not exist, return -1.



 Example 1:

 Input: [[0,1],[1,0]]


 Output: 2

 Example 2:

 Input: [[0,0,0],[1,1,0],[1,1,0]]


 Output: 4



 Note:

 1 <= grid.length == grid[0].length <= 100
 grid[r][c] is 0 or 1
 
 
 */
#include <vector>
#include <queue>

using std::queue;
using std::vector;


class ShortestPathBinaryMatrix {
public:
    
    int doit_bfs(vector<vector<int>>& grid) {
        
        auto m = grid.size(), n = grid[0].size();
        queue<std::tuple<int, int, int>> que;
        if (grid[0][0] != 0)
            return -1;
        
        que.push({0, 0, 0});
        int dxx[8]={0,0,1,1,1,-1,-1,-1};
        int dyy[8]={1,-1,0,1,-1,0,1,-1};
        
        while (!que.empty()) {
            
            auto c = que.front();
            auto path = std::get<0>(c), x = std::get<1>(c), y = std::get<2>(c);
            que.pop();
            if (x == m-1 && y == n-1)
                return path + 1;
            
            for (auto i = 0; i < 8; i++) {
                
                auto x1 = x + dxx[i], y1 = y + dyy[i];
                
                if (x1 < 0 || x1 >= m || y1 < 0 || y1 >= n)
                    continue;
                
                if (grid[x1][y1] == 0) {
                    que.push({path+1, x1, y1});
                    grid[x1][y1] = 1;
                }
            }
        }
        
        return -1;
    }
    
    int doit_bfs_1(vector<vector<int>>& grid) {
        
        auto m1=grid.size(), m2=grid[0].size();
        queue<int> q;
        int level=0;
        int dxx[8]={0,0,1,1,1,-1,-1,-1};
        int dyy[8]={1,-1,0,1,-1,0,1,-1};
        
        if(grid[0][0]==0){
            q.push(0);
            grid[0][0]=1;
        }
        
        while(!q.empty())
        {
            auto n = q.size();
            level++;
            
            for(int i=0; i<n; i++)
            {
                int a=q.front();
                q.pop();
                
                int x=a/1000;
                int y=a%1000;
                
                if(x==m1-1 && y==m2-1)
                    return level;
                
                
                for(int j=0;j<8;j++)
                {
                    int dx=dxx[j],dy=dyy[j];
                    if(x+dx>=0 && y+dy>=0 && x+dx<m1 && y+dy<m2 && grid[x+dx][y+dy]==0){
                        grid[x+dx][y+dy]=1;
                        int b=x+dx;b*=1000;b+=y+dy;
                        q.push(b);
                        
                    }
                }
            }
        }
        
        return -1;
    }
};
