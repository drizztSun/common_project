/*
411. Minimum Unique Word Abbreviation


A string can be abbreviated by replacing any number of non-adjacent substrings with their lengths. For example, a string such as "substitution" could be abbreviated as (but not limited to):

"s10n" ("s ubstitutio n")
"sub4u4" ("sub stit u tion")
"12" ("substitution")
"su3i1u2on" ("su bst i t u ti on")
"substitution" (no substrings replaced)
Note that "s55n" ("s ubsti tutio n") is not a valid abbreviation of "substitution" because the replaced substrings are adjacent.

The length of an abbreviation is the number of letters that were not replaced plus the number of substrings that were replaced. For example, the abbreviation "s10n" has a length of 3 (2 letters + 1 substring) and "su3i1u2on" has a length of 9 (6 letters + 3 substrings).

Given a target string target and an array of strings dictionary, return an abbreviation of target with the shortest possible length such that it is not an abbreviation of any string in dictionary. If there are multiple shortest abbreviations, return any of them.

 

Example 1:

Input: target = "apple", dictionary = ["blade"]
Output: "a4"
Explanation: The shortest abbreviation of "apple" is "5", but this is also an abbreviation of "blade".
The next shortest abbreviations are "a4" and "4e". "4e" is an abbreviation of blade while "a4" is not.
Hence, return "a4".
Example 2:

Input: target = "apple", dictionary = ["blade","plain","amber"]
Output: "1p3"
Explanation: "5" is an abbreviation of both "apple" but also every word in the dictionary.
"a4" is an abbreviation of "apple" but also "amber".
"4e" is an abbreviation of "apple" but also "blade".
"1p3", "2p2", and "3l1" are the next shortest abbreviations of "apple".
Since none of them are abbreviations of words in the dictionary, returning any of them is correct.
 

Constraints:

target.length == m
dictionary.length == n
1 <= m <= 21
0 <= n <= 1000
1 <= dictionary[i] <= 100
log2(n) + m <= 21 if n > 0

*/

#include <vector>
#include <string>
#include <unordered_set>

using std::unordered_set;
using std::vector;
using std::string;

class MinAbbreviation {

    /*
        411.Minimum-Unique-Word-Abbreviation
        此题不需要遍历所有的字典里的单词的缩写形式．

        首先，我们应该注意到，如果字典里的单词和ｔａｒｇｅｔ的长度不一致，那么永远不会有冲突．所以一下子将范围缩小到那些与ｔａｒｇｅｔ等长的单词了．

        其次，缩写的方案怎么确定呢？其实就是任意一个字符可以选择取或不取．所以就是2^N次方，用一个Ｎ位的二进制数（作为ｍａｓｋ）就可以表示了．有0的ｂｉｔ表示改成数字，有１的ｂｉｔ表示保留字母．这样一个ｍａｓｋ就表示一种缩写方案．

        因此，我们不需要用ＤＦＳ显式地穷尽字典或target的所有缩写字符串，只要逐个查验缩写方案即可．我们将所有ｍａｓｋ按照题目中定义的长度按从小到大排序．每尝试一个ｍａｓｋ，就查看依照这种缩写方案得到的ｔａｒｇｅｔ，是否与字典里的单词依靠同样一种缩写方案得到的字符串相同．如果没有冲突的，那么我们就可以立马选用这种缩写方案．
    */
    string minAbbreviation(string target, vector<string>& dictionary) 
    {
        if (dictionary.size()==0)
            return std::to_string(target.size());        
                
        unordered_set<string>Set;                
        int N = target.size();
        
        for (auto str:dictionary)
        {
            if (str.size()==N)
                Set.insert(str);
        }               
                
        vector<std::pair<int,int>>masks;        
        for (int i=0; i<(1<<N); i++)        
            masks.push_back({len(i,N),i});  
                       
        std::sort(masks.begin(),masks.end());
        
        for (int i=0; i<masks.size(); i++)
        {
            int mask = masks[i].second;
            string a = abbr(target,mask);
            int flag = 1;
            
            for (auto word:Set)
            {
                string b = abbr(word, mask);
                if (a==b)
                {
                    flag = 0;
                    break;
                }
            }            
            if (flag == 1) return a;
        }
    }
    
    
    int len(int mask, int N)
    {
        int count = 0;
        for (int i=0; i<N; i++)
        {
            if (((mask>>(N-1-i))&1)==1)        
                count++;
            else
            {
                int j = i+1;
                while (j<N && ((mask>>(N-1-j))&1)==0)
                    j++;
                count++;
                i = j-1;
            }
        }        
        return count;
    }
    
    string abbr(string A, int mask)
    {       
        string result;
        int N = A.size();
        
        for (int i=0; i<N; i++)
        {
            if (((mask>>(N-1-i))&1)==1)
                result.push_back(A[i]);
            else
            {
                int j = i+1;
                while (j<N && ((mask>>(N-1-j))&1)==0)
                    j++;
                result += std::to_string(j-i);
                i = j-1;
            }
        }
        return result;
    }

public:
    
    string doit_str(string target, vector<string>& dictionary) {
        
    }
};