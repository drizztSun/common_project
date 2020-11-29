/*
 
 1585. Check If String Is Transformable With Substring Sort Operations
 
 Given two strings s and t, you want to transform string s into string t using the following operation any number of times:

 Choose a non-empty substring in s and sort it in-place so the characters are in ascending order.
 For example, applying the operation on the underlined substring in "14234" results in "12344".

 Return true if it is possible to transform string s into string t. Otherwise, return false.

 A substring is a contiguous sequence of characters within a string.

  

 Example 1:

 Input: s = "84532", t = "34852"
 Output: true
 Explanation: You can transform s into t using the following sort operations:
 "84532" (from index 2 to 3) -> "84352"
 "84352" (from index 0 to 2) -> "34852"
 Example 2:

 Input: s = "34521", t = "23415"
 Output: true
 Explanation: You can transform s into t using the following sort operations:
 "34521" -> "23451"
 "23451" -> "23415"
 Example 3:

 Input: s = "12345", t = "12435"
 Output: false
 Example 4:

 Input: s = "1", t = "2"
 Output: false
  

 Constraints:

 s.length == t.length
 1 <= s.length <= 105
 s and t only contain digits from '0' to '9'.
 */
#include <string>
#include <queue>
#include <vector>

using std::vector;
using std::queue;
using std::string;

class IsTransformable {
    
    
public:
    
    
    bool doit_gready(string s, string t) {
        
        
        vector<queue<int>> dp(10);
        
        for (auto i = 0; i < s.length(); i++)
            dp[s[i] - '0'].push(i);
        
        for(auto c : t) {
            
            int digit = c - '0';
            if (dp[digit].empty())
                return false;
            
            int pos = dp[digit].front();
            dp[digit].pop();
            
            for (auto i = 0; i < digit; i++)
                if (!dp[i].empty() && dp[i].front() < pos)
                    return false;
        }
        
        return true;
    }
    
    
    vector<int> next;
    
    bool isTransformable(string s, string t) {
        if (s.size() != t.size()) return false;
        
        next = vector<int>(10, 0);
        return internal(s, 0, t, 0);
    }
    
    bool internal(string& s, int sb, string& t, int tb) {
        while (tb < s.size()) {
            if (s[sb] == 'a')
                ++sb;
            else if (s[sb] == t[tb])
                ++sb, ++tb;
            else
                break;
        }
        
        if (tb == s.size()) return true;
        
        int cur;
        for(cur = std::max(sb, next[t[tb] - '0']); cur < s.size(); ++cur) {
            if (s[cur] == 'a') continue;
            
            if (s[cur] == t[tb]) {
                s[cur] = 'a';
                next[t[tb] - '0'] = cur + 1;
                break;
            } else if (s[cur] < t[tb]) {
                return false;
            }
        }
        
        if (cur == s.size()) return false;
        return internal(s, sb, t, tb+1);
    }
};


