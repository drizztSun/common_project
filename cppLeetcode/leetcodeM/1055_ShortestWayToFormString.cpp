/*
1055. Shortest Way to Form String

From any string, we can form a subsequence of that string by deleting some number of characters (possibly no deletions).

Given two strings source and target, return the minimum number of subsequences of source such that their concatenation equals target. If the task is impossible, return -1.

 

Example 1:

Input: source = "abc", target = "abcbc"
Output: 2
Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".
Example 2:

Input: source = "abc", target = "acdbc"
Output: -1
Explanation: The target string cannot be constructed from the subsequences of source string due to the character "d" in target string.
Example 3:

Input: source = "xyz", target = "xzyxz"
Output: 3
Explanation: The target string can be constructed as follows "xz" + "y" + "xz".
 

Constraints:

Both the source and target strings consist of only lowercase English letters from "a"-"z".
The lengths of source and target string are between 1 and 1000.
*/
#include <string>

using std::string;

class ShortestWay {

public:
    
    int doit_search(string source, string target) {
        int count = 0;
        int i = 0 ; 
        int j = 0;

        while(i < target.length())
        {
            int start = j;
            while(j < source.length() && source[j] != target[i])
                j++;

            if(start == 0 && j == source.length())
                return -1;

            if(source[j] == target[i])
            {
                j++;
                i++;
                if(i == target.length() && j < source.length())
                    count++;
            }
            
            if(j == source.length())
            {
                j = 0;
                count++;
            }
        }
        return count;
    }
};