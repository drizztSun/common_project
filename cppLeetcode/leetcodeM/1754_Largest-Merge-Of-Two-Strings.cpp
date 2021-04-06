/*
1754.Largest-Merge-Of-Two-Strings.cpp


You are given two strings word1 and word2. You want to construct a string merge in the following way: while either word1 or word2 are non-empty, choose one of the following options:

If word1 is non-empty, append the first character in word1 to merge and delete it from word1.
For example, if word1 = "abc" and merge = "dv", then after choosing this operation, word1 = "bc" and merge = "dva".
If word2 is non-empty, append the first character in word2 to merge and delete it from word2.
For example, if word2 = "abc" and merge = "", then after choosing this operation, word2 = "bc" and merge = "a".
Return the lexicographically largest merge you can construct.

A string a is lexicographically larger than a string b (of the same length) if in the first position where a and b differ, a has a character strictly larger than the corresponding character in b.
For example, "abcd" is lexicographically larger than "abcc" because the first position they differ is at the fourth character, and d is greater than c.



Example 1:

Input: word1 = "cabaa", word2 = "bcaaa"
Output: "cbcabaaaaa"
Explanation: One way to get the lexicographically largest merge is:
- Take from word1: merge = "c", word1 = "abaa", word2 = "bcaaa"
- Take from word2: merge = "cb", word1 = "abaa", word2 = "caaa"
- Take from word2: merge = "cbc", word1 = "abaa", word2 = "aaa"
- Take from word1: merge = "cbca", word1 = "baa", word2 = "aaa"
- Take from word1: merge = "cbcab", word1 = "aa", word2 = "aaa"
- Append the remaining 5 a's from word1 and word2 at the end of merge.
Example 2:

Input: word1 = "abcabc", word2 = "abdcaba"
Output: "abdcabcabcaba"


Constraints:

1 <= word1.length, word2.length <= 3000
word1 and word2 consist only of lowercase English letters.


*/
#include <string>

using std::string;
  
class LargestMergeTwoStrings {

    /*
                1754,Largest-Merge-Of-Two-Strings
        如果word1和Word2的首字母不同，那么我们显然会优先选择首字母更大的那个。那么如果word1和word2的首字母相同呢？这里有个巧妙的贪心策略，
        就是将两个字符串各自扔掉首字母，查看剩下的字符串谁大？对于剩下字符串字典序较大的那个字符串，我们在本轮优先选取它的首字母。这是因为这样做可以让它后面更大的字符优先暴露出来。

        以上的做法可以合并成一个策略：查看当前两个字符串谁的字典序更大，就优先取谁的首字母。

        这样的做法的时间复杂度是o(N^2)。也有更复杂的线性时间的做法，就不做要求了。
    */
    string largestMerge(string word1, string word2) 
    {
        string ret;
        int i=0, j=0;
        while (i<word1.size() && j<word2.size())
        {
            if (word1.substr(i)>word2.substr(j))
            {
                ret.push_back(word1[i]);
                i++;
            }
            else
            {
                ret.push_back(word2[j]);
                j++;
            }
        }
        while (i<word1.size())
        {
            ret.push_back(word1[i]);
            i++;
        }
        while (j<word2.size())
        {
            ret.push_back(word2[j]);
            j++;
        }
        return ret;
    }

public:
    
    string doit_greedy(string word1, string word2) 
    {
        string ret;
        int i=0, j=0;
        while (i < word1.size() && j < word2.size())
        {
            if (word1.substr(i) > word2.substr(j))
            {
                ret.push_back(word1[i]);
                i++;
            }
            else
            {
                ret.push_back(word2[j]);
                j++;
            }
        }
        while (i < word1.size())
        {
            ret.push_back(word1[i]);
            i++;
        }
        
        while (j < word2.size())
        {
            ret.push_back(word2[j]);
            j++;
        }
        return ret;
    }
};