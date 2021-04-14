/*
1810. Minimum Path Cost in a Hidden Grid


This is an interactive problem.

There is a robot in a hidden grid, and you are trying to get it from its starting cell to the target cell in this grid. The grid is of size m x n, and each cell in the grid is either empty or blocked. It is guaranteed that the starting cell and the target cell are different, and neither of them is blocked.

Each cell has a cost that you need to pay each time you move to the cell. The starting cell's cost is not applied before the robot moves.

You want to find the minimum total cost to move the robot to the target cell. However, you do not know the grid's dimensions, the starting cell, nor the target cell. You are only allowed to ask queries to the GridMaster object.

The GridMaster class has the following functions:

boolean canMove(char direction) Returns true if the robot can move in that direction. Otherwise, it returns false.
int move(char direction) Moves the robot in that direction and returns the cost of moving to that cell. If this move would move the robot to a blocked cell or off the grid, the move will be ignored, the robot will remain in the same position, and the function will return -1.
boolean isTarget() Returns true if the robot is currently on the target cell. Otherwise, it returns false.
Note that direction in the above functions should be a character from {'U','D','L','R'}, representing the directions up, down, left, and right, respectively.

Return the minimum total cost to get the robot from its initial starting cell to the target cell. If there is no valid path between the cells, return -1.

Custom testing:

The test input is read as a 2D matrix grid of size m x n and four integers r1, c1, r2, and c2 where:

grid[i][j] == 0 indicates that the cell (i, j) is blocked.
grid[i][j] >= 1 indicates that the cell (i, j) is empty and grid[i][j] is the cost to move to that cell.
(r1, c1) is the starting cell of the robot.
(r2, c2) is the target cell of the robot.
Remember that you will not have this information in your code.

 

Example 1:

Input: grid = [[2,3],[1,1]], r1 = 0, c1 = 1, r2 = 1, c2 = 0
Output: 2
Explanation: One possible interaction is described below:
The robot is initially standing on cell (0, 1), denoted by the 3.
- master.canMove('U') returns false.
- master.canMove('D') returns true.
- master.canMove('L') returns true.
- master.canMove('R') returns false.
- master.move('L') moves the robot to the cell (0, 0) and returns 2.
- master.isTarget() returns false.
- master.canMove('U') returns false.
- master.canMove('D') returns true.
- master.canMove('L') returns false.
- master.canMove('R') returns true.
- master.move('D') moves the robot to the cell (1, 0) and returns 1.
- master.isTarget() returns true.
- master.move('L') doesn't move the robot and returns -1.
- master.move('R') moves the robot to the cell (1, 1) and returns 1.
We now know that the target is the cell (0, 1), and the minimum total cost to reach it is 2. 
Example 2:

Input: grid = [[0,3,1],[3,4,2],[1,2,0]], r1 = 2, c1 = 0, r2 = 0, c2 = 2
Output: 9
Explanation: The minimum cost path is (2,0) -> (2,1) -> (1,1) -> (1,2) -> (0,2).
Example 3:

Input: grid = [[1,0],[0,1]], r1 = 0, c1 = 0, r2 = 1, c2 = 1
Output: -1
Explanation: There is no path from the robot to the target cell.
 

Constraints:

1 <= n, m <= 100
m == grid.length
n == grid[i].length
0 <= grid[i][j] <= 100

*/


/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     int move(char direction);
 *     boolean isTarget();
 * };
 */

#include <vector>
#include <queue>
#include <functional>
#include <unordered_map>
#include <string>
#include <array>

using std::array;
using std::string;
using std::unordered_map;
using std::priority_queue;
using std::vector;

class ShortestPath {

    class GridMaster {
    public:
      bool canMove(char direction) { return true; }
      int move(char direction) {return 1; }
      bool isTarget() { return true; }
    };

    /*
        1810.Minimum-Path-Cost-in-a-Hidden-Grid
        开辟一个200x200的二维矩阵。将起始点设置为(100,100)。先通过DFS走遍所有的格子，标记每个格子的cost和是否是障碍物，以及终点的位置。然后再从起点开始，用Dijkstra算法求得起点到终点的最小权重路径，
    */
    typedef array<int,3> AI3;
    
