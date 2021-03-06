# 824. Goat Latin

# A sentence S is given, composed of words separated by spaces. Each word consists of lowercase and uppercase letters only.

# We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.)

# The rules of Goat Latin are as follows:

# If a word begins with a vowel (a, e, i, o, or u), append "ma" to the end of the word.
# For example, the word 'apple' becomes 'applema'.

# If a word begins with a consonant (i.e. not a vowel), remove the first letter and append it to the end, then add "ma".
# For example, the word "goat" becomes "oatgma".

# Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
# For example, the first word gets "a" added to the end, the second word gets "aa" added to the end and so on.
# Return the final sentence representing the conversion from S to Goat Latin.


# Example 1:

# Input: "I speak Goat Latin"
# Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
# Example 2:

# Input: "The quick brown fox jumped over the lazy dog"
# Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"


# Notes:

# S contains only uppercase, lowercase and spaces. Exactly one space between each word.
# 1 <= S.length <= 150.


"""
Approach #1: String [Accepted]
Intuition

We apply the steps given in the problem in a straightforward manner. The difficulty lies in the implementation.

Algorithm

For each word in the sentence split, if it is a vowel we consider the word, otherwise we consider the rotation of the word (either word[1:] + word[:1] in Python, otherwise word.substring(1) + word.substring(0, 1) in Java).

Afterwards, we add "ma", the desired number of "a"'s, and a space character.

Complexity Analysis

Time Complexity: O(N ** 2), where NN is the length of S. This represents the complexity of rotating the word and adding extra "a" characters.

Space Complexity: O(N ** 2), the space added to the answer by adding extra "a" characters.

"""


class ToGoatLatin:

    def doit(self, S):
        def convert(word):
            if word[0] not in 'aeiouAEIOU':
                word = word[1:] + word[:1]
            return word + 'ma'

        return " ".join(convert(word) + 'a' * i
                        for i, word in enumerate(S.split(), 1))

    def doit(self, S):
        words = S.split()
        ans = []
        for i, w in enumerate(words):
            if w[0].lower() in ('a', 'e', 'i', 'o', 'u'):
                w += 'ma'
            else:
                w = w[1:] + w[0] + 'ma'

            w += 'a' * (i + 1)

            ans.append(w)

        return ' '.join(ans)


if __name__ == '__main__':

    # "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
    res = ToGoatLatin().doit("I speak Goat Latin")

    # "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
    res = ToGoatLatin().doit("The quick brown fox jumped over the lazy dog")

    # "Eachmaa ordwmaaa onsistscmaaaa ofmaaaaa owercaselmaaaaaa andmaaaaaaa uppercasemaaaaaaaa etterslmaaaaaaaaa onlymaaaaaaaaaa"
    res = ToGoatLatin().doit("Each word consists of lowercase and uppercase letters only")

    pass
