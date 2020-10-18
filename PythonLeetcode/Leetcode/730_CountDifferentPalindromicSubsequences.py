"""
730. Count Different Palindromic Subsequences

# Given a string S, find the number of different non-empty palindromic subsequences in S, and return that number modulo 10^9 + 7.

# A subsequence of a string S is obtained by deleting 0 or more characters from S.

# A sequence is palindromic if it is equal to the sequence reversed.

# Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some i for which A_i != B_i.

# Example 1:
# Input:
# S = 'bccb'
# Output: 6
# Explanation:
# The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
# Note that 'bcb' is counted only once, even though it occurs twice.

# Example 2:
# Input:
# S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
# Output: 104860361
# Explanation:
# There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 10^9 + 7.

# Note:

# The length of S will be in the range [1, 1000].
# Each character S[i] will be in the set {'a', 'b', 'c', 'd'}.
"""


class CountPalindromicSubsequences:

    """
    # I started out with only the DFS part, got TLE, then designed the DP part cache and passed.

    # The computations are done in DFS(start, end) in which I computed the answer for the string S[start, end].
    # cache is only to save the results of the computations in order to avoid repetitions.

    # In DFS(start, end), for instance, for the letter 'a',
    # I compute the number of palindromes that start and end with 'a' in the following way:

    # First of all, I compute when 'a' appears first (index i) and last (index j) in the segment I am considering.
    # Then it breaks down into two cases:

    # If i == j. There is only one 'a' in the segment. So the answer is 1.

    # If i != j. The possible palindromes are 'a', 'aa', and 'a*a' where '*' stands for any palindromes contained in S[i+1:j].
    # The answer would be DFS(i+1,j) + 2. Since I want to avoid repetitive computation, I write cache(i+1,j) + 2 instead.

    # The worst case time complexity is O(n^2). The best case time complexity is O(n).

    # Btw, to make this algorithm even faster, one could set check to be a 2D list instead of a dictionary,
    # but that would occupy more space.
    """
    def doit_dp_dfs(self, S):
        """
        :type S: str
        :rtype: int
        """
        dp = {}

        # return the amount of distinct palindromes of S[start:end]
        def search(start, end):

            if (start, end) in dp:
                return dp[(start, end)]

            # if less then two, 'bb', 'bc' are two elements
            if end <= start + 2:
                return end - start

            count = 0
            for c in ['a', 'b', 'c', 'd']:

                # s, e = S.index(c, start, end), S.rindex(c, start, end)
                s, e = S.find(c, start, end), S.rfind(c, start, end)

                if s == -1 or e == -1:
                    continue

                # could be 'a' 'aa' and searched 'a*a'
                count += search(s+1, e) + 2 if s != e else 1

            dp[(start, end)] = count % 1000000007

            return dp[(start, end)]
            
        return search(0, len(S))

    def doit_dfs_dp(self, S: str) -> int:
        from functools import lru_cache
        mod = 10 ** 9 + 7
        chars = set(S)
        next = {key: [len(S)] * len(S) for key in chars}
        prev = {key: [-1] * len(S) for key in chars}

        for key in chars:
            prev_position = -1
            for i in range(len(S)):
                if S[i] == key:
                    prev_position = i
                prev[key][i] = prev_position

            next_position = len(S)
            for i in range(len(S) - 1, -1, -1):
                if S[i] == key:
                    next_position = i
                next[key][i] = next_position

        @lru_cache(None)
        def search(i, j):
            if j < i:
                return 0
            # count number of palindromic sequence in S[i: j + 1]
            res = 0
            for key in chars:
                if j < next[key][i]:
                    continue

                if next[key][i] == prev[key][j]:
                    res += 1
                    continue

                # next[key][i] < prev[key][j]
                res += 2 + search(next[key][i] + 1, prev[key][j] - 1)
            return res % mod

        return search(0, len(S) - 1) % mod

    """
    Approach #1 Dynamic Programming (using 3D array) [Accepted]
    Intuition and Algorithm
    
    Let dp[x][i][j] be the answer for the substring S[i...j] where S[i] == S[j] == 'a'+x. Note that since we only have 4 characters a, b, c, d, thus 0 <= x < 4. The DP formula goes as follows:
    
    If S[i] != 'a'+x, then dp[x][i][j] = dp[x][i+1][j], note that here we leave the first character S[i] in the window out due to our definition of dp[x][i][j].
    
    If S[j] != 'a'+x, then dp[x][i][j] = dp[x][i][j-1], leaving the last character S[j] out.
    
    If S[i] == S[j] == 'a'+x, then dp[x][i][j] = 2 + dp[0][i+1][j-1] + dp[1][i+1][j-1] + dp[2][i+1][j-1] + dp[3][i+1][j-1]. 
    When the first and last characters are the same, we need to count all the distinct palindromes (for each of a,b,c,d) within the sub-window S[i+1][j-1] plus the 2 palindromes contributed by the first and last characters.
    
    Let n be the length of the input string S, The final answer would be dp[0][0][n-1] + dp[1][0][n-1] + dp[2][0][n-1] + dp[3][0][n-1] mod 1000000007.


    """
    def doit_dp_2(self, S):
        n = len(S)
        mod = 1000000007
        dp = [[[0 for _ in range(n)] for _ in range(n)] for _ in range(4)]

        for i in range(n - 1, -1, -1):
            for j in range(i, n):
                for k in range(4):
                    c = chr(ord('a') + k)
                    if j == i:
                        if S[i] == c:
                            dp[k][i][j] = 1
                        else:
                            dp[k][i][j] = 0
                    else:  # j > i
                        if S[i] != c:
                            dp[k][i][j] = dp[k][i + 1][j]
                        elif S[j] != c:
                            dp[k][i][j] = dp[k][i][j - 1]
                        else:  # S[i] == S[j] == c
                            if j == i + 1:
                                dp[k][i][j] = 2  # "aa" : {"a", "aa"}
                            else:  # length is > 2
                                dp[k][i][j] = 2
                                for m in range(4):  # count each one within subwindows [i+1][j-1]
                                    dp[k][i][j] += dp[m][i + 1][j - 1]
                                    dp[k][i][j] %= mod

        ans = 0
        for k in range(4):
            ans += dp[k][0][n - 1]
            ans %= mod

        return ans


    """
    Approach #2: Dynamic Programming (using 2D array) [Accepted]
    Intuition
    
    Almost every palindrome is going to take one of these four forms: a_a, b_b, c_c, or d_d, where _ represents a palindrome of zero or more characters. (The only other palindromes are a, b, c, d, and the empty string.)
    
    Let's try to count palindromes of the form a_a - the other types are similar. Evidently, we should take the first and last a, 
    then count all the palindromes that can be formed in between, as this provides us strictly more possibilities for _ to be a palindrome. This reveals an optimal substructure that is ideal for dynamic programming.
    
    Algorithm
    
    Let dp(i, j) be the number of palindromes (including the palindrome '') in the string T = S[i], S[i+1], ..., S[j]. To count palindromes in T of the form a_a, 
    we will need to know the first and last occurrence of 'a' in this string. This can be done by a precomputed dp: next[i][0] will be the next occurrence of 'a' in S[i:], next[i][1] will be the next occurrence of 'b' in S[i:], and so on.
    
    Also, we will need to know the number of unique letters in T to count the single letter palindromes. We can use the information from next to deduce it: if next[i][0] is in the interval [i, j], then 'a' occurs in T, and so on.
    
    As many states dp(i, j) do not need to be computed, the most natural approach is a top-down variation of dynamic programming.
    """
    def doit_dp_1(self, S):
        N = len(S)
        A = [ord(c) - ord('a') for c in S]
        prv = [None] * N
        nxt = [None] * N

        last = [None] * 4
        for i in xrange(N):
            last[A[i]] = i
            prv[i] = tuple(last)

        last = [None] * 4
        for i in range(N-1, -1, -1):
            last[A[i]] = i
            nxt[i] = tuple(last)

        MOD = 10**9 + 7
        memo = [[None] * N for _ in range(N)]
        def dp(i, j):
            if memo[i][j] is not None:
                return memo[i][j]
            ans = 1
            if i <= j:
                for x in range(4):
                    i0 = nxt[i][x]
                    j0 = prv[j][x]
                    if i <= i0 <= j:
                        ans += 1
                    if None < i0 < j0:
                        ans += dp(i0+1, j0-1)
            ans %= MOD
            memo[i][j] = ans
            return ans

        return dp(0, N-1) - 1


    def doit1(self, S):
        """
        :type S: str
        :rtype: int
        """
        result = set()
        d = set()
        
        def search(content, prefix, suffix,  result):

            if content in d:
                return 
            if not content:
                return 

            for i in set(content):
                s, e = content.find(i), content.rfind(i)
                result.add( prefix + i + suffix)
                if s != e:
                    result.add( prefix + i + i + suffix)
                    search(content[s+1: e], prefix+i, i+suffix, result)
            d.add(content)
            return 
                    
        search(S, '', '', result)
        return len(result)
        

if __name__ == "__main__":

    res = CountPalindromicSubsequences().doit_dp_dfs('bccb')

    #res = CountPalindromicSubsequences().doit_dp_dfs('baccdb')

    #res = CountPalindromicSubsequences().doit_dp_dfs('abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba')