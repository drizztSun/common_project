/*
214. Shortest Palindrome

Given a string s, you can convert it to a palindrome by adding characters in front of it. 

Find and return the shortest palindrome you can find by performing this transformation. 

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

        有了以上两点证明,那么我们就只要找到最大的i,使得s[0:i]==r[len(s)-i:]，即在r中找到最长的后缀，使得其等于s的前缀。
        
        实现这个可以有两种方法：1. 暴力尝试这个长度。2. 类似KMP中求后缀数组的方法，计算数组r的suf[i]，即r中截止位置i的最长后缀字符串使得恰好是s的前缀字符串。

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

    string doit_KMP(string s) {
        
        string rev(s);
        reverse(begin(rev), end(rev));
        
        string newform = s + '#' + rev;
        
        int n = newform.length();
        vector<int> pattern(n, 0);
        
        int j = 0;
        for (int i = 1; i < n; i++) {
            
            int j = pattern[i-1];
            while (j > 0 && newform[j] != newform[i]) {
                j =  pattern[j-1];
            }
            
            pattern[i] = j + (newform[j] == newform[i]);
        }
        
        string addon = s.substr(pattern.back());
        reverse(begin(addon), end(addon));
        
        return addon + s;
    }

    string doit_str(string s) {

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

    /*
        Approach #3 KMP [Accepted]
        Intuition

        We have seen that the question boils down to finding the largest palindrome substring from the beginning.

        The people familiar with KMP(Knuth–Morris–Pratt) algorithm may wonder that the task at hand can be easily be compared with the concept of the lookup table in KMP.

        KMP Overview:

        KMP is a string matching algorithm that runs in O(n+m)O(n+m) times, where nn and mm are sizes of the text and string to be searched respectively. The key component of KMP is the failure function lookup table,say f(s)f(s). The purpose of the lookup table is to store the length of the proper prefix of the string b_{1}b_{2}...b_{s}b 
        1
        ​	
        b 
        2
        ​	
        ...b 
        s
        ​	
        that is also a suffix of b_{1}b_{2}...b_{s}b 
        1
        ​	
        b 
        2
        ​	
        ...b 
        s
        ​	
        . This table is important because if we are trying to match a text string for b_{1}b_{2}...b_{n}b 
        1
        ​	
        b 
        2
        ​	
        ...b 
        n
        ​	
        , and we have matched the first ss positions, but when we fail, then the value of lookup table for ss is the longest prefix of b_{1}b_{2}...b_{n}b 
        1
        ​	
        b 
        2
        ​	
        ...b 
        n
        ​	
        that could possibly match the text string upto the point we are at. Thus, we don't need to start all over again, and can resume searching from the matching prefix.

        The algorithm to generate the lookup table is easy and inutitive, as given below:

        f(0) = 0
        for(i = 1; i < n; i++)
        {
            t = f(i-1)
            while(t > 0 && b[i] != b[t])
                t = f(t-1)
            if(b[i] == b[t]){
                ++t
            f(i) = t
        }
        Here, we first set f(0)=0 since, no proper prefix is available.
        Next, iterate over ii from 11 to n-1n−1:
        Set t=f(i-1)t=f(i−1)
        While t>0 and char at ii doesn't match the char at tt position, set t=f(t)t=f(t), which essentially means that we have problem matching and must consider a shorter prefix, which will be b_{f(t-1)}b 
        f(t−1)
        ​	
        , until we find a match or t becomes 0.
        If b_{i}==b_{t}b 
        i
        ​	
        ==b 
        t
        ​	
        , add 1 to t
        Set f(i)=tf(i)=t
        The lookup table generation is as illustrated below:

        KMP

        Wait! I get it!!

        In Approach #1, we reserved the original string ss and stored it as \text{rev}rev. We iterate over ii from 00 to n-1n−1 and check for s[0:n-i] == rev[i:]s[0:n−i]==rev[i:]. Pondering over this statement, had the \text{rev}rev been concatenated to ss, this statement is just finding the longest prefix that is equal to the suffix. Voila!

        Algorithm

        We use the KMP lookup table generation
        Create \text{new_s} as s + \text{"#"} + \text{reverse(s)} and use the string in the lookup-generation algorithm
        The "#" in the middle is required, since without the #, the 2 strings could mix with each ther, producing wrong answer. For example, take the string \text{"aaaa"}"aaaa". Had we not inserted "#" in the middle, the new string would be \text{"aaaaaaaa"}"aaaaaaaa" and the largest prefix size would be 7 corresponding to "aaaaaaa" which would be obviously wrong. Hence, a delimiter is required at the middle.
        Return reversed string after the largest palindrome from beginning length(given by n-\text{f[n_new-1]}) + original string ss

        Complexity analysis

        Time complexity: O(n)O(n).

        In every iteration of the inner while loop, tt decreases until it reaches 0 or until it matches. After that, it is incremented by one. Therefore, in the worst case, tt can only be decreased up to nn times and increased up to nn times.
        Hence, the algorithm is linear with maximum (2 * n) * 2(2∗n)∗2 iterations.
        Space complexity: O(n)O(n). Additional space for the reverse string and the concatenated string.
    */
    string doit_KMP(string s){

        int n = s.size();
        string rev(s);
        reverse(rev.begin(), rev.end());
        string s_new = s + "#" + rev;
        
        int n_new = s_new.size();
        vector<int> f(n_new, 0);
        
        for (int i = 1; i < n_new; i++) {
            int t = f[i - 1];
            while (t > 0 && s_new[i] != s_new[t])
                t = f[t - 1];
            if (s_new[i] == s_new[t])
                ++t;
            f[i] = t;
        }
        return rev.substr(0, n - f[n_new - 1]) + s;
    }
};