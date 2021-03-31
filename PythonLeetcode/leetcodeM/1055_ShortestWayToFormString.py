"""
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


"""


class ShortestWay:

    def doit_search(self, source: str, target: str) -> int:
        
        i, j = 0, 0
        cnt = 0
        
        while i < len(target):
            
            start = j
            while j < len(source) and source[j] != target[i]:
                j += 1
                
            if start == 0 and j == len(source):
                return -1
            
            if j != len(source) and source[j] == target[i]:
                i += 1
                j += 1
                
                if i == len(target) and j < len(source):
                    cnt += 1
                    
            if j == len(source):
                j = 0
                cnt += 1
                
        return cnt