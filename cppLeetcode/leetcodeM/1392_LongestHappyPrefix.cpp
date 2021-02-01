/*
1392. Longest Happy Prefix


A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).

Given a string s. Return the longest happy prefix of s .

Return an empty string if no such prefix exists.

 

Example 1:

Input: s = "level"
Output: "l"
Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".
Example 2:

Input: s = "ababab"
Output: "abab"
Explanation: "abab" is the largest prefix which is also suffix. They can overlap in the original string.
Example 3:

Input: s = "leetcodeleet"
Output: "leet"
Example 4:

Input: s = "a"
Output: ""
 

Constraints:

1 <= s.length <= 10^5
s contains only lowercase English letters.


*/
#include <string>
#include <vector>

using std::vector;
using std::string;

class LongestHappyPrefix {

public:
    
    /*
        1392.Longest-Happy-Prefix
        这道题所求的东西其实就是KMP算法中的一个重要的预处理步骤，称为求后缀数组。

        我们令dp[i]表示该字符串最长的前缀字符串，使得其恰等于截止i位置的后缀字符串。即如果dp[i]=j,那么s[0:j-1] = s[i-j+1:i].

        我们利用一下动态规划的思想，看看dp[i]能否从dp[i-1]的信息推演过来？我们令j=dp[i-1]，即查看截止i-1位置的最长后缀字符串，用星号表示（长度为j）：

        * * * * * * * * * * * * * * * * *   X  ________________________________  * * * * * * * * * * * * * * * * *   Y
                                    j-1, j                                                                   i-1, i
        如果在s[i]和s[j]这两处的字符相同（即X==Y），那么显然我们就说明dp[i]可以在之前长度j的后缀字符串上再延长一位，即dp[i] = j+1.

        如果在s[i]和s[j]这两处的字符不相同（即X!=Y），我们该如何寻找截止i位置的最长后缀字符串呢？我们把目光放到s[0:j-1]这段区间上来。我们类似的其实也有dp[j-1]，这段长度表示截止j-1位置时的最长后缀字符串，我们画出来看看：

        + + + + + Z ____________ + + + + +  X  ________________________________  _______________________ + + + + +   Y
            j'-1                    j-1, j                                                                   i-1, i
        我们令j' = dp[j-1]，那么有s[0:j'-1] = s[j-j':j-1]，同时我们这两段区间必然也和s[i-j':i-1]相同！此时我们就又有了希望，如果s[j']和s[i]这两处的字符相同（即Z==Y），那么我们就又有了一段截止i位置时的最长字符串（长度为j'）。

        当然，也有可能Z和Y匹配不成功，那么我们可以同理再考察截止j'-1位置的最长后缀字符串，它的长度应该是j'' = dp[j'-1]，然后再尝试考察s[j'']是否与s[i]相同...

        所以我们发现一个规律：对于dp[i]，我们先看长度为j=dp[i-1]的前缀字符串，是否能有s[j]==s[i]。不行，就再看长度为j'=dp[j'-1]的前缀字符串，是否能有s[j']==s[i]。不行就再看长度为j''=dp[j''-1]的前缀字符串，是否能有s[j'']==s[i]...直至最终停下来，得到一个最终可利用的前缀长度j，那么dp[i] = j + (s[i]==s[j])

        总结一下：

        for (int i=1; i<n; i++)
        {
            // compute dp[i]
            int j = dp[i-1];
            while (j>0 && s[j]!=s[i])
            j = dp[j-1];
            dp[i] = j+(s[j]==s[i]);   
        }    
        特别注意dp[0]=0（因为我们求的是最长“真前缀”），所以循环从index为1的元素开始。

        suffix[i] = the maximum length k. s, t. s[0:k-1] = s[i-k+1]
    */
    
    string longestPrefix(string s) {

        int n = s.size();
        vector<int>dp(n);
        dp[0] = 0;

        for (int i=1; i<n; i++)
        {
            int j = dp[i-1];                       
            while (j>=1 && s[j]!=s[i])
            {
                j = dp[j-1];
            }          
            dp[i] = j + (s[j]==s[i]);
        }

        int len = dp[n-1];
        return s.substr(0, len);
        
    }
};