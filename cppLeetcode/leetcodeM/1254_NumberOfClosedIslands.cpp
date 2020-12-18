/*
1254. Number of Closed Islands

Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.

 

Example 1:



Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
Output: 2
Explanation: 
Islands in gray are closed because they are completely surrounded by water (group of 1s).
Example 2:



Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
Output: 1
Example 3:

Input: grid = [[1,1,1,1,1,1,1],
               [1,0,0,0,0,0,1],
               [1,0,1,1,1,0,1],
               [1,0,1,0,1,0,1],
               [1,0,1,1,1,0,1],
               [1,0,0,0,0,0,1],
               [1,1,1,1,1,1,1]]
Output: 2
 

Constraints:

1 <= grid.length, grid[0].length <= 100
0 <= grid[i][j] <=1


*/
#include <vector>

using std::vector;

class Solution {

public:
    
    bool ok = true;
    
    void dfs(vector<vector<int>>& a, int i, int j, vector<vector<bool>>& vis){

        if(i < 0 || j < 0 || i > a.size() - 1 || j > a[0].size() - 1 || a[i][j] == 1 || vis[i][j]){
            return;
        }

        if(i == a.size() - 1 || j == a[0].size() - 1 || i == 0 || j == 0){
            ok = false;
        }

        vis[i][j] = true;
        dfs(a, i + 1, j, vis);
        dfs(a, i - 1, j, vis);
        dfs(a, i, j + 1, vis);
        dfs(a, i, j - 1, vis);
    }
    
    int closedIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int result = 0;
        vector<vector<bool>> vis(n, vector<bool>(m, false));

        for(int i = 0;i<n;i++){
            for(int j = 0;j<m;j++){

                if(grid[i][j] == 0 && !vis[i][j]){

                    ok = true;
                    dfs(grid, i, j, vis);
                    if(ok)  
                        result++;
                }
            }
        }
        return result;
    }
};