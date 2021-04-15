/*
675. Cut Off Trees for Golf Event

You are asked to cut off all the trees in a forest for a golf event. The forest is represented as an m x n matrix. In this matrix:

0 means the cell cannot be walked through.
1 represents an empty cell that can be walked through.
A number greater than 1 represents a tree in a cell that can be walked through, and this number is the tree's height.
In one step, you can walk in any of the four directions: north, east, south, and west. If you are standing in a cell with a tree, you can choose whether to cut it off.

You must cut off the trees in order from shortest to tallest. When you cut off a tree, the value at its cell becomes 1 (an empty cell).

Starting from the point (0, 0), return the minimum steps you need to walk to cut off all the trees. If you cannot cut off all the trees, return -1.

You are guaranteed that no two trees have the same height, and there is at least one tree needs to be cut off.

 

Example 1:


Input: forest = [[1,2,3],[0,0,4],[7,6,5]]
Output: 6
Explanation: Following the path above allows you to cut off the trees from shortest to tallest in 6 steps.
Example 2:


Input: forest = [[1,2,3],[0,0,0],[7,6,5]]
Output: -1
Explanation: The trees in the bottom row cannot be accessed as the middle row is blocked.
Example 3:

Input: forest = [[2,3,4],[0,0,5],[8,7,6]]
Output: 6
Explanation: You can follow the same path as Example 1 to cut off all the trees.
Note that you can cut off the first tree at (0, 0) before making any steps.
 

Constraints:

m == forest.length
n == forest[i].length
1 <= m, n <= 50
0 <= forest[i][j] <= 10^9


*/
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <deque>
#include <map>

using std::map;
using std::deque;
using std::vector;
using std::queue;

class CutOffTree {

    /*
                675.Cut-Off-Trees-for-Golf-Event
        典型的用BFS求最短路径的问题。
    */
    int cutOffTree(vector<vector<int>>& forest) 
    {
        map<int, std::pair<int,int>>Map;
        int M=forest.size();
        int N=forest[0].size();
        
        for (int i=0; i<M; i++)
         for (int j=0; j<N; j++)
         {
             if (forest[i][j]>1)            
                 Map[forest[i][j]]={i,j};             
         }
        
        int x=0;
        int y=0;
        int result=0;
        for (auto a:Map)
        {
            int m=a.second.first;
            int n=a.second.second;
            
            int step=Go(x,y,m,n,forest);
            if (step==-1) return -1;
            else result+=step;
            x=m;
            y=n;
        }
        
        return result;
            
    }
    
