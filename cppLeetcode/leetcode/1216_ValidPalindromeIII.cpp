/*
 1216. Valid Palindrome III
 
 
 Given a string s and an integer k, find out if the given string is a K-Palindrome or not.

 A string is K-Palindrome if it can be transformed into a palindrome by removing at most k characters from it.

  

 Example 1:

 Input: s = "abcdeca", k = 2
 Output: true
 Explanation: Remove 'b' and 'e' characters.
  

 Constraints:

 1 <= s.length <= 1000
 s has only lowercase English letters.
 1 <= k <= s.length
 
 */
#include<string>
#include<vector>

using std::string;
using std::vector;

class ValidPalindrome {

    /*
        1216.Valid-Palindrome-III
        此题和1312题很相似的想法。想要将一个字符串s变成一个回文串（无论是通过增加还是删除），一个技巧就是构造另一个字符串t是s的逆序。于是，如果要求增加字符，那么s和t的shorted common supersequence就是需要增加的最少字符；
        如果要求删除字符，那么s和t的longest common subsequence就对应着需要删除的最少字符。

        本题求出s和t的LCS后，只需要判断s的长度减去LCS的长度（即对于s而言最少需要删除的字符）是否小于等于k即可。
    */
    bool isValidPalindrome(string s, int k) 
    {
        int m = s.size();
        string t = s;
        reverse(t.begin(),t.end());
        
        s = "#"+s;
        t = "#"+t;
                
        auto dp = vector<vector<int>>(m+1,vector<int>(m+1,0));
        
        for (int i = 1; i <= m; i++) 
            for (int j = 1; j <= m; j++) 
            {             
                if (s[i] == t[j]) 
                    dp[i][j] = dp[i - 1][j - 1]+1; 
                else
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]); 
            }         
  
        return m-dp[m][m]<=k;
    }

public:
    
    bool doit_dp_bottomup(string s, int k) {
        
        auto n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (auto length = 0; length < n; length++) {
        
            for (auto i = 0; i < n - length; i++) {
                
                auto j = i + length;
                
                if (i == j)
                    dp[i][j] = 1;
                else {
                    dp[i][j] = std::max(dp[i+1][j], dp[i][j-1]);
                    if (s[i] == s[j]) {
                        dp[i][j] = std::max(dp[i+1][j-1] + 2, dp[i][j]);
                    }
                }
            }
        }
        
        return dp[0][n-1] >= n - k;
    }
};
