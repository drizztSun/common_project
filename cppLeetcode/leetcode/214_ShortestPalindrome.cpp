/*
214. Shortest Palindrome

Given a string s, you can convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

 

Example 1:

Input: s = "aacecaaa"
Output: "aaacecaaa"
Example 2:

Input: s = "abcd"
Output: "dcbabcd"
 

Constraints:

0 <= s.length <= 5 * 10^4
s consists of lowercase English letters only.

*/
#include <string>
#include <algorithm>
#include <vector>

using std::vector;
using std::string;


class ShortestPalindrome {

public:

    /*
        214.Shortest-Palindrome
        此题的解法非常巧妙.首先,题意是试图将s分解为s=A'AB的形式,其中A'是A的逆序,求使得A'A最长的分解方式.

        如果我们将s整体逆序写成r,那么r=B'A'A.可以发现s的前段和r的后端恰好都是A'A.此外,反过来考虑,已知r是s的逆序,并且r的尾端等于s的首端,那么这段相同的字符串一定是个palindrome,即A'A的形式.

        有了以上两点证明,那么我们就只要找到最大的i,使得s[0:i]==r[len(s)-i:]，即在r中找到最长的后缀，使得其等于s的前缀。实现这个可以有两种方法：1. 暴力尝试这个长度。2. 类似KMP中求后缀数组的方法，计算数组r的suf[i]，即r中截止位置i的最长后缀字符串使得恰好是s的前缀字符串。

        最终suf[n-1]就是A'A的最大长度。因此B = s.substr(len). 返回的答案就是ret = B'+s.

        |-add-|
        O O O | X X X X | X X X

        P = A`AB (orig)
        S = B'A'A (reversed(A))

        surfix[i] => self-related surfix array, the longest length k, s.t. p[0:k-1] = p[i-k+1:i]

        KMP: Search p in s
        dp[i]: the longest length k, s.t. p[0:k-1] = s[i-k+1.i]
        when dp[i] = p.size()

        214: dp[n-1] : the longest length k len(A`A), s.t. p[0:k-1] = s[n-k:n-1]

    */

    string doit_KMP(string t) {
        
        if (t == "") return t;
        
        string p = t;
        string s = t;
        std::reverse(begin(s), end(s));

        int n = p.length();
        vector<int> suffix(n, 0); // self-related about p
        
        for (int i = 1; i < n; i++){
            int j = suffix[i-1];
            while (j > 0 && p[j] != p[i]) {
                j = suffix[j-1];
            }
            suffix[i] = j + (p[i] == p[j]);
        }

        vector<int> dp(n, 0); //mutual-related about s
        dp[0] = (s[0] == p[0]); // first element
        // p[:k] == s[n-k:n-1] Then we find len(A`A), calculate B
        for (int i = 1; i < n; i++) {

            int j = dp[i-1];

            while (j > 0 && s[i] != p[j]) {
                j = suffix[j-1];
            }

            dp[i] = j + (s[i] == p[j]);
        }

        int len = dp[n-1];
        string B = p.substr(len);
        std::reverse(begin(B), end(B));
        return B + p;
    }
    
    
    string doit_(string s) {

        if (s=="") return s;
        string t = s;
        reverse(t.begin(),t.end());
        
        int N = s.size();
        int len = N;
        while (s.substr(0,len)!=t.substr(N-len,len))
            len--;
        
        t = s.substr(len);
        reverse(t.begin(),t.end());
        return t+s;
    }
};