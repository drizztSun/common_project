"""
727. Minimum Window Subsequence

Given strings S and T, find the minimum (contiguous) substring W of S, so that T is a subsequence of W.

If there is no such window in S that covers all characters in T, return the empty string "".
If there are multiple such minimum-length windows, return the one with the left-most starting index.

Example 1:

Input:
S = "abcdebdde", T = "bde"
Output: "bcde"
Explanation:
"bcde" is the answer because it occurs before "bdde" which has the same length.
"deb" is not a smaller window because the elements of T in the window must occur in order.


Note:

All the strings in the input will only contain lowercase letters.
The length of S will be in the range [1, 20000].
The length of T will be in the range [1, 100].
"""


class MinWindowSubsequence:
    """
    Approach #1: Dynamic Programming (Postfix Variation) [Accepted]
    Intuition

    Let's work on a simpler problem: T = 'ab'. Whenever we find some 'b' in S, we look for the most recent 'a' that occurred before it, and that forms a candidate window 'a' = S[i], ..., S[j] = 'b'.

    A weak solution to that problem would be to just search for 'a' every time we find a 'b'.
    With a string like 'abbb...bb' this would be inefficient. A better approach is to remember the last 'a' seen.
    Then when we see a 'b', we know the start of the window is where we last saw 'a', and the end of the window is where we are now.

    How can we extend this approach to say, T = 'abc'? Whenever we find some 'c' in S, such as S[k] = 'c',
    we can remember the most recent window that ended at 'b', let's say [i, j]. Then our candidate window (that is, the smallest possible window ending at k) would be [i, k].

    Our approach in general works this way. We add characters to T one at a time, and for every S[k] = T[-1]
    we always remember the length of the candidate window ending at k. We can calculate this using knowledge of the length of the previous window (so we'll need to remember the last window seen).
    This leads to a dynamic programming solution.

    Algorithm

    As we iterate through T[j], let's maintain cur[e] = s as the largest index such that T[:j] is a subsequence of S[s: e+1], (or -1 if impossible.)
    Now we want to find new, the largest indexes for T[:j+1].

    To update our knowledge as j += 1, if S[i] == T[j], then last (the largest s we have seen so far) represents a new valid window [s, i].

    In Python, we use cur and new, while in Java we use dp[j] and dp[~j] to keep track of the last two rows of our dynamic programming.

    At the end, we look at all the windows we have and choose the best.

    Complexity Analysis

    Time Complexity: O(ST)O(ST), where S, TS,T are the lengths of S, T. We have two for-loops.

    Space Complexity: O(S)O(S), the length of dp.
    """
    def doit_dp(self, S: str, T: str) -> str:
        """
        :param S:
        :param T:
        :return:
        """
        cur = [i if x == T[0] else None for i, x in enumerate(S)]
        #At time j when considering T[:j+1],
        #the smallest window [s, e] where S[e] == T[j]
        #is represented by cur[e] = s.
        for j in range(1, len(T)):
            last = None
            new = [None] * len(S)
            #Now we would like to calculate the candidate windows
            #"new" for T[:j+1].  'last' is the last window seen.
            for i, u in enumerate(S):
                if last is not None and u == T[j]:
                    new[i] = last
                if cur[i] is not None:
                    last = cur[i]
            cur = new

        #Looking at the window data cur, choose the smallest length
        #window [s, e].
        ans = (0, len(S))
        for e, s in enumerate(cur):
            if s != None and s >= 0 and e - s < ans[1] - ans[0]:
                ans = (s, e)

        return S[ans[0]: ans[1]+1] if ans[1] < len(S) else ""


    def doit_dp_2(self, S: str, T: str) -> str:
        '''
        dp[i]: for T[j], update dp[i] as last seen T[j-1]
        '''

        res = ''
        cur = -1
        while True:
            s = cur + 1
            for t in T:
                cur = S.find(t, cur + 1)
                if cur == -1:
                    return res
            cur = e = cur + 1
            for t in T[::-1]:
                cur = S.rfind(t, s, cur)
            if not res or e - cur < len(res):
                res = S[cur:e]


    """
    Approach #2: Dynamic Programming (Next Array Variation) [Accepted]
    Intuition
    
    Let's guess that the minimum window will start at S[i]. We can assume that S[i] = T[0]. Then, we should find the next occurrence of T[1] in S[i+1:], 
    say at S[j]. Then, we should find the next occurrence of T[2] in S[j+1:], and so on.
    
    Finding the next occurrence can be precomputed in linear time so that each guess becomes O(T)O(T) work.
    
    Algorithm
    
    We can precompute (for each i and letter), next[i][letter]: the index of the first occurrence of letter in S[i:], or -1 if it is not found.
    
    Then, we'll maintain a set of minimum windows for T[:j] as j increases. At the end, we'll take the best minimum window.
    """
    def doit_dp_1(self, S, T):
        N = len(S)
        nxt = [None] * N
        last = [-1] * 26
        for i in range(N-1, -1, -1):
            last[ord(S[i]) - ord('a')] = i
            nxt[i] = tuple(last)

        windows = [[i, i] for i, c in enumerate(S) if c == T[0]]
        for j in range(1, len(T)):
            letter_index = ord(T[j]) - ord('a')
            windows = [[root, nxt[i+1][letter_index]]
                       for root, i in windows
                       if 0 <= i < N-1 and nxt[i+1][letter_index] >= 0]

        if not windows:
            return ""

        i, j = min(windows, key=lambda i, j: j-i)
        return S[i: j+1]




