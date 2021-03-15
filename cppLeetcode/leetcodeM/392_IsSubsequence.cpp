/*
392. Is Subsequence


Given two strings s and t, check if s is a subsequence of t.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

 

Example 1:

Input: s = "abc", t = "ahbgdc"
Output: true
Example 2:

Input: s = "axc", t = "ahbgdc"
Output: false
 

Constraints:

0 <= s.length <= 100
0 <= t.length <= 104
s and t consist only of lowercase English letters.
 

Follow up: If there are lots of incoming s, say s1, s2, ..., sk where k >= 109, and you want to check one by one to see if t has its subsequence. In this scenario, how would you change your code?
*/


#include <string>
#include <unordered_map>
#include <vector>

using std::vector;
using std::unordered_map;
using std::string;


class IsSubsequence {

    /*
        392.Is-Subsequence
        普通的双指针解法就不再赘述。考虑follow up的问题。显然，需要提前建立关于t的一些信息的存储，方便s来查阅，用空间换时间嘛。

        结合双指针解法的思路，如果在t[pos]找到了s[i]，则只需要在pos之后去寻找s[i+1]。所以提前构建映射：t的每个字符和该字符出现位置:

        Map[s[i]].push_back(i);
        建立pos的初始位置-1. 然后遍历s[i]：在Map[s[i]]里找第一个大于pos的位置并更新pos，则之后对于s[i+1]的查找必须从t的新pos位置开始。

        int pos=-1;
        for (int i=0; i<s.size()-1; i++)
        {
        int flag=0;
        for (int j: Map[s[i]])
        {
            if (j>pos)
            {
                pos = j;
                flag = 1;
            }
        }
        if (flag==0) retrun false; // 对于s[i]，在t中没有找到合适的位置
        }
        return true;
    */
    bool isSubsequence(string s, string t) 
    {
        int i=0;
        int j=0;
        while (i<s.size() && j<t.size())
        {
            if (s[i]!=t[j])
                j++;
            else
            {
                i++;
                j++;
            }
        }
        if (i<s.size())
            return false;
        else
            return true;
    }

    bool isSubsequence(string s, string t) 
    {
        unordered_map<char,vector<int>>Map;
        for (int i=0; i<t.size(); i++)
            Map[t[i]].push_back(i);
            
        int NextStart = -1;
        for (int i=0; i<s.size(); i++)
        {
            char ch = s[i];
            int flag=0;
            
            for (int j:Map[ch])
            {
                if (j>NextStart)
                {
                    flag = 1;
                    NextStart = j;
                    break;
                }
            }
            if (flag==0) return false;
        }
        
        return true;
    }


public:
    
    bool doit_(string s, string t) {

        int i = 0;

        for (auto c : t) {
            if (c == s[i]) {
                i++;
                if (i == s.length()) return true;
            }
        }
        
        return i == s.length();
    }
};