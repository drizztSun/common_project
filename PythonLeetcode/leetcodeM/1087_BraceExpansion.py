"""
1087. Brace Expansion

A string S represents a list of words.

Each letter in the word has 1 or more options.
If there is one option, the letter is represented as is.
If there is more than one option, then curly braces delimit the options.  For example, "{a,b,c}" represents options ["a", "b", "c"].

For example, "{a,b,c}d{e,f}" represents the list ["ade", "adf", "bde", "bdf", "cde", "cdf"].

Return all words that can be formed in this manner, in lexicographical order.



Example 1:

Input: "{a,b}c{d,e}f"
Output: ["acdf","acef","bcdf","bcef"]
Example 2:

Input: "abcd"
Output: ["abcd"]


Note:

1 <= S.length <= 50
There are no nested curly brackets.
All characters inside a pair of consecutive opening and ending curly brackets are different.

"""


class BraceExpansion:

    """
    A character can be:
    1. {: the following characters will be in braces untill };
    2. }: add each sorted option character to current strings;
    3. ,: ignored;
    4. alphabet in {}: put it into the option list
    5. alphabet not in {}: add it to current strings directly
    """
    def doit_bfs(self, S: str) -> list:
        from collections import deque

        result, brace = deque([[]]), False
        options, n = [], len(S)

        for i in range(n):

            if S[i] == '{':
                brace = True

            elif S[i] == '}':
                m = len(result)
                options.sort()
                for I in range(m):
                    cur = result.popleft()
                    for c in options:
                        result.append(cur + [c])

                options = []
                brace = False

            elif brace:
                if S[i] != ',':
                    options.append(S[i])

            else:
                for j in range(len(result)):
                    result[j].append(S[i])

        for i in range(len(result)):
            result[i] = ''.join(result[i])

        return list(result)

    def doit_dfs(self, S):
        """
        :type S: str
        :rtype: List[str]
        """
        # depth first search
        out = []
        def search(cur, i):
            res = []
            if i==len(S):
                out.append(cur)
                return
            if S[i]=='{':
                i+=1
                while(S[i]!='}'):
                    if S[i]!=',':
                        res.append(S[i])
                    i+=1
                i+=1 # ignore '}'
            else:
                res.append(S[i])
                i+=1
            for ele in sorted(res):
                search(cur+ele, i)
        search('', 0)
        return out

