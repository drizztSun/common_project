/*
 
 200. Number of Islands
 
 Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
 An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 You may assume all four edges of the grid are all surrounded by water.

 Example 1:

 Input:
 11110
 11010
 11000
 00000

 Output: 1
 Example 2:

 Input:
 11000
 11000
 00100
 00011

 Output: 3
 
 */

#include <vector>
#include <queue>
#include <functional>
#include <unordered_set>
#include <unordered_map>

using std::unordered_map;
using std::unordered_set;
using std::queue;
using std::vector;


class NumIslands {

    /*
        200.Number-of-Islands
        BFS的模板
        for (int i=0; i<N; i++)  // 遍历所有元素
        {
            if (Yes) {q.push(i);}  // 符合条件的话，加入新元素至空队列
            while (!q.empty()) 
            {
                    x = q.front();   //队首弹出一个元素
                    q.pop();
                    x1 = adjacent(x); // 每出列一个元素，则入列其相邻元素
                    if (visited(x1)==0) 
                        q.push(x1);
            }
        }
        DFS的模板
        for (int i=0; i<N; i++)  // 遍历所有元素
        {
            if (No) continue  // 不符合条件的话忽略
            visited[i]=1;
            explore(grid, visited, i); 
        }

        void explore(grid, visited, i)
        {
            for (int k=0; k<4; k++)
            {
                int m = ... //寻找相邻元素
                if (Yes)    //满足条件的话，就从m开始递归
                {
                visited[m]=1;
                explore(grid, visited, m);           
                }
            }
        }
        Union Find
        将坐标(i,j)转化为标量值的index=i*N+j。

        每遍历到一个点，查看其邻接的四个点，依次尝试做Union。每个聚类集合，其共有的Father用最小的横纵坐标来表述。
    */
    int numIslands(vector<vector<char>>& grid) 
    {
        int M=grid.size();
        if (M==0) return 0;
        int N=grid[0].size();
        auto visited=vector<vector<int>>(M,vector<int>(N,0));
        auto dir=vector<std::pair<int,int>>{{0,1},{0,-1},{1,0},{-1,0}};
        
        int count=0;
        queue<std::pair<int,int>>q;
        for (int i=0; i<M; i++)
         for (int j=0; j<N; j++)
         {
             if (grid[i][j]=='0' || visited[i][j]==1) continue;
             
             visited[i][j]=1;
             q.push({i,j});
             count++;
             
             while (!q.empty())
             {
                 
                 for (int k=0; k<4; k++)
                 {
                     int m=q.front().first+dir[k].first;
                     int n=q.front().second+dir[k].second;
                     if (m>=0 && m<M && n>=0 && n<N && visited[m][n]==0 && grid[m][n]=='1')
                     {
                         q.push({m,n});
                         visited[m][n]=1;
                     }
                 }
                 q.pop();
             }
         }
         
         return count;
        
    }

    int M;
    int N;
    vector<std::pair<int,int>> dir = vector<std::pair<int,int>>{{0,1},{0,-1},{1,0},{-1,0}};
    
public:
    int numIslands(vector<vector<char>>& grid) 
    {
        M=grid.size();
        if (M==0) return 0;
        N=grid[0].size();
        auto visited=vector<vector<int>>(M,vector<int>(N,0));
        
        int count=0;
        
        for (int i=0; i<M; i++)
         for (int j=0; j<N; j++)
         {
             if (grid[i][j]=='0' || visited[i][j]==1)  continue;
             
             visited[i][j]=1;
             explore(grid,visited,i,j);
             count++;
         }
         
         return count;
        
    }
    
    void explore(vector<vector<char>>& grid, vector<vector<int>>& visited, int i, int j)
    {
        for (int k=0; k<4; k++)
        {
            int m=i+dir[k].first;
            int n=j+dir[k].second;
            
            if (m>=0 && m<M && n>=0 && n<N && grid[m][n]=='1' && visited[m][n]==0)
            {
                visited[m][n]=1;
                explore(grid,visited,m,n);
            }
        }
        return;
    }

    unordered_map<int,int>Father;
    int M;
    int N;
    public:
    int numIslands(vector<vector<char>>& grid)
    {
        M=grid.size();
        if (M==0) return 0;
        N=grid[0].size();
        for (int i=0; i<M; i++)
         for (int j=0; j<N; j++)
         {
             Father[i*N+j]=i*N+j;
         }

        vector<std::pair<int,int>>dir={{1,0},{-1,0},{0,1},{0,-1}};
        for (int i=0; i<M; i++)
         for (int j=0; j<N; j++)
         {
             if (grid[i][j]=='0')
                 continue;
             
             for (int k=0; k<4; k++)
             {
                 int x=i+dir[k].first;
                 int y=j+dir[k].second;
                 if (x<0||x>=M||y<0||y>=N)
                     continue;
                 if (grid[x][y]=='0')
                     continue;                 
                 if (FindSet(x*N+y)!=FindSet(i*N+j))
                     Union(x*N+y,i*N+j);
             }
         }    
        
        unordered_set<int>Set;
        for (int i=0; i<M; i++)
         for (int j=0; j<N; j++)
         {
             if (grid[i][j]=='0') continue;
             Set.insert(FindSet(i*N+j));
         }
        
        return Set.size();

    }
    
    int FindSet(int x)
    {
        if (x!=Father[x])
            Father[x]=FindSet(Father[x]);
        return Father[x];
    }
    
    void Union(int x, int y)
    {
        x=Father[x];
        y=Father[y];
        bool flag;
        if (x/N<y/N)
            flag=true;
        else if (x/N==y/N && x%N<=y%N)
            flag=true;
        else
            flag=false;

        if (flag)
            Father[y]=x;
        else
            Father[x]=y;
    }

public:

    
    struct DSU {
        
        vector<int> parent_;
        
        DSU(int n) : parent_(n, 0) {
            for (int i = 0; i < n; i++)
                parent_[i] = i;
        }
        
        int Find(int a) {
            while (parent_[a] != a) {
                parent_[a] = parent_[parent_[a]];
                a = parent_[a];
            }
            return a;
        }
        
        void Union(int a, int b) {
            int pa = Find(a);
            int pb = Find(b);
            
            parent_[pa] = pb;
        }
    };

    int doit_disjoint(vector<vector<char>>&& grid) {
        if (grid.empty())
            return 0;
        
        int N = grid.size(), M = grid[0].size();
        DSU dsu(N * M);
        
        for (int i = 0; i < N; i++)
            for (int j =0; j < M; j++) {
                if (grid[i][j] == '1') {
                    int base = i * M + j;
                    vector<std::pair<int, int>> buf;
                    buf.push_back({i, j});
                    
                    while (!buf.empty()) {
                        int x = buf.back().first, y = buf.back().second;
                        buf.pop_back();
                        
                        grid[x][y] = '2';
                        for (auto c : vector<std::pair<int, int>>{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}) {
                            int x1 = x + c.first, y1 = y + c.second;
                            if (x1 > -1 && x1 < N && y1 > -1 && y1 < M && grid[x1][y1] == '1') {
                                dsu.Union(x1 * M + y1, base);
                                buf.push_back({x1, y1});
                            }
                        }
                    }
                }
            }
        
        int res = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (grid[i][j] == '2' && dsu.Find(i * M + j) == i * M + j)
                    res++;
        
        return res;
    }
    
    int doit_dfs(vector<vector<char>>& grid) {
        int n = grid.size();
        if (n == 0) return 0;

        int m = grid[0].size();
        if (m == 0) return 0;

        std::function<void(int, int)> dfs = [&](int i, int j){
            if (i < 0 || i == n || j < 0 || j == m) return;

            if (grid[i][j]=='0') return;

            grid[i][j]='0';
            dfs(i-1, j);
            dfs(i, j-1);
            dfs(i, j+1);
            dfs(i+1, j);
        };

        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '1')
                    res++;
                dfs(i, j);
            }
        }

        return res;
    }

    int doit_bfs(vector<vector<char>>&& grid) {

        int m = grid.size();
        if (m == 0) return 0;

        int n = grid[0].size();
        if (n == 0) return 0;

        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {

                if (grid[i][j] != '1') continue;
                
                res++;
                queue<int> buf;
                buf.push(i*n+j);
                grid[i][j] = '2';

                while (!buf.empty()) {

                    int cur = buf.front();
                    buf.pop();
                    int x = cur/n, y = cur%n;

                    for (auto delta : vector<std::pair<int, int>>{{0, -1}, {0, 1}, {1, 0}, {-1, 0}}) {
                        
                        int x1 = x + delta.first, y1 = y + delta.second;
                        
                        if (x1 < 0 || x1 >= m || y1 < 0 || y1 >= n || grid[x1][y1] != '1') continue;

                        grid[x1][y1] = '2';
                        
                        buf.push(x1 * n + y1);
                    }
                }
            }
        }
        return res;
    }
};