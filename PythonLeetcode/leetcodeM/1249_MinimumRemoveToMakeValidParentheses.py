"""
1249. Minimum Remove to Make Valid Parentheses

Given a string s of '(' , ')' and lowercase English characters.

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions )
so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.


Example 1:

Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
Example 2:

Input: s = "a)b(c)d"
Output: "ab(c)d"
Example 3:

Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.
Example 4:

Input: s = "(a(b(c)d)"
Output: "a(b(c)d)"

"""


class MinRemoveToMakeValid:

    def doit_1(self, s: str) -> str:

        def delete_invalid_closing(string, open_symbol, close_symbol):
            sb = []
            balance = 0
            for c in string:
                if c == open_symbol:
                    balance += 1
                if c == close_symbol:
                    if balance == 0:
                        continue
                    balance -= 1
                sb.append(c)
            return "".join(sb)

        # Note that s[::-1] gets the reverse of s.
        s = delete_invalid_closing(s, "(", ")")

        s = delete_invalid_closing(s[::-1], ")", "(")

        return s[::-1]

    def doit(self, s: str) -> str:

        # Parse 1: Remove all invalid ")"
        first_parse_chars = []
        balance = 0
        open_seen = 0
        for c in s:
            if c == "(":
                balance += 1
                open_seen += 1
            if c == ")":
                if balance == 0:
                    continue
                balance -= 1
            first_parse_chars.append(c)

        # Parse 2: Remove the rightmost "("
        result = []
        open_to_keep = open_seen - balance
        for c in first_parse_chars:
            if c == "(":
                open_to_keep -= 1
                if open_to_keep < 0:
                    continue
            result.append(c)

        return "".join(result)


if __name__ == '__main__':

    MinRemoveToMakeValid().doit_dp(s = "lee(t(c)o)de)")

    MinRemoveToMakeValid().doit_dp(s = "a)b(c)d")

    MinRemoveToMakeValid().doit_dp(s = "))((")

    MinRemoveToMakeValid().doit_dp(s = "(a(b(c)d)")

