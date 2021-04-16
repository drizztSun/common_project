/*
1263. Minimum Moves to Move a Box to Their Target Location



Storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.

The game is represented by a grid of size m x n, where each element is a wall, floor, or a box.

Your task is move the box 'B' to the target position 'T' under the following rules:

1) Player is represented by character 'S' and can move up, down, left, right in the grid if it is a floor (empy cell).
2) Floor is represented by character '.' that means free cell to walk.
3) Wall is represented by character '#' that means obstacle  (impossible to walk there). 

There is only one box 'B' and one target cell 'T' in the grid.
The box can be moved to an adjacent free cell by standing next to the box and then moving in the direction of the box. This is a push.
The player cannot walk through the box.
Return the minimum number of pushes to move the box to the target. If there is no way to reach the target, return -1.

 

Example 1:



Input: grid = [["#","#","#","#","#","#"],
               ["#","T","#","#","#","#"],
               ["#",".",".","B",".","#"],
               ["#",".","#","#",".","#"],
               ["#",".",".",".","S","#"],
               ["#","#","#","#","#","#"]]
Output: 3
Explanation: We return only the number of times the box is pushed.
Example 2:

Input: grid = [["#","#","#","#","#","#"],
               ["#","T","#","#","#","#"],
               ["#",".",".","B",".","#"],
               ["#","#","#","#",".","#"],
               ["#",".",".",".","S","#"],
               ["#","#","#","#","#","#"]]
Output: -1
Example 3:

Input: grid = [["#","#","#","#","#","#"],
               ["#","T",".",".","#","#"],
               ["#",".","#","B",".","#"],
               ["#",".",".",".",".","#"],
               ["#",".",".",".","S","#"],
               ["#","#","#","#","#","#"]]
Output: 5
Explanation:  push the box down, left, left, up and up.
Example 4:

Input: grid = [["#","#","#","#","#","#","#"],
               ["#","S","#",".","B","T","#"],
               ["#","#","#","#","#","#","#"]]
Output: -1
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m <= 20
1 <= n <= 20
grid contains only characters '.', '#',  'S' , 'T', or 'B'.
There is only one character 'S', 'B' and 'T' in the grid.


*/

#include <vector>
#include <deque>

using std::deque;
using std::vector;


class MinPushBox {

    /*
        1263.Minimum-Moves-to-Move-a-Box-to-Their-Target-Location
        这道题可以用比较粗暴的BFS来实现。每个状态包括(bx,by,px,py)表示box和person的坐标，同时用一个四维数组flag[bx][by][px][py]来记录到达这个状态需要多少次移动（move）。

        每次从队列中弹出一个状态，我们就遍历person朝四个方向可以变动的位置，再加入队列之中。注意到这个新状态对应的最少移动次数flag[bx][by][px_new][py_new]=flag[bx][by][px][py]不会变化，
        但如果我们仍然依照传统BFS的策略将这个新状态加入队列末尾，可能会导致队列中的状态所对应的move不是递增的，最终无法搜索到正确的最少move次数。解决方法是：用deque而不是queue，将这个新状态加入到队列的首端而不是末端！完美！

        对于每次从队列中弹出的一个状态，我们还需要查看person是否就在box的四周且可以推动它。如果是的话，我们就推动盒子，从而得到新的状态(bx_new,by_new,bx,by)。
        易知flag[bx_new][by_new][bx][by]=flag[bx][by][px][py]+1。所以我们应该将这个新状态应该加入双端队列的末尾！

        这种用双端队列来实现BFS的技巧，值得好好体会！
    */

    struct Node {
        int bx, by, px, py;
    };

    int minPushBox_bfs_dp(vector<vector<char>>& grid) 
    {
        int m = grid.size();
        int n = grid[0].size();
        int bx,by,px,py,tx,ty;
        
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                if (grid[i][j]=='S')
                {
                    px = i, py = j;
                    grid[i][j] = '.';
                }
                else if (grid[i][j]=='B')
                {
                    bx = i, by = j;
                    grid[i][j] = '.';
                }
                else if (grid[i][j]=='T')
                {
                    tx = i, ty = j;
                    grid[i][j] = '.';
                }
            }
        
        deque<Node>q;
        q.push_back({bx,by,px,py});
        int memo[21][21][21][21];
        memset(memo, 255, sizeof(memo));
        memo[bx][by][px][py] = 0;
        auto dir = vector<std::pair<int,int>>({{1,0},{-1,0},{0,1},{0,-1}});
        
        while (!q.empty())
        {
            auto [bx, by, px, py] = q.front();
            q.pop_front();
            if (bx==tx && by==ty)
                return memo[bx][by][px][py];
            
            for (int k=0; k<4; k++)
            {
                int x = px+dir[k].first;
                int y = py+dir[k].second;
                if (x<0||x>=m||y<0||y>=n) continue;
                if (grid[x][y]!='.') continue;
                if (x==bx && y==by) continue;
                if (memo[bx][by][x][y]>=0) continue;
                memo[bx][by][x][y] = memo[bx][by][px][py];
                q.push_front({bx,by,x,y});               
            }
            if (abs(px-bx)+abs(py-by)==1)
            {
                for (int k=0; k<4; k++)
                {
                    if (px+dir[k].first==bx && py+dir[k].second==by)
                    {
                        int bx2 = bx+dir[k].first;
                        int by2 = by+dir[k].second;
                        if (bx2<0||bx2>=m||by2<0||by2>=n) continue;
                        if (grid[bx2][by2]!='.') continue;
                        if (memo[bx2][by2][bx][by]>=0) continue;
                        memo[bx2][by2][bx][by] = memo[bx][by][px][py]+1;
                        q.push_back({bx2,by2,bx,by});
                    }
                }
            }
        }
        return -1;
    }
};