/*
686. Repeated String Match


Given two strings a and b, return the minimum number of times you should repeat string a so that string b is a substring of it. If it is impossible for b​​​​​​ to be a substring of a after repeating it, return -1.

Notice: string "abc" repeated 0 times is "",  repeated 1 time is "abc" and repeated 2 times is "abcabc".

 

Example 1:

Input: a = "abcd", b = "cdabcdab"
Output: 3
Explanation: We return 3 because by repeating a three times "abcdabcdabcd", b is a substring of it.
Example 2:

Input: a = "a", b = "aa"
Output: 2
Example 3:

Input: a = "a", b = "a"
Output: 1
Example 4:

Input: a = "abc", b = "wxyz"
Output: -1
 

Constraints:

1 <= a.length <= 104
1 <= b.length <= 104
a and b consist of lower-case English letters.



*/
#include <string>

using std::string;


class RepeatStringMatch {

public:

    int doit_rollinghash(string a, string b) {
        
        int q = (b.length()-1) / a.length() + 1;

        auto check = [&](int s) {
            for (int i = 0; i < b.length(); i++) 
                if (b[i] != a[(i+s) % a.length()]) return false;
            return true;
        };

        long long b_hash = 0, a_hash = 0;
        const int MOD = 1e9 + 7;
        for (auto c: b) {
            b_hash = (b_hash * 26 + c - 'a') % MOD;
        }

        long long power = 1;
        for (int i = 0; i < b.length(); i++) {
            a_hash = (a_hash * 26 + a[i % a.length()]) % MOD;
            power = power * 26 % MOD;
        }

        if (a_hash == b_hash && check(0)) return q;

        for (int i = b.length(); i < (q+1) * a.length(); i++) {

            a_hash = (a_hash * 26 + (a[i % a.length()] - 'a') - (a[(i - b.length()) % a.length()] - 'a') * power) % MOD;

            if (a_hash == b_hash && check((i - b.length()) % a.length() + 1)) 
                return i < q * a.length() ? q : q + 1;
        }

        return -1;
    }
};