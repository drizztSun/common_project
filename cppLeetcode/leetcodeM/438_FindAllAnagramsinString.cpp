/*
438. Find All Anagrams in a String

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

*/
#include <vector>
#include <string>

using std::string;
using std::vector;

class AllAnagrams {

    /*
        438.Find-All-Anagrams-in-a-String
        1. 注意到本题的查验子串的窗口长度是固定的s.size()，所以不需要双指针，单指针即可。
        2. 需要构造字符的哈希表时，用数组而不是map，效率更高。但记得一定要赋初值 vectorMap(256,0)
        3. 数组之间判断是否相等的比较，直接用 == 即可。
        4. 仔细考虑循环条件，不要遗漏最后一次比较。
        完全相同的问题有 567.Permutation in String
    */

    vector<int> doit_hashtable(string s, string p) 
    {
        vector<int>P(255,0);
        vector<int>S(255,0);
        for (char ch:p) P[ch]++;
        
        vector<int>results;
        for (int i=0; i<s.size(); i++)
        {
            S[s[i]]++;
            if (i>=p.size()) S[s[i-p.size()]]--;            
            if (S==P) results.push_back(i-p.size()+1);
        }
        return results;
    }