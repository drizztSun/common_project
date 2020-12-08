/*
 1593. Split a String Into the Max Number of Unique Substrings
 
 Given a string s, return the maximum number of unique substrings that the given string can be split into.

 You can split string s into any list of non-empty substrings, where the concatenation of the substrings forms the original string.
 However, you must split the substrings such that all of them are unique.

 A substring is a contiguous sequence of characters within a string.

  

 Example 1:

 Input: s = "ababccc"
 Output: 5
 Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc']. Splitting like ['a', 'b', 'a', 'b', 'c', 'cc'] is not valid as you have 'a' and 'b' multiple times.
 Example 2:

 Input: s = "aba"
 Output: 2
 Explanation: One way to split maximally is ['a', 'ba'].
 Example 3:

 Input: s = "aa"
 Output: 1
 Explanation: It is impossible to split the string any further.
  

 Constraints:

 1 <= s.length <= 16

 s contains only lower case English letters.
 
 */
#include <unordered_set>
#include <string>

using std::string;
using std::unordered_set;


class SplitStringIntoUniqueSubstrings {
    
public:
    
    int doit_dfs_backtracking(string s) {
        
        unordered_set<string> Set;
        int ans = 0;
        
        std::function<void(int, int)> dfs = [&](int cutidx, int length) {
            
            if (cutidx == s.length()) {
                ans = std::max(ans, length);
                return;
            }
            
            if (length + s.length() - cutidx < ans)
                return;
            
            
            for (int i = cutidx; i < s.length(); i++) {
                
                string cut = s.substr(cutidx, i - cutidx+1);
                if (Set.find(cut) == Set.end()) {
                    Set.insert(cut);
                    dfs(i+1, length+1);
                    Set.erase(cut);
                }
            }
        };
        
        dfs(0, 0);
        
        return ans;
    }
};


void test_1593_SplitStringIntoUniqueSubstrings() {
    
    SplitStringIntoUniqueSubstrings().doit_dfs_backtracking("ababccc");
}
