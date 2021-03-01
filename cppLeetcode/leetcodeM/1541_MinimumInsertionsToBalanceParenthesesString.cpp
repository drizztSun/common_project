/*
1541. Minimum Insertions to Balance a Parentheses String


Given a parentheses string s containing only the characters '(' and ')'. A parentheses string is balanced if:

Any left parenthesis '(' must have a corresponding two consecutive right parenthesis '))'.
Left parenthesis '(' must go before the corresponding two consecutive right parenthesis '))'.
In other words, we treat '(' as openning parenthesis and '))' as closing parenthesis.

For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" and "(()))" are not balanced.

You can insert the characters '(' and ')' at any position of the string to balance it if needed.

Return the minimum number of insertions needed to make s balanced.

 

Example 1:

Input: s = "(()))"
Output: 1
Explanation: The second '(' has two matching '))', but the first '(' has only ')' matching. We need to to add one more ')' at the end of the string to be "(())))" which is balanced.
Example 2:

Input: s = "())"
Output: 0
Explanation: The string is already balanced.
Example 3:

Input: s = "))())("
Output: 3
Explanation: Add '(' to match the first '))', Add '))' to match the last '('.
Example 4:

Input: s = "(((((("
Output: 12
Explanation: Add 12 ')' to balance the string.
Example 5:

Input: s = ")))))))"
Output: 5
Explanation: Add 4 '(' at the beginning of the string and one ')' at the end. The string becomes "(((())))))))".
 

Constraints:

1 <= s.length <= 10^5
s consists of '(' and ')' only.

*/
#include <string>

using std::string;


class MinInsertion {

    /*
        1541.Minimum-Insertions-to-Balance-a-Parentheses-String
        本题和 921 Minimum Add to Make Parentheses Valid本质一样。区别只在于一个左括号必须和两个连续的右括号匹配。我们仍然可以沿用贪心法的思想，用count来记录未被匹配的左括号的数目。变化在于：

        我们需要连续两个右括号，才能试图与之前的一个左括号对消。如果不存在连续的两个右括号，我们必须先手工增加一个右括号，即ret++，然后再试图匹配左括号消减count。
        如果最终有剩余未被匹配的左括号，我们需要增加两倍数目的右括号与之对应，即ret+=count*2.
    */
    int doit_parenthesis(string s) 
    {
        int count = 0;
        int ret = 0;
        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='(')
                count++;
            else
            {
                if (i+1<s.size() && s[i+1]==')')
                {
                    count--;
                    i++;
                }
                else
                {
                    count--;
                    ret++;
                }
            }
            if (count<0)
            {
                ret++;
                count=0;
            }
        }
        return ret + count*2;
    }

public:
    
    int doit_(string s) {
        
        int opening = 0, closing = 0;
        int total = 0;

        for (int i = 0; i < s.length();) {

            while (i < s.size() && s[i] == '(') {
                opening++, i++;
            }

            while (i < s.size() && s[i] == ')') {
                closing++, i++;
            }

            if (opening * 2 == closing)
                opening = closing = 0;

            else if (opening * 2 > closing) {

                // more ( then 2 times ), there is still ( left.
                opening -= closing / 2;
                if (closing % 2 == 1) {
                    total++;
                    opening--;
                }
                closing = 0;
            } else {
                // ( is more then 2 times ), 
                closing -= 2 * opening;
                total += closing / 2;
                if (closing % 2 == 1) {
                    total += 2;
                }
                opening = closing = 0;
            }
        }

        return total + 2 * opening;
    }
};