    int visited[201][201];
    int cost[201][201];
    string d = "ULRD";
    int targetX, targetY;
    vector<std::pair<int,int>> dir = {{-1,0},{0,-1},{0,1},{1,0}};
    
public:
    int findShortestPath(GridMaster &master) 
    {
        for (int i=0; i<201; i++)
            for (int j=0; j<201; j++)
                cost[i][j] = -1;
        
        visited[100][100] = 1;
        dfs(master, 100, 100);
        
        for (int i=0; i<201; i++)
            for (int j=0; j<201; j++)
                visited[i][j] = 0;
                
        priority_queue<AI3,vector<AI3>, std::greater<>>pq;
        pq.push({0,100,100});
                
        while (!pq.empty())
        {
            auto [c,x,y] = pq.top();
            pq.pop();
            visited[x][y] = 1;        
            if (x==targetX && y==targetY)
                return c;
            
            for (int k=0; k<4; k++)
            {
                int i = x+dir[k].first;
                int j = y+dir[k].second;
                if (cost[i][j]==-1) continue;    
                if (i<0 || i>=200 || j<0|| j>=200) continue;
                if (visited[i][j]==1) continue;
                
                pq.push({c+cost[i][j], i, j});
            }
        }
        
        return -1;        
    }
    
    void dfs(GridMaster &master, int x, int y)
    {
        
        if (master.isTarget())
        {
            targetX = x;
            targetY = y;
        }
        for (int k=0; k<4; k++)
        {       
            int i = x+dir[k].first;
            int j = y+dir[k].second;
            if(visited[i][j]==1) continue;
            
            if (master.canMove(d[k]))
            {                
                int c = master.move(d[k]);
                visited[i][j] = 1;
                cost[i][j] = c;
                dfs(master, i,j);
                master.move(d[3-k]);
            }
            else
            {
                visited[i][j] = 1;                
            }
        }
    }


    int findShortestPath(GridMaster &master) {
        // DFS followed by Dijkstra's algorithm
        std::pair<int, int> targetPos{-1, -1};
        vector<vector<int>> grid(201, vector<int>(201));
        vector<vector<int>> dists(201, vector<int>(201, INT_MAX)); // distance vector
        vector<std::pair<int, int>> dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // directions up down left and right
        vector<char> charDirs{'U', 'D', 'L', 'R'}, countCharDirs{'D', 'U', 'R', 'L'}; // characters of directions
        auto comp = [&](const auto& p1, const auto& p2)
        {
            return dists[p1.first][p1.second] > dists[p2.first][p2.second];
        };
        
        priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, decltype(comp)> heap(comp); // min heap
        dists[100][100] = 0;
        heap.push({100, 100});
        dfs(master, grid, dirs, charDirs, countCharDirs, targetPos, 100, 100); // dfs to initialize grid
        
        if (targetPos.first < 0)
        {
            return -1; // no path to the target
        }

        while (!heap.empty()) // Dijkstra
        {
            auto nextPos = heap.top();
            if (nextPos == targetPos)
            {
                return dists[nextPos.first][nextPos.second]; // reach the target
            }
            
            for (const auto& d : dirs) // look at 4 directions
            {
                int r = nextPos.first + d.first, c = nextPos.second + d.second;
                if (grid[r][c] > 0)
                {
                    int cost = dists[nextPos.first][nextPos.second] + grid[r][c]; // cost to reach the adjacent cell
                    if (cost < dists[r][c]) // update the heap as well as distance matrix
                    {
                        dists[r][c] = cost;
                        heap.push({r, c});
                    }
                }
            }
            
            heap.pop(); // current cell was examined already
        }
        
        return -1;
    }
    
private:
    void dfs(GridMaster& master, vector<vector<int>>& grid, vector<std::pair<int, int>>& dirs, vector<char>& charDirs, vector<char>& countCharDirs, std::pair<int, int>& targetPos, int row, int col)
    {
        if (master.isTarget())
        {
            targetPos = {row, col}; // find target cell
        }
        
        for (int i = 0; i < 4; ++i) // 4 directions
        {
            if (master.canMove(charDirs[i]) && grid[row + dirs[i].first][col + dirs[i].second] <= 0)
            {
                grid[row + dirs[i].first][col + dirs[i].second] = master.move(charDirs[i]);
                dfs(master, grid, dirs, charDirs, countCharDirs, targetPos, row + dirs[i].first, col + dirs[i].second);
                grid[row][col] = master.move(countCharDirs[i]); // fill in the grid
            }
        }
    }

public:

