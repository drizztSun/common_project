/*
827. Making A Large Island

You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.

Return the size of the largest island in grid after applying this operation.

An island is a 4-directionally connected group of 1s.

 

Example 1:

Input: grid = [[1,0],[0,1]]
Output: 3
Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
Example 2:

Input: grid = [[1,1],[1,0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
Example 3:

Input: grid = [[1,1],[1,1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 4.
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 500
grid[i][j] is either 0 or 1.


*/
#include <vector>
#include <queue>
#include <unordered_set>
#include <functional>

using std::queue;
using std::unordered_set;
using std::vector;


class LargestIsland {

public:
    
    int doit_bfs_dfs(vector<vector<int>>& grid) {
        
        int m = grid.size(), n = grid[0].size();
        vector<int> areas{0, 0};
        int direct[5] = {-1, 0, 1, 0, -1};
        
        std::function<int(int, int, int)> search = [&](int x, int y, int index) {
          
            int cnt = 0;
            queue<std::pair<int, int>> qu;
            qu.push({x, y});
            grid[x][y] = index;
            
            while (!qu.empty()) {
                
                int x = qu.front().first, y = qu.front().second;
                qu.pop();
                cnt++;
                
                for (int k = 0; k < 4; k++) {
                    int xx = x + direct[k], yy = y + direct[k+1];
                 
                    if (xx < 0 || xx >= m || yy < 0 || yy >= n || grid[xx][yy] != 1) continue;
                    grid[xx][yy] = index;
                    qu.push({xx, yy});
                }
            }
            
            
            return cnt;
        };
        
        for (int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    areas.push_back(search(i, j, areas.size()));
                }
            }
        }
        
        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    
                    unordered_set<int> tmp;
                    for (int k = 0; k < 4; k++) {
                        int x = i + direct[k], y = j + direct[k+1];
                        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0) continue;
                        tmp.insert(grid[x][y]);
                    }
                    
                    int tmparea = 0;
                    for (auto c : tmp)
                        tmparea += areas[c];
                    
                    ans = std::max(ans, tmparea+1);
                }
            }
        }
        
        return std::max(ans, *max_element(begin(areas), end(areas)));
    }
};