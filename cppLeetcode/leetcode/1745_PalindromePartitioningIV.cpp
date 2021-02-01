/*
1745. Palindrome Partitioning IV


Given a string s, return true if it is possible to split the string s into three non-empty palindromic substrings. Otherwise, return false.​​​​​

A string is said to be palindrome if it the same string when reversed.

 

Example 1:

Input: s = "abcbdd"
Output: true
Explanation: "abcbdd" = "a" + "bcb" + "dd", and all three substrings are palindromes.
Example 2:

Input: s = "bcbddxy"
Output: false
Explanation: s cannot be split into 3 palindromes.
 

Constraints:

3 <= s.length <= 2000
s​​​​​​ consists only of lowercase English letters.

*/
#include <string>
#include <vector>

using std::vector;
using std::string;



class PalindromePartitioningIV {

public:

    /*
        1745.Palindrome-Partitioning-IV
        关于判定一个字符串中的substring是否为回文串，区间型的DP是最常规的手段。在这里，我们可以提前用o(N^2)的时间预处理s，得到dp[i][j]表示任意一个子区间是否为回文串。

        然后我们再循环遍历两个分界点i和j，将s分割为三部分，这样只需要直接调用dp[0][i],dp[i+1][j-1],dp[j+1][n-1]就可以知道这三部分是否分别都是回文串。这两层循环的时间复杂度也是o(N^2).

        另外，本题有线性时间复杂度的Manacher算法。
    */
    int dp[2000][2000];

    bool doit_dp_1(string s) 
    {
        int n = s.size();
        for (int i=0; i<n; i++)
            dp[i][i] = 1;
        for (int i=0; i+1<n; i++)
            if (s[i]==s[i+1])
                dp[i][i+1] = 1;
        
        
        for (int len = 3; len <= n; len ++) 
            for (int i=0; i+len-1<n; i++)
            {
                int j = i+len-1;
                if (s[i]==s[j])
                    dp[i][j] = dp[i+1][j-1];
                else
                    dp[i][j] = 0;
            }
        
        for (int i=0; i<n; i++)
            for (int j=i+2; j<n; j++)
            {
                if (dp[0][i] && dp[i+1][j-1] && dp[j][n-1])
                    return true;
            }
        return false;
    }
    
    bool doit_dp(string s) {
        
        int n = s.length();
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        for (int i = 0; i < n; i++) {
            for (int j = i; j > -1; j--) {
                if (s[i] == s[j] && (i - j < 2 || dp[j+1][i-1]))
                    dp[j][i] = true;
            }
        }

        for (int i = 0; i < n; i++) {
            if (!dp[0][i]) continue;
            for (int j = n - 1; j > i + 1; j--) {
                if (dp[i+1][j-1] && dp[j][n-1]) return true;
            }
        }

        return false;
    }
};