/*
1358. Number of Substrings Containing All Three Characters


Given a string s consisting only of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.

 

Example 1:

Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 
Example 2:

Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 
Example 3:

Input: s = "abc"
Output: 1
 

Constraints:

3 <= s.length <= 5 x 10^4
s only consists of a, b or c characters.

*/
#include <string>

using std::string;

class NumberOfSubstrings {


public:

    /*
        Solution 1: Sliding Window
        Find many similar sliding window problem at the end of post.

        Time O(N)
        Space O(1)
    */

    int doit_slidingwindow(string s) {

        int i = 0, res = 0;
        int base[3] = {0,0,0};

        for (int j = 0; j < s.length(); j++) {
            ++base[s[j] - 'a'];

            while (base[0] && base[1] && base[2]) {
                --base[s[i++] - 'a'];
            }

            res += i;
        }

        return res;
    }

    /*
        Solution II
        last will record the position of last occurrence.
        If the ending index of substring is i,
        the starting position should be on the left of min(last),
        in order to have all 3 different letters.
        And in this case, the starting index can be in range [0, min(last)],
        min(last) + 1 in total.

        Time O(N)
        Space O(1)
    */
    int doit_slidingwindow(string s) {
        
        int last[3] = {-1, -1, -1}, res = 0, n = s.length();

        for (int i = 0; i < n; ++i) {
        
            last[s[i] - 'a'] = i;
        
            res += 1 + std::min({last[0], last[1], last[2]});
        }
        
        return res;
    }
}