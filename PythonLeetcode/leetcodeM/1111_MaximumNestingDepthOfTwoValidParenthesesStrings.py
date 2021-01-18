"""
1111. Maximum Nesting Depth of Two Valid Parentheses Strings

A string is a valid parentheses string (denoted VPS) if and only if it consists of "(" and ")" characters only, and:

It is the empty string, or
It can be written as AB (A concatenated with B), where A and B are VPS's, or
It can be written as (A), where A is a VPS.
We can similarly define the nesting depth depth(S) of any VPS S as follows:

depth("") = 0
depth(A + B) = max(depth(A), depth(B)), where A and B are VPS's
depth("(" + A + ")") = 1 + depth(A), where A is a VPS.
For example,  "", "()()", and "()(()())" are VPS's (with nesting depths 0, 1, and 2), and ")(" and "(()" are not VPS's.



Given a VPS seq, split it into two disjoint subsequences A and B, such that A and B are VPS's (and A.length + B.length = seq.length).

Now choose any such A and B such that max(depth(A), depth(B)) is the minimum possible value.

Return an answer array (of length seq.length) that encodes such a choice of A and B:  answer[i] = 0 if seq[i] is part of A, else answer[i] = 1.
Note that even though multiple answers may exist, you may return any of them.



Example 1:

Input: seq = "(()())"
Output: [0,1,1,1,1,0]
Example 2:

Input: seq = "()(())()"
Output: [0,0,0,1,1,0,1,1]


Constraints:

1 <= seq.size <= 10000

"""


class MaxDepthAfterSplit:

    # Logic: If it is an even depth bracket, assign it to A, else assign it to B. 
    # Using this alternating assigning logic to A or B, we achieve the minimum depth possible for max(depth(A),depth(B)).
    def doit_(self, seq: str) -> list:

        c = 0
        res = []
        for i in range(len(seq)):

            if c == 0:
                c += 1

                if seq[i] == '(':
                    res.append(1)
                else:
                    res.append(0)
            elif c == 1:
                c -= 1
                if seq[i] == ')':
                    res.append(1)
                else:
                    res.append(0)

        return res

    """
        I first found this problem be a little confusing because of the long explanation. In my opinion, the grammar rules for a VPS could be much more succinctly defined using a context free grammar:

        A -> (A)
        A -> AA
        A -> ε
        where ε is the empty string.

        Furthermore, the examples only have parenthesis nested to a depth of 2. I wanted to see how this problem would look for a more deeply nested VPS, so I made this example:

        `s = "(())()()((()))"`
        I thought about it for a bit, and figured out that the answer for this example would be:

        [0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0]

        As I worked through this example, an inkling of a solution quickly appeared to me. To construct the VPS, all one has to do is alternate which subsequence one is adding 
        to if the character they are currently iterating over is not the same as the previous character that was iterated over. 
        This is where the bottom up part of the solution comes in: We initialize the first character to be in set A (by marking the value at index 0 in the result array to be 0), 
        and then iterate through the remaining characters in the sequence. Code below:

    """
    def doit_(self, seq: str) -> list:
        result = [None for _ in range(len(seq))]
        result[0] = 0
        prev = seq[0]
        
        for i in range(1, len(seq)):
            c = seq[i]
            if c != prev:
                result[i] = result[i-1]
            else:
                if result[i-1] == 1:
                    result[i] = 0
                else:
                    result[i] = 1
            prev = c
        return result