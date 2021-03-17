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


class FindAnagrams {

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

public:

    /*
        Approach 1: Sliding Window with HashMap
        Let's start from the simplest approach: sliding window + two counter hashmaps letter -> its count. 
        The first hashmap is a reference counter pCount for string p, and the second one is a counter sCount for string in the sliding window.

        The idea is to move sliding window along the string s, recompute the second hashmap sCount in a constant time and compare it with the first hashmap pCount. 
        If sCount == pCount, then the string in the sliding window is a permutation of string p, and one could add its start position in the output list.

        Algorithm

        Build reference counter pCount for string p.

        Move sliding window along the string s:

        Recompute sliding window counter sCount at each step by adding one letter on the right and removing one letter on the left.

        If sCount == pCount, update the output list.

        Return output list.

        Implementation
        Complexity Analysis

        Time complexity: O(N_s + N_p) since it's one pass along both strings.

        Space complexity: O(1), because pCount and sCount contain not more than 26 elements.
    */
    
    /*
        Approach 2: Sliding Window with Array
        Algorithm

        Hashmap is quite complex structure, with known performance issues in Java. Let's implement approach 1 using 26-elements array instead of hashmap:

        Element number 0 contains count of letter a.

        Element number 1 contains count of letter b.

        ...

        Element number 26 contains count of letter z.

        Algorithm

        Build reference array pCount for string p.

        Move sliding window along the string s:

        Recompute sliding window array sCount at each step by adding one letter on the right and removing one letter on the left.

        If sCount == pCount, update the output list.

        Return output list.

        Implementation


        Complexity Analysis

        Time complexity: O(N_s + N_p) since it's one pass along both strings.

        Space complexity: O(1), because pCount and sCount contain 26 elements each.
    */
    vector<int> doit_slidingwindow(string s, string p) {

        int n = s.size();
        int m = p.size();
        vector<int> Pcount(26,0),Scount(26,0),res; 
        if(s.size() < p.size()) return res; // base case for error cheaking. If s's length is samller than p's then there is not anagram possible

        // This loop is used to create the initial window which will be = p's length;
        // Loop through the strings and just increment the count;
        for(int i = 0;i<m;i++) {
            Pcount[p[i] - 'a']++; 
            Scount[s[i] - 'a']++;  
        }

        // For the initial window if both the arrays are same then stating index is 0;        
        if(Pcount == Scount) res.push_back(0);
        
        // This loop is used to slide the window and keep cheaking for the rest of the string;
        for(int i = m;i<n;i++) {
            Scount[s[i] - 'a']++; // Once a new element enters the window we should increament it's count in the Scount array;
            Scount[s[i-m] - 'a']--; // Since we include one element in the window we should decrement the count of the element that goes out of the window
            if(Pcount == Scount){
                res.push_back(i - m + 1); // if both the count arrays are same then store the index;
            }
        }
        return res;
    }
};
