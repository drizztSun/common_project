#include <vector>

using std::vector;

class Matrix {

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