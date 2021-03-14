/*
 159. Longest Substring with At Most Two Distinct Characters
 
 Given a string s , find the length of the longest substring t  that contains at most 2 distinct characters.

 Example 1:

 Input: "eceba"
 Output: 3
 Explanation: t is "ece" which its length is 3.
 Example 2:

 Input: "ccaabbb"
 Output: 5
 Explanation: t is "aabbb" which its length is 5.
 */

#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::vector;


class LengthOfLongestSubstringTwoDistinct {

    /*
        159. Longest-Substring-with-At-Most-Two-Distinct Characters
        需要一个记录每种字符出现次数的映射，这里为了加快效率，我们不用Map，而是直接用一个数组 vectorMap(128,0)，用字符的ascii码作为index，注意需要开辟至少256个空间才能装下所有字母字符。

        另外还需要一个计数器count还记载目前指针范围内有几种字符。

        按照个人的习惯，最外层用for循环来遍历j。然后分情况讨论：

        1. Map[s[j]]>0，说明s[j]已经被合法收录，故可继续往后遍历j。
        2. Map[s[j]]==0 && count<2，说明s[j]可以被合法收录，故可继续往后遍历j。
        3. Map[s[j]]==0 && count==2，说明i~j已经包含两种字符了，故需要不断退s[i]直至count<2。注意此时仍要收录s[j]。 在每种情况下，i~j都是包含两种字符的合法子串，故都要update一下result。
    */
    int lengthOfLongestSubstringTwoDistinct(string s) 
    {
        vector<int>Map(256,0);
        int count=0;
        int result=0;
        int i=0;
        int j=0;
        
        for (int j=0; j<s.size(); j++)
        {
            if (Map[s[j]]>0)
            {
                Map[s[j]]++;
            }                
            else if (Map[s[j]]==0 && count<2)
            {
                Map[s[j]]++;
                count++;
            }
            else if (Map[s[j]]==0 && count==2)
            {
                while (count==2)
                {
                    Map[s[i]]--;
                    if (Map[s[i]]==0)
                        count--;
                    i++;
                }                    
                Map[s[j]]++;
                count++;
            }
            
            result = std::max(result,j-i+1);            
        }
        
        return result;
    }


    
public:

    int doit_twopointer(string s) {
        
        unordered_map<char, int> buf;
        int ans = 0;
        
        for (int i = 0, j = 0; i < s.length(); i++) {
            
            buf[s[i]]++;
            
            while (j < i && buf.size() > 2) {
                buf[s[j]]--;
                if (buf[s[j]] == 0) buf.erase(s[j]);
                j++;
            }
            
            ans = std::max(ans, i - j + 1);
        }
        
        return ans;
    }
    
    int doit_twopointer(string s) {
        
        int best = 0;
        int j = 0;
        int buff[256] = {0};
        int cnt = 0;
        
        for (int i = 0; i < s.length(); i++) {
            
            buff[s[i]]++;
            if (buff[s[i]] == 1)
                cnt++;
            
            while (j < i && cnt > 2) {
                buff[s[j]]--;
                if (buff[s[j]] == 0)
                    cnt--;
                j++;
            }
            
            best = std::max(best, i - j + 1);
        }
        
        return best;
    }
};
