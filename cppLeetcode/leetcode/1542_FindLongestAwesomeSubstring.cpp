/*
1542. Find Longest Awesome Substring

Given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it palindrome.

Return the length of the maximum length awesome substring of s.

 

Example 1:

Input: s = "3242415"
Output: 5
Explanation: "24241" is the longest awesome substring, we can form the palindrome "24142" with some swaps.
Example 2:

Input: s = "12345678"
Output: 1
Example 3:

Input: s = "213123"
Output: 6
Explanation: "213123" is the longest awesome substring, we can form the palindrome "231132" with some swaps.
Example 4:

Input: s = "00"
Output: 2
 

Constraints:

1 <= s.length <= 10^5
s consists only of digits.


*/
#include <string>
#include <vector>

using std::vector;
using std::string;

/*
Longest/Shortest substring of XXX

Solution 0: Brute Force(n^2) TLE

Solution 1L Prefix + Hashtable O(n)

Define a state of prefix string input[0~i], update the state when extend the prefix

index[S] := first/last index when state S occurred

Let's assume state Si, Sj occurred at [i, j], i < j, connd(Si, Sj) = True, input[i+1~j] is a solution 
ans its length is j - (i+1) + 1 = j - i

index[S init] = -1 # base state "occured" before the start, this handles the case when entire prefix is a solution.

ans = max/min{i - index[S cur]} 0 <= i < n

325. Maximum Size Subarray Sum Equals K (locked) state: prefix sum, Sj = s, Si = s - k => sum(input[i+1 ~ j]) == k

*/



class LongestAwesomeString {

public:

    /*
    Awesine string / Palindrome:

    1) 0 or 1 char occurs odd times and rest of the chars occur even times.

    Since we only care about parity, we can use 1 bit for each digit

    1) state is a 10bit binary string in int format.
    2) 0: even times, 1: odd times

    If the state occurred twice at [i, j] means all digits in s[i+1~j] 
    */
    
    int doit_prefix_hashtable(string s) {

        const int kInf = 1e9 + 7;
        vector<int> idx(1<<10, kInf);
        idx[0] = -1;

        int mask = 0;
        int ans = 0;
        for (int i = 0; s[i]; i++) {

            mask ^= (1 << (s[i] - '0'));
            ans = std::max(ans, i - idx[mask]);

            for (int j = 0; j < 10; j++) {
                ans = std::max(ans, i - idx[mask ^ (1 << j)]);
            }

            idx[mask] = std::min(idx[mask], i);
        }

        return ans;
    }
};