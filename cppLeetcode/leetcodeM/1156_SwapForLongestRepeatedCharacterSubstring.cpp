/*
1156. Swap For Longest Repeated Character Substring

Given a string text, we are allowed to swap two of the characters in the string. Find the length of the longest substring with repeated characters.

 

Example 1:

Input: text = "ababa"
Output: 3
Explanation: We can swap the first 'b' with the last 'a', or the last 'b' with the first 'a'. Then, the longest repeated character substring is "aaa", which its length is 3.
Example 2:

Input: text = "aaabaaa"
Output: 6
Explanation: Swap 'b' with the last 'a' (or the first 'a'), and we get longest repeated character substring "aaaaaa", which its length is 6.
Example 3:

Input: text = "aaabbaaa"
Output: 4
Example 4:

Input: text = "aaaaa"
Output: 5
Explanation: No need to swap, longest repeated character substring is "aaaaa", length is 5.
Example 5:

Input: text = "abcdef"
Output: 1
 

Constraints:

1 <= text.length <= 20000
text consist of lowercase English characters only.


*/
#include <string>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::string;

class MaxRepOpt1 {

public:
    
    int doit_(string text) {
        
        vector<std::pair<char, int>> groups;
        int length = 0, res = 0;
        char last = text[0];
        unordered_map<int, int> cnt;


        for (char c : text) {
            if (last != c) {
                groups.push_back({last, length});
                length = 0;
            }
            cnt[c]++;
            length++;
            last = c;
        }
        groups.push_back({last, length});

        for (auto [c, k] : groups) {
            res = std::max(res, min(cnt[c], k + 1));
        }

        for (int i = 1; i < groups.size()-1; i++) {
            if (groups[i-1].first == groups[i+1].first && groups[i].second == 1) {
                res = std::max(res, min(groups[i-1].second + groups[i+1].second + 1, cnt[groups[i+1].first]));
            }
        }

        return res;
    }
};