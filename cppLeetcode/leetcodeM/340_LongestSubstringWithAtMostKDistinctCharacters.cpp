/*
340. Longest Substring with At Most K Distinct Characters


Given a string s and an integer k, return the length of the longest substring of s that contains at most k distinct characters.

 

Example 1:

Input: s = "eceba", k = 2
Output: 3
Explanation: The substring is "ece" with length 3.
Example 2:

Input: s = "aa", k = 1
Output: 2
Explanation: The substring is "aa" with length 2.
 

Constraints:

1 <= s.length <= 5 * 104
0 <= k <= 50

*/
#include <vector>
#include <string>

using std::vector;
using std::string;

class LengthOfLongestSubstringKDistinct {

    /*
        340.Longest-Substring-with-At-Most-K-Distinct-Characters.cpp
        解法1：固定左边界，探索右边界(开区间)
                for (int i=0; i<n; i++)
                {
                    while (j<n && count + (freq[s[j]]+1 == 1) <= k)
                    {
                        freq[s[j]]++;
                        count += (freq[s[j]] == 1);
                        j++;
                    }
                    ret = max(ret, j-i);
                    
                    freq[s[i]]--;
                    count -= (freq[s[i]] == 0);
                }
        解法1：固定右边界，探索左边界(闭区间)
                for (int j=0; j<s.size(); j++)
                {                        
                    freq[s[j]]++;
                    if (freq[s[j]]==1) count++;
                    
                    while (count>k)
                    {
                        freq[s[i]]--;
                        if (freq[s[i]]==0)
                            count--;
                        i++;
                    }
                    ret = max(ret, j-i+1);            
                }
    
    */
    int lengthOfLongestSubstringKDistinct_left(string s, int k) 
    {
        vector<int> freq(256,0);
        int n = s.size();
        int j = 0;
        int ret = 0;
        int count = 0;
        for (int i=0; i<n; i++)
        {
            while (j<n && count + (freq[s[j]]+1 == 1) <= k)
            {
                freq[s[j]]++;
                count += (freq[s[j]] == 1);
                j++;
            }
            ret = std::max(ret, j-i);
            
            freq[s[i]]--;
            count -= (freq[s[i]] == 0);
        }
        return ret;        
    }

    int lengthOfLongestSubstringKDistinct_right(string s, int k) 
    {
        vector<int>freq(256,0);
        int count = 0;
        int i = 0;
        int ret = 0;
        for (int j=0; j<s.size(); j++)
        {                        
            freq[s[j]]++;
            if (freq[s[j]]==1) count++;
            
            while (count>k)
            {
                freq[s[i]]--;
                if (freq[s[i]]==0)
                    count--;
                i++;
            }
            ret = std::max(ret, j-i+1);            
        }
        return ret;        
    }

public:
    
    int doit_slidingwindow(string s, int k) {
        
        int best = 0;
        int buf[256] = {0};
        int j = 0;
        int cnt = 0;
        
        for (int i = 0; i < s.length(); i++) {
            
            buf[s[i]]++;
            if (buf[s[i]] == 1)
                cnt++;
            
            while (j <= i && cnt > k) {
                buf[s[j]]--;
                if (buf[s[j]] == 0)
                    cnt--;
                j++;
            }
            
            best = std::max(best, i - j + 1);
        }
        
        return best;
    }
};