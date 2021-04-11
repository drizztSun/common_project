/*
51. N-Queens

The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

 

Example 1:


Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
Example 2:

Input: n = 1
Output: [["Q"]]
 

Constraints:

1 <= n <= 9
*/

#include <vector>
#include <string>

using std::string;
using std::vector;


class SolveNQueens {

    /*
        
        051.N-Queens
        经典的八皇后问题，用DFS实现的回溯算法。

        根据题目的性质，整个棋盘的布局其实可以用一个一维数组就可以表示:

        vector<int>Q_pos(n); // Q_pos[row]的数值表示第row行可以摆放皇后的位置。
        在第row行找到一个可行的摆放位置后，就可以把找第row+1行的任务交给递归函数去做就行了。核心代码如下：

        for (int col=0; col<n; col++)
        {
            if (isValid(Q_pos,row,col)
            {
            Q_pos[row]=col;
            DFS(Q_pos,row+1,results);
            Q_pos[row]=-1;
            }
        }x
        之所以称之为回溯算法，是因为对于每一行row，可能有若干个候选位置col，需要平行地探索。所以对每个col进行DFS后，都需要重置Q_pos[row]的数值，顾名思义就是重新来一遍。
    */

    vector<vector<string>> solveNQueens(int n) 
    {
        vector<vector<string>>results;
        vector<int>Qpos(n,-1);
        DFS(0,results,Qpos);
        return results;
    }
    
    void DFS(int row, vector<vector<string>>&results, vector<int>&Qpos)
    {
        int n = Qpos.size();
        
        if (row==n)
        {
            vector<string> board;
            for (int i=0; i<n; i++)
            {
                string temp;
                for (int j=0; j<n; j++)
                    temp+='.';
                temp[Qpos[i]]='Q';
                board.push_back(temp);
            }
            results.push_back(board);
        }
        else
        {
            for (int col=0; col<n; col++)
            {
                if (isValid(Qpos,row,col))
                {
                    Qpos[row]=col;
                    DFS(row+1,results,Qpos);
                    Qpos[row]=-1;
                }
            }
        }
    }
    
    bool isValid(vector<int>Qpos, int row, int col)
    {
        for (int i=0; i<row; i++)
        {
            if (Qpos[i]==col || abs(i-row)==abs(Qpos[i]-col))
                return false;
        }
        return true;
    }

public:
    
    vector<vector<string>> doit_(int n) {
        
    }
};