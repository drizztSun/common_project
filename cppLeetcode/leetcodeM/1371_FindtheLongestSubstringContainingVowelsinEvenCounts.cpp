/*
1371. Find the Longest Substring Containing Vowels in Even Counts


Given the string s, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.

 

Example 1:

Input: s = "eleetminicoworoep"
Output: 13
Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.
Example 2:

Input: s = "leetcodeisgreat"
Output: 5
Explanation: The longest substring is "leetc" which contains two e's.
Example 3:

Input: s = "bcbcbc"
Output: 6
Explanation: In this case, the given string "bcbcbc" is the longest because all vowels: a, e, i, o and u appear zero times.
 

Constraints:

1 <= s.length <= 5 x 10^5
s contains only lowercase English letters.
*/


#include <string>
#include <unordered_map>
#include <vector>

using std::vector;
using std::unordered_map;
using std::string;


class LongestSubstring {

    /*
        1371.Find-the-Longest-Substring-Containing-Vowels-in-Even-Counts
        本题是prefix+Hash+状压的综合考察。

        本题要求寻找最长substring，使得其中元音字母的频次是偶数。对于一个区间内的频次，我们必然不会挨个去统计，通常会采用前缀数组的方法。这样就转化为了减法：freq[i:j] = preFreq[j]-preFreq[i-1].

        我们考察以第j个元素结尾的、最长的符合要求的子串。那么如何确定这个子串的左边界i呢？假设我们只关心一个字母a，我们希望[i:j]区间内该字母频次是偶数，必然要求该字母的preFreq[j]和preFreq[i-1]的奇偶性要相同。目前我们对preFreq[j]是已知的（假设是奇数），所以只要知道最小的i使得preFreq[i-1]是偶数即可。于是我们可以建立一个hash表，在遍历j的过程中，存下最早出现奇数次preFreq的位置j即可。

        本题要求区间内五个元音字母的频次都是偶数，所以我们可以用5个bit组成的二进制数来编码，来代表preFreq[j]里五个字母频次的奇偶性。
        比如说我们遍历到j时，preFreq[j]对应的key=00100，就表示前j个元素里，字母i出现了奇数次而其他元音字母出现了偶数次。此时我们只要查看Map里是否之前曾经出现过这个相同的key，有的话，那么最长区间的左端点就是i = Map[key]+1，而区间长度就是j-Map[key]. 考察完j之后，如果key未曾被加入过Map中，则要记录Map[key] = j.
    */
    int findTheLongestSubstring(string s) 
    {
        vector<int>count(5,0);
        unordered_map<int,int>Map;
        Map[0] = -1;
        int ret = 0;
        
        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='a')
                count[0] = (count[0]+1)%2;
            if (s[i]=='e')
                count[1] = (count[1]+1)%2;
            if (s[i]=='i')
                count[2] = (count[2]+1)%2;
            if (s[i]=='o')
                count[3] = (count[3]+1)%2;
            if (s[i]=='u')
                count[4] = (count[4]+1)%2;
            
            int code = 0;
            for (int i=0; i<5; i++)
                code = code*2 + count[i];
            
            if (Map.find(code)!=Map.end())
                ret = std::max(ret, i-Map[code]);
            else
                Map[code] = i;
        }
        
        return ret;
    }

public:

    int doit_hashtable_presum(string s) {

        int status = 0, res = 0;

        unordered_map<char, int> vowels{{'a', 1}, {'e', 2}, {'i', 3}, {'o', 4}, {'u', 5}};
        unordered_map<int, int> buff{{0, -1}};
        
        for (int i = 0; i < s.size(); i++) {
            
            char c = s[i];
            
            if (vowels.count(c) > 0)
                status ^= (1 << vowels[c]);
            
            if (buff.count(status) > 0)
                res = std::max(res, i - buff[status]);
            else
                buff[status] = i;
            
        }
        
        return res;
    }
};