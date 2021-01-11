"""
1209. Remove All Adjacent Duplicates in String II


Given a string s, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them causing the left and the right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made.

It is guaranteed that the answer is unique.

 

Example 1:

Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.
Example 2:

Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
Example 3:

Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"
 

Constraints:

1 <= s.length <= 10^5
2 <= k <= 10^4
s only contains lower case English letters.

"""


class RemoveAllAdjacentDuplicates:


    """
        Approach 3: Stack
        Instead of storing counts for each character, we can use a stack. When a character does not match the previous one, we push 1 to the stack. Otherwise, we increment the count on the top of the stack.

        Stack Illustration

        Algorithm

        Iterate through the string:

        If the current character is the same as the one before, increment the count on the top of the stack.

        Otherwise, push 1 to the stack.
        If the count on the top of the stack equals k, erase last k characters and pop from the stack.

        Note that, since Integer is immutable in Java, we need to pop the value first, increment it, and then push it back (if it's less than k).


        Complexity Analysis

        Time complexity: O(n), where nn is a string length. We process each character in the string once.

        Space complexity: O(n) for the stack.
    """
    def doit_stack(self, s: str, k: int) -> str:
        
        stack = []
        for c in s:
            if not stack or stack[-1][0] != c:
                stack.append([c, 1])
            else:
                stack[-1][1] += 1
                if stack[-1][1] == k:
                    stack.pop()
        ans = ''
        for c, cnt in stack:
            ans += c * cnt
        return ans


    """
        Approach 5: Two Pointers
        This method was proposed by @lee215, and we can use it to optimize string operations in approaches 2 and 3. Here, we copy characters within the same string using the fast and slow pointers. 
        Each time we need to erase k characters, we just move the slow pointer k positions back.

        Two Pointers Illustration

        Algorithm

        Initialize the slow pointer (j) with zero.

        Move the fast pointer (i) through the string:

        Copy s[i] into s[j].

        If s[j] is the same as s[j - 1], increment the count on the top of the stack.

        Otherwise, push 1 to the stack.
        If the count equals k, decrease j by k and pop from the stack.

        Return j first characters of the string.


        Complexity Analysis
    """
    def doit_twopointer(self, s: str, k: int) -> str:

        stack = []
        j = 0

        for i in range(len(s)):
            s[j] = s[i]

            if j == 0 or s[j] != s[j-1]:
                stack.push(1)
            else:
                stack[-1] += 1
                if stack[-1] == k:
                    j -= k

        return s[:j]


"""
1047. Remove All Adjacent Duplicates In String

Given a string S of lowercase letters, a duplicate removal consists of choosing two adjacent and equal letters, and removing them.

We repeatedly make duplicate removals on S until we no longer can.

Return the final string after all such duplicate removals have been made.  It is guaranteed the answer is unique.

 

Example 1:

Input: "abbaca"
Output: "ca"
Explanation: 
For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal, and this is the only possible move.  
The result of this move is that the string is "aaca", of which only "aa" is possible, so the final string is "ca".
 

Note:

1 <= S.length <= 20000
S consists only of English lowercase letters.

"""
class RemoveDuplicatesII:
    
    def doit_stack(self, s: str, k: int) -> str:
        
        buff = []

        for c in s:

            if not buff or buff[-1] != c:
                buff.append(c)
            else:
                buff.pop()

        return ''.join(buff)