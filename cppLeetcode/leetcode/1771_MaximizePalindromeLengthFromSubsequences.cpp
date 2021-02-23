/*
1771. Maximize Palindrome Length From Subsequences


You are given two strings, word1 and word2. You want to construct a string in the following manner:

1. Choose some non-empty subsequence subsequence1 from word1.
2. Choose some non-empty subsequence subsequence2 from word2.
3. Concatenate the subsequences: subsequence1 + subsequence2, to make the string.
Return the length of the longest palindrome that can be constructed in the described manner. If no palindromes can be constructed, return 0.

A subsequence of a string s is a string that can be made by deleting some (possibly none) characters from s without changing the order of the remaining characters.

A palindrome is a string that reads the same forward as well as backward.

 

Example 1:

Input: word1 = "cacb", word2 = "cbba"
Output: 5
Explanation: Choose "ab" from word1 and "cba" from word2 to make "abcba", which is a palindrome.
Example 2:

Input: word1 = "ab", word2 = "ab"
Output: 3
Explanation: Choose "ab" from word1 and "a" from word2 to make "aba", which is a palindrome.
Example 3:

Input: word1 = "aa", word2 = "bb"
Output: 0
Explanation: You cannot construct a palindrome from the described method, so return 0.
 

Constraints:

1 <= word1.length, word2.length <= 1000
word1 and word2 consist of lowercase English letters.

*/
#include <vector>
#include <string>

using std::vector;
using std::string;


class LongestPalindrome {

public:

    /*
        1771.Maximize-Palindrome-Length-From-Subsequences
        解法1：双序列DP（LCS）
        本题的突破口是：A的子序列s与B的子序列t拼接起来是回文串，那么意味着t的逆序（记做t'）肯定能与s的某段前缀相同。

        A: xxx a x b x c xxx
        B: xxx c x b x a xxx
        B':xxx a x b x c xxx
        我们希望整体的回文串越长，那么自然希望B的逆序里（记做B'）能与A中的子序列匹配的字符越多越好。也就是说，我们需要求A和B'的最长公共子序列（LCS）。

        那么答案就是这个LCS长度的两倍吗？并不是。LCS只是描述了A和B中能够组成的最长的相互对称序列。但是如果A的后半段，或者B的前半段（即B'的后半段），存在自相关的对称序列的话，也是可以贡献在答案里的，例如：

        A: x x x a x b x c [x d e d]
        B: [x x x] c x b x a x x x x
        B':x x x a x b x c [x x x x]
        所以当我们已知dp[i][j]表示A的前i个元素、B'的前j个元素能够组成的LCS时，还要查看A[i+1:m]存在的最长回文串长度、或者B[j+1:n]存在的最长回文串长度。两者取更大的那个，结合之前的互相对称的LCS，才是最后的答案。

        解法2：直接区间型DP（求palindrome length）
        我们直接将word1和word2拼接起来记做word，根据区间型DP，很容易计算dp[i][j]表示区间word[i:j]内的最长回文子序列的长度。但是，符合要求的答案还需要有一个额外的限制：回文串必须跨越两个初始字符串。
        解决方法很简单：计算dp[i][j]的过程中，如果遇到word[i]==word[j]，并且检验发现i与j跨越两个初始字符串，那么这样的dp[i][j]就是符合题目要求的，用来更新最终的答案。
    */

    int doit_dp(string word1, string word2) {
        
        int m = word1.size(), n = word2.size();        
        int t = m + n;
        string word = word1 + word2;
        int ret = 0;

        vector<vector<int>> dp(t, vector<int>(t,0));

        for (int i = 0; i < t; i++)
            dp[i][i] = 1;
        
        for (int len = 2; len <= t; len++)
            for (int i = 0; i + len - 1 < t; i++)
            {
                int j = i + len - 1;
                if (word[i] == word[j])
                {
                    dp[i][j] = dp[i+1][j-1]+2;
                    if (i<m && j>=m)
                        ret = std::max(ret, dp[i][j]);
                }                    
                else
                    dp[i][j] = std::max(dp[i+1][j], dp[i][j-1]);
            }                
        return ret;
    }

    int doit_dp_bottomup(string word1, string word2) 
    {
        int m = word1.size(), n = word2.size();        
        reverse(word2.begin(), word2.end());
        word1 = "#"+word1;
        word2 = "#"+word2;


        auto isPalindrome = [](string& word, int n) -> vector<vector<int>> {

            auto dp = vector<vector<int>>(n+1, vector<int>(n+1));
            for (int i=1; i<=n; i++)
                dp[i][i] = 1;
            for (int len=2; len<=n; len++)
                for (int i=1; i+len-1<=n; i++)
                {
                    int j = i+len-1;
                    if (word[i]==word[j])
                        dp[i][j] = dp[i+1][j-1]+2;
                    else
                        dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            return dp;
        };
                        
        auto dp1 = isPalindrome(word1, m);
        auto dp2 = isPalindrome(word2, n);       
        
        int ret = 0;
        auto dp = vector<vector<int>>(m+1, vector<int>(n+1,0));
        
        for (int i=1; i<=m; i++)
            for (int j=1; j<=n; j++)
            {
                if (word1[i]==word2[j])
                {
                    dp[i][j] = dp[i-1][j-1]+1;
                    ret = max(ret, dp[i][j]*2 + max(i+1<=m ? dp1[i+1][m]:0, j+1<=n ? dp2[j+1][n]:0));
                }                    
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }                
        return ret;
    }
};