/*
 
 471. Encode String with Shortest Length
 
 Given a non-empty string, encode the string such that its encoded length is the shortest.

 The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.

 Note:

 k will be a positive integer and encoded string will not be empty or have extra space.
 You may assume that the input string contains only lowercase English letters. The string's length is at most 160.
 If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them is fine.
  

 Example 1:

 Input: "aaa"
 Output: "aaa"
 Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.
  

 Example 2:

 Input: "aaaaa"
 Output: "5[a]"
 Explanation: "5[a]" is shorter than "aaaaa" by 1 character.
  

 Example 3:

 Input: "aaaaaaaaaa"
 Output: "10[a]"
 Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".
  

 Example 4:

 Input: "aabcaabcd"
 Output: "2[aabc]d"
 Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".
  

 Example 5:

 Input: "abbbabbbcabbbabbbc"
 Output: "2[2[abbb]c]"
 Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".
 */
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

class EncodeShorestString {
    
public:
    
    int get_repeat_count(string pattern, string s) {
        auto n = pattern.length();
        int i = 0, cnt = 0;
        while (i < s.length() && pattern == s.substr(i, n)) {
            i += n;
            cnt++;
        }
        return cnt;
    }

    string dfs(string s, unordered_map<string, string>& memo) {
        
        if (s.length() < 5)
            return s;
        
        if (memo.count(s) > 0)
            return memo[s];
        
        auto n = s.length();
        auto encoding_str = s;
        
        for (auto i = n/2; i >= 1; i--) {
            
            string pattern = s.substr(0, i);
            
            if (pattern.length() + 3 > encoding_str.length())
                continue;
            
            auto pn = pattern.length();
            int cnt = get_repeat_count(pattern, s);
            
            for (auto j = cnt; j >= 1; j--) {
                
                string candidate = pattern;
                if (j > 1)
                    candidate = std::to_string(j) + "[" + dfs(pattern, memo) + "]";
                
                candidate += dfs(s.substr(j*pn, s.length() - j*pn), memo);
                
                if (candidate.length() < encoding_str.length()) {
                    encoding_str = candidate;
                }
            }
        }
        
        memo[s] = encoding_str;
        return encoding_str;
    }
    
    string doit_dfs(string s) {
        unordered_map<string, string> memo;
        return dfs(s, memo);
    }
};

void test_471_encoding_string_with_shortest_length() {
    
    EncodeShorestString().doit_dfs("aaaaa");
}
