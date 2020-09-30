"""
451. Sort Characters By Frequency

Given a string, sort it in decreasing order based on the frequency of characters.

Example 1:

Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
Example 2:

Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.
Example 3:

Input:
"Aabb"

Output:
"bbAa"

Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
"""


class FrequencySort:

    def doit(self, s: str) -> str:
        from collections import Counter
        return ''.join(s[0]*s[1] for s in sorted(Counter(s).items(), key=lambda x: -x[1]))

    def doit(self, s):
        """
        :type s: str
        :rtype: str
        """
        alphabet = {}
        for c in s:
            alphabet[c] = alphabet.get(c, 0) + 1

        data = []
        for c in alphabet.keys():
            data.append((alphabet[c], c))

        data.sort(key=lambda x: x[0], reverse=1)

        res = ''
        for c in data:
            res += c[1] * c[0]

        return res