/*
408. Valid Word Abbreviation


Given a non-empty string s and an abbreviation abbr, return whether the string matches with the given abbreviation.

A string such as "word" contains only the following valid abbreviations:

["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
Notice that only the above abbreviations are valid abbreviations of the string "word". Any other string is not a valid abbreviation of "word".

Note:
Assume s contains only lowercase letters and abbr contains only lowercase letters and digits.

Example 1:
Given s = "internationalization", abbr = "i12iz4n":

Return true.
Example 2:
Given s = "apple", abbr = "a2e":

Return false.

*/

#include <string>

using std::string;


class ValidWordAbbreviation {

    /*
        408.Valid-Word-Abbreviation
        思路非常直接，遍历一遍abbr，移动abbr的同时也移动word的指针，看看每一步都是否对应。

        需要注意的细节：

        数字不能有前导0. 比如word=ab, abbr=02就应该输出false.
        abbr遍历完之后，word的遍历也应该恰好结束。即if (i!=word.size()) return false;
    
    */
    bool validWordAbbreviation(string word, string abbr) 
    {
        int i=0;
        int j=0;
        
        while (j<abbr.size())
        {
            if (i>=word.size()) return false;
            
            if (abbr[j]=='0')
                return false;
            else if (abbr[j]>='0' && abbr[j]<='9')
            {
                int num=0;
                while (j<abbr.size() && abbr[j]>='0' && abbr[j]<='9')
                {
                    num=num*10+abbr[j]-'0';
                    j++;
                }
                i+=num;
            }
            else if (abbr[j]>='a' && abbr[j]<='z')
            {
                if (abbr[j]!=word[i])
                    return false;
                else
                {
                    i++;
                    j++;
                }
            }
        }
        
        if (i!=word.size()) 
            return false;
        else
            return true;
        
    }

public:

    bool doit_str(string word, string abbr) {
        
        int i = 0, j = 0;
        int n = word.size(), m = abbr.size();
        
        while (i < n && j < m) {
            if (isdigit(abbr[j])) {
                if (abbr[j] == '0') return false;
                int k = 0;
                while(j < m && isdigit(abbr[j]))
                    k = k*10 + abbr[j++] - '0';
                i += k;
            } else {
                if (word[i++] != abbr[j++])
                    return false;
            }
        }
        
        return i == n && j == m;
    }
};
