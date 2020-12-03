/*
 
 1162. As Far from Land as Possible
 
 Given an n x n grid containing only values 0 and 1, where 0 represents water and 1 represents land, find a water cell such that its distance to the nearest land cell is maximized, and return the distance. If no land or water exists in the grid, return -1.

 The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.



 Example 1:


 Input: grid = [[1,0,1],[0,0,0],[1,0,1]]
 Output: 2
 Explanation: The cell (1, 1) is as far as possible from all the land with distance 2.
 Example 2:


 Input: grid = [[1,0,0],[0,0,0],[0,0,0]]
 Output: 4
 Explanation: The cell (2, 2) is as far as possible from all the land with distance 4.


 Constraints:

 n == grid.length
 n == grid[i].length
 1 <= n <= 100
 grid[i][j] is 0 or 1

 */
#include <vector>
#include <list>
#include <deque>

using std::deque;
using std::list;
using std::vector;

class MaxDistance {
    
public:
    vector<vector<int>> dir = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    
    int doit_bfs_dijstra(vector<vector<int>>& grid) {
        int maxi = 0;
        list<std::pair<int, int>> ver;
        int r = grid.size(), c = grid[0].size();
        
        vector<vector<int>> dp (r, vector<int>(c, INT_MAX));
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == 0)
                    continue;
                ver.push_back(std::make_pair(i, j));
                dp[i][j] = 0;
            }
        }
        
        if (ver.empty())
            return -1;
        
        while (!ver.empty()) {
            int x = ver.front().first, y = ver.front().second;
            ver.pop_front();
            maxi = std::max(maxi, dp[x][y]);
            
            for (int p = 0; p < dir.size(); p++) {
                int x1 = x + dir[p][0], y1 = y + dir[p][1];
                if (x1 >= 0 && x1 < r && y1 >= 0 && y1 < c) {
                    if (grid[x1][y1] == 0 && dp[x1][y1] > dp[x][y] + 1) {
                        ver.push_back(std::make_pair(x1, y1));
                        dp[x1][y1] = dp[x][y] + 1;
                    }
                }
            }
        }
        
        maxi = (maxi == 0) ? -1 : maxi;
        return maxi;
    }
    
    int doit_bfs(vector<vector<int>>& grid) {
        
        deque<std::pair<int, int>> queue;
        auto n = grid.size();
        
        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < n; j++) {
                if (grid[i][j] == 1)
                    queue.push_back({i, j});
            }
        }
        
        int length = queue.size();
        if (length == 0 || length == n*n)
            return -1;
        
        int d = -1;
        while (!queue.empty()) {
            
            length = queue.size();
            
            while (length > 0) {
                
                auto c = queue.front();
                queue.pop_front();
                
                int x = c.first, y = c.second;
                for (int p = 0; p < dir.size(); p++) {
                    int x1 = x + dir[p][0], y1 = y + dir[p][1];
                    
                    if (x1 >= 0 && x1 < n && y1 >= 0 && y1 < n && grid[x1][y1] == 0){
                        grid[x1][y1] = 1;
                        queue.push_back({x1, y1});
                    }
                }
                length--;
            }
            
            d += 1;
        }
        
        return d;
    }
};