    int grid[50001];
    int dir[4][2]={{0, 1},{1, 0},{0, -1},{-1, 0}};
    string d="RDLU";
    int tx,ty;
    
    void dfs(GridMaster &master,int x,int y, vector<bool> &access) {
        if(master.isTarget()) {
            tx=x,ty=y;
        }
		
        access[x*201+y]=true;
        for(int i=0;i<4;i++) {
            int cx=x+dir[i][0], cy=y+dir[i][1];
            if(master.canMove(d[i]) && !access[cx*201+cy]) {
                grid[cx*201+cy]=master.move(d[i]);
                dfs(master,cx,cy, access);
                grid[x*201+y]=master.move(d[(i+2)%4]);
            }
        }
    }
public:    
    int findShortestPath(GridMaster &master) {
        vector<bool> access(50001, false);
        dfs(master,100,100, access);
        
        vector<bool> vis(50001, false);
        priority_queue<std::pair<int,int>,vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> q;
        q.push({0,100*201+100});
        vis[100*201+100]=true;
        while(!q.empty()) {
            std::pair<int,int> p=q.top();
            q.pop();
            int x=p.second/201, y=p.second%201, cost=p.first;
            if(x==tx && y==ty) {
                return cost;
            }
			
            for(int i=0;i<4;i++) {
                int cx=x+dir[i][0], cy=y+dir[i][1];
                if(!vis[cx*201+cy] && access[cx*201+cy]) {
                    q.push({cost+grid[cx*201+cy],cx*201+cy});
                    vis[cx*201+cy]=true;
                }
            }
        }
        return -1;
    }


public:

    int doit_dfs_diajkstra(GridMaster &master) {

        int n = 201;
        vector<vector<int>> grid(n, vector<int>(n, 0));
        int dir[5] = {-1, 0, 1, 0, -1};
        unordered_map<char, int> dirMap{{'U', 1}, {'D', 3}, {'R', 2}, {'L', 0}};
        unordered_map<char, char> revDir{{'U', 'D'}, {'D', 'U'}, {'R', 'L'}, {'L', 'R'}};
        int tx = -1, ty = -1;


        std::function<void(int, int)> dfs = [&](int i, int j) {

            if (master.isTarget()) {
                tx = i, ty = j;
            }

            for (auto [m, v] : dirMap) {
                int x = i + dir[v], y = j + dir[v+1];
                if (master.canMove(m) && !grid[x][y]) {
                    grid[x][y] = master.move(m);
                    dfs(x, y);
                    grid[i][j] = master.move(revDir[m]);
                }
            }
        };

        dfs(100, 100);

        vector<bool> vis(50001, false);
        priority_queue<std::pair<int,int>,vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> q;
        q.push({0,100*n+100});
        vis[100*n+100]=true;
        while(!q.empty()) {
            std::pair<int,int> p=q.top();
            q.pop();
            int i=p.second/n, j=p.second%n, cost=p.first;
            if(i==tx && j==ty) {
                return cost;
            }
			
            for (auto [m, v] : dirMap) {
                int x = i + dir[v], y = j + dir[v+1];
                if(!vis[x*n+y] && grid[x][y]) {
                    q.push({cost + grid[x][y], x*n+y});
                    vis[x*n+y]=true;
                }
            }
        }
        return -1;
    }
};