/*
221. Maximal Square


Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

Example:

Input:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output: 4
*/
#include <vector>

using std::vector;

class MaximalSquare {

public:

    /*
        Approach #2 (Dynamic Programming) [Accepted]
        Algorithm

        We will explain this approach with the help of an example.

        0 1 1 1 0
        1 1 1 1 1
        0 1 1 1 1
        0 1 1 1 1
        0 0 1 1 1
        We initialize another matrix (dp) with the same dimensions as the original one initialized with all 0’s.

        dp(i,j) represents the side length of the maximum square whose bottom right corner is the cell with index (i,j) in the original matrix.

        Starting from index (0,0), for every 1 found in the original matrix, we update the value of the current element as

        dp(i, j) = min(dp(i−1,j), dp(i−1,j−1), dp(i,j−1)) + 1.

        We also remember the size of the largest square found so far. In this way, we traverse the original matrix once and find out the required maximum size.
        This gives the side length of the square (say maxsqlenmaxsqlen). The required result is the area maxsqlen^2.

        To understand how this solution works, see the figure below.

        Max Square

        An entry 2 at (1, 3)(1,3) implies that we have a square of side 2 up to that index in the original matrix.
        Similarly, a 2 at (1, 2)(1,2) and (2, 2)(2,2) implies that a square of side 2 exists up to that index in the original matrix.
        Now to make a square of side 3, only a single entry of 1 is pending at (2, 3)(2,3). So, we enter a 3 corresponding to that position in the dp array.

        Now consider the case for the index (3, 4)(3,4). Here, the entries at index (3, 3)(3,3) and (2, 3)(2,3) imply that a square of side 3 is possible up to their indices.
        But, the entry 1 at index (2, 4)(2,4) indicates that a square of side 1 only can be formed up to its index.
        Therefore, while making an entry at the index (3, 4)(3,4), this element obstructs the formation of a square having a side larger than 2.
        Thus, the maximum sized square that can be formed up to this index is of size 2\times22×2.

        Complexity Analysis

        Time complexity : O(mn). Single pass.

        Space complexity : O(mn). Another matrix of same size is used for dp.
     
    */
    int doit_dp(vector<vector<char>>& matrix) {

        int m = matrix.size(), n = matrix[0].size();

        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        int ans = 0;
        for (int i = 1; i <= m; i++) {

            for (int j = 1; j <= n; j++) {
                
                if (matrix[i-1][j-1] == '1') {
                    dp[i][j] = std::min( std::min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
                    ans = std::max(ans, dp[i][j]);
                }
            }
        }
        
        return ans * ans;
    }

    /*
        Approach #3 (Better Dynamic Programming) [Accepted]
        Algorithm

        In the previous approach for calculating dp of i^{th} row we are using only the previous element and the (i-1)^{th} row. Therefore, we don't need 2D dp matrix as 1D dp array will be sufficient for this.

        Initially the dp array contains all 0's. As we scan the elements of the original matrix across a row, we keep on updating the dp array as per the equation 
        dp[j] = min(dp[j-1],dp[j],prev)dp[j] = min(dp[j−1],dp[j],prev), where prev refers to the old dp[j-1]dp[j−1]. For every row, we repeat the same process and update in the same dp array.

        Max Square 

        java

        public class Solution {
            public int maximalSquare(char[][] matrix) {
                int rows = matrix.length, cols = rows > 0 ? matrix[0].length : 0;
                int[] dp = new int[cols + 1];
                int maxsqlen = 0, prev = 0;
                for (int i = 1; i <= rows; i++) {
                    for (int j = 1; j <= cols; j++) {
                        int temp = dp[j];
                        if (matrix[i - 1][j - 1] == '1') {
                            dp[j] = Math.min(Math.min(dp[j - 1], prev), dp[j]) + 1;
                            maxsqlen = Math.max(maxsqlen, dp[j]);
                        } else {
                            dp[j] = 0;
                        }
                        prev = temp;
                    }
                }
                return maxsqlen * maxsqlen;
            }
        }
        Complexity Analysis

        Time complexity : O(mn). Single pass.

        Space complexity : O(n). Another array which stores elements in a row is used for dp.
    */
    int doit_dp(vector<vector<char>>& matrix) {

        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(2, vector<int>(n+1, 0));
        int ans = 0;

        for (int i = 1; i <= m; i++) {
            int index = i % 2;

            for (int j = 1; j <= n; j++) {
                
                dp[index][j] = 0;
                
                if (matrix[i-1][j-1] == '1') {
                    dp[index][j] = std::min( std::min(dp[1-index][j], dp[index][j-1]), dp[1-index][j-1]) + 1;
                    ans = std::max(ans, dp[index][j]);
                }
            }
        }
        
        return ans * ans;
    }

};