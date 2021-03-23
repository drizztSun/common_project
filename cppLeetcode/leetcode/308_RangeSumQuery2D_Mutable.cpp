/*
308. Range Sum Query 2D - Mutable

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Implement the NumMatrix class:

NumMatrix(int[][] matrix) initializes the object with the integer matrix matrix.
void update(int row, int col, int val) updates the value of matrix[row][col] to be val.
int sumRegion(int row1, int col1, int row2, int col2) returns the sum of the elements of the matrix array inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
 

Example 1:


Input
["NumMatrix", "sumRegion", "update", "sumRegion"]
[[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [3, 2, 2], [2, 1, 4, 3]]
Output
[null, 8, null, 10]

Explanation
NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8
numMatrix.update(3, 2, 2);
numMatrix.sumRegion(2, 1, 4, 3); // return 10
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
-105 <= matrix[i][j] <= 105
0 <= row < m
0 <= col < n
-105 <= val <= 105
0 <= row1 <= row2 < m
0 <= col1 <= col2 < n
At most 104 calls will be made to sumRegion and update.


*/
#include <vector>
using std::vector;


class NumMatrix_BIT {

	vector<vector<int>> _bits;
	vector<vector<int>> _matrix;

	int _rangesums(int i, int j) {

		int total = 0;
		while (j > 0) {
			total += _bits[i][j];
			j -= j & (-j);
		}
		return total;
	}

public:

	NumMatrix_BIT(vector<vector<int>>& matrix) {

		int m = matrix.size(), n = matrix[0].size();
		_bits.resize(m, vector<int>(n + 1, 0));
		_matrix = matrix;

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				int base = j + 1;
				while (base < n + 1) {
					_bits[i][base] += matrix[i][j];
					base += base & (-base);
				}
			}
		}
	}

	void update(int row, int col, int val) {

		int diff = val - _matrix[row][col];
		_matrix[row][col] = val;
		col++;
		while (col < _bits[0].size()) {
			_bits[row][col] += diff;
			col += col & (-col);
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		int total = 0;
		for (int i = row1; i <= row2; i++) {
			total += _rangesums(i, col2 + 1) - _rangesums(i, col1);
		}
		return total;
	}
};
