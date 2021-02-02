/*
28. Implement strStr(

Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Clarification:

What should we return when needle is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().

 

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1
Example 3:

Input: haystack = "", needle = ""
Output: 0
 

Constraints:

0 <= haystack.length, needle.length <= 5 * 104
haystack and needle consist of only lower-case English characters.

*/

#include <string>
#include <vector>

using std::vector;
using std::string;

class Strstr {

public:

    /*
        028.Implement-strStr

        KMP算法
        首先我们要预处理模式串p（也就是needle），得到一个关于模式串的后缀数组suf。suf[i]表示在字符串p中，截止i位置的最长的后缀字符串，使得它恰好也是p的前缀。比如说，如果j=suf[i]，那么p[0:j-1]=p[i-j+1:i]。关于后缀数组的计算，请见1392.Longest-Happy-Prefix.

        假设我们已经有了模式串的后缀数组suf，那么我们如何来求解这个题呢？我们对于字符串s（也就是haystack）也定义类似的后缀数组dp。其中dp[i]表示s里截止i位置的最长的后缀字符串，使得它恰好也是p的前缀。注意，这里如果j=suf[i]，那么p[0:j-1]=s[i-j+1:i]。显然，如果dp[i]==p.size()，那么意味着以s[i]为结尾的后缀字符串与p完全匹配。

        我们试图用动态规划的想法，看看dp[i]是否能从dp[i-1]得到。如下图：我们想计算dp[i]。我们看一下dp[i-1]，记j=dp[i-1]，那么p就有一段长度为j的前缀字符串与s[i-1]结尾的后缀字符串匹配。

        s:    ________________ * * * * * * * * * * * * * * * *  X _________
                                                            i-1 i
        p:                     * * * * * * * * * * * * * * * *  Y _________
                                                            j-1 j
        此时如果有s[i]==p[j]（即X==Y），那么显然已知匹配的长度自然就可以延长1位，即dp[i]=j+1.

        那么如果没有X==Y怎么办呢？我们把眼光放到suf[j-1]上，记j'=suf[j-1]，那么p就有一段长度为j'的前缀字符串与p[j-1]结尾的后缀字符串匹配.

        s:    ________________ _______________________ + + + +  X _________
                                                            i-1 i
        p:                     + + + + Z _____________ + + + +  Y _________
                                    j'-1                    j-1 j
        不难推导出p[0:j'-1]也与s[i-j':i-1]必然是相等的。所以我们在计算dp[i]的时候可以利用这段长度：只要Z==X，那么dp[i] = j'+1.

        如果Z和X仍然不等，那么我们就再把眼光放到suf[j'-1]上，即j''=suf[j'-1]，同理推导出p[0:j''-1]也与s[i-j'':i-1]必然是相等的，此时只要考察s[i]和p[j'']是否相等个，就可以将dp[i]推至j''+1...

        依次类推j',j'',j'''..直到我们找到合适的j（注意j可以是0），使得p里面长度为j的前缀字符串，恰好等于截止s[i-1]的后缀字符串。于是dp[i]能否突破0，就取决于dp[j]+(s[i]==p[j])了。代码如下：

        for (int i=1; i<n; i++)
        {
        // compute dp[i]
        int j = dp[i-1];
        while (j>0 && p[j]!=s[i])
            j = suf[j-1];
        dp[i]  = j+(p[j]==s[i]);
        }
        注意dp[0]需要单独计算：dp[0] = (s[0]==p[0])

        当我们计算得到第一处dp[i]=p.size()时，就说明找到了完整匹配的模式串。

        Sunday算法
        预处理needle构造一个shift数组。该数组记录了needle里的字符最后一次出现的位置距离needle结尾的位移。

        举个例子，最开始将haystack和needle左对齐，如果发现needle和haystack匹配不上，就考察haystack[n]的字符（即needle长度n之后的第一个字符）。

        1). 如果这个字符在shift里有记录，那么将needle整体右移相应的位移，这样使得haystack[n]和needle里最后一次出现的字符（这两个字符相同）对齐，再从needle首字符开始逐一判断匹配。

        2). 如果这个字符不存在needle里面，则shift里默认给n+1，即将整个needle右移至haystack[n]之后，再从needle首字符开始逐一判断匹配。
    
    
    */
    int doit_KMP(string haystack, string needle) 
    {
        int n = haystack.size();
        int m = needle.size();
        if (m==0) return 0;
        if (n==0) return -1;

        auto preprocess = [](const string& s) -> vector<int> {

            int n = s.size();
            vector<int>dp(n,0);
            for (int i=1; i<n; i++)
            {
                int j = dp[i-1];                       
                while (j>=1 && s[j]!=s[i])
                {
                    j = dp[j-1];
                }          
                dp[i] = j + (s[j]==s[i]);
            }
            return dp;
        };

        vector<int> suf = preprocess(needle);
        
        vector<int>dp(n,0);
        dp[0] = (needle[0]==haystack[0]);
        if (m==1 && dp[0]==1)
            return 0;

        for (int i=1; i<n; i++)
        {
            int j = dp[i-1];
            while (j>0 && needle[j]!=haystack[i])
                j = suf[j-1];
            dp[i] = j + (needle[j]==haystack[i]);
            if (dp[i]==needle.size())
                return i-needle.size()+1;
        }
        return -1;
    }

    int doit_sunday(string haystack, string needle) 
    {
        int m = needle.size();
        int n = haystack.size();
        
        if (m==0) return 0;
        if (n==0) return -1;
                    
        vector<int>shift(512,0);
        for (int i=0; i<512; i++)
            shift[i]=m+1;
        for (int i=0; i<m; i++)
            shift[needle[i]]=m-i;
        
        int s=0;
        int j;
        while (s<=n-m)
        {
            j=0;

            while (haystack[s+j]==needle[j])
            {
                j++;
                if (j==m) return s;
            }
            s+=shift[haystack[s+m]];
        }
        
        return -1;
    }
    
    int doit_(string haystack, string needle) {

        int m = haystack.length(), n = needle.length();

        if (n == 0) return 0;
        if (m == 0) return -1;
        
        vector<int> pattern{0, 0};
        int j = 0;

        for (int i = 1; i < needle.length(); i++) {

            while (j > 0 && needle[j] != needle[i]) {
                j = pattern[j];
            }

            if (needle[i] == needle[j])
                j++;

            pattern.push_back(j);
        }

        
        j = 0;
        for (int i = 0; i < haystack.length(); i++) {

            while (j > 0 && haystack[i] != needle[j]) {
                j = pattern[j];
            }

            if (haystack[i] == needle[j])
                j++;

            if (j == n)
                return i - n + 1;
        }

        return -1;
    }
};