    int Go(int x0, int y0, int m, int n, vector<vector<int>>& forest)
    {
        vector<std::pair<int,int>>dir={{0,1},{0,-1},{1,0},{-1,0}};
        int M=forest.size();
        int N=forest[0].size();
        auto visited=vector<vector<int>>(M,vector<int>(N,0));
        
        queue<std::pair<int,int>>q;
        q.push({x0,y0});
        visited[x0][y0]=1;
        int count=-1;
        
        while (!q.empty())
        {
            int num=q.size();
            count++;
            
            for (int i=0; i<num; i++)
            {
                int x=q.front().first;
                int y=q.front().second;                
                q.pop();
                if (x==m && y==n) return count;                
                                
                for (int k=0; k<4; k++)
                {
                    int a=x+dir[k].first;
                    int b=y+dir[k].second;
                    if (a<0 || a>=M || b<0 || b>=N) continue;
                    if (forest[a][b]==0) continue;
                    if (visited[a][b]==1) continue;
                    q.push({a,b});
                    visited[a][b]=1;
                }
            }
        }
        
        return -1;
    }


public:
    /*
        Approach #1: BFS [Accepted]
        Intuition and Algorithm

        We perform a breadth-first-search, processing nodes (grid positions) in a queue. seen keeps track of nodes that have already been added to the queue at some point - those nodes will be already processed or are in the queue awaiting processing.

        For each node that is next to be processed, we look at it's neighbors. If they are in the forest (grid), they haven't been enqueued, and they aren't an obstacle, we will enqueue that neighbor.

        We also keep a side count of the distance travelled for each node. If the node we are processing is our destination 'target' (tr, tc), we'll return the answer.
    */
    int doit_bfs(vector<vector<int>>& forest) {

        int m = forest.size(), n = forest[0].size();
        vector<std::tuple<int, int, int>> trees;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (forest[i][j] > 1) {
                    trees.push_back({forest[i][j], i, j});
                }
            }
        }

        std::sort(begin(trees), end(trees), [](auto& a, auto& b) {
            return std::get<0>(a) < std::get<0>(b);
        });

        std::function<int(int, int, int, int)> bfs = [&](int sx, int sy, int tx, int ty) {

            vector<vector<bool>> visited(m, vector<bool>(n, false));
            int direction[] = {-1, 0, 1, 0, -1};
            queue<std::pair<int, int>> qu;
            qu.push({sx, sy});
            visited[sx][sy] = true;
            int levels = 0;

            while (!qu.empty()) {
                int size = qu.size();
                while (size--) {
                    
                    auto [x, y] = qu.front();

                    if (x == tx && y == ty) 
                        return levels;

                    for (int i = 0; i < 4; i++) {
                        int x1 = x + direction[i], y1 = y + direction[i+1];
                        if (x1 < 0 || x1 == m || y1 < 0 || y1 == n || visited[x1][y1] || forest[x1][y1] == 0)
                            continue;
                        qu.push({x1, y1});
                        visited[x1][y1] = true;
                    }
                    qu.pop();
                }
                levels++;
            }
            return -1;
        };

        int ans = 0, sx = 0, sy = 0;
        for (int i = 0; i < trees.size(); i++) {
            int tx = std::get<1>(trees[i]), ty = std::get<2>(trees[i]);
            int tmp = bfs(sx, sy, tx, ty);
            if (tmp == -1) return -1;
            ans += tmp;
            sx = tx;
            sy = ty;
        }

        return ans;
    }

    int doit_hadlock_bfs(vector<vector<int>>& forest) {

        int m = forest.size(), n = forest[0].size();
        vector<std::tuple<int, int, int>> trees;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (forest[i][j] > 1) {
                    trees.push_back({forest[i][j], i, j});
                }
            }
        }

        std::sort(begin(trees), end(trees), [](auto& a, auto& b) {
            return std::get<0>(a) < std::get<0>(b);
        });

        std::function<int(int, int, int, int)> bfs = [&](int sx, int sy, int tx, int ty) {

            vector<vector<bool>> visited(m, vector<bool>(n, false));
            deque<std::tuple<int, int, int>> qu;
            qu.push_back({0, sx, sy});
            int levels = 0;

            while (!qu.empty()) {

                auto& c = qu.front();
                int detour = std::get<0>(c), x = std::get<1>(c), y = std::get<2>(c);
                qu.pop_front();

                if (!visited[x][y]) {
                    visited[x][y] = true;
                    
                    if (x == tx && y == ty) 
                        return detour * 2 + abs(sx - tx) + abs(sy - ty);


                    for (auto [x1, y1, closer]: vector<std::tuple<int, int, int>>{{x-1, y, x > tx}, {x+1, y, x < tx}, {x, y-1, y > ty}, {x, y + 1, y < ty}}) {
                        if (x1 < 0 || x1 == m || y1 < 0 || y1 == n || forest[x1][y1] == 0)
                            continue;
                        if (closer) {
                            qu.push_front({detour, x1, y1});
                        } else {
                            qu.push_back({detour+1, x1, y1});
                        }
                    }
                }
            }
            return -1;
        };

        int ans = 0, sx = 0, sy = 0;
        for (int i = 0; i < trees.size(); i++) {
            int tx = std::get<1>(trees[i]), ty = std::get<2>(trees[i]);
            int tmp = bfs(sx, sy, tx, ty);
            if (tmp == -1) return -1;
            ans += tmp;
            sx = tx;
            sy = ty;
        }

        return ans;
    }
};