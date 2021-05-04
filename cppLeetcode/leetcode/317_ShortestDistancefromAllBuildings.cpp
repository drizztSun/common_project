/*
317. Shortest Distance from All Buildings

You are given an m x n grid grid of values 0, 1, or 2, where:

each 0 marks an empty land that you can pass by freely,
each 1 marks a building that you cannot pass through, and
each 2 marks an obstacle that you cannot pass through.
You want to build a house on an empty land that reaches all buildings in the shortest total travel distance. You can only move up, down, left, and right.

Return the shortest travel distance for such a house. If it is not possible to build such a house according to the above rules, return -1.

The total travel distance is the sum of the distances between the houses of the friends and the meeting point.

The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

 

Example 1:


Input: grid = [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]
Output: 7
Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2).
The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal.
So return 7.
Example 2:

Input: grid = [[1,0]]
Output: 1
Example 3:

Input: grid = [[1]]
Output: -1
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 100
grid[i][j] is either 0, 1, or 2.
There will be at least one building in the grid.
*/

#include <vector>
#include <queue>

using std::queue;
using std::vector;


class ShortestDistancefromAllBuildings {

public:

    int doit_bfs(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        auto total = grid;
        int walk = 0, mindist, delta[] = {0, 1, 0, -1, 0};

        for (int i=0; i<m; ++i) {
            for (int j=0; j<n; ++j) {

                if (grid[i][j] == 1) {
                
                    mindist = -1;
                    auto dist = grid;
                
                    queue<std::pair<int, int>> q;
                    q.emplace(i, j);
                
                    while (q.size()) {
                
                        auto ij = q.front();
                        q.pop();
                
                        for (int d=0; d<4; ++d) {
                
                            int i = ij.first + delta[d];
                            int j = ij.second + delta[d+1];
                
                            if (i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == walk) {
                                grid[i][j]--;
                                dist[i][j] = dist[ij.first][ij.second] + 1;
                                total[i][j] += dist[i][j] - 1;
                                q.emplace(i, j);
                                if (mindist < 0 || mindist > total[i][j])
                                    mindist = total[i][j];
                            }
                        }
                    }
                    // walked times.
                    walk--;
                }
            }
        }
        return mindist;
    }
};