/*
1312. Minimum Insertion Steps to Make a String Palindrome

Given a string s. In one step you can insert any character at any index of the string.

Return the minimum number of steps to make s palindrome.

A Palindrome String is one that reads the same backward as well as forward.

 

Example 1:

Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we don't need any insertions.
Example 2:

Input: s = "mbadm"
Output: 2
Explanation: String can be "mbdadbm" or "mdbabdm".
Example 3:

Input: s = "leetcode"
Output: 5
Explanation: Inserting 5 characters the string becomes "leetcodocteel".
Example 4:

Input: s = "g"
Output: 0
Example 5:

Input: s = "no"
Output: 1
 

Constraints:

1 <= s.length <= 500
All characters of s are lower case English letters.

*/

#include <vector>
#include <string>

using std::vector;
using std::string;

class MinInsertions {

    /*
        1312.Minimum-Insertion-Steps-to-Make-a-String-Palindrome
        解法1：
        第一种方法是：我们将原数列s逆序得到t。本题的答案等同于求这两个字符串的shortest common supersequence (SCS)。

        这个转换其实并不容易理解。我们只能大概地有一种直观的感受：因为s和t是逆序关系，s最后一个字符等于t的第一个字符，应该让s放置于t的前面，尽可能地重合s的尾部和t的头部来提高字符重用的利用效率。所以最终s和t的SCS应该是个回文串。既然SCS的第一个S是shortest的意思，那么这个SCS就是通过s可以得到的最短的回文串。

        这么转换之后，本题就是1092.Shortest-Common-Supersequence.

        解法2：
        另一种更容易理解和想到的方法是区间型DP：定义dp[i][j]表示区间s[i:j]变成回文串最少需要多少添加多少字符。状态转移方程很容易理解：

        if (s[i]==s[j])  
        dp[i][j]=dp[i+1][j-1]; 
        else 
        dp[i][j] = min(dp[i+1][j]+1,dp[i][j-1]+1) 
        // 前者表示让s[i+1:j]已经成为回文串，再在s[j]后添加一个与s[i]相同的字符使得s[i:j]变成回文串
        // 前者表示让s[i:j-1]已经成为回文串，再在s[i]前添加一个与s[j]相同的字符使得s[i:j]变成回文串
        Leetcode Link
    */
    int minInsertions(string s) 
    {
        int n = s.size();
        auto dp = vector<vector<int>>(1+n,vector<int>(1+n,0));
        string t = s;
        reverse(t.begin(),t.end());
        s = "#"+s;
        t = "#"+t;
        
        for (int i=1; i<=n; i++)
        {
            dp[i][0] = i;
            dp[0][i] = i;
        }
        
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++)
            {
                if (s[i]==t[j])
                    dp[i][j] = dp[i-1][j-1]+1;
                else
                    dp[i][j] = min(dp[i-1][j]+1, dp[i][j-1]+1);
            }
        return dp[n][n] - n;
    }

    int minInsertions(string s) 
    {
        int m = s.size();        
        auto dp = vector<vector<int>>(m,vector<int>(m,0));

        for (int i=0; i<m; i++)
            dp[i][i] = 0;

        for (int len = 2; len <=m; len++)
            for (int i=0; i+len-1<m; i++)
            {
                int j = i+len-1;
                if (s[i]==s[j])
                    dp[i][j] = dp[i+1][j-1];
                else
                    dp[i][j] = min(dp[i][j-1]+1, dp[i+1][j]+1);
            }
        return dp[0][m-1];
        
    }

public:
    
    int doit_dp_bottomup(string s) {
        
        int n = s.length();

        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int L = 0; L < n; L++) {

            for (int i = 0; i < n-L; i++) {
                
                int j = i + L;

                if (s[i] == s[j]) {
                    dp[i][j] = j <= i+2 ? 0 : dp[i+1][j-1];
                } else {
                    dp[i][j] = std::min(dp[i+1][j], dp[i][j-1]) + 1;
                }
            }
        }

        return dp[0][n-1];
    }
};