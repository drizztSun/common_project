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
#include <string>

using std::string;

class LengthOfLongestSubstringKDistinct {

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