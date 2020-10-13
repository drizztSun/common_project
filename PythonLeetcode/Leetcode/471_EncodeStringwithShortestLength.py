"""
471. Encode String with Shortest Length

Given a non-empty string, encode the string such that its encoded length is the shortest.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.

Note:

k will be a positive integer and encoded string will not be empty or have extra space.
You may assume that the input string contains only lowercase English letters. The string's length is at most 160.
If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them is fine.


Example 1:

Input: "aaa"
Output: "aaa"
Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.


Example 2:

Input: "aaaaa"
Output: "5[a]"
Explanation: "5[a]" is shorter than "aaaaa" by 1 character.


Example 3:

Input: "aaaaaaaaaa"
Output: "10[a]"
Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".


Example 4:

Input: "aabcaabcd"
Output: "2[aabc]d"
Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".


Example 5:

Input: "abbbabbbcabbbabbbc"
Output: "2[2[abbb]c]"
Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".

"""


class Encode:

    def doit_dp(self, s:str):

        dp = [['' for _ in range(len(s))] for _ in range(len(s))]

        n = len(s)
        for step in range(1, n + 1):
            for i in range(n - step + 1):
                j = i + step - 1
                dp[i][j] = s[i:i + step + 1]
                for k in range(i, j):
                    left = dp[i][k]
                    right = dp[k + 1][j]
                    if len(left) + len(right) < len(dp[i][j]):
                        dp[i][j] = left + right

                t = s[i : j + 1]
                replace = ''
                pos = (t + t).find(t, 1)
                if pos >= len(t):
                    replace = t
                else:
                    replace = str(len(t) // pos) + '[' + dp[i][i + pos - 1] + ']'
                if len(replace) < len(dp[i][j]):
                    dp[i][j] = replace

        return dp[0][n - 1]

    """
    Options 1: DFS with Memoization
    Since we need to find the shortest length encoding, we will start with substring of length 1..n/2
    For each such substring, we will try to find, how many continuous repeatitions of that substring is present in the original string
    For cnt = 1 ..X (total number of repetations e.g. aaaa => X = 4), we will take the cnt[substring] + DFS (Remaining string)
    we will pick the minimum length encoded value among all such variations
    Complexity = o(n) for length iteration, o(n) for cnt iterations, and O(n) to fill up the cache
    """
    def doit_dfs(self, s: str) -> str:

        def get_repeat_count(pattern, s):
            n = len(pattern)
            i, cnt = 0, 0
            while i < len(s) and s[i:i+n] == pattern:
                cnt += 1
                i += n
            return cnt

        def dfs(s, memo):
            if len(s) < 5:
                return s

            if s in memo:
                return memo[s]

            encoding_str = s
            for i in range(len(s)//2, 0, -1):
                pattern = s[:i]

                # No point trying this pattern as we already have a shorter encoded string
                # 3 is for 'num' '[' and ']'
                if len(pattern) + 3 > len(encoding_str):
                    continue

                cnt = get_repeat_count(pattern, s)

                for k in range(cnt, 0, -1):
                    candidate = (pattern if k == 1 else (str(k) + '[' + dfs(pattern, memo) + ']')) + dfs(s[len(pattern)*k:], memo)
                    if len(candidate) < len(encoding_str):
                        encoding_str = candidate
            memo[s] = encoding_str
            return encoding_str

        if not s:
            return s

        return dfs(s, {})

    def doit_dfs_1(self, s: str) -> str:
        if not s:
            return ""

        encode_map = {}

        def getRepeat(s1, s2):
            if len(s1) > len(s2):
                return 0

            l = len(s1)
            i = 0
            cnt = 1
            while i + l <= len(s2) and s2[i:i + l] == s1:
                cnt += 1
                i += l
            return cnt

        def dfs(s, encode_map):
            if not s:
                return ""

            if s in encode_map:
                return encode_map[s]

            sol = s
            for i in range(len(s)):
                cnt = getRepeat(s[:i + 1], s[i + 1:])
                for k in range(1, cnt + 1):
                    j = (i + 1) * k
                    encode_first = dfs(s[:i + 1], encode_map)
                    tmp_first = str(k) + "[" + encode_first + "]"
                    if len(tmp_first) >= j:
                        tmp_first = s[:j]
                    tmp_second = dfs(s[j:], encode_map)
                    tmp = tmp_first + tmp_second
                    if len(tmp) < len(sol):
                        sol = tmp
            encode_map[s] = sol
            return sol

        return dfs(s, encode_map)


if __name__ == '__main__':

    Encode().doit_dfs("aaaaa")