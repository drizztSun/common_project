/*
311. Sparse Matrix Multiplication


Given two sparse matrices A and B, return the result of AB.

You may assume that A's column number is equal to B's row number.

Example:

Input:

A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]

B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]

Output:

     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |
 

Constraints:

1 <= A.length, B.length <= 100
1 <= A[i].length, B[i].length <= 100
-100 <= A[i][j], B[i][j] <= 100

*/


#include <vector>

using std::vector;


class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {

        int m = A.size(), p = A[0].size(), n = B[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {
                int base = 0;
                for (int k = 0; k < p; k++) {
                    base += A[i][k] * B[k][j];
                }
                ans[i][j] = base;
            }
        }
        return ans;
    }
};