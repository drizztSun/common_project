/*
1081. Smallest Subsequence of Distinct Characters

Return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.

Note: This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters/

 

Example 1:

Input: s = "bcabc"
Output: "abc"
Example 2:

Input: s = "cbacdcbc"
Output: "acdb"
 

Constraints:

1 <= s.length <= 1000
s consists of lowercase English letters.

*/
#include <string>
#include <vector>

using std::vector;
using std::string;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        
        int last_position[256]{-1};
        for (int i = 0; i < s.length(); i++)
            last_position[s[i]] = i;
        
        vector<char> st;
        bool seen[256]{false};
        for (int i = 0; i < s.length(); i++) {
            
            if (!seen[s[i]]) {
                
                while (!st.empty() && st.back() > s[i] && last_position[st.back()] > i) {
                    seen[st.back()] = false;
                    st.pop_back();
                }
                
                st.push_back(s[i]);
                seen[s[i]] = true;
            }
        }
        
        return string(st.begin(), st.end());
    }
};