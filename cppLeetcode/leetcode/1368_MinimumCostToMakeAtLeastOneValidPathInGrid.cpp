/*
1368. Minimum Cost to Make at Least One Valid Path in a Grid

Given a m x n grid. Each cell of the grid has a sign pointing to the next cell you should visit if you are currently in this cell. The sign of grid[i][j] can be:
1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])
Notice that there could be some invalid signs on the cells of the grid which points outside the grid.

You will initially start at the upper left cell (0,0). A valid path in the grid is a path which starts from the upper left cell (0,0) 
and ends at the bottom-right cell (m - 1, n - 1) following the signs on the grid. The valid path doesn't have to be the shortest.

You can modify the sign on a cell with cost = 1. You can modify the sign on a cell one time only.

Return the minimum cost to make the grid have at least one valid path.

 

Example 1:


Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
Output: 3
Explanation: You will start at point (0, 0).
The path to (3, 3) is as follows. (0, 0) --> (0, 1) --> (0, 2) --> (0, 3) change the arrow to down with cost = 1 --> (1, 3) --> (1, 2) --> (1, 1) --> (1, 0) 
change the arrow to down with cost = 1 --> (2, 0) --> (2, 1) --> (2, 2) --> (2, 3) change the arrow to down with cost = 1 --> (3, 3)
The total cost = 3.
Example 2:


Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
Output: 0
Explanation: You can follow the path from (0, 0) to (2, 2).
Example 3:


Input: grid = [[1,2],[4,3]]
Output: 1
Example 4:

Input: grid = [[2,2,2],[2,2,2]]
Output: 3
Example 5:

Input: grid = [[4]]
Output: 0
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 100

*/
#include <vector>
#include <queue>
#include <algorithm>
#include <array>

using std::queue;
using std::priority_queue;
using std::vector;
using std::array;

class MinimumCostTo {

public:

    /*
        1368.Minimum-Cost-to-Make-at-Least-One-Valid-Path-in-a-Grid
        解法1：BFS
        如果不给修改的机会，那么我们能遍历到哪些格子？显然就是从(0,0)顺着箭头走，假设能走到Set0 = {p1,p2,...pk}这些位置。

        然后考虑如果给一次修改的机会，我们能遍历到哪些格子？我们会从之前Set0集合里考察每一个格子，思考如果不按照当前的箭头走，而是可以修改成任意方向的话，下一步会到哪里？
        比如说p1原本的箭头指向p2，现在我们允许修改一次p1的箭头方向，那么p1可能可以走到上述集合之外的q1。同时我们顺着q1的箭头走，又可以遍历到q2,q3,q4...等一系列的位置。
        
        可见这一系列{qi}点集就是“给一次修改机会”所能到达的位置。同理，我们还可以修改p1的箭头指向r1，或者选择Set0中的其他格子修改箭头，这些操作都能得到“给一次修改机会”所能到达的位置，我们标记为Set1。

        我们看出来，从Set0到Set1，就是一个BFS的过程。同理从Set1到Set2，也是BFS的过程：不断从一个集合，扩展到下一个集合，伴随step+=1.直到发现经过若干步（即修改若干次箭头）之后，就可以遍历到右下角，那么就可以返回答案。

        需要注意的是，在上述过程中，从q1顺着原有的箭头扩展到q2,q3,q4...的过程也是遍历，这层遍历时的step都是保持不变的。对于这层遍历，我们也可以用dfs来实现。

        解法2：Dijkstra
        如果格子A的符号导向的是格子B，那么我们就认为AB之间的边权重是0；否则我们就认为AB之间的边权重是1. 于是本题就变成了求起点到终点的最短路径问题。因为图中任意两点之间的边权重不等，所以用Dijkstra是显而易见的方案。
    */
    typedef array<int,3> AI3;

    int doit_dijkstra(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> visited(m, vector<int>(n, 0));
        priority_queue<AI3, vector<AI3>, std::greater<>>pq;
        pq.push({0,0,0});
        
        vector<std::pair<int,int>> dir({{0,1},{0,-1},{1,0},{-1,0}});
        
        while (!pq.empty())
        {
            auto [steps, x, y] = pq.top();
            pq.pop();
            if (visited[x][y]) continue;
            visited[x][y] = 1;

            if (x==m-1 && y==n-1)
                return steps;

            for (int k=0; k<4; k++)
            {
                int i = x+dir[k].first;
                int j = y+dir[k].second;
                
                if (i<0||i>=m||j<0||j>=n) continue;
                if (visited[i][j]==1) continue;

                int addon = grid[x][y]==k+1 ? 0:1;
                pq.push({steps+addon, i, j});
            }
        }
        return 0;
    }


    int visited[101][101];
    int m,n;
    vector<std::pair<int,int>>dir;

public:
    int doit_bfs(vector<vector<int>>& grid) 
    {
        m = grid.size();
        n = grid[0].size();
        dir = {{0,1},{0,-1},{1,0},{-1,0}};

        queue<std::pair<int,int>>q;
        vector<std::pair<int,int>>temp;
        dfs(0,0,temp,grid);
        for (auto x: temp)
            q.push(x);
        
        int step = 0;
        
        while (!q.empty())
        {
            int len = q.size();
            while (len--)
            {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for (int k=0; k<4; k++)
                {
                    int a = x+dir[k].first;
                    int b = y+dir[k].second;
                    if (a<0||a>=m||b<0||b>=n) continue;
                    if (visited[a][b]==1) continue;

                    vector<std::pair<int,int>>temp;
                    // put same cost point into the queue, if current direction x,y can be continued as the same direction. lie -> -> or <- <-
                    dfs(a,b,temp,grid);
                    for (auto x:temp)
                    {
                        if (x.first==m-1 && x.second==n-1)
                            return step+1;
                        q.push(x);                        
                    }
                }
            }
            step++;
        }
        return 0;
    }

    void dfs(int x, int y, vector<std::pair<int,int>>&temp, vector<vector<int>>& grid)
    {
        // put same cost point into the queue.
        if (x<0||x>=m||y<0||y>=n) return;
        if (visited[x][y]==1) return;
        temp.push_back({x,y});
        visited[x][y] = 1;

        int i = x + dir[grid[x][y]-1].first;
        int j = y + dir[grid[x][y]-1].second;
        dfs(i,j,temp,grid);
    }


};
