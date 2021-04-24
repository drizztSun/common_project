/*
758. Bold Words in String

Given a set of keywords words and a string S, make all appearances of all keywords in S bold. Any letters between <b> and </b> tags become bold.

The returned string should use the least number of tags possible, and of course the tags should form a valid combination.

For example, given that words = ["ab", "bc"] and S = "aabcd", we should return "a<b>abc</b>d". Note that returning "a<b>a<b>b</b>c</b>d" would use more tags, so it is incorrect.

Constraints:

words has length in range [0, 50].
words[i] has length in range [1, 10].
S has length in range [0, 500].
All characters in words[i] and S are lowercase letters.
Note: This question is the same as 616: https://leetcode.com/problems/add-bold-tag-in-string/

*/
#include <string>
#include <vector>

using std::vector;
using std::string;

class BoldWords {

public:
    
    string doit_(vector<string>& words, string S) {
        
        int n = S.length();
        vector<int> D(n, 0);
        
        for (auto c: words) {
            
            int L = c.length();
            
            for (int i = 0; i <= S.length()-L; i++) {
             
                if (S.substr(i, L) == c) {
                    for (int k = i; k < i+L; k++)
                        D[k] = 1;
                }
            }
        }
        
        string ans;
        
        for (int i = 0; i < n; i++) {
            
            if (D[i] == 0) {
                ans.push_back(S[i]);
                continue;
            }
            
            int j = i;
            while (j < n && D[j] == 1) j++;
            
            ans += "<b>" + S.substr(i, j-i) + "</b>";
            i = j-1;
        }
        
        return ans;
    }
};