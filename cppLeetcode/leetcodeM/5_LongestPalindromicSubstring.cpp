/*
5. Longest Palindromic Substring


Given a string s, return the longest palindromic substring in s.

 

Example 1:

Input: s = "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: s = "cbbd"
Output: "bb"
Example 3:

Input: s = "a"
Output: "a"
Example 4:

Input: s = "ac"
Output: "a"
 

Constraints:

1 <= s.length <= 1000
s consist of only digits and English letters (lower-case and/or upper-case),


*/
#include <string>
#include <vector>

using std::vector;
using std::string;


class LongestPalindrome {

    /*
        005.Longest-Palindromic-Substring
        解法1：
        考虑以每个字符为对称中心（或者为对称中心线左边的字符），同时往左往右推广，看看将回文半径最长能推至哪里。这个解法比较好写，复杂度是o(N^2)

        解法2：
        有个更好的线性时间的Manacher算法，可以参考 https://segmentfault.com/a/1190000003914228 这里简单的介绍一下算法。

        我们将s = aaaba，填充"#"得到 t = #a#a#a#b#a#，我们令数组P[i]表示以t[i]为对称中心的最大回文半径。这样做就是为了解决回文长度奇偶性的问题。在字符串t中，最大的P[i]就代表了最长的回文半径。

        如今我们期望能以线性的速率得到P[i]，而不是按照解法1那样，对于每个i都要往两边扩展。所以我们思考，如果我们已知了P[0],..,P[i-1]，该如何得到P[i]呢？

        我们维护两个变量，maxRight表示在所有P[0],...,P[i-1]为中心的完整回文串中，能够到达的最右边的位置。对应这个回文串的中心，就是maxCenter.

        我们在考虑i的时候，如果i>=maxRight，我们就按照解法1，老老实实地往两边扩展，从半径为0开始，探索P[i]。

        如果i<maxRight，我们其实对P[i]可以有一个初步的估计，不用从零开始。这个估计就是min(P[maxCenter*2-i], maxRight-i)。可以这么考虑：令 j = maxCenter*2-i是与i关于maxCenter对称的点。
        
        因为maxCenter对应的回文串非常长，包裹了以j为中心的回文串，必然也会包裹了以i为中心的回文串。因为i和j完全关于maxCenter对称，所以以i为中心的回文串半径至少该与以j为中心的回文串半径相同（或者说这两个回文串整体都相同）。
        
        当然，这也是有个前提，就是这个回文串都被包裹在以maxCenter为中心的大回文串里面。所有我们需要取min(P[maxCenter*2-i], maxRight-i)。

        这样，我们就可以顺序地探索往P[i]，并找到其中的最大值maxLen，和对应的i的索引maxCenter。注意P的构建是基于t的，那么如何返回基于s的那个回文串呢？其实很巧妙，输出的就是: s.substr((maxCenter-maxLen/2),maxLen)
    */
    string longestPalindrome_manacher(string s) 
    {
        string t="#";
        for (int i=0; i<s.size(); i++)
            t+= s.substr(i,1)+"#";
        
        int N = t.size();
        vector<int>P(N,0);
        int maxCenter = -1;
        int maxRight = -1;
        
        for (int i=0; i<N; i++)
        {
            int k;
            if (i<maxRight)
            {
                k = std::min(P[maxCenter*2-i],maxRight-i);
                while (i-k>=0 && i+k<N && t[i-k]==t[i+k]) k++;                
            }
            else
            {
                k = 0;
                while (i-k>=0 && i+k<N && t[i-k]==t[i+k]) k++;
            }
            P[i] = k-1;
            if (i+k-1>maxRight)
            {
                maxRight = i+k-1;
                maxCenter = i;
            }
        }
        
        int maxLen = -1;
        int center;
        for (int i=0; i<P.size(); i++)
        {
            if (P[i]>maxLen)
            {
                maxLen = P[i];
                center = i;                
            }
        }
        return s.substr((center - maxLen)/2, maxLen);
    }


public:
    
    string doit_dp(string s) {
        
        int n = s.length();
        
        if (n < 2) return s;
        
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        string ans{s[0]};
        int maxl = 1;
        
        for (int i = 0; i < n; i++) {
            
            dp[i][i] = 1;
            
            for (int j = 0; j < i; j++) {
                
                if (s[i] == s[j] && (i - j < 2 || dp[j+1][i-1] != 0)) 
                    dp[j][i] = 2 + (i - j < 2 ? 0 : dp[j+1][i-1]);
                
                if (dp[j][i] > maxl) {
                    maxl = dp[j][i];
                    ans = s.substr(j, i - j + 1);
                }
            }
        }
        
        return ans;
    }

    string doit_dp(string s) {

        int n = s.length();
        
        if (n < 2) return s;
        
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        
        string ans{s[0]};
        int maxl = 1;
        
        for (int i = 0; i < n; i++) {
            
            dp[i][i] = true;
            
            for (int j = 0; j < i; j++) {
                
                dp[j][i] = s[i] == s[j] && (i - j < 2 || dp[j+1][i-1]);
                
                if (dp[j][i] && i - j + 1 > maxl) {
                    maxl = i - j + 1;
                    ans = s.substr(j, i - j + 1);
                }
            }
        }
        
        return ans;
    }
};