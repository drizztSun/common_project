"""
678. Valid Parenthesis String

Given a string containing only three types of characters: '(', ')' and '*', write a function to check whether this string is valid. We define the validity of a string by these rules:

. Any left parenthesis '(' must have a corresponding right parenthesis ')'.
. Any right parenthesis ')' must have a corresponding left parenthesis '('.
. Left parenthesis '(' must go before the corresponding right parenthesis ')'.
. '*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.

An empty string is also valid.

Example 1:
Input: "()"
Output: True

Example 2:
Input: "(*)"
Output: True

Example 3:
Input: "(*))"
Output: True

Note:
The string size will be in the range [1, 100].


"""


class ValidParentthesis:


    def doit_math(self, s: str) -> bool:

        left = 0
        for c in s:
            if c  == '(' or c == '*':
                left += 1
            else:
                left -=1

            if left < 0: return False
        
        if left == 0: return True

        right = 0
        for c in s[::-1]:
            if c == ')' or c == '*':
                right += 1
            else:
                right -= 1

            if right < 0: return False

        return True


    def doit_(self, s: str) -> bool:
        from functools import lru_cache
        
        @lru_cache(None)
        def dfs(i, left, right):

            if i == len(s):
                return left == right

            if right > left:
                return False

            if s[i] == '(':
                return dfs(i+1, left + 1, right)

            if s[i] == ')':
                return dfs(i+1, left, right+1)

            if left > right:
                if dfs(i+1, left, right+1):
                    return True
            
            if dfs(i+1, left + 1, right):
                return True

            return dfs(i+1, left, right)
                
        return dfs(0, 0, 0)

    def doit_stack(self, s: str) -> bool:
        stack = []
        for x in s:
            if x == "(" or x == "*":
                stack.append(x)
            else:
                if "(" in stack:
                    index = stack[::-1].index("(")
                    del stack[len(stack)-index-1]
                elif "*" in stack:
                    index = stack.index("*")
                    del stack[index]
                else:
                    return False
        c = 0    
        while(stack):
            x = stack.pop()
            if x == "*":
                c+=1
            else:
                c-=1
            if c < 0:
                return False
        return True

    """
        Approach #2: Dynamic Programming [Accepted]
        Intuition and Algorithm

        Let dp[i][j] be true if and only if the interval s[i], s[i+1], ..., s[j] can be made valid. Then dp[i][j] is true only if:

        s[i] is '*', and the interval s[i+1], s[i+2], ..., s[j] can be made valid;

        or, s[i] can be made to be '(', and there is some k in [i+1, j] such that s[k] can be made to be ')', plus the two intervals cut by s[k] (s[i+1: k] and s[k+1: j+1]) can be made valid;


        Complexity Analysis

        Time Complexity: O(N^3), where NN is the length of the string. There are O(N^2) states corresponding to entries of dp, and we do an average of O(N) work on each state.

        Space Complexity: O(N^2), the space used to store intermediate results in dp.
    """
    def doit_dp(self, s):
        if not s: return True
        LEFTY, RIGHTY = '(*', ')*'

        n = len(s)
        dp = [[False] * n for _ in s]
        for i in range(n):
            if s[i] == '*':
                dp[i][i] = True
            if i < n-1 and s[i] in LEFTY and s[i+1] in RIGHTY:
                dp[i][i+1] = True

        for size in range(2, n):
            for i in range(n - size):
                if s[i] == '*' and dp[i+1][i+size]:
                    dp[i][i+size] = True
                elif s[i] in LEFTY:
                    for k in range(i+1, i+size+1):
                        if (s[k] in RIGHTY and
                                (k == i+1 or dp[i+1][k-1]) and
                                (k == i+size or dp[k+1][i+size])):
                            dp[i][i+size] = True
        return dp[0][-1]

    """ 
        Approach #3: Greedy [Accepted]
        Intuition

        When checking whether the string is valid, we only cared about the "balance": the number of extra, open left brackets as we parsed through the string. For example, when checking whether '(()())' is valid, we had a balance of 1, 2, 1, 2, 1, 0 as we parse through the string: '(' has 1 left bracket, '((' has 2, '(()' has 1, and so on. This means that after parsing the first i symbols, (which may include asterisks,) we only need to keep track of what the balance could be.

        For example, if we have string '(***)', then as we parse each symbol, the set of possible values for the balance is [1] for '('; [0, 1, 2] for '(*'; [0, 1, 2, 3] for '(**'; [0, 1, 2, 3, 4] for '(***', and [0, 1, 2, 3] for '(***)'.

        Furthermore, we can prove these states always form a contiguous interval. Thus, we only need to know the left and right bounds of this interval. That is, we would keep those intermediate states described above as [lo, hi] = [1, 1], [0, 2], [0, 3], [0, 4], [0, 3].

        Algorithm

        Let lo, hi respectively be the smallest and largest possible number of open left brackets after processing the current character in the string.

        If we encounter a left bracket (c == '('), then lo++, otherwise we could write a right bracket, so lo--. If we encounter what can be a left bracket (c != ')'), then hi++, otherwise we must write a right bracket, so hi--. If hi < 0, then the current prefix can't be made valid no matter what our choices are. Also, we can never have less than 0 open left brackets. At the end, we should check that we can have exactly 0 open left brackets.


        Complexity Analysis

        Time Complexity: O(N), where NN is the length of the string. We iterate through the string once.

        Space Complexity: O(1), the space used by our lo and hi pointers. However, creating a new character array will take O(N) space.
    """
    def doit_greedy(self, s):
        lo = hi = 0
        for c in s:
            lo += 1 if c == '(' else -1
            hi += 1 if c != ')' else -1
            if hi < 0: break
            lo = max(lo, 0)

        return lo == 0