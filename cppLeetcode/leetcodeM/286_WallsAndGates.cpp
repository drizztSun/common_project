/*
286. Walls and Gates

You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

Example: 

Given the 2D grid:

INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
After running your function, the 2D grid should be:

  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4


*/
#include <vector>
#include <queue>


using std::queue;
using std::vector;


class WallsAndGates {

public:
    
    void doit_(vector<vector<int>>& rooms) {
        if (rooms.empty()) return;
        
        int m = rooms.size(), n = rooms[0].size();
        int INF = 2147483647;
        queue<int> qu;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (rooms[i][j] == 0) qu.push(i * n + j);

        while (!qu.empty()) {

            int size = qu.size();
            while (size--) {

                int x = qu.front()/n, y = qu.front()%n;
                qu.pop();

                for (auto delta : vector<std::pair<int, int>>{{0, -1}, {0, 1}, {1, 0}, {-1, 0}}) {
                    int x1 = x + delta.first, y1 = y + delta.second;
                    if (x1 < 0 || x1 == m || y1 < 0 || y1 == n || rooms[x1][y1] != INF) continue;

                    rooms[x1][y1] = rooms[x][y] + 1;
                    qu.push(x1 * n + y1);
                }
            }
        }
    }
};