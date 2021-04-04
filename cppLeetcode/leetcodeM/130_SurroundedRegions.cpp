/*
130. Surrounded Regions

Given an m x n matrix board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

 

Example 1:


Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
Explanation: Surrounded regions should not be on the border, which means that any 'O' on the border of the board are not flipped to 'X'. 
Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'. Two cells are connected if they are adjacent cells connected horizontally or vertically.
Example 2:

Input: board = [["X"]]
Output: [["X"]]
 

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 200
board[i][j] is 'X' or 'O'.

*/

#include <queue>
#include <vector>
#include <unordered_map>
#include <functional>

using std::unordered_map;
using std::vector;
using std::queue;


class SurroundRegions {

    /*
        130.Surrounded-Regions
        BFS
        此题用BFS的想法会更直接。找到所有在边界上的O点，以其为基础做BFS的扩散，标记为#。最后，所有剩余的O都转化为X。

        注意，在BFS队列的处理中，进队列的时候就标记#，而不是在出队列的时候。这样能够避免很多各自的重复入列。

        Union Find
        遍历时忽略所有的X，仅对所有的O进行集合编组。注意，在初始编组中，我们对所有在边界上的O点统一编组为-1，非边界上的O点编组序号为其本身的index。

        在第二遍遍历的过程中，我们对所有想邻接的O点进行Union。Union的规则其实不需要改动，因为-1永远比任何index而言都是最小的，按照最小编号进行Union的法则，所有与边界相通的O点都可以最终归为-1. 
        但要注意的是，在FindSet的操作中需要特殊的操作，需要判断if (Father[x]==-1) return -1;因为对于与边界相邻的O点，其递归的终点不是x==Father[x]而是-1.
    */
public:
    void solve(vector<vector<char>>& board) 
    {
        int M=board.size();
        if (M==0) return;
        int N=board[0].size();
        
        for (int i=0; i<M; i++)
        {
            if (board[i][0]=='O') BFS(i,0,board);
            if (board[i][N-1]=='O') BFS(i,N-1,board);
        }
        
        for (int j=0; j<N; j++)
        {
            if (board[0][j]=='O') BFS(0,j,board);
            if (board[M-1][j]=='O') BFS(M-1,j,board);
        }
        
        for (int i=0; i<M; i++)
         for (int j=0; j<N; j++)
         {
             if (board[i][j]=='#') 
                 board[i][j]='O';
             else if (board[i][j]=='O') 
                 board[i][j]='X';
         }        
            
    }
    
    void BFS(int i, int j, vector<vector<char>>& board)
    {
        vector<std::pair<int,int>>dir={{1,0},{-1,0},{0,1},{0,-1}};
        queue<std::pair<int,int>>q;
        q.push({i,j});
        board[i][j]='#';
        int M=board.size();
        int N=board[0].size();
        
        while (!q.empty())
        {
            int x=q.front().first;
            int y=q.front().second;            
            q.pop();
            
            for (int k=0; k<4; k++)
            {
                int m=x+dir[k].first;
                int n=y+dir[k].second;
                if (m<0||m>=M||n<0||n>=N)
                    continue;
                if (board[m][n]!='O')
                    continue;
                board[m][n]='#';
                q.push({m,n});
            }
        }
    }

public:

    unordered_map<int,int>Father;
    int M;
    int N;

    void solve(vector<vector<char>>& board)
    {
        M=board.size();
        if (M==0) return;
        N=board[0].size();
        for (int i=0; i<M; i++)
         for (int j=0; j<N; j++)
         {
             if (board[i][j]=='X') continue;
             if (i==0 || i==M-1 || j==0 || j==N-1)
                 Father[i*N+j]=-1;
             else
                 Father[i*N+j]=i*N+j;
         }

        vector<std::pair<int,int>>dir={{1,0},{-1,0},{0,1},{0,-1}};
        for (int i=0; i<M; i++)
         for (int j=0; j<N; j++)
         {
             if (board[i][j]=='X') continue;
             for (int k=0; k<4; k++)
             {
                 int x=i+dir[k].first;
                 int y=j+dir[k].second;
                 if (x<0||x>=M||y<0||y>=N) continue;
                 if (board[x][y]=='X') continue;
                 if (FindSet(x*N+y)!=FindSet(i*N+j))
                     Union(x*N+y,i*N+j);
             }
         }

        for (int i=0; i<M; i++)
         for (int j=0; j<N; j++)
         {
             if (board[i][j]=='X') continue;
             if (FindSet(i*N+j)!=-1)
                 board[i][j]='X';
         }
    }

    int FindSet(int x)
    {
        if (Father[x]==-1)
            return -1;
        if (Father[x]!=x)
        {
            Father[x]=FindSet(Father[x]);
        }
        return Father[x];
    }

    void Union(int x,int y)
    {
        x=Father[x];
        y=Father[y];
        
        bool flag;
        if (x/N<y/N)
            flag=1;
        else if (x%N==y%N)
            flag=1;
        else
            flag=0;
        
        if (flag)        
            Father[y]=x;        
        else    
            Father[x]=y;        
    }


public:
    
    void doit_dfs(vector<vector<char>>& board) {
        
        int m = board.size();
        if (m == 0) return;
        
        int n = board[0].size();
        if (n == 0) return;
        
        int dir[5] = {-1, 0, 1, 0, -1};
        
        std::function<void(int, int)> dfs = [&](int i, int j) {
          
            if (board[i][j] != 'O') return;
            
            board[i][j] = '1';
            
            for (int k = 0; k < 4; k++) {
                int x = i + dir[k], y = j + dir[k+1];
                
                if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] != 'O') continue;
                
                dfs(x, y);
            }
        };
        
        for (int i = 0; i < m; i++) {
            dfs(i, 0);
            dfs(i, n-1);
        }
        
        for (int j = 1; j < n-1; j++) {
            dfs(0, j);
            dfs(m-1, j);
        }
        
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '1')
                    board[i][j] = 'O';
                else if (board[i][j] == 'O')
                    board[i][j] = 'X';
            }
        }
    }
};