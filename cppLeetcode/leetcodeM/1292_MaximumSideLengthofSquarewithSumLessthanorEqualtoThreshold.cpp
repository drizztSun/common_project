/*
1292. Maximum Side Length of a Square with Sum Less than or Equal to Threshold


Given a m x n matrix mat and an integer threshold. Return the maximum side-length of a square with a sum less than or equal to threshold or return 0 if there is no such square.

 

Example 1:


Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
Output: 2
Explanation: The maximum side length of square with sum less than 4 is 2 as shown.
Example 2:

Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
Output: 0
Example 3:

Input: mat = [[1,1,1,1],[1,0,0,0],[1,0,0,0],[1,0,0,0]], threshold = 6
Output: 3
Example 4:

Input: mat = [[18,70],[61,1],[25,85],[14,40],[11,96],[97,96],[63,45]], threshold = 40184
Output: 2
 

Constraints:

1 <= m, n <= 300
m == mat.length
n == mat[i].length
0 <= mat[i][j] <= 10000
0 <= threshold <= 10^5

*/

#include <vector>

using std::vector;

class MaxSideLength {

    /*
        1292.Maximum-Side-Length-of-a-Square-with-Sum-Less-than-or-Equal-to-Threshold
        本题可以遍历每个方阵，查看方阵的和sum是否满足条件。这样的时间复杂度是o(N^3)，其中遍历每个元素作为方阵的右下角需要o(N^2)，探索不同的边长需要o(N)。

        本题更高效的方法就是二分搜值。猜测一个边长len，查看是否有一个方阵的sum满足条件。这样的时间复杂度是o(logN*N^2).

        注意，本题中计算一个方阵的sum的方法可以是o(1)，只要提前计算所有(0,0)到(i,j)的矩阵和presum[i][j]。
    */
    int doit_binary_search(vector<vector<int>>& mat, int threshold) 
    {
        int m = mat.size(), n = mat[0].size();   
        vector<vector<int>> presum(m+1, vector<int>(n+1, 0));
                       
        for (int i=1; i<=m; i++)
            for (int j=1; j<=n; j++)
                presum[i][j] = presum[i-1][j]+presum[i][j-1]-presum[i-1][j-1]+mat[i-1][j-1];


        auto isOK = [&] (int len, int threshold)
        {
            for (int i=len; i<=m; i++)
                for (int j=len; j<=n; j++) {
                    int sum = presum[i][j] - presum[i][j-len] - presum[i-len][j] + presum[i-len][j-len];
                    if (sum <= threshold) return true;
                }
            return false;
        };

        int left = 1, right = std::min(m,n);
        while (left < right)
        {
            int mid = right-(right-left)/2;
            if (isOK(mid, threshold))
                left = mid;
            else
                right = mid-1;
        }
        return isOK(left, threshold) ? left : 0;
    }

public:


    int doit_dp(vector<vector<int>>& mat, int threshold) {
        
        const int m = mat.size();
        const int n = mat[0].size();
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int y = 1; y <= m; ++y)
        for (int x = 1; x <= n; ++x)
            dp[y][x] = dp[y][x - 1] + dp[y - 1][x]  - dp[y - 1][x - 1] + mat[y - 1][x - 1];
        
        auto rangeSum = [&](int x1, int y1, int x2, int y2) {
        return dp[y2][x2] - dp[y2][x1 - 1] - dp[y1 - 1][x2] + dp[y1 - 1][x1 - 1];
        };
        
        int ans = 0;
        for (int y = 1; y <= m; ++y)
        for (int x = 1; x <= n; ++x)
            for (int k = 0; y + k <= m && x + k <= n; ++k) {
            if (rangeSum(x, y, x + k, y + k) > threshold) break;
            ans = std::max(ans, k + 1);
            }
        return ans;  
    }

    int doit_dp_binary_search(vector<vector<int>>& mat, int threshold) {
        const int m = mat.size();
        const int n = mat[0].size();
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int y = 1; y <= m; ++y)
        for (int x = 1; x <= n; ++x)
            dp[y][x] = dp[y][x - 1] + dp[y - 1][x]  - dp[y - 1][x - 1] + mat[y - 1][x - 1];
        
        auto rangeSum = [&](int x1, int y1, int x2, int y2) {
        return dp[y2][x2] - dp[y2][x1 - 1] - dp[y1 - 1][x2] + dp[y1 - 1][x1 - 1];
        };
        
        int ans = 0;
        for (int y = 1; y <= m; ++y)
        for (int x = 1; x <= n; ++x) {
            int l = 0;
            int r = std::min(m - y, n - x) + 1;
            while (l < r) {
            int m = l + (r - l) / 2;
            // Find smllest l that > threshold, ans = (l + 1) - 1
            if (rangeSum(x, y, x + m, y + m) > threshold)
                r = m;
            else
                l = m + 1;
            }
            ans = std::max(ans, (l + 1) - 1);
        }
        return ans;  
    }

    /*
        Solution 3: Bounded Search
        Time complexity: O(m*n + min(m,n))
    */
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        const int m = mat.size();
        const int n = mat[0].size();
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int y = 1; y <= m; ++y)
        for (int x = 1; x <= n; ++x)
            dp[y][x] = dp[y][x - 1] + dp[y - 1][x]  - dp[y - 1][x - 1] + mat[y - 1][x - 1];
        
        auto rangeSum = [&](int x1, int y1, int x2, int y2) {
        return dp[y2][x2] - dp[y2][x1 - 1] - dp[y1 - 1][x2] + dp[y1 - 1][x1 - 1];
        };
        
        int ans = 0;
        for (int y = 1; y <= m; ++y)
        for (int x = 1; x <= n; ++x)
            for (int k = ans; y + k <= m && x + k <= n; ++k) {
            if (rangeSum(x, y, x + k, y + k) > threshold) break;
            ans = std::max(ans, k + 1);
            }
        return ans;  
    }
    
    int doit_binary_search(vector<vector<int>>& mat, int threshold) {
        
        int m = mat.size(), n = mat[0].size();
        
        for (int i = 0; i < m; i++) {
            int tmp = 0;
            for (int j = 0; j < n; j++) {
                tmp += mat[i][j];
                mat[i][j] = tmp + (i > 0 ? mat[i-1][j] : 0);
            }
        }
        
        auto find = [&](int L, int threshold) {
        
            for (int i = L-1; i < m; i++) {
                for (int j = L-1; j < n; j++) {
                    int ans = mat[i][j];
                    if (i >= L) ans -= mat[i-L][j];
                    if (j >= L) ans -= mat[i][j - L];
                    if (i >= L && j >= L) ans += mat[i - L][j - L];
                    if (ans <= threshold) return true;
                }
            }

            return false;
        };
        
        int low = 1, high = std::min(n, m);
        while (low < high) {

            int mid = high-(high-low)/2;

            if (find(mid, threshold))
                low = mid;
            else
                high = mid-1;
        }

        return find(low, threshold) ? low : 0;
    }
};