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
#include <array>
#include <unordered_map>
#include <functional>

using std::unordered_map;
using std::array;
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

    /*
        1778.Shortest-Path-in-a-Hidden-Grid
        
        本题巧妙地将DFS和BFS结合起来。

        因为机器人只能单线程操作，只能到了一个位置再移动到另一个位置，无法像BFS那样并行地让多个机器人朝不同方向扩散。所以本题只能用DFS的方法，指挥机器人一步一步“深度优先+回溯”地探索完整个房间，标记每个格子的状态。DFS结束后将房间的平面图记录在内存，就可以用BFS求到终点的最短路径。
    */

    typedef std::pair<int,int> PII;
    int grid[1000][1000];    
    int visited[1000][1000];
    int visited2[1000][1000];

    int findShortestPath(GridMaster &master) 
    {   
        visited[500][500] = 1;
        dfs(500, 500, master);
        
        auto dir = vector<PII>({{-1,0},{1,0},{0,-1},{0,1}});
        
        queue<PII>q;
        q.push({500,500});
        visited2[500][500]=1;        
        
        int step = 0;
        while (!q.empty())
        {
            int len = q.size();
            step++;
            while (len--)
            {
                auto [i,j] = q.front();
                q.pop();
                
                for (int k=0; k<4; k++)
                {                    
                    int x = i + dir[k].first;
                    int y = j + dir[k].second;
                    if (grid[x][y]==2) return step;                        
                    if (grid[x][y]==0) continue;
                    if (visited2[x][y]==1) continue;
                        
                    visited2[x][y] = 1;
                    q.push({x,y});                        
                }
            }
        }
        return -1;
        
    }
    
    void dfs(int i, int j, GridMaster &master)
    {
        auto dir = vector<PII>({{-1,0},{1,0},{0,-1},{0,1}});
        vector<char> move({'U','D','L','R'});
        
        grid[i][j] = 1;
        
        if (master.isTarget())
        {
            grid[i][j] = 2;
            return;
        }
        
        for (int k=0; k<4; k++)
        {
            int x = i+dir[k].first;
            int y = j+dir[k].second;
            if (visited[x][y]) continue;
            
            if (master.canMove(move[k])==false)
                grid[x][y] = 0;
            else 
            {
                visited[x][y] = 1;
                master.move(move[k]);
                
                dfs(x,y,master);                
                
                int kk;
                if (k==0) kk=1;
                else if (k==1) kk=0;
                else if (k==2) kk=3;
                else if (k==3) kk=2;
                master.move(move[kk]);
            }                
        }
    }

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
        
        if(m.isTarget()) 
            grid[i][j] = 2;
        else 
            grid[i][j] = 1;
        
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



    int doit_dfs(GridMaster &master) {
        
        vector<vector<int>> grid(1001, vector<int>(1001, 0));
        
        unordered_map<char, std::pair<int, int>> dir{{'L', {0, -1}}, {'R', {0, 1}}, {'U', {-1, 0}}, {'D', {1, 0}}};
        unordered_map<char, char> revs{{'U', 'D'}, {'D', 'U'}, {'L', 'R'}, {'R', 'L'}};
        
        std::function<void(int, int)> dfs = [&](int i, int j) {
            
            grid[i][j] = master.isTarget() ? 2 : 1;
        
            for (auto it: dir) {
                if (master.canMove(it.first) && grid[i+it.second.first][j+it.second.second] == 0) {
                    master.move(it.first);
                    dfs(i+it.second.first, j+it.second.second);
                    master.move(revs[it.first]);
                }
            }
        };
        
        dfs(500, 500);
        
        queue<std::pair<int, int>> qu;
        qu.push({500, 500});
        int step = 0;
        
        while (!qu.empty()) {
            
            int sz = qu.size();
            
            while (sz--) {
                
                auto it = qu.front();
                int x = it.first, y = it.second;
                qu.pop();
                
                //printf("%d\n", grid[x][y]);
                
                if (grid[x][y] == -2) return step;
                
                if (grid[x][y] = 0) continue;
                
                if (x > 0 && grid[x-1][y] > 0) {
                    grid[x-1][y] *= -1;
                    qu.emplace(x-1, y);
                }
                
                if (x < 1000 && grid[x+1][y] > 0) {
                    grid[x+1][y] *= -1;
                    qu.emplace(x+1, y);
                }
                
                if (y > 0 && grid[x][y-1] > 0) {
                    grid[x][y-1] *= -1;
                    qu.emplace(x, y-1);
                }
                
                if (y < 1000 && grid[x][y+1] > 0) {
                    grid[x][y+1] *= -1;
                    qu.emplace(x, y+1);
                }
            }
            
            step++;
        }
        
        return -1;
    }
};