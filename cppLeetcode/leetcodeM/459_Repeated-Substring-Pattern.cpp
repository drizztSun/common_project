/*
459.Repeated-Substring-Pattern

Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. 
You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.

 

Example 1:

Input: "abab"
Output: True
Explanation: It's the substring "ab" twice.
Example 2:

Input: "aba"
Output: False
Example 3:

Input: "abcabcabcabc"
Output: True
Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)


*/
#include <string>
#include <vector>
#include <functional>

using std::hash;
using std::vector;
using std::string;


class RepeatedSubstringPattern {

public:
    
    /*
         """
        Approach 4: Knuth-Morris-Pratt Algorithm (KMP)
        Lookup Table

        Rabin-Karp is the best fit for the multiple pattern search, whereas KMP is typically used for the single pattern search.

        The key to KMP is the partial match table, often called lookup table, or failure function table. It stores the length of the longest prefix that is also a suffix.

        Here are two examples

        a b c a b c a
        0 0 0 1 2 3 4

        "ab"   -- No common prefix/surfix
        "abc"   -- No common prefix/surfix
        "abca"  -- Length of common prefix/surfix "a" = 1
        "abcab" -- Length of common prefix/surfix "ab" = 2
        "abcabc" -- Length of common prefix/surfix "abc" = 3
        "abcabca" -- Length of common prefix/surfix "abca" = 4

        a b a b b a
        0 0 1 2 0 1

        "ab" -- No common prefix/surfix
        "aba" -- Length of common prefix/surfix "a" = 1
        "abab" -- Length of common prefix/surfix "ab" = 2
        "ababb" -- No common prefix/surfix
        "ababba" -- Length of common prefix/surfix "a" = 1
        
        How to Get an Answer

        Once we have a lookup table, we know the length l of common prefix/suffix for the input string: l = dp[n - 1].

        That means that n - l should the length of the repeated sequence. To confirm that, one should verify if n - l is a divisor of n.

        (a b c (a b c a b c) a b c) -- Length of common prefix/surfix "ab" = 9

        (n-l) = 3 should be the length of repeated pattern

        (a b c) a b c a b c (a b c)

        How to check: n % (n-l) == 0 --> True --> It's a repeated pattern string


        a b a b b a => The longest common prefix/suffix length l = 1    
        
        n - l = 5 should be the length of repeated pattern

        (a b a b b) a

        How to check: n % (n-l) == 0 --> False --> It is not a reapted pattern string

        Algorithm

        Construct lookup table:

        dp[0] = 0 since one character is not enough to speak about proper prefix / suffix.

        Iterate over i from 1 to n:

        Introduce the second pointer j = dp[i - 1].

        While j > 0 and there is no match s[i] != s[j], do one step back to consider a shorter prefix: j = dp[j - 1].

        If we found a match s[i] == s[j], move forward: j += 1

        Write down the length of common prefix / suffix: dp[i] = j.

        Now we have a length of common prefix / suffix for the entire string: l = dp[n - 1].

        The string is a repeated pattern string if this length is nonzero and n - l is a divisor of n. Return l != 0 and n % (n - l) == 0.

        Implementation


        Complexity Analysis

        Time complexity: O(N). During the execution, j could be decreased at most NN times and then increased at most NN times, that makes overall execution time to be linear O(N).

        Space complexity: O(N) to keep the lookup table.
    """
    
    */
    bool doit_KMP(string s) {

        int n = s.length();
        vector<int> suffix(n, 0);
        // Construct partial match table (lookup table).
        // It stores the length of the proper prefix that is also a proper suffix.
        // ex. ababa --> [0, 0, 1, 2, 1]
        // ab --> the length of common prefix / suffix = 0
        // aba --> the length of common prefix / suffix = 1
        // abab --> the length of common prefix / suffix = 2
        // ababa --> the length of common prefix / suffix = 1

        for (int i = 1; i < n; i++) {

            int j = suffix[i-1];

            while (j > 0 && s[i] != s[j]) {
                j = suffix[j-1];
            }

            suffix[i] = j + (s[i] == s[j]);
        }
        
        int l = suffix[n-1];
        // check if it's repeated pattern string
        return l > 0 && n % (n-l) == 0;
    }

    bool doit_rollinghash(string s) {
        int n = s.size();
        if (n < 2) return false;
        if (n == 2) return s[0] == s[1];    
            
        for (int i = sqrt(n); i > 0; i--) {
            if (n % i == 0) {
                vector<int> divisors;
                divisors.push_back(i);
                if (i != 1) {
                    divisors.push_back(n / i);    
                }
                for (int l : divisors) {
                    string tmp = s.substr(0, l);
                    int firstHash = hash<string>{}(tmp);
                    int currHash = firstHash;
                    int start = l;
                    while (start != n && currHash == firstHash) {
                        tmp = s.substr(start, l);
                        currHash = hash<string>{}(tmp);
                        start += l;    
                    }
                    if (start == n && currHash == firstHash) {
                        return true;    
                    }    
                }     
            }    
        }     
        return false;

};