/*
1139. Largest 1-Bordered Square

Given a 2D grid of 0s and 1s, return the number of elements in the largest square subgrid that has all 1s on its border, or 0 if such a subgrid doesn't exist in the grid.

 

Example 1:

Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
Output: 9
Example 2:

Input: grid = [[1,1,0,0]]
Output: 1
 

Constraints:

1 <= grid.length <= 100
1 <= grid[0].length <= 100
grid[i][j] is 0 or 1

*/
#include <vector>

using std::vector;

class LargestBorderedSquare {

public:

    /*
        Explanation
        Count the number of consecutive 1s on the top and on the left.
        From length of edge l = min(m,n) to l = 1, check if the 1-bordered square exist.

        Complexity
        Time O(N^3)
        Space O(N^2)
    */
    int largest1BorderedSquare(vector<vector<int>>& A) {
        int m = A.size(), n = A[0].size();
        vector<vector<int>> left(m, vector<int>(n)), top(m, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                left[i][j] = A[i][j] + (j && A[i][j] ? left[i][j - 1] : 0);
                top[i][j] = A[i][j] + (i && A[i][j] ? top[i - 1][j] : 0);
            }
        }
        for (int l = std::min(m, n); l > 0; --l)
            for (int i = 0; i < m - l + 1; ++i)
                for (int j = 0; j < n - l + 1; ++j)
                    if (std::min({top[i + l - 1][j], top[i + l - 1][j + l - 1], left[i][j + l - 1], left[i + l - 1][j + l - 1]}) >= l)
                        return l * l;
        return 0;
    }
}