/*
718. Maximum Length of Repeated Subarray


Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.

Example 1:

Input:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
Output: 3
Explanation: 
The repeated subarray with maximum length is [3, 2, 1].
 

Note:

1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100
 

*/
#include <vector>

using std::vector;

class MaximumLengthOfReaptedSubarray {

public:

    /*
        718.Maximum-Length-of-Repeated-Subarray
        本题的本质就是Longest Common Subarray，和Longest Common Subsequence属于同一类的题目，双序列DP是最常规的解法。本题的状态转移方程更直观。

        根据双序列DP的套路，令dp[i][j]表示以i结尾的subarray和以j结尾的subarray相等的最大长度，则有：

        dp[i][j] = dp[i-1][j-1]+1 if A[i]==B[j] else 0
    */
    int doit_dp(vector<int>& A, vector<int>& B) 
    {
        int m = A.size();
        int n = B.size();
        A.insert(A.begin(), 0);
        B.insert(B.begin(), 0);
        int dp[m+1][n+1];
        memset(dp, 0, sizeof(int)*(m+1)*(n+1));
        int ret = 0;

        for (int i=1; i<=m; i++)
            for (int j=1; j<=n; j++)
            {
                dp[i][j] = A[i]==B[j]? dp[i-1][j-1]+1 : 0;
                ret = std::max(ret, dp[i][j]);
            }
        return ret;
    }
};