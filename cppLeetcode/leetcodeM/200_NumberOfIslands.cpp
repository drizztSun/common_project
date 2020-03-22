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
using std::vector;

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


class NumIslands {
public:
    int doit(vector<vector<char>>&& grid) {
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
    
    
    void dfs(vector<vector<char>>& grid, int i, int j, int n, int m){
        if (i<0 || i==n || j<0 || j==m) return;
        if (grid[i][j]=='0')
            return;
        grid[i][j]='0';
        dfs(grid, i-1, j, n, m);
        dfs(grid, i, j-1, n, m);
        dfs(grid, i, j+1, n, m);
        dfs(grid, i+1, j, n, m);
    }
    int numIslands(vector<vector<char>>& grid) {
        int n=grid.size();
        if (n==0)
            return 0;
        int m=grid[0].size();
        if (m==0)
            return 0;
        // vector<vector<int>> v(n, vector<int>(m, 0));
        int res=0;
        for (int i=0; i<n; ++i){
            for (int j=0; j<m; ++j){
                if (grid[i][j]=='1')
                    res++;
                dfs(grid, i, j, n, m);
            }
        }
        return res;
    }
};


void test_200_number_of_islands() {
    
    
    auto res1 = NumIslands().doit(vector<vector<char>>{
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    });

    auto res2 = NumIslands().doit(vector<vector<char>>{
        {'1','1','0','0','0'},
        {'1','1','0','1','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    });
    
    auto res3 = NumIslands().doit(vector<vector<char>>{
        {'1'},
        {'1'}
    });
    
    return;
}
