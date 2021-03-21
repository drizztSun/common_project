/*
1778. Shortest Path in a Hidden Grid

This is an interactive problem.

You are given a robot in a hidden grid, and it wants to go to a target cell in this grid. The grid is of size m x n, and each cell in the grid can be empty or blocked. It is guaranteed that the start point and the robot's destination are different, and neither of them is blocked.

You want to find the robot's minimum distance to the target cell. However, you do not know the grid's dimensions, or the starting point of the robot, or its target destination. You are only allowed to ask queries to your GridMaster object.

You are given a class GridMaster which you can call the following functions from:

boolean GridMaster.canMove(char direction) returns true if the robot can move in that direction. Otherwise, it returns false.
void GridMaster.move(char direction) moves the robot in that direction. If this move would move the robot to a blocked cell or off the grid, it will be ignored, and the robot would remain in the same position.
boolean GridMaster.isTarget() returns true if the robot is currently on the target cell. Otherwise, it returns false.
Note that direction in the above functions should be a character from {'U','D','L','R'}, representing the directions up, down, left, and right, respectively.

Return the minimum distance between the robot's initial starting cell and the target cell if there is a path between them. Otherwise, return -1.

Custom testing:

The test input is read as a 2D matrix grid of size m x n where:

grid[i][j] == -1 indicates that the robot is in cell (i, j).
grid[i][j] == 0 indicates that the cell (i, j) is blocked.
grid[i][j] == 1 indicates that the cell (i, j) is empty.
grid[i][j] == 2 indicates that the cell (i, j) is the target cell.
There is exactly one -1 and 2 in grid. Remember that you will not have this information in your code.

 

Example 1:

Input: grid = [[1,2],[-1,0]]
Output: 2
Explanation: One possible interaction is described below:
The robot is initially standing on cell (1, 0), denoted by the -1.
- master.canMove('U') returns True.
- master.canMove('D') returns False.
- master.canMove('L') returns False.
- master.canMove('R') returns False.
- master.move('U') moves the robot to the cell (0, 0).
- master.isTarget() returns False.
- master.canMove('U') returns False.
- master.canMove('D') returns True.
- master.canMove('L') returns False.
- master.canMove('R') returns True.
- master.move('R') moves the robot to the cell (0, 1).
- master.isTarget() returns True. 
We now know that the target is the cell (0, 1), and the shortest path to the target is 2.
Example 2:

Input: grid = [[0,0,-1],[1,1,1],[2,0,0]]
Output: 4
Explanation: The minimum distance between the robot and the target is 4.
Example 3:

Input: grid = [[-1,0],[0,2]]
Output: -1
Explanation: There is no path from the robot to the target cell.
 

Constraints:

m == grid.length
n == grid[i].length
1 <= n, m <= 500
grid[i][j] is either -1, 0, 1, or 2.
There is exactly one -1 in grid.
There is exactly one 2 in grid.

*/

#include <vector>
#include <queue>
#include <unordered_set>

using std::unordered_set;
using std::queue;
using std::vector;

/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     void move(char direction);
 *     boolean isTarget();
 * };
 */

class ShortestPath {

    class GridMaster {
    public:
       bool canMove(char direction) {return false;};
       void move(char direction);
       bool isTarget() {return true;};  
    };

public:

    // Run-time is O(M*N), space is O(M*N). Idea is to first hack the map by using the robot to indiscriminately traverse all possible regions and record the result. 
    // Then, use BFS and map data to find shortest path.
    int g[1000][1000] = {};
    vector<std::pair<char, array<int, 2>>> dirs{{'U', {0, 1}}, {'D', {0, -1}}, {'L', {-1, 0}}, {'R', {1, 0}}};
    
    void map(GridMaster &master, int x, int y, char back) {
        g[x][y] = master.isTarget() ? 2 : 1;
        for (auto i = 0; i < dirs.size(); ++i) {
            auto& [d, dxy] = dirs[i];
            if (g[x + dxy[0]][y + dxy[1]] == 0) {
                if (master.canMove(d)) {
                    master.move(d);
                    map(master, x + dxy[0], y + dxy[1], dirs[i % 2 ? i - 1 : i + 1].first);
                }
                else 
                    g[x + dxy[0]][y + dxy[1]] = -1;
            }
        }
        master.move(back);
    }
    int findShortestPath(GridMaster &master) {
        int x = 500, y = 500, cnt = 0;
        map(master, x, y, 'U');
        vector<std::pair<int, int>> q{{x, y}};

        while (!q.empty()) {
        
            vector<std::pair<int, int>> q1;
            for (auto [x, y] : q) {
        
                if (g[x][y] == 2)
                    return cnt;
        
                if (g[x][y] == 1) {
                    g[x][y] = -1;
                    for (auto [_, dd] : dirs)
                        q1.push_back({x + dd[0], y + dd[1]});
                }
            }
            ++cnt;
            swap(q, q1);
        }
        return -1;
    }

public:

    int findShortestPath(GridMaster& master) {
        vector<std::vector<char>> grid(1001, std::vector<char>(1001, 0));
        dfs(grid, master, 500, 500);
        std::queue<std::pair<int,int>> q;
        q.emplace(500, 500), q.emplace(-1, -1);
        int steps{0};
        std::unordered_set<int> visited;
        while(!q.empty()) {
            auto [i, j]{q.front()}; q.pop();
            if(i == -1) {
                if(q.empty()) break;
                ++steps;
                q.emplace(-1,-1);
                continue;
            }
            
            if(grid[i][j] == 2) return steps;
            else if(grid[i][j] < 0) continue;
            else grid[i][j] *= -1;
            
            if(i > 0 && grid[i-1][j] > 0) q.emplace(i-1, j);
            if(i < 1000 && grid[i+1][j] > 0) q.emplace(i+1, j);
            if(j > 0 && grid[i][j-1] > 0) q.emplace(i, j-1);
            if(j < 1000 && grid[i][j+1] > 0) q.emplace(i, j+1);           
        }
        
        return -1;
    }
    
    static void dfs(std::vector<std::vector<char>>& grid, GridMaster& m, int i, int j) {
        if(m.isTarget()) grid[i][j] = 2;
        else grid[i][j] = 1;
        
        if(m.canMove('U') && grid[i-1][j] == 0) {
            m.move('U');
            dfs(grid, m, i-1, j);
            m.move('D');
        }
        if(m.canMove('D') && grid[i+1][j] == 0) {
            m.move('D');
            dfs(grid, m, i+1, j);
            m.move('U');
        }
        if(m.canMove('L') && grid[i][j-1] == 0) {
            m.move('L');
            dfs(grid, m, i, j-1);
            m.move('R');
        }
        if(m.canMove('R') && grid[i][j+1] == 0) {
            m.move('R');
            dfs(grid, m, i, j+1);
            m.move('L');
        }
    }
};