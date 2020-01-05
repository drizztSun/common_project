# 819. Most Common Word

# Given a paragraph and a list of banned words, return the most frequent word that is not in the list of banned words.
# It is guaranteed there is at least one word that isn't banned, and that the answer is unique.

# Words in the list of banned words are given in lowercase, and free of punctuation.  Words in the paragraph are not case sensitive.
# The answer is in lowercase.


# Example:

# Input:
# paragraph = "Bob hit a ball, the hit BALL flew far after it was hit."
# banned = ["hit"]
# Output: "ball"
# Explanation:
# "hit" occurs 3 times, but it is a banned word.
# "ball" occurs twice(and no other word does), so it is the most frequent non-banned word in the paragraph.
# Note that words in the paragraph are not case sensitive,
# that punctuation is ignored(even if adjacent to words, such as "ball,"),
# and that "hit" isn't the answer even though it occurs more because it is banned.


# Note:

# 1 <= paragraph.length <= 1000.
# 0 <= banned.length <= 100.
# 1 <= banned[i].length <= 10.
# The answer is unique, and written in lowercase(even if its occurrences in paragraph may have uppercase symbols, and even if it is a proper noun.)
# paragraph only consists of letters, spaces, or the punctuation symbols !?',
# .
# There are no hyphens or hyphenated words.
# Words only consist of letters, never apostrophes or other punctuation symbols.

from collections import Counter
import re


class MostCommonWord:

    def doit1(self, paragraph, banned):
        banset = set(banned)
        for c in ";.!?,'":
            paragraph = paragraph.replace(c, ' ')

        cnt = Counter(paragraph.lower().split())
        ans, maxv = '', 0
        for k, v in cnt.items():
            if k not in banset and v > maxv:
                maxv = v
                ans = k
        return ans

    def doit(self, paragraph, banned):
        c = Counter(re.split('[!?\',;. ]', paragraph.lower()))
        for (word, count) in c.most_common():
            if word not in banned and word != '':
                return word

    def doit(self, paragraph, banned):

        bannedset = set(banned)
        cnter = {}
        s, alpha = -1, False

        maxv, ans = -1, ''
        for i in range(len(paragraph) + 1):
            if (i == len(paragraph) or not paragraph[i].isalpha()) and alpha:
                sub = paragraph[s:i].lower()
                if sub not in banned:
                    if sub not in cnter:
                        cnter[sub] = 0
                    cnter[sub] += 1
                    if cnter[sub] > maxv:
                        maxv = cnter[sub]
                        ans = sub
                    s = -1
            elif i < len(paragraph) and paragraph[i].isalpha() and not alpha:
                alpha, s = True, i

            alpha = i < len(paragraph) and paragraph[i].isalpha()
        return ans


if __name__ == '__main__':

    res = MostCommonWord().doit(
        paragraph="Bob hit a ball, the hit BALL flew far after it was hit.", banned=["hit"])  # "ball"

    res = MostCommonWord().doit(
        paragraph="Bob. hIt, baLl", banned=["bob", "hit"])
