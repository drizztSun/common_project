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


class LongestPrefix {

public:
    
    string doit_KMP(string s) {
        
        int n = s.length();
        vector<int> dp(n, 0);
        
        for (int i = 1; i < n; i++) {
            
            int j = dp[i-1];
            
            while (j > 0 && s[j] != s[i]) {
                j = dp[j-1];
            }
            
            dp[i] = j + (s[j] == s[i]);
        }
        
        return s.substr(0, dp[n-1]);
    }
};