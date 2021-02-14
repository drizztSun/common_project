/*
1759. Count Number of Homogenous Substrings


Given a string s, return the number of homogenous substrings of s. Since the answer may be too large, return it modulo 109 + 7.

A string is homogenous if all the characters of the string are the same.

A substring is a contiguous sequence of characters within a string.



Example 1:

Input: s = "abbcccaa"
Output: 13
Explanation: The homogenous substrings are listed as below:
"a"   appears 3 times.
"aa"  appears 1 time.
"b"   appears 2 times.
"bb"  appears 1 time.
"c"   appears 3 times.
"cc"  appears 2 times.
"ccc" appears 1 time.
3 + 1 + 2 + 1 + 3 + 2 + 1 = 13.
Example 2:

Input: s = "xy"
Output: 2
Explanation: The homogenous substrings are "x" and "y".
Example 3:

Input: s = "zzzzz"
Output: 15


Constraints:

1 <= s.length <= 105
s consists of lowercase letters.

*/
#include <string>

using std::string;

class CountHomogenousSubstrings {

public:

    int doit(string s) {

        char last;
        int count = 0, hmod = 1e9+7; 
        int res = 0;

        for (int i = 0; i <= s.length(); i++) {

            if (i == s.length() || last != s[i]) {
                res = (res + count * (count - 1) / 2) % hmod;
                count = 0;
            }

            if (i != s.length()) {
                count++;
                last = s[i];
            }
        }

        return res;
    }



    int doit_(string s) {

        int res = 0, cur = 0, count = 0, mod = 1e9 + 7;
        
        for (int a: s) {
            count = a == cur ? count + 1 : 1;
            cur = a;
            res = (res + count) % mod;
        }
        return res;
    }


}