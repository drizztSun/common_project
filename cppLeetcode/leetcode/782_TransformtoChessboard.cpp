/*

# 782. Transform to Chessboard

# An N x N board contains only 0s and 1s. In each move, you can swap any 2 rows with each other,
# or any 2 columns with each other.

# What is the minimum number of moves to transform the board into a "chessboard" - a board
# where no 0s and no 1s are 4-directionally adjacent? If the task is impossible, return -1.

# Examples:
# Input: board = [[0,1,1,0],
#                 [0,1,1,0],
#                 [1,0,0,1],
#                 [1,0,0,1]]
# Output: 2
# Explanation:
# One potential sequence of moves is shown below, from left to right:

# 0110     1010     1010
# 0110 --> 1010 --> 0101
# 1001     0101     1010
# 1001     0101     0101

# The first move swaps the first and second column.
# The second move swaps the second and third row.


# Input: board = [[0, 1], [1, 0]]
# Output: 0
# Explanation:
# Also note that the board with 0 in the top left corner,
# 01
# 10

# is also a valid chessboard.

# Input: board = [[1, 0], [1, 0]]
# Output: -1
# Explanation:
# No matter what sequence of moves you make, you cannot end with a valid chessboard.
# Note:

# board will have the same number of rows and columns, a number in the range [2, 30].
# board[i][j] will be only 0s or 1s.



*/

#include <vector>
#include <algorithm>
using namespace std;


class MovesToChessboard {
public:
	int doit(vector<vector<int>>& board) {

		int N = board.size();

		for (auto i = 0; i < board.size(); i++)
			for (auto j = 0; j < board[0].size(); j++)
				if (board[0][0] ^ board[0][j] ^ board[i][0] ^ board[i][j])
					return -1;

		int lnum = 0, rnum = 0;
		int col = 0, row = 0;
		for (auto i = 0; i < board.size(); i++) {
			if (board[0][i] == 1)
				lnum++;
			col += board[0][i] == i % 2 ? 1 : 0;
			

			if (board[i][0] == 1)
				rnum++;
			row += board[i][0] == i % 2 ? 1 : 0;				
		}


		if (!(lnum >= N / 2 && lnum <= (N + 1) / 2) || !(rnum >= N / 2 && rnum <= (N + 1) / 2))
			return -1;

		if (N % 2) {
			if (col % 2)
				col = N - col;
			if (row % 2)
				row = N - row;
		}
		else {
			col = col > N - col ? N - col : col;
			row = row > N - row ? N - row : row;
		}

		return (col + row) / 2;
	}

	int doit1(vector<vector<int>>& b) {

		int N = b.size(), rowSum = 0, colSum = 0, rowSwap = 0, colSwap = 0;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				if (b[0][0] ^ b[i][0] ^ b[0][j] ^ b[i][j])
					return -1;

		for (int i = 0; i < N; ++i) {
			rowSum += b[0][i];
			colSum += b[i][0];
			rowSwap += b[i][0] == i % 2;
			colSwap += b[0][i] == i % 2;
		}

		if (N / 2 > rowSum || rowSum > (N + 1) / 2)
			return -1;

		if (N / 2 > colSum || colSum > (N + 1) / 2)
			return -1;

		if (N % 2) {
			if (colSwap % 2)
				colSwap = N - colSwap;

			if (rowSwap % 2)
				rowSwap = N - rowSwap;
		}
		else {
			colSwap = min(N - colSwap, colSwap);
			rowSwap = min(N - rowSwap, rowSwap);
		}
		return (colSwap + rowSwap) / 2;
	}

	int doit2(vector<vector<int>>& board) {
		int N = board.size(), row = 0, col = 0, r = 0, l = 0;
		for (auto i = 1; i < N; i++)
			for (auto j = 1; j < N; j++)
				if (board[0][0] ^ board[0][j] ^ board[i][0] ^ board[i][j])
					return -1;

		for (auto i = 0; i < N; i++) {
			row += board[0][i] == 1 ? 1 : -1;
			col += board[i][0] == 1 ? 1 : -1;

			if (i & 1) {
				r += board[0][i];
				l += board[i][0];
			}
		}

		if (row < -1 || row > 1 || col < -1 || col > 1)
			return -1;

		if (row % 2)
			return min(N / 2 - r, r) + min(N / 2 - l, l);
		else
			return (row > 0 ? r : N / 2 - r) + (col > 0 ? l : N / 2 - l);
	}
};


void Test_782_TransformtoChessboard() {


	int res1 = MovesToChessboard().doit(vector<vector<int>> { {0, 1, 1, 0}, { 0, 1, 1, 0 }, { 1, 0, 0, 1 }, { 1, 0, 0, 1 } } );
	int res2 = MovesToChessboard().doit(vector<vector<int>> { {0, 1}, {1, 0}});
	int res3 = MovesToChessboard().doit(vector<vector<int>> { {1, 0}, {1, 0}});
	int res4 = MovesToChessboard().doit(vector<vector<int>> { {1, 1, 0}, {0, 0, 1}, {0, 0, 1}});

	return;
}