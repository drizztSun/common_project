"""
1297. Maximum Number of Occurrences of a Substring


Given a string s, return the maximum number of ocurrences of any substring under the following rules:

The number of unique characters in the substring must be less than or equal to maxLetters.
The substring size must be between minSize and maxSize inclusive.
 

Example 1:

Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
Output: 2
Explanation: Substring "aab" has 2 ocurrences in the original string.
It satisfies the conditions, 2 unique letters and size 3 (between minSize and maxSize).
Example 2:

Input: s = "aaaa", maxLetters = 1, minSize = 3, maxSize = 3
Output: 2
Explanation: Substring "aaa" occur 2 times in the string. It can overlap.
Example 3:

Input: s = "aabcabcab", maxLetters = 2, minSize = 2, maxSize = 3
Output: 3
Example 4:

Input: s = "abcde", maxLetters = 2, minSize = 3, maxSize = 3
Output: 0
 

Constraints:

1 <= s.length <= 10^5
1 <= maxLetters <= 26
1 <= minSize <= maxSize <= min(26, s.length)
s only contains lowercase English letters.

"""


class MaxFreq:


    """
        The following algorithm is also O(n, minSize) in time, but uses a trie to track substrings.

        (Update: the input limit is minSize <= min(26, s.length), so people are right, O(n * minSize) ~ O(26 n) ~ O(n).)

        Each item in the data array is [ponter_to_a_trie_node, visited_letters_set].

        Imagine starting from each letter of s to scan the substrings simultaneously, at the same speed. If two substrings are same, then their ponter_to_a_trie_node will point to the same trie node.
    """
    def doit_(self, s: str, maxLetters: int, minSize: int, maxSize: int) -> int:
        import collections
        T = lambda: collections.defaultdict(T)
        trie = T()
        data = [[trie, set()] for _ in range(len(s))]
        res = 0

        for l in range(minSize):
            
            for start in range(len(s)):
                index = start + l
                if index == len(s):
                    break

                this_data = data[start]
                c = s[index]
                this_data[1].add(c)
                
                if len(this_data[1]) <= maxLetters and l == minSize - 1:
                    this_data[0][c].setdefault("#", 0)
                    this_data[0][c]["#"] += 1
                    res = max(res, this_data[0][c]["#"])
                
                this_data[0] = this_data[0][c]
        return res

    def doit(self, s: str, maxLetters: int, minSize: int, maxSize: int) -> int:
        from collections import Counter
        return max([j for i, j in Counter(s[i:i+minSize] for i in range(len(s) - minSize + 1)).items() if len(set(i)) <= maxLetters] or [0])

        