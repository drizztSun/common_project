/*
489. Robot Room Cleaner


Given a robot cleaner in a room modeled as a grid.

Each cell in the grid can be empty or blocked.

The robot cleaner with 4 given APIs can move forward, turn left or turn right. Each turn it made is 90 degrees.

When it tries to move into a blocked cell, its bumper sensor detects the obstacle and it stays on the current cell.

Design an algorithm to clean the entire room using only the 4 given APIs shown below.

interface Robot {
  // returns true if next cell is open and robot moves into the cell.
  // returns false if next cell is obstacle and robot stays on the current cell.
  boolean move();

  // Robot will stay on the same cell after calling turnLeft/turnRight.
  // Each turn will be 90 degrees.
  void turnLeft();
  void turnRight();

  // Clean the current cell.
  void clean();
}
Example:

Input:
room = [
  [1,1,1,1,1,0,1,1],
  [1,1,1,1,1,0,1,1],
  [1,0,1,1,1,1,1,1],
  [0,0,0,1,0,0,0,0],
  [1,1,1,1,1,1,1,1]
],
row = 1,
col = 3

Explanation:
All grids in the room are marked by either 0 or 1.
0 means the cell is blocked, while 1 means the cell is accessible.
The robot initially starts at the position of row=1, col=3.
From the top left corner, its position is one row below and three columns right.
Notes:

The input is only given to initialize the room and the robot's position internally. You must solve this problem "blindfolded". In other words, you must control the robot using only the mentioned 4 APIs, without knowing the room layout and the initial robot's position.
The robot's initial position will always be in an accessible cell.
The initial direction of the robot will be facing up.
All accessible cells are connected, which means the all cells marked as 1 will be accessible by the robot.
Assume all four edges of the grid are all surrounded by wall.
*/




/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */

#include <string>
#include <unordered_set>
#include <vector>
#include <functional>
#include <set>

using std::set;
using std::vector;
using std::unordered_set;
using std::string;

class CleanRoom {

    class Robot {
    public:
      // Returns true if the cell in front is open and robot moves into the cell.
      // Returns false if the cell in front is blocked and robot stays in the current cell.
      bool move();
 
      // Robot will stay in the same cell after calling turnLeft/turnRight.
      // Each turn will be 90 degrees.
      void turnLeft();
      void turnRight();
 
      // Clean the current cell.
      void clean();
    };

    /*
        489.Robot-Room-Cleaner
        比较常规的DFS，但是题目却很有趣，而且对于考察回溯的概念要求很高．

        基本的流程是：

        (1) 每新探索(DFS)一个格子，先判断是否曾经来过，曾经来过的话什么都不用做，return．注意，这里是指＂新探索＂一个格子．如果确定不是新探索，而是在回溯的过程中到了这个地方，不适用于这个规则．

        如果这是一个新格子，就clean()，并且标记已经来过．然后依次向四个方向探索：

        (2) 首先向当前方向继续探索：步骤是：move, DFS（递归的过程，新探索下一个格子）, turnRight, turnRight, move, turnRight, turnRight．后面这五步是一个必要的回溯过程，保证回到了探索之前的状态．

        (３) 然后turnRight,找到下一个方向，重复(２)的过程．

        (４) 然后turnRight,找到下一个方向，重复(２)的过程．

        (５) 然后turnRight,找到下一个方向，重复(２)的过程．

        完整结束了这个格子的探索．
    */
    unordered_set<string>visited;
    int dir;

    void cleanRoom(Robot& robot) 
    {
        string code = std::to_string(0)+"#"+std::to_string(0);
        visited.insert(code);
        DFS(robot,0,0,0);  //[x,y,dir]
    }
    
    void DFS(Robot& robot, int x, int y, int curDir)
    {
        vector<std::pair<int,int>>dir({{0,1},{1,0},{0,-1},{-1,0}});        
        robot.clean();
        for (int k=0; k<4; k++)
        {
            int nxtDir = (curDir+k)%4;            
            int i = x+dir[nxtDir].first;
            int j = y+dir[nxtDir].second;
            string code = std::to_string(i)+"#"+std::to_string(j);
                
            if (visited.find(code)==visited.end() && robot.move())
            {
                visited.insert(code);
                DFS(robot,i,j,nxtDir);
                robot.turnLeft();
                robot.turnLeft();
                robot.move();
                robot.turnLeft();
                robot.turnLeft();            
            }                
            robot.turnRight();         
        }
    }

    void doit_dfs(Robot& robot) {
        
        unordered_set<string> visited;
        int dir[5] = {-1, 0, 1, 0, -1};
        
        auto key = [](int x, int y) -> std::string {
            return std::to_string(x) + '#' + std::to_string(y);    
        };
        
        std::function<void(int, int, int)> dfs = [&](int i, int j, int curdir) {
            
            robot.clean();
            
            for (int k = 0; k <4; k++) {
                
                int nextdir = (curdir+k) % 4;
                int x = i + dir[nextdir], y = j + dir[nextdir+1];
                string hashkey = key(x, y);
                
                if (visited.count(hashkey) == 0 && robot.move()) {
                    
                    visited.insert(hashkey);
                    
                    dfs(x, y, nextdir);
                    
                    robot.turnLeft();
                    robot.turnLeft();
                    robot.move();
                    robot.turnLeft();
                    robot.turnLeft();
                }
                
                robot.turnRight();
            }
        };
        
        visited.insert(key(0, 0));
        
        dfs(0, 0, 0);
    }


public:

    int dist[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    set<std::pair<int,int>> visited;
    void move_back(Robot& robot) {
        robot.turnRight();
        robot.turnRight();
        robot.move();
        robot.turnRight();
        robot.turnRight();
    }
    
    void dfs(Robot& robot, int x, int y, int dir) {
        visited.insert({x,y});
        robot.clean();
        int nx,ny,ndir;
        int i;
        for(i = 0; i < 4; i++) {
            ndir = (dir + i)%4;
            nx = x + dist[ndir][0];
            ny = y + dist[ndir][1];
            
            if(!visited.count({nx,ny}) && robot.move()) {
                dfs(robot,nx,ny,ndir);
                move_back(robot);                
            }
            robot.turnRight();
        }
    }
    
    void cleanRoom(Robot& robot) {
       dfs(robot,0,0,0);
    }
};