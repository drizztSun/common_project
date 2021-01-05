/*
678. Valid Parenthesis String

Given a string containing only three types of characters: '(', ')' and '*', write a function to check whether this string is valid. We define the validity of a string by these rules:

Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
An empty string is also valid.

Example 1:
Input: "()"
Output: True
Example 2:
Input: "(*)"
Output: True
Example 3:
Input: "(*))"
Output: True
Note:
The string size will be in the range [1, 100].

*/

#include <string>

using std::string;



class CheckValidString {

public:

    /*
    O(n)
    */
    bool doit_(string s) {
        
        int leftbalance = 0;
        
        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] == '(' || s[i] == '*')
                leftbalance++;
            else
                leftbalance--;

            // anytime, if left is not enough, and more right closing  
            if(leftbalance < 0) return false;
        }

        // left + star == right, 
        if (leftbalance == 0) return true;

        // left + star > right, we need star to be right
        int rightbalance = 0;

        for(int i = s.size() - 1;i>=0;i--)  {
            
            if(s[i] == ')' || s[i] == '*')
            
                rightbalance++;
            else
                rightbalance--;

            // if right + star < left, it is invalid    
            if(rightbalance < 0) return false;
        }

        // right + star > left and left + star > right. so star could be change to left/right/empty, to balance it. so it is alreays True.
        return true;
    }
};