"""
439. Ternary Expression Parser

Given a string representing arbitrarily nested ternary expressions, calculate the result of the expression. 
You can always assume that the given expression is valid and only consists of digits 0-9, ?, :, T and F (T and F represent True and False respectively).

Note:

1. The length of the given string is ≤ 10000.
2. Each number will contain only one digit.
3. The conditional expressions group right-to-left (as usual in most languages).
4. The condition will always be either T or F. That is, the condition will never be a digit.
5. The result of the expression will always evaluate to either a digit 0-9, T or F.

Example 1:

Input: "T?2:3"

Output: "2"

Explanation: If true, then result is 2; otherwise result is 3.
Example 2:

Input: "F?1:T?4:5"

Output: "4"

Explanation: The conditional expressions group right-to-left. Using parenthesis, it is read/evaluated as:

             "(F ? 1 : (T ? 4 : 5))"                   "(F ? 1 : (T ? 4 : 5))"
          -> "(F ? 1 : 4)"                 or       -> "(T ? 4 : 5)"
          -> "4"                                    -> "4"
Example 3:

Input: "T?T?F:5:3"

Output: "F"

Explanation: The conditional expressions group right-to-left. Using parenthesis, it is read/evaluated as:

             "(T ? (T ? F : 5) : 3)"                   "(T ? (T ? F : 5) : 3)"
          -> "(T ? F : 3)"                 or       -> "(T ? F : 5)"
          -> "F"                                    -> "F"

"""


class ParseTernary:

    """
        439.Ternary-Expression-Parser
        
        此题粗看很复杂，实际很明晰。

        需要最早解析的字符串，其实是已经形成标准型a?X:Y的这五个连续字符。所以在第一次出现这五个连续字符之前的字符，都可以不断存进一个栈里供后续处理。

        具体的算法是，当发现?字符，表明这可能是一组标准型的head。所以把a?之前的字符串扔进栈里，然后重置curRes并顺着a?继续向后探索。如果还有出现类似?的标记，则重复之前的入栈操作；
        反之，如果之后curRes集齐五个字符，则说明这五个字符是类似a?X:Y的标准型，可以被解析变为一个字符。此时考虑一下栈里的栈顶元素，如果栈顶元素加上当前的这一个字符（curRes），又构成五个字符的话，可以进一步解析；
        如此重复直至栈顶无法提供凑齐五个字符的string，此时curRes需要顺着expression继续探索下去。

        a?X:Y
        a?b?X:Y
        a?b?X:c?Y:Z

        最终返回的是当前的字符串，即curRes。
    """
    def doit_stack(self, expression: str) -> str:

        st = []
        i = 0
        current = ''

        while i < len(expression):

            if i+1 < len(expression) and expression[i+1] == '?':
                st.append(current)
                current = expression[i]
            else:
                current += expression[i]

                while len(current) == 5:
                    res = current[2] if current[0] == 'T' else current[4]
                    current = st.pop() + res
            i += 1
            
        return current
                    
