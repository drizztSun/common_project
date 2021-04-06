/*
418. Sentence Screen Fitting

Given a rows x cols screen and a sentence represented by a list of non-empty words, find how many times the given sentence can be fitted on the screen.

Note:

A word cannot be split into two lines.
The order of words in the sentence must remain unchanged.
Two consecutive words in a line must be separated by a single space.
Total words in the sentence won't exceed 100.
Length of each word is greater than 0 and won't exceed 10.
1 ≤ rows, cols ≤ 20,000.
Example 1:

Input:
rows = 2, cols = 8, sentence = ["hello", "world"]

Output: 
1

Explanation:
hello---
world---

The character '-' signifies an empty space on the screen.
Example 2:

Input:
rows = 3, cols = 6, sentence = ["a", "bcd", "e"]

Output: 
2

Explanation:
a-bcd- 
e-a---
bcd-e-

The character '-' signifies an empty space on the screen.
Example 3:

Input:
rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]

Output: 
1

Explanation:
I-had
apple
pie-I
had--

The character '-' signifies an empty space on the screen.
*/

#include <string>
#include <vector>

using std::vector;
using std::string;
 

class WordsTyping {

    /*
            418.Sentence-Screen-Fitting
        此题如果按照逐个单词去分析处理，结果会超时．更合理的方式是按照逐个ｃｏｌｓ的长度去处理．这里将sentence的所有单词用空格串联起来：

            for (auto str:sentence)
                {
                    if (str.size()>cols) return 0;
                    s+= str+" ";
                }   
        注意，这里可以提前处理不合法的例子．

        初始的字符idex是０，每处理一行，我们就把index+=cols，此时如果index落到了空格上，一切ＯＫ，说明至此的所有字符都可以放在一个row里面．如果没有落到空格上，说明某个单词没有写完就触碰了边界，这时候我们将index慢慢回退直至遇到了一个空格为止．

        重复以上过程，当处理完rows行之后，看看此刻的index是length的多少倍，就说明能重复多少个字符串．
    */
    int wordsTyping(vector<string>& sentence, int rows, int cols) 
    {
        string s;
        for (auto str:sentence)
        {
            if (str.size()>cols) return 0;
            s+= str+" ";
        }   
        
        int i = 0;
        int len = s.size();
        
        for (int k=0; k<rows; k++)
        {
            i+=cols;
            while (s[i%len]!=' ')
                i--;
            i++;
        }
        return i/len;
    }
};