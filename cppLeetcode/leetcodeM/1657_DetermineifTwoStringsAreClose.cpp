/*
1657. Determine if Two Strings Are Close


Two strings are considered close if you can attain one from the other using the following operations:

    . Operation 1: Swap any two existing characters.
        .For example, abcde -> aecdb
    . Operation 2: Transform every occurrence of one existing character into another existing character, and do the same with the other character.
        .For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)

You can use the operations on either string as many times as necessary.

Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.

 

Example 1:

Input: word1 = "abc", word2 = "bca"
Output: true
Explanation: You can attain word2 from word1 in 2 operations.
Apply Operation 1: "abc" -> "acb"
Apply Operation 1: "acb" -> "bca"
Example 2:

Input: word1 = "a", word2 = "aa"
Output: false
Explanation: It is impossible to attain word2 from word1, or vice versa, in any number of operations.
Example 3:

Input: word1 = "cabbba", word2 = "abbccc"
Output: true
Explanation: You can attain word2 from word1 in 3 operations.
Apply Operation 1: "cabbba" -> "caabbb"
Apply Operation 2: "caabbb" -> "baaccc"
Apply Operation 2: "baaccc" -> "abbccc"
Example 4:

Input: word1 = "cabbba", word2 = "aabbss"
Output: false
Explanation: It is impossible to attain word2 from word1, or vice versa, in any amount of operations.
 

Constraints:

1 <= word1.length, word2.length <= 105
word1 and word2 contain only lowercase English letters.


*/

#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

using std::vector;
using std::unordered_set;
using std::string;



class CloseStrings {

    /*
        1657.Determine-if-Two-Strings-Are-Close
        第一条规则说明单纯的乱序不影响判断两个字符串是否close。只要两个字符串排序后是一样的，那么就是close。

        第二条规则说明两个问题：首先两个字符串必须包含相同种类的字母，因为规则二本身无法创造出新的字母。如果两个字符串的字母种类不同，那么规则二是无法使得他们一致的（即使是乱序）。
        其次，同一个字符串中不同种类的字符可以互换彼此的频次，因此必然要求这两个字符串的字母频次分布也一致。因此一个close的必要条件就是将两个字符串的频次数组都分别排序，查验它们是否相同。
    */
    bool closeStrings(string word1, string word2) 
    {
        unordered_set<char>Set1;
        unordered_set<char>Set2;

        vector<int>a(26,0);
        vector<int>b(26,0);
        for (auto ch:word1)
        {
            a[ch-'a']+=1;
            Set1.insert(ch);
        }            
        for (auto ch:word2)
        {
            b[ch-'a']+=1;
            Set2.insert(ch);
        }
            
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        return a==b && Set1==Set2;        
    }

public:
    
    bool doit_greedy(string word1, string word2) {
        
        if (word1.length() != word2.length()) return false; 
        
        unordered_set<char> set1, set2;
        
        auto frequency = [](const string& word, unordered_set<char>& wordset) {
            
            vector<int> cnt(26, 0);
            for (auto c: word) {
                cnt[c-'a']++;
                wordset.insert(c);
            }
            
            vector<int> freq;
            
            for (int i = 0; i < 26; i++) {
                if (cnt[i] > 0) freq.push_back(cnt[i]);
            }
            
            std::sort(begin(freq), end(freq));
            return freq;
        };
        
        auto freq1 = frequency(word1, set1);
        auto freq2 = frequency(word2, set2);
        
        return freq1 == freq2 && set1 == set2;
    }
};