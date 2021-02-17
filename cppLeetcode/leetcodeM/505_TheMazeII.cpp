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
#include <algorithm>

using std::priority_queue;
using std::queue;
using std::vector;


class MazeII {

public:

    /*
        505.The-Maze-II
        本题中从某点朝四个方向走的路径权重不同，所以本题不适合用常规的BFS求解最短路径。此题是适用标准Dijkstra（BFS+PQ）算法的模板题。

        Dijkstra算法的整体框架类似于BFS，将起点放入一个队列中。每个回合从队首弹出一个位置，然后将这个位置邻接的四个位置压入队列，直至我们弹出终点。不同之处在于我们使用的是一个优先队列，
        里面存放给的是行走状态的两个信息{steps, position}，并且按照steps从小到大排序。如果某个position第一次从队列中弹出，那么根据贪心思想，意味着从起点到达这个position的最短路径就是steps。

        注意，已经被确认最短路径的position就再不需要放入队列中。
    */
    typedef vector<int> VI;

    int doit_dfs_heap_dijkstra(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) 
    {
        int M=maze.size();
        int N=maze[0].size();
        
        vector<std::pair<int,int>> dir({{1,0},{-1,0},{0,1},{0,-1}});        
        auto resolved = vector<vector<int>>(M,vector<int>(N,0));
        
        priority_queue<VI, vector<VI>, std::greater<>> pq;
        pq.push({0, start[0], start[1]});
        
        while (!pq.empty())
        {
            int d = pq.top()[0];
            int x = pq.top()[1];
            int y = pq.top()[2];
            pq.pop();

            if (x==destination[0] && y==destination[1])
                return d;
            
            if (resolved[x][y] == 1) continue;
            resolved[x][y] = 1;
            
            for (int k=0; k<4; k++)
            {
                int i = x, j = y, step=0;
                while (i+dir[k].first>=0 && i+dir[k].first<M && j+dir[k].second>=0 && j+dir[k].second<N && maze[i+dir[k].first][j+dir[k].second]==0)
                {
                    step++;
                    i = i+dir[k].first;
                    j = j+dir[k].second;
                }
                if (resolved[i][j]) continue;
                pq.push({d+step, i, j});
            }
        }
        
        return -1;
    }
    
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
                while(x - 1 >= 0 && maze[x-1][y] == 0) x--;
                if(visited[x][y] > visited[i][j] + abs(i-x))  {
                    visited[x][y] = visited[i][j] + abs(i-x);
                    q.push({x,y});
                }
                //down
                x = i, y = j;
                while(x + 1 < maze.size() && maze[x+1][y] == 0) x++;
                if(visited[x][y] >  visited[i][j] + abs(i-x))  {
                    visited[x][y] = visited[i][j] + abs(i-x);
                    q.push({x,y});
                }
                //left
                x = i, y = j;
                while(y - 1 >= 0 && maze[x][y-1] == 0) y--;
                if(visited[x][y] > visited[i][j] + abs(j - y))  {
                    visited[x][y] = visited[i][j] + abs(j - y);
                    q.push({x,y});
                }
                //right
                 x = i, y = j;
                while(y + 1 < maze[0].size() && maze[x][y+1] == 0) y++;
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
            while(x - 1 >= 0 && maze[x-1][y] == 0) x--;
            if(dist[x][y] > dist[i][j] + abs(i-x))  {
                dist[x][y] = dist[i][j] + abs(i-x);
                pq.push({dist[x][y], x,y});
            }
        
            //down
            x = i, y = j;
            while(x + 1 < maze.size() && maze[x+1][y] == 0) x++;
            if(dist[x][y] > dist[i][j] + abs(i-x))  {
                dist[x][y] = dist[i][j] + abs(i-x);
                pq.push({dist[x][y], x,y});
            }
        
            //left
            x = i, y = j;
            while(y - 1 >= 0 && maze[x][y-1] == 0) y--;
            if(dist[x][y] > dist[i][j] + abs(j - y))  {
                dist[x][y] = dist[i][j] + abs(j - y);
                pq.push({dist[x][y], x,y});
            }
        
            //right
            x = i, y = j;
            while(y + 1 < maze[0].size() && maze[x][y+1] == 0) y++;
            if(dist[x][y] > dist[i][j] + abs(j - y))  {
                dist[x][y] = dist[i][j] + abs(j - y);
                pq.push({dist[x][y], x,y});
            }
        }

        return  dist[destination[0]][destination[1]] != INT_MAX ?  dist[destination[0]][destination[1]] : - 1;
    }

};