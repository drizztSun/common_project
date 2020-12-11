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

#include <stdio.h>
#include <string>

using std::string;


class LengthOfLongestSubstringTwoDistinct {
    
public:
    
    int doit_twopointer(string s) {
        
        int best = 0;
        int j = 0;
        int buff[256] = {0}
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
            
            best = max(best, i - j + 1);
        }
        
        return best;
    }
};
