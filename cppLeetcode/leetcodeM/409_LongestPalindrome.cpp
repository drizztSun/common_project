/*
409. Longest Palindrome

Given a string s which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters.

Letters are case sensitive, for example, "Aa" is not considered a palindrome here.

 

Example 1:

Input: s = "abccccdd"
Output: 7
Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
Example 2:

Input: s = "a"
Output: 1
Example 3:

Input: s = "bb"
Output: 2
 

Constraints:

1 <= s.length <= 2000
s consists of lowercase and/or uppercase English letters only.





*/
#include <vector>
#include <string>

using std::string;
using std::vector;

class LongestPalindrome {

public:
    
    /*
        409.Longest-Palindrome
        注意，出现了奇数次的字符也可以参与构建回文串：其中一个可以全部采用；剩余的只需要取用其偶数次。

        所以，判定方法是：

                int sum=0;
                int flag=0;
                for (auto a:Map)
                {
                    if ((a % 2) ==1)
                    {
                        sum+=a-1;
                        flag=1;
                    }
                    else
                        sum+=a;
                }        
                return sum+flag;    
    */
    int doit_hashtable(string s) 
    {
        vector<int>Map(256,0);
        for (int i=0; i<s.size(); i++)
            Map[s[i]]++;
        
        int sum=0;
        int flag=0;
        for (auto a:Map)
        {
            if ((a % 2) ==1)
            {
                sum+=a-1;
                flag=1;
            }
            else
                sum+=a;
        }
        
        return sum+flag;
    }