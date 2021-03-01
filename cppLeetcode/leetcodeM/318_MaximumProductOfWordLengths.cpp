/*
318. Maximum Product of Word Lengths

Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. 
You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:

Input: ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16 
Explanation: The two words can be "abcw", "xtfn".
Example 2:

Input: ["a","ab","abc","d","cd","bcd","abcd"]
Output: 4 
Explanation: The two words can be "ab", "cd".
Example 3:

Input: ["a","aa","aaa","aaaa"]
Output: 0 
Explanation: No such pair of words.
 

Constraints:

0 <= words.length <= 10^3
0 <= words[i].length <= 10^3
words[i] consists only of lowercase English letters.

*/

#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::string;

class MaximumProduct {

    /*
        318.Maximum-Product-of-Word-Lengths
        最直观的想法，从字符串数组中穷举两两的组合，找出最大的乘积，这样o(n^2)的复杂度其实可以接受。主要的问题就是对于每一对组合，要判断这两个字符串是否有相同的字母，这样的操作需要不少的语句，乘以n^2之后耗时就非常可观。

        我们的想法是预处理一遍words，利用o(n)的时间将其字母信息存储下来，当穷举两两组合时所需要的判定时间减少。

        一个比较简单的想法是，因为小写字母只有26个，可以用一个32位的int每一个bit来代表一个字母出现与否。这样只用一个int就能编码一个word所包含的字母信息了。两个word是否含有有相同的字母，则让两个对应code进行与操作，如果结果不是0，说明有一个bit不是零，代表了这个字母在两个word里都出现过。
    */
    int doit_bitmask(vector<string>& words) 
    {
        vector<int>codes(words.size(),0);
        
        for (int i=0; i<words.size(); i++)
        {
            string s=words[i];
            int code=0;
            for (int j=0; j<s.size(); j++)
            {
                int x=s[j]-'a';
                code = (code|(1<<x));
            }
            codes[i]=code;
        }        
        
        
        int result=0;
        for (int i=0; i<words.size(); i++)
         for (int j=0; j<words.size(); j++)
         {
             if ((codes[i]&codes[j])!=0) continue;
             result=max(result,(int)words[i].size()*(int)words[j].size());
         }
        return result;
    }

public:

    int doit_bitmask(vector<string> words) {
        
        unordered_map<int, int> buff;
        
        for (auto word: words)
        {
            int tmp = 0;
            for (auto c: word)
                tmp |= 1<<(c - 'a');
            
            buff[tmp] = std::max(buff[tmp], static_cast<int>(word.length()));
        }
        
        int maxlen = 0;
        for (auto it1 : buff)
            for (auto it2 : buff)
                if ((it1.first & it2.first) == 0) {
                    maxlen = std::max(maxlen, it1.second * it2.second);
                }
        return maxlen;

    }



}