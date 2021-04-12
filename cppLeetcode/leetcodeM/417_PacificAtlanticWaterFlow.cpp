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

    /*
            417.Pacific-Atlantic-Water-Flow 
        此题DFS和BFS都适用，但一般用DFS的递归写起来比BFS更简洁。

        void DFS(int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& visited)
        {
            vector<pair<int,int>>dir={{1,0},{-1,0},{0,-1},{0,1}};
            
            for (int k=0; k<4; k++)
            {
                visited[i][j]=1;
                int m=i+dir[k].first;
                int n=j+dir[k].second;

                if (m<0 || m==M || n<0 || n==N) continue;
                if (visited[m][n]==1) continue;
                if (matrix[m][n]<matrix[i][j]) continue;            
                
                DFS(m,n,matrix,visited);
            }
        }
    */
    int M,N;
public:
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) 
    {
        M=matrix.size();
        if (M==0) return {};
        N=matrix[0].size();
        
        auto pac=vector<vector<int>>(M,vector<int>(N,0));
        auto atl=vector<vector<int>>(M,vector<int>(N,0));
        
        for (int j=0; j<N; j++)
            DFS(0,j,matrix,pac);            
        for (int i=1; i<M; i++)
            DFS(i,0,matrix,pac);
        for (int j=0; j<N; j++)
            DFS(M-1,j,matrix,atl);
        for (int i=0; i<M-1; i++)
            DFS(i,N-1,matrix,atl);
        
        vector<pair<int, int>>results;
        for (int i=0; i<M; i++)
            for (int j=0; j<N; j++)
            {
                if (atl[i][j]==1 && pac[i][j]==1)
                    results.push_back({i,j});
            }
        return results;
    }
    
    void DFS(int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& visited)
    {
        vector<pair<int,int>>dir={{1,0},{-1,0},{0,-1},{0,1}};
        
        for (int k=0; k<4; k++)
        {
            visited[i][j]=1;
            int m=i+dir[k].first;
            int n=j+dir[k].second;

            if (m<0 || m==M || n<0 || n==N) continue;
            if (visited[m][n]==1) continue;
            if (matrix[m][n]<matrix[i][j]) continue;            
            
            DFS(m,n,matrix,visited);
        }
    }

public:

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) 
    {
        int m = matrix.size();
        if (m==0) return {};
        int n = matrix[0].size();
        auto visited1 = vector<vector<int>>(m, vector<int>(n,0));
        auto visited2 = vector<vector<int>>(m, vector<int>(n,0));
        
        vector<pair<int,int>>starts;
        for (int i=0; i<m; i++)
            starts.push_back({i,-1});
        for (int j=0; j<n; j++)
            starts.push_back({-1,j});
        bfs(matrix, starts, visited1);
        
        starts.clear();
        for (int i=0; i<m; i++)
            starts.push_back({i,n});
        for (int j=0; j<n; j++)
            starts.push_back({m,j});
        bfs(matrix, starts, visited2);
        
        vector<vector<int>>rets;
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
                if (visited1[i][j]&&visited2[i][j])
                    rets.push_back({i,j});
        return rets;
    }
    
    void bfs(vector<vector<int>>& matrix, vector<pair<int,int>>&starts, vector<vector<int>>& visited)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        auto dir = vector<pair<int,int>>({{1,0},{-1,0},{0,1},{0,-1}});
        queue<pair<int,int>>q;
        for (auto x: starts) q.push(x);
        while (!q.empty())
        {
            auto [x,y] = q.front();
            q.pop();
            for (int k=0; k<4; k++)
            {
                int i = x+dir[k].first;
                int j = y+dir[k].second;
                if (i<0||i>=m||j<0||j>=n) continue;
                if (visited[i][j]) continue;
                if (x>=0&&x<m&&y>=0&&y<n && matrix[i][j]<matrix[x][y]) continue;
                visited[i][j] = 1;
                q.push({i,j});
            }
        }
    }


public:

    vector<vector<int>> doit_dfs(vector<vector<int>>& heights) {
        
        int m = heights.size(), n = heights[0].size();
        int dir[5] = {-1, 0, 1, 0, -1};
        vector<vector<int>> reachable(m, vector<int>(n, 0));
        
        std::function<void(int, int, vector<vector<int>>&, int)> dfs = [&](int i, int j, vector<vector<int>>& reachable, int type) {
            
            if (reachable[i][j] & type) return;
            
            reachable[i][j] ^= type;
            
            for (int k = 0; k < 4; k++) {
                
                int x = i + dir[k], y = j + dir[k+1];
                if (x < 0 || x >= m || y < 0 || y >= n || heights[x][y] < heights[i][j]) continue;
                dfs(x, y, reachable, type);
            }
        };
        
        
        for(int i = 0; i < m; i++) {
            dfs(i, 0, reachable, 1);
            dfs(i, n-1, reachable, 2);
        }
        
        for (int j = 0; j < n; j++) {
            dfs(0, j, reachable, 1);
            dfs(m-1, j, reachable, 2);
        }
        
        vector<vector<int>> res;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (reachable[i][j] == 3) res.push_back({i, j});
            }
        }
        
        return res;
    }

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