"""
1653. Minimum Deletions to Make String Balanced


You are given a string s consisting only of characters 'a' and 'b'​​​​.

You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.

Return the minimum number of deletions needed to make s balanced.

 

Example 1:

Input: s = "aababbab"
Output: 2
Explanation: You can either:
Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
Example 2:

Input: s = "bbaaaaabb"
Output: 2
Explanation: The only solution is to delete the first two characters.
 

Constraints:

1 <= s.length <= 105
s[i] is 'a' or 'b'​​.

"""


class MinimumDeletions:
    
    """
        Greedy. Use bCnt to record count for preserved b (have no way to be replaced by a) up till now, use res to record deletion count.

        Traverse string s, for each char ch:
        (1) If it's b, we don't know whether to delete it or not, only increase bCnt by 1.
        (2) If it's a, we will make deletion only when bCnt is > 0, which means there're b preserved before and has no way to be replaced by traversed a. 
        We might delete current a, or delete previous b, but we don't know yet since this is decided by furture remainig chars. 
        But no matter what we delete, the deletion cnt res will always increase by 1. Use the greedy idea, even if we delete current a, still decrease bCnt by 1 to indicate this b can be replaced by a if later we need it to be replaced

        eg1. aabba
        aabb -> res = 0, bCnt = 2;
        aabba -> res = 1, bCnt = 1;
        ans: aabb

        eg2. aabbaaa
        aabb -> res = 0, bCnt = 2;
        aabba -> res = 1, bCnt = 1 (aabb, or aaba)
        aabbaa -> res = 2, bCnt = 0 (aabb, or aaaa)
        aabbaaa -> res = 2, bCnt = 0 (aaaaa)
    """
    
    def doit_greedy(self, s: str) -> int:

        bCnt, res = 0, 0

        for c in s:
            if c == 'a' and bCnt > 0:
                bCnt -= 1
                res += 1
            elif c == 'b':
                bCnt += 1

        return res


