/*
994. Rotting Oranges

You are given an m x n grid where each cell can have one of three values:

    . 0 representing an empty cell,
    . 1 representing a fresh orange, or
    . 2 representing a rotten orange.

Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

 

Example 1:


Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Example 2:

Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
Example 3:

Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 10
grid[i][j] is 0, 1, or 2.

*/
#include <vector>
#include <queue>

using std::vector;
using std::queue;


class OrangesRotting {

public:
    
    int doit_bfs(vector<vector<int>>& grid) {
        
        queue<std::pair<int, int>> qu;
        int fresh = 0;
        int m = grid.size(), n = grid[0].size();
        
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 2)
                    qu.push({i, j});
                else if (grid[i][j] == 1)
                   fresh++;
        
        int d[5] = {-1, 0, 1, 0, -1};
        int ans = 0;
        
        while (!qu.empty() && fresh > 0) {
            
            int size = qu.size();
            
            ans++;
            
            while (size--) {
                
                auto cur = qu.front();
                qu.pop();
                
                for (int i = 0; i < 4; i++) {
                    
                    int x = cur.first + d[i], y = cur.second + d[i+1];
                    
                    if(x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != 1) continue;
                    
                    grid[x][y] = 2;
                    fresh--;
                    qu.push({x, y});
                }
                
            }
        }
        
        return fresh == 0 ? ans : -1;
    }
};