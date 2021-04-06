/*
1616. Split Two Strings to Make Palindrome

You are given two strings a and b of the same length. 

Choose an index and split both strings at the same index, splitting a into two strings: aprefix and asuffix where a = aprefix + asuffix, and splitting b into two strings: bprefix and bsuffix where b = bprefix + bsuffix. Check if aprefix + bsuffix or bprefix + asuffix forms a palindrome.

When you split a string s into sprefix and ssuffix, either ssuffix or sprefix is allowed to be empty. For example, if s = "abc", then "" + "abc", "a" + "bc", "ab" + "c" , and "abc" + "" are valid splits.

Return true if it is possible to form a palindrome string, otherwise return false.

Notice that x + y denotes the concatenation of strings x and y.

 

Example 1:

Input: a = "x", b = "y"
Output: true
Explaination: If either a or b are palindromes the answer is true since you can split in the following way:
aprefix = "", asuffix = "x"
bprefix = "", bsuffix = "y"
Then, aprefix + bsuffix = "" + "y" = "y", which is a palindrome.
Example 2:

Input: a = "abdef", b = "fecab"
Output: true
Example 3:

Input: a = "ulacfd", b = "jizalu"
Output: true
Explaination: Split them at index 3:
aprefix = "ula", asuffix = "cfd"
bprefix = "jiz", bsuffix = "alu"
Then, aprefix + bsuffix = "ula" + "alu" = "ulaalu", which is a palindrome.
Example 4:

Input: a = "xbdef", b = "xecab"
Output: false
 

Constraints:

1 <= a.length, b.length <= 105
a.length == b.length
a and b consist of lowercase English letters

*/


#include <string>

using std::string;



class PalindromeFormation {

    /*
                1616.Split-Two-Strings-to-Make-Palindrome
        本题的意思是，判断是否找到一个位置将两个字符串都截为两部分，使得A的前半部分和B的后半部分拼接起来能成为一个回文数。

        A: XXX | XXXXX
        B: YYY | YYYYY
        如果找不到的话，我们会把A和B对换，同样的目标我们再求一次。

        假设存在这样的一个位置，能够使得A的前半部分和B的后半部分拼接起来能成为一个回文数，那么意味着可以将这个截断位置对称翻转的话，

        A: XXX | XX | XXX
        B: YYY | YY | YYY
        A1和B3应该是回文对称的；A2或者B2本身就是一个回文串。如果A的第二部分是回文，那么A1+A2+B3就是一个回文串；如果B的第二部分是回文，那么A1+B2+B3就是一个回文串。

        反之，如果上面的条件都不成立，那么说明我们无法找到满足题意的“截断位置”。
    
    */
    bool checkPalindromeFormation(string a, string b) 
    {
        return check(a,b) || check(b,a);        
    }
    
    bool check(string&a, string& b)
    {
        int i=0, j=b.size()-1;
        while (i<j && a[i]==b[j])
        {
            i++;
            j--;
        }
        if (i>=j) return true;
        return isPalindrome(a.substr(i,j-i+1))||isPalindrome(b.substr(i,j-i+1));
    }
    
    bool isPalindrome(string s)
    {
        int i=0, j = s.size()-1;
        while (i<j && s[i]==s[j])
        {
            i++;
            j--;
        }
        return i>=j;
    }


public:

    bool doit_greedy(string a, string b) {
        
        if (a.length() != b.length()) return false;

        auto prefix = [](const string& target1, const string& target2) {

            int i = 0, j = target2.length()-1;

            while (i < j && target1[i] == target2[j]) {
                i++, j--;
            };

            return i;
        };

        auto find = [](const string& target, int index) {

            int i = index, j = target.length() - index - 1;

            while (i < j && target[i] == target[j]) {
                i++, j--;
            }

            return i == j;
        };

        int aprefix = prefix(a, b), bprefix = prefix(b, a);

        return find(a, aprefix) || find(a, bprefix) || find(b, aprefix) || find(b, bprefix);
    }
};