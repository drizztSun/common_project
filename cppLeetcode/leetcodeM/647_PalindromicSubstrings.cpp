/*
647. Palindromic Substrings

Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

Example 1:

Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
 

Example 2:

Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 

Note:

The input string length won't exceed 1000.
 

*/

#include <string>
#include <vector>

using std::vector;
using std::string;


class PalindromicSubstrings {

    /*
        647.Palindromic-Substrings
        遍历 for (i=0; i<n; i++)，考察以i为中心的回文串个数（回文串长度为奇数）、i和i+1为中心的回文串个数（回文串长度为偶数），分别加入总的结果中。

        考察方法是以中心i往两边扩散。一旦发现无法实现中心对称，则可以跳过这个i。整体的时间复杂度是 o(n^2)
    */
    int countSubstrings(string s) 
    {
        int count=0;
        int n=s.size();
        
        for (int i=0; i<s.size(); i++)
        {
            int len=0;
            while (i-len>=0 && i+len<n && s[i-len]==s[i+len])
                len++;
            count+=len;
            
            len=0;
            while (i-len>=0 && i+1+len<n && s[i-len]==s[i+1+len])
                len++;
            count+=len;
        }
        return count;
    }

    int doit_dp(string s) {

        int n = s.length();
        
        vector<vector<int>> cnt(n, vector<int>(n, 0));
        
        vector<vector<bool>> dp(n, vector<bool>(n));
        
        
        for (int i = 0; i < n; i++) {
            
            for (int j = i; j >=0; j--) {
                
                if (s[i] == s[j] && (i - j < 2 || dp[j+1][i-1]))
                    dp[j][i] = true;
                
                if (i == j) 
                    cnt[j][i] = 1;
                else if (i - j == 1)
                    cnt[j][i] = 2 + int(s[i] == s[j]);
                else {
                    cnt[j][i] = dp[j][i] ? 1 : 0;
                    cnt[j][i] += cnt[j+1][i] + cnt[j][i-1] - cnt[j+1][i-1];
                }
            }
        }
        
        return cnt[0][n-1];


    }
};
