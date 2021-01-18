/*
505. The Maze II

There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the ball's start position, the destination and the maze, find the shortest distance for the ball to stop at the destination. 
The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included). If the ball cannot stop at the destination, return -1.

The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.

 

Example 1:

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (4, 4)

Output: 12

Explanation: One shortest way is : left -> down -> left -> down -> right -> down -> right.
             The total distance is 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12.

Example 2:

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (3, 2)

Output: -1

Explanation: There is no way for the ball to stop at the destination.

 

Note:

There is only one ball and one destination in the maze.
Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.

*/
#include <vector>
#include <queue>
#include <queue>
#include <numeric>

using std::priority_queue;
using std::queue;
using std::vector;


class MazeII {

public:
    
    int doit_bfs(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        queue<vector<int>> q;
        q.push({start[0], start[1]});
        vector<vector<int>> visited(maze.size(), vector<int>(maze[0].size(), INT_MAX));
        visited[start[0]][start[1]] = 0;
        int res = INT_MAX;
        while(!q.empty()) {
            int size = q.size(); 
            while(size--) {
                auto p = q.front(); q.pop();
                int i = p[0], j = p[1];
                int x = i, y = j;
                //up
                while(x - 1 >= 0 and maze[x-1][y] == 0) x--;
                if(visited[x][y] > visited[i][j] + abs(i-x))  {
                    visited[x][y] = visited[i][j] + abs(i-x);
                    q.push({x,y});
                }
                //down
                x = i, y = j;
                while(x + 1 < maze.size() and maze[x+1][y] == 0) x++;
                if(visited[x][y] >  visited[i][j] + abs(i-x))  {
                    visited[x][y] = visited[i][j] + abs(i-x);
                    q.push({x,y});
                }
                //left
                x = i, y = j;
                while(y - 1 >= 0 and maze[x][y-1] == 0) y--;
                if(visited[x][y] > visited[i][j] + abs(j - y))  {
                    visited[x][y] = visited[i][j] + abs(j - y);
                    q.push({x,y});
                }
                //right
                 x = i, y = j;
                while(y + 1 < maze[0].size() and maze[x][y+1] == 0) y++;
                if(visited[x][y] > visited[i][j] + abs(j - y)) {
                    visited[x][y] = visited[i][j] + abs(j - y);
                    q.push({x,y});
                }
            }
        }
        return  visited[destination[0]][destination[1]] != INT_MAX ?  visited[destination[0]][destination[1]] : - 1;
    }

    int doit_dijstra(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        priority_queue<vector<int>, vector<vector<int>>, std::greater<vector<int>>>pq;
        pq.push({0, start[0], start[1]});
        vector<vector<int>> dist(maze.size(), vector<int>(maze[0].size(), INT_MAX));
        dist[start[0]][start[1]] = 0;

        while(!pq.empty()) {
            auto p = pq.top(); pq.pop();
            int i = p[1], j = p[2];
            int x = i, y = j;
            //up
            while(x - 1 >= 0 and maze[x-1][y] == 0) x--;
            if(dist[x][y] > dist[i][j] + abs(i-x))  {
                dist[x][y] = dist[i][j] + abs(i-x);
                pq.push({dist[x][y], x,y});
            }
            //down
            x = i, y = j;
            while(x + 1 < maze.size() and maze[x+1][y] == 0) x++;
            if(dist[x][y] > dist[i][j] + abs(i-x))  {
                dist[x][y] = dist[i][j] + abs(i-x);
                pq.push({dist[x][y], x,y});
            }
            //left
            x = i, y = j;
            while(y - 1 >= 0 and maze[x][y-1] == 0) y--;
            if(dist[x][y] > dist[i][j] + abs(j - y))  {
                dist[x][y] = dist[i][j] + abs(j - y);
                pq.push({dist[x][y], x,y});
            }
            //right
            x = i, y = j;
            while(y + 1 < maze[0].size() and maze[x][y+1] == 0) y++;
            if(dist[x][y] > dist[i][j] + abs(j - y))  {
                dist[x][y] = dist[i][j] + abs(j - y);
                pq.push({dist[x][y], x,y});
            }
        } 
        return  dist[destination[0]][destination[1]] != INT_MAX ?  dist[destination[0]][destination[1]] : - 1;
    }

};