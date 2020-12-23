/*
1210. Minimum Moves to Reach Target with Rotations


In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1).
The grid has empty cells represented by zeros and blocked cells represented by ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).

In one move the snake can:

1) Move one cell to the right if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
2) Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
3) Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).
4) Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).

Return the minimum number of moves to reach the target.

If there is no way to reach the target, return -1.



Example 1:



Input: grid = [[0,0,0,0,0,1],
               [1,1,0,0,1,0],
               [0,0,0,0,1,1],
               [0,0,1,0,1,0],
               [0,1,1,0,0,0],
               [0,1,1,0,0,0]]
Output: 11
Explanation:
One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right, down].
Example 2:

Input: grid = [[0,0,1,1,1,1],
               [0,0,0,0,1,1],
               [1,1,0,0,0,1],
               [1,1,1,0,0,1],
               [1,1,1,0,0,1],
               [1,1,1,0,0,0]]
Output: 9


Constraints:

2 <= n <= 100
0 <= grid[i][j] <= 1
It is guaranteed that the snake starts at empty cells.



*/
#include <stdio.h>
#include <vector>


using std::vector;


class MinimumMovesToReachTargetWithRotation {
    
public:
    
    /*
     
     When we see a (likely) DP problem, we should think about what is important (quote by Erricto). The important here is the position of the snake, that is: the coordinates of the tail, and the direction.
     So, the state of the snake on the board can be represent with a triplet [x,y,z] with [x,y] is coordinates of the tail, and z = 0 if horizontal and z = 1 if vertical.
     When the states are well defined, we can use dfs with memorization to solve the problem easily, as all possible transitions from one state to other states is clearly defined in the description.

     One small notes is you should not rotate two times in a row. Use a variable rotate to check it.
     */
    
    int doit_dfs_dp(vector<vector<int>>&& grid) {
        
        int n = grid.size();
        vector<vector<vector<int>>> cache(n, vector<vector<int>>(n, vector<int>(2)));
        int INF = 1e9 + 7;
        
        std::function<int(int, int, int, int)> dfs = [&](int x, int y, int z, int rotate) {
            
            int nx = z == 0? x: x+1;
            int ny = z == 0? y+1: y;
            
            if (x >= n || y >= n || nx >= n || ny >= n)
                return INF;
            
            if (cache[x][y][z] > 0)
                return cache[x][y][z];
            
            if (grid[x][y] == 1 || grid[nx][ny] == 1)
                return INF;
            
            if (x == n-1 && y == n-2 && z == 0)
                return 0;
            
            int res = INF;
            
            // move right
            res = std::min(res, dfs(x, y+1, z, 0));
            
            // move down
            res = std::min(res, dfs(x+1, y, z, 0));
            
            // rotate
            if (!rotate && x+1 < n && y+1 < n && grid[x+1][y+1] == 0) {
                res = std::min(res, dfs(x, y, 1^z, 1));
            }
            
            return cache[x][y][z] = res == INF ? INF : (res + 1);
        };
        
        int ret = dfs(0, 0, 0, 0);
        
        return ret == INF ? -1 : ret;
    }
};


void test_1210_minimum_moves_to_reach() {
    
    
    MinimumMovesToReachTargetWithRotation().doit_dfs_dp(vector<vector<int>>{{0,0,0,0,0,1}, {1,1,0,0,1,0},{0,0,0,0,1,1},{0,0,1,0,1,0},{0,1,1,0,0,0},{0,1,1,0,0,0}});
    
}
