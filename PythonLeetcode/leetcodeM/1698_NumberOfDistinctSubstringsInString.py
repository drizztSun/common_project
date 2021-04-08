"""
1698. Number of Distinct Substrings in a String


Given a string s, return the number of distinct substrings of s.

A substring of a string is obtained by deleting any number of characters (possibly zero) from the front of the string and any number (possibly zero) from the back of the string.



Example 1:

Input: s = "aabbaba"
Output: 21
Explanation: The set of distinct strings is ["a","b","aa","bb","ab","ba","aab","abb","bab","bba","aba","aabb","abba","bbab","baba","aabba","abbab","bbaba","aabbab","abbaba","aabbaba"]
Example 2:

Input: s = "abcdefg"
Output: 28


Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.


Follow up: Can you solve this problem in O(n) time complexity?

"""


class CountDistinct:

    def doit_rollinghash(self, s: str) -> int:

        ans = 1
        hmod, base = 10 ** 9 + 7, 26
        power = 1
        hashbase = 0

        for L in range(1, len(s)):

            power = (power * base) % hmod

            hashbase = (hashbase * base + ord(s[L - 1]) - ord('a')) % hmod

            buf = set([hashbase])
            hashcode = hashbase

            for j in range(L, len(s)):
                hashcode = (hashcode * base + ord(s[j]) - ord('a')) % hmod
                hashcode = (hashcode - power * (ord(s[j - L]) - ord('a')) % hmod + hmod) % hmod

                buf.add(hashcode)

            ans += len(buf)

        return ans

    def build_lcp(self, s, sa):
        """
        Kasai algorithm to build LCP
        s: string
        sa: suffix array
        rank: inverse suffix array

        k: number of common prefixes between suffixes
        """
        n = len(sa)
        rank = [0] * n
        for i in range(n):
            rank[sa[i]] = i

        k = 0
        lcp = [0] * n
        for i in range(n):
            if rank[i] == n - 1:
                k = 0
                continue
            j = sa[rank[i] + 1]
            while i + k < n and j + k < n and s[i + k] == s[j + k]:
                k += 1
            lcp[rank[i]] = k
            k = max(k - 1, 0)
        return lcp

    def sort_bucket(self, s, buckets, order):
        d = defaultdict(list)
        for bucket in buckets:
            key = s[bucket : bucket + order]
            d[key].append(bucket)

        result = []
        for k, v in sorted(d.items()):
            if len(v) > 1:
                result.extend(self.sort_bucket(s, v, order << 1))  # or `order * 2`
            else:
                result.append(v[0])

        return result

    def suffix_array_manber_myers(self, s):
        return self.sort_bucket(s, (range(len(s))), 1)

    def countDistinct(self, s: str) -> int:
        """
        Example:
        -----
        String: azaza
        -----
        Total number of substrings: n(n + 1) / 2
        -------------------
        a az aza azaz azaza
        z za zaz zaza
        a az aza
        z za
        z
        --------------------
        15
        """
        sa = self.suffix_array_manber_myers(s)
        lcp = self.build_lcp(s, sa)
        n = len(s)
        return ((n * (n + 1)) // 2) - sum(lcp)