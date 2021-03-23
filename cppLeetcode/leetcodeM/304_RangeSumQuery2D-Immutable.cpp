/*
304. Range Sum Query 2D - Immutable

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Implement the NumMatrix class:

NumMatrix(int[][] matrix) initializes the object with the integer matrix matrix.
int sumRegion(int row1, int col1, int row2, int col2) returns the sum of the elements of the matrix array inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
 

Example 1:


Input
["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
[[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [1, 1, 2, 2], [1, 2, 2, 4]]
Output
[null, 8, 11, 12]

Explanation
NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e sum of the red rectangele).
numMatrix.sumRegion(1, 1, 2, 2); // return 11 (i.e sum of the green rectangele).
numMatrix.sumRegion(1, 2, 2, 4); // return 12 (i.e sum of the blue rectangele).
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
-105 <= matrix[i][j] <= 105
0 <= row1 <= row2 < m
0 <= col1 <= col2 < n
At most 104 calls will be made to sumRegion.

*/

#include <vector>

using std::vector;

class NumMatrix {

    vector<vector<int>> _rangesums;

public:
    
    NumMatrix(vector<vector<int>>& matrix) {

        int m = matrix.size();
        int n = matrix[0].size();

        _rangesums.resize(m+1, vector<int>(n+1, 0));

        for (int i = 1; i < _rangesums.size(); i++) {
            int total = 0;
            for (int j = 1; j < _rangesums[0].size(); j++) {
                total += matrix[i-1][j-1];
                _rangesums[i][j] += total + (i > 0 ? _rangesums[i-1][j] : 0);
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        
        return _rangesums[row2+1][col2+1] + _rangesums[row1][col1] - _rangesums[row2+1][col1] - _rangesums[row1][col2+1];
    }
};