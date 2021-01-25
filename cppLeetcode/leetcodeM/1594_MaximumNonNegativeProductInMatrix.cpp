/*
1594. Maximum Non Negative Product in a Matrix

You are given a rows x cols matrix grid. Initially, you are located at the top-left corner (0, 0), and in each step, you can only move right or down in the matrix.

Among all possible paths starting from the top-left corner (0, 0) and ending in the bottom-right corner (rows - 1, cols - 1), find the path with the maximum non-negative product. 
The product of a path is the product of all integers in the grid cells visited along the path.

Return the maximum non-negative product modulo 109 + 7. If the maximum product is negative return -1.

Notice that the modulo is performed after getting the maximum product.

 

Example 1:

Input: grid = [[-1,-2,-3],
               [-2,-3,-3],
               [-3,-3,-2]]
Output: -1
Explanation: It's not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.
Example 2:

Input: grid = [[1,-2,1],
               [1,-2,1],
               [3,-4,1]]
Output: 8
Explanation: Maximum non-negative product is in bold (1 * 1 * -2 * -4 * 1 = 8).
Example 3:

Input: grid = [[1, 3],
               [0,-4]]
Output: 0
Explanation: Maximum non-negative product is in bold (1 * 0 * -4 = 0).
Example 4:

Input: grid = [[ 1, 4,4,0],
               [-2, 0,0,1],
               [ 1,-1,1,1]]
Output: 2
Explanation: Maximum non-negative product is in bold (1 * -2 * 1 * -1 * 1 * 1 = 2).
 

Constraints:

1 <= rows, cols <= 15
-4 <= grid[i][j] <= 4

*/
#include <vector>

using std::vector;

class MaxProductPath {

public:

    int doit_dp(vector<vector<int>>& grid) {

        const int n = grid.size(), m = grid[0].size();

        vector<vector<int>> dpMax(n, vector<int>(m, -100LL));
        vector<vector<int>> dpMin(n, vector<int>(m, 100LL));

        dpMax[0][0] = dpMin[0][0] = grid[0][0];

        vector<std::pair<int,int>> dr = {{0,-1}, {-1,0}};

        int hMod = 1e9 + 7;
        
        for(int i=0;i<n;i++) 
            for(int j=0;j<m;j++){
                for(auto [di, dj] : dr){
                    
                    int x = i+di, y = j+dj;
                    if(x<0 || y<0) continue;

                    dpMax[i][j] = std::max(dpMax[i][j], grid[i][j] * dpMax[x][y] );
                    dpMax[i][j] = std::max(dpMax[i][j], grid[i][j] * dpMin[x][y] );

                    dpMin[i][j] = std::min(dpMin[i][j], grid[i][j] * dpMax[x][y] );
                    dpMin[i][j] = std::min(dpMin[i][j], grid[i][j] * dpMin[x][y] );
            }
        }
        
        
        return std::max({-1LL, dpMax[n-1][m-1], dpMin[n-1][m-1]}) % hMod;
    }
};