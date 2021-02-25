/*
1297. Maximum Number of Occurrences of a Substring


Given a string s, return the maximum number of ocurrences of any substring under the following rules:

The number of unique characters in the substring must be less than or equal to maxLetters.
The substring size must be between minSize and maxSize inclusive.
 

Example 1:

Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
Output: 2
Explanation: Substring "aab" has 2 ocurrences in the original string.
It satisfies the conditions, 2 unique letters and size 3 (between minSize and maxSize).
Example 2:

Input: s = "aaaa", maxLetters = 1, minSize = 3, maxSize = 3
Output: 2
Explanation: Substring "aaa" occur 2 times in the string. It can overlap.
Example 3:

Input: s = "aabcabcab", maxLetters = 2, minSize = 2, maxSize = 3
Output: 3
Example 4:

Input: s = "abcde", maxLetters = 2, minSize = 3, maxSize = 3
Output: 0
 

Constraints:

1 <= s.length <= 10^5
1 <= maxLetters <= 26
1 <= minSize <= maxSize <= min(26, s.length)
s only contains lowercase English letters.

*/
#include <vector>
#include <string>
#include <unordered_map> 

using std::vector;
using std::unordered_map;
using std::string;


class MaximumNumberOfOcuurance {

public:

    /*
        Intuition
        If a string have occurrences x times,
        any of its substring must appear at least x times.

        There must be a substring of length minSize, that has the most occurrences.
        So that we just need to count the occurrences of all substring with length minSize.


        Explanation
        Find the maximum occurrences of all substrings with length k = minSize


        Complexity
        Time O(KN), where K = minSize
        Space O(KN)


        Python:
    */
    int doit_(string s, int maxLetters, int minSize, int maxSize) {
        // maxsize is useless, minsize should cover the answser          
        unordered_map<string, int> buff;
        int cnt[26] = {0};
        int length = 0;
        
        for (int i = 0; i < s.size(); i++) {
            
            int c = s[i] - 'a';
            cnt[c]++;
            if (cnt[c] == 1)
                length++;
            
            if (i < minSize - 1) continue;
            
            if (i >= minSize) {
                int c2 = s[i-minSize] - 'a';
                cnt[c2]--;
                if (cnt[c2] == 0) length--;
            }
            
            if (length <= maxLetters)
                buff[s.substr(i-minSize+1, minSize)]++;
        }
        
        int ans = 0;
        for (auto it : buff) {
            ans = std::max(ans, it.second);
        }
        return ans;
    }
};