/*
529. Minesweeper

Let's play the minesweeper game (Wikipedia, online game)!

You are given a 2D char matrix representing the game board. 'M' represents an unrevealed mine, 'E' represents an unrevealed empty square, 'B' represents a revealed blank square that has no adjacent (above, below, left, right, and all 4 diagonals) mines, digit ('1' to '8') represents how many mines are adjacent to this revealed square, and finally 'X' represents a revealed mine.

Now given the next click position (row and column indices) among all the unrevealed squares ('M' or 'E'), return the board after revealing this position according to the following rules:

If a mine ('M') is revealed, then the game is over - change it to 'X'.
If an empty square ('E') with no adjacent mines is revealed, then change it to revealed blank ('B') and all of its adjacent unrevealed squares should be revealed recursively.
If an empty square ('E') with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
Return the board when no more squares will be revealed.
 

Example 1:

Input: 

[['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'M', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E']]

Click : [3,0]

Output: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Explanation:

Example 2:

Input: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Click : [1,2]

Output: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'X', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Explanation:

 

Note:

The range of the input matrix's height and width is [1,50].
The click position will only be an unrevealed square ('M' or 'E'), which also means the input board contains at least one clickable square.
The input board won't be a stage when game is over (some mines have been revealed).
For simplicity, not mentioned rules should be ignored in this problem. For example, you don't need to reveal all the unrevealed mines when the game is over, consider any cases that you will win the game or flag any squares.


*/


#include <functional>
#include <vector>
#include <queue>

using std::queue;
using std::vector;

class MineSweeper {

    /*
        529.Minesweeper
        此题首选BFS，基础题，但队列中的操作需要仔细考虑成熟。

        我们点击一个格子，首先判断是否是M，是的话直接返回。

        如果是非M，我们就考察周围8个格子，计算他们中间有地雷的个数。如果有地雷的话，那么就将这个格子标记数字，结束对这个格子的操作。特别注意，这个时候不能直接返回board，因为队列中还有很多各自没处理呢。
        如果一圈都没有地雷的话，就标记'B'，并把这一圈的格子加入队列处理。

        上面的操作可行，但是会MLE。一个格子A将周围的8个收入队列中，而它相邻的格子B也会将周围的8个收入队列中，会有大量的重复。所以需要一个visited来记录每个已经收入队列中的格子，已经收录的就不要再收了。
    */
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) 
    {
        int M = board.size();
        int N = board[0].size();
        
        if (board[click[0]][click[1]]=='M')
        {
            board[click[0]][click[1]] = 'X';
            return board;
        }
        
        auto visited = vector<vector<int>>(M,vector<int>(N,0));
        auto dir = vector<std::pair<int,int>>({{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}});
        
        queue<std::pair<int,int>>q;
        q.push({click[0],click[1]});
        visited[click[0]][click[1]] = 1;
        
        while (!q.empty())
        {
            int x0 = q.front().first;
            int y0 = q.front().second;
            q.pop();
            
            int count = 0;
            vector<std::pair<int,int>>next;
            
            for (int k=0; k<8; k++)
            {
                int x = x0+dir[k].first;
                int y = y0+dir[k].second;
                
                if (x<0||x>=M||y<0||y>=N)
                    continue;
                
                if (board[x][y]=='M')
                    count++;
                else
                {
                    if (visited[x][y]==0)
                        next.push_back({x,y});
                }
            }
            
            if (count==0)
            {
                board[x0][y0] = 'B';
                for (auto p: next)
                {
                    q.push(p);
                    visited[p.first][p.second] = 1;
                }  
            }
            else
            {
                board[x0][y0] = '0'+count;
            }
        }
        
        return board;
    }

public:

    vector<vector<char>> doit_dfs(vector<vector<char>>& board, vector<int>& click) {

        int M = board.size();
        int N = board[0].size();
        
        if (board[click[0]][click[1]]=='M')
        {
            board[click[0]][click[1]] = 'X';
            return board;
        }
        
        auto visited = vector<vector<int>>(M,vector<int>(N,0));
        auto dir = vector<std::pair<int,int>>({{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}});

        std::function<void(int, int)> dfs = [&](int i, int j) {
            if (visited[i][j] == 1 || board[i][j] != 'E') return;
            
            int count = 0;
            vector<std::pair<int,int>> next;
            for (int k=0; k<8; k++)
            {
                int x = i+dir[k].first;
                int y = j+dir[k].second;
                
                if (x<0||x>=M||y<0||y>=N)
                    continue;
                
                if (board[x][y]=='M')
                    count++;
                else
                {
                    if (visited[x][y]==0)
                        next.push_back({x,y});
                }
            }

            visited[i][j] = 1;

            if (count == 0) {
                board[i][j] = 'B';

                for (auto c: next)
                    dfs(c.first, c.second);
            } else {
                board[i][j] = count + '0';
            }
        };

        dfs(click[0], click[1]);
        return board;
    }
};