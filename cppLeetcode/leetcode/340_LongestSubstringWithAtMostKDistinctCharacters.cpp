/*
 340. Longest Substring with At Most K Distinct Characters
 
 Given a string, find the length of the longest substring T that contains at most k distinct characters.

 Example 1:

 Input: s = "eceba", k = 2
 Output: 3
 Explanation: T is "ece" which its length is 3.
 Example 2:

 Input: s = "aa", k = 1
 Output: 2
 Explanation: T is "aa" which its length is 2.
 
 */
#include <stdio.h>
#include <string>


using std::string;

class LongestSubstringAtMostKDistinctCharacters {
    
public:
    
    int doit_twopointers(string s, int k) {
        
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
