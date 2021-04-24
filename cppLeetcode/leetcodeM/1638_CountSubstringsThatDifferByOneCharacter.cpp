/*
 
 1638. Count Substrings That Differ by One Character
 
 Given two strings s and t, find the number of ways you can choose a non-empty substring of s and replace a single character by a different character such that the resulting substring is a substring of t.
 In other words, find the number of substrings in s that differ from some substring in t by exactly one character.

 For example, the underlined substrings in "computer" and "computation" only differ by the 'e'/'a', so this is a valid way.

 Return the number of substrings that satisfy the condition above.

 A substring is a contiguous sequence of characters within a string.

  

 Example 1:

 Input: s = "aba", t = "baba"
 Output: 6
 Explanation: The following are the pairs of substrings from s and t that differ by exactly 1 character:
 ("aba", "baba")
 ("aba", "baba")
 ("aba", "baba")
 ("aba", "baba")
 ("aba", "baba")
 ("aba", "baba")
 The underlined portions are the substrings that are chosen from s and t.
 ​​Example 2:
 Input: s = "ab", t = "bb"
 Output: 3
 Explanation: The following are the pairs of substrings from s and t that differ by 1 character:
 ("ab", "bb")
 ("ab", "bb")
 ("ab", "bb")
 ​​​​The underlined portions are the substrings that are chosen from s and t.
 Example 3:
 Input: s = "a", t = "a"
 Output: 0
 Example 4:

 Input: s = "abe", t = "bbc"
 Output: 10
  

 Constraints:

 1 <= s.length, t.length <= 100
 s and t consist of lowercase English letters only.

 
 
 */

#include <stdio.h>
#include <string>
#include <vector>

using std::vector;
using std::string;




class CountSubstringsDifferByOneCharacter {

    /*
        1638.Count-Substrings-That-Differ-by-One-Character
        最初的感觉可能是一道双序列型的DP。所以我首先写出的是状态变量dp[i][j]，表示字符串s的前i个、字符串t的前j个能有多少种答案。接下来我就会考虑如何从s[i]和t[j]下手：怎么样能使得s[i]和t[j]是符合要求的substring的一部分？

        我发现，当s[i]!=t[j]的时候，我们不得不计算s[i]和t[j]之前有多少个连续的、相等的字符的个数a。这个时候灵光一现，如果我们也计算出s[i]和t[j]之后有多少个连续的、相等的字符的个数b，那么我们其实就解决了一类符合题意的substring的pattern：
        那就是以s[i]和t[j]做为“Differ by One Character”的位置，那么这样的字符串其实就是有(a+1)*(b+1)个。事实上，所有的符合条件的substring都可以归为若干类，每一类都有着相同的“Differ by One Character”的位置(i,j).

        所以至此，本题的思路就有了。我们遍历所有的配对(i,j)，如何s[i]!=t[j]，那么我们就计算相应的a和b（定义见前），然后ret+=(a+1)*(b+1).至于a和b，显然我们提前计算出来。
        令dp1[i][j]表示s[i]和t[j]之前的最长的相同substring（包括s[i]和t[j]本身）；令dp2[i][j]表示s[i]和t[j]之后的最长的相同substring（包括s[i]和t[j]本身）。这两个量都很容易用动态规划来解决。
    */
    int dp1[102][102];
    int dp2[102][102];

    int countSubstrings(string s, string t) 
    {
        int m = s.size(); 
        int n = t.size();
        s = "#"+s+"#";
        t = "#"+t+"#";
        
        for (int i=1; i<=m; i++)
            for (int j=1; j<=n; j++)
            {
                if (s[i]==t[j])
                    dp1[i][j] = dp1[i-1][j-1]+1;
                else
                    dp1[i][j] = 0;                
            }

        for (int i=m; i>=1; i--)
            for (int j=n; j>=1; j--)
            {
                if (s[i]==t[j])
                    dp2[i][j] = dp2[i+1][j+1]+1;
                else
                    dp2[i][j] = 0;
            }
        
        int ret = 0;
        for (int i=1; i<=m; i++)
            for (int j=1; j<=n; j++)
            {
                if (s[i]!=t[j])
                    ret += (dp1[i-1][j-1]+1)*(dp2[i+1][j+1]+1);
            }
        return ret;
    }

    
public:

    /*
        Intuition
        Choose a start point for s and a start point for t, and then compare characters one by one.


        Explanation
        Try to match from s[i] and t[j],
        where i = 0 or j = 0.

        cur is the current number of consecutive same characters.
        pre is the previous number of consecutive same characters.


        Complexity
        Time O(mn)
        Space O(1)
    */
    int countSubstrings(string s, string t) {

        auto helper = [](const string& s, const string& t, int i, int j) {
            int res = 0, pre = 0, cur = 0;
            for (int n = s.length(), m = t.length(); i < n && j < m; ++i, ++j) {
                cur++;
                if (s[i] != t[j])
                    pre = cur, cur = 0;
                res += pre;
            }
            return res;
        };

        int res = 0 ;
        for (int i = 0; i < s.length(); ++i)
            res += helper(s, t, i, 0);

        for (int j = 1; j < t.length(); ++j)
            res += helper(s, t, 0, j);
        
        return res;
    }
    
    int doit_dp(string s, string t)
    {
        int m = s.size();
        int n = t.size();
     
        vector<vector<int>> dp1(m+2, vector<int>(n+2));
        vector<vector<int>> dp2(m+2, vector<int>(n+2));
        
        s = "#"+s+"#";
        t = "#"+t+"#";
        
        for (int i=1; i<=m; i++)
            for (int j=1; j<=n; j++)
            {
                if (s[i]==t[j])
                    dp1[i][j] = dp1[i-1][j-1]+1;
                else
                    dp1[i][j] = 0;
            }
        
        for (int i=m; i>=1; i--)
            for (int j=n; j>=1; j--)
            {
                if (s[i]==t[j])
                    dp2[i][j] = dp2[i+1][j+1]+1;
                else
                    dp2[i][j] = 0;
            }
        
        int ret = 0;
        for (int i=1; i<=m; i++)
            for (int j=1; j<=n; j++)
            {
                if (s[i]!=t[j])
                    ret += (dp1[i-1][j-1]+1)*(dp2[i+1][j+1]+1);
            }
        return ret;
    }
};
