/*

37. Sudoku Solver

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
The '.' character indicates empty cells.

 

Example 1:


Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
Explanation: The input board is shown above and the only valid solution is shown below:


 

Constraints:

board.length == 9
board[i].length == 9
board[i][j] is a digit or '.'.
It is guaranteed that the input board has only one solution.
*/

#include <vector>
using namespace std;

// <backtracking>
class SolveSudoku {

	/*
		037.Sudoku-Solver
		常规的回溯和深度遍历。在每一个空格上，尝试1-9，每填一个数都需要查验是否和已有数字重复（三个方向）以及进行下一步的递归。

		特别注意，如果所有的后续递归都返回失败的话，这个空格还需要重新置空再返回。
	*/
	void solveSudoku(vector<vector<char>>& board) 
    {
       if (board.size()!=9 || board[0].size()!=9) return;
       bool temp = DFS(board, 0, 0);
    }
    
    bool DFS(vector<vector<char>>& board, int i, int j)
    {
        if (i==9) return true;
        if (j==9) return DFS(board, i+1, 0);
        if (board[i][j]!='.') return DFS(board, i, j+1);
        
        for (int k='1'; k<='9'; k++)
        {
            board[i][j]=k;
            if (isValid(board,i,j) && DFS(board, i, j+1))
                return true;            
        }
        board[i][j]='.';
        return false;
    }
    
    bool isValid(vector<vector<char>>& board, int i, int j)
    {
        for (int row=0; row<9; row++)
        {
            if (row!=i && board[row][j]==board[i][j])
                return false;
        }
        for (int col=0; col<9; col++)
        {
            if (col!=j && board[i][col]==board[i][j])
                return false;
        }
        int m=i/3*3;
        int n=j/3*3;
        for (int p=m; p<m+3; p++)
         for (int q=n; q<n+3; q++)
         {
             if ((p!=i||q!=j)&&board[p][q]==board[i][j])
                 return false;
         }
        return true;
    }

public:


	int verifyBoard(const vector<vector<char>> & board, vector<int> points) {

		char base = '1';
		vector<bool> column(9, false);
		int col_num = 0;
		for (auto i = 0; i < 9; i++) {
			if (board[i][points[1]] != '.') {
				if (column[board[i][points[1]] - base])
					return -1;
				else {
					column[board[i][points[1]] - base] = true;
					col_num++;
				}
			}
		}

		vector<bool> row(9, false);
		int row_num = 0;
		for (auto i = 0; i < 9; i++) {
			if (board[points[0]][i] != '.') {
				if (row[board[points[0]][i] - base])
					return -1;
				else {
					row[board[points[0]][i] - base] = true;
					row_num++;
				}
			}
		}

		vector<bool> square(9, false);
		int r = points[0] - points[0] % 3, l = points[1] - points[1] % 3;
		int square_num = 0;
		for (int i = r; i < r + 3; i++)
			for (int j = l; j < l + 3; j++) {
				if (board[i][j] != '.') {
					if (square[board[i][j] - base])
						return -1;
					else {
						square[board[i][j] - base] = true;
						square_num++;
					}
				}
			}

		return col_num == 9 && row_num == 9 && square_num == 9 ? 1 : 0;
	}

public:
	void doit(vector<vector<char>>& board) {

		int N = board.size();
		vector<vector<int>> points;
		for (auto i = 0; i < board.size(); i++)
			for (auto j = 0; j < board[0].size(); j++) {
				if (board[i][j] == '.')
					points.push_back({ i, j, 0});
			}

		
		int i = 0;
		while (i >= 0) {
			
			while (i < points.size() && points[i][2] < 9) {
				
				points[i][2]++;
				int x = points[i][0], y = points[i][1];
				char val = '0' + points[i][2];
				board[x][y] = val;
				
				int res = verifyBoard(board, points[i]);
				if (res != -1) {
					i++;
				} 
			}

			if (i == points.size())
				return;

			if (points[i][2] == 9) {
				int x = points[i][0], y = points[i][1];
				board[x][y] = '.';
				points[i][2] = 0;
			}

			i -= 1;
		}
	}
};

// 
class Solution {
public:
	bool solve(vector<vector<char>>& board, vector<vector<int>>& count, 
		vector<pair<int, int>>& empty_pos, int fill_idx) {

		if (fill_idx == empty_pos.size())
			return true;

		int r = empty_pos[fill_idx].first;
		int c = empty_pos[fill_idx].second;
		int b = r / 3 * 3 + c / 3;
		int mask;

		for (int n = 1; n <= 9; ++n) {
			mask = 1 << (n - 1);
			if (count[0][r] & mask || count[1][c] & mask || count[2][b] & mask)
				continue;

			board[r][c] = '0' + n;
			count[0][r] |= mask;
			count[1][c] |= mask;
			count[2][b] |= mask;

			if (solve(board, count, empty_pos, fill_idx + 1)) {
				return true;
			}
			else {
				board[r][c] = '.';
				count[0][r] ^= mask;
				count[1][c] ^= mask;
				count[2][b] ^= mask;
			}
		}

		return false;
	}

	void solveSudoku(vector<vector<char>>& board) {
		if (board.size() != 9 || board[0].size() != 9)
			return;

		vector<pair<int, int>> empty_pos;
		vector<vector<int>> count(3, vector<int>(9, 0));    // row_count, col_count, box_count
		int b, mask;  // box_index

		for (int r = 0; r < 9; ++r) {
			for (int c = 0; c < 9; ++c) {
				if (board[r][c] == '.') {
					empty_pos.push_back({ r, c });
				}
				else {
					b = r / 3 * 3 + c / 3;
					mask = 1 << (board[r][c] - '0' - 1);
					if (count[0][r] & mask || count[1][c] & mask || count[2][b] & mask)
						return;
					count[0][r] |= mask;
					count[1][c] |= mask;
					count[2][b] |= mask;
				}
			}
		}

		solve(board, count, empty_pos, 0);
	}
};