/*
567. Permutation in String

Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. 
In other words, one of the first string's permutations is the substring of the second string.

 

Example 1:

Input: s1 = "ab" s2 = "eidbaooo"
Output: True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input:s1= "ab" s2 = "eidboaoo"
Output: False
 

Constraints:

The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].

*/
#include <string>

using std::string;

class PermutationStrings {

public:

    bool doit_slidingwindow(string s1, string s2) {

        if (s1.length() > s2.length()) return false;

        int m1[26]{0}, m2[26]{0};
        for (auto c: s1) 
            m1[c-'a']++;

        auto equal = [&]() {
            for (int i = 0; i < 26; i++)
                if (m1[i] != m2[i]) return false;
            return true;
        };

        int l1 = s1.length();
        for (int i = 0; i < s2.length(); i++) {

            if (equal()) return true;

            m2[s2[i] - 'a']++;

            if (i < l1) continue;

            m2[s2[i-l1] - 'a']--;
        }
        
        return equal();
    }
};