/*
 
 1307. Verbal Arithmetic Puzzle
 
 Given an equation, represented by words on left side and the result on right side.

 You need to check if the equation is solvable under the following rules:

 Each character is decoded as one digit (0 - 9).
 Every pair of different characters they must map to different digits.
 Each words[i] and result are decoded as one number without leading zeros.
 Sum of numbers on left side (words) will equal to the number on right side (result).
 Return True if the equation is solvable otherwise return False.



 Example 1:

 Input: words = ["SEND","MORE"], result = "MONEY"
 Output: true
 Explanation: Map 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8, 'Y'->'2'
 Such that: "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652
 Example 2:

 Input: words = ["SIX","SEVEN","SEVEN"], result = "TWENTY"
 Output: true
 Explanation: Map 'S'-> 6, 'I'->5, 'X'->0, 'E'->8, 'V'->7, 'N'->2, 'T'->1, 'W'->'3', 'Y'->4
 Such that: "SIX" + "SEVEN" + "SEVEN" = "TWENTY" ,  650 + 68782 + 68782 = 138214
 Example 3:

 Input: words = ["THIS","IS","TOO"], result = "FUNNY"
 Output: true
 Example 4:

 Input: words = ["LEET","CODE"], result = "POINT"
 Output: false


 Constraints:

 2 <= words.length <= 5
 1 <= words[i].length, result.length <= 7
 words[i], result contains only upper case English letters.
 Number of different characters used on the expression is at most 10.

 
 
 */

#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;



/*
 1307.Verbal-Arithmetic-Puzzle
 本题就是一个暴力搜索，逐个将字母尝试匹配数字，没有问题的话就处理下一个字母，有问题的话就返回匹配其他数字。为了方便对齐，我们将所有字符串都逆序排列：

 CBA
 ED
 F
 ----
 IHG
 我们dfs的顺序就是逐个处理CEFIBDHGA。当每一列的加数字符匹配完之后（比如说CEF），我们需要查验它们的sum是否与result（也就是I）对应的数字一致。我们需要考虑大致需要剪支的情况：

 I已经匹配过了，但是与sum不一致。
 I没有匹配过，但是sum已经匹配过其他字符了。
 所以我们需要两个hash表，一个记录每个字符对应的数字，另一个记录每个数字是否已经被匹配过。

 大致的递归函数的形式是：dfs(int i, int j, int sum)，其中(i,j)表示我们在处理第i行、第j列的字符，试图给其赋值一个数字；sum表示该列当前的累加和。
 
 
 */


class VerbalArithmeticPuzzle {


public:

    bool doit_dfs(vector<string>& words, string result) {
        
        vector<int> letters(128, -1);
        vector<bool> visited(10, false);
    
        for (auto& word : words) {
            if (result.length() < word.length())
                return false;
            std::reverse(begin(word), end(word));
        }
        
        std::reverse(begin(result), end(result));
        
        std::function<bool(int, int, int)> dfs = [&](int i, int j, int sums) {
            
            if (j == result.size()) {
                if (sums != 0)
                    return false;
                
                if (result.size() > 1 && letters[result.back()] == 0)
                    return false;
                
                return true;
            }
            
            if (i == words.size()) {
                
                int remainder = sums % 10, accum = sums / 10;
                char rch = result[j];
                
                if (letters[rch] != -1) {
                    if (remainder != letters[rch])
                        return false;
                    
                    return dfs(0, j+1, accum);
                } else {
                    
                    letters[rch] = remainder;
                    visited[remainder] = true;
                    if (dfs(0, j+1, accum))
                        return true;
                    visited[remainder] = false;
                    return false;
                }
            }
            
            char c = words[i][j];
            if (letters[c] != -1) {
                
                // first number is not zero, 0876
                if (words[i].size() > 1 && j == words[i].size() - 1 && letters[c] == 0)
                    return false;
                
                return dfs(i+1, j, sums + letters[c]);
            
            } else {
                
                for (int d = 0; d < 10; d++) {
                    
                    if (visited[d])
                        continue;
                    
                    letters[c] = d;
                    visited[d] = true;
                    
                    if (dfs(i+1, j, sums + d))
                        return true;
                    
                    letters[c] = -1;
                    visited[d] = false;
                }
                
                return false;
            }
            
            return false;
        };
        
        return dfs(0, 0, 0);
    }
    
    
};
