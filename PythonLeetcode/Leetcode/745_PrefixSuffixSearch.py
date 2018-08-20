    # 745. Prefix and Suffix Search

# Given many words, words[i] has weight i.

# Design a class WordFilter that supports one function, WordFilter.f(String prefix, String suffix). 
# It will return the word with given prefix and suffix with maximum weight. If no word exists, return -1.
 
# Examples:
# Input:
# WordFilter(["apple"])
# WordFilter.f("a", "e") // returns 0
# WordFilter.f("b", "") // returns -1


# Note:
# words has length in range [1, 15000].
# For each test case, up to words.length queries WordFilter.f may be made.
# words[i] has length in range [1, 10].
# prefix, suffix have lengths in range [0, 10].
# words[i] and prefix, suffix queries consist of lowercase letters only.


import collections


class Node:

    def __init__(self):
        """
        """
        self.maxWeight_ = []
        self.table_ = collections.defaultdict(Node)


# <TLE>
class Solution:

    def __init__(self, words):
        """
        :type words: List[str]
        """
        self.prefix_, self.suffix_ = Node(), Node()
        self.words_ = []

        for c in words:
            self.words_.append(c)
            self.insert(c, len(self.words_) - 1)

    def insert(self, word, w):
        """
        :param word:
        :return:
        """
        node = self.prefix_
        node.maxWeight_.append(w)
        for i in range(len(word)):
            node.table_[word[i]].maxWeight_.append(w)
            node = node.table_[word[i]]

        node = self.suffix_
        node.maxWeight_.append(w)
        for i in reversed(range(len(word))):
            node.table_[word[i]].maxWeight_.append(w)
            node = node.table_[word[i]]

    def f(self, prefix, suffix):
        """
        :type prefix: str
        :type suffix: str
        :rtype: int
        """
        node = self.prefix_
        prefixw = node.maxWeight_
        for i in range(len(prefix)):
            if prefix[i] not in node.table_:
                prefixw = []
                break

            node = node.table_[prefix[i]]
            prefixw = node.maxWeight_

        node = self.suffix_
        suffixw = node = self.suffix_
        for i in reversed(range(len(suffix))):
            if suffix[i] not in node.table_:
                suffixw = []
                break

            node = node.table_[suffix[i]]
            suffixw = node.maxWeight_

        combo = list(set(prefixw) & set(suffixw))
        return -1 if not combo else combo[-1]


# Store all the words corresponding to its prefixes and suffixes. For example, for two words bat and bar,
# the prefixes and suffixes dictionary will look as such:

# prefixes
# {
#  '': {'bat', 'bar'},
#  'b': {'bat', 'bar'},
#  'ba': {'bat', 'bar'},
#  'bar': {'bar'},
#  'bat': {'bat'},
# }

# suffixes
# {
#  't': {'bat'},
#  'at': {'bat'},
#  'bat': {'bat'},
#  'r': {'bar'},
#  'ar': {'bar'},
#  'bar': {'bar'},
# }
# f('b', 'at') => set intersection of {'bat', 'bar'} and {'bat'} => 'bat'.


class WordFilter:

    def __init__(self, words):
        """
        :type words: List[str]
        """
        self.prefix_ = collections.defaultdict(set)
        self.suffix_ = collections.defaultdict(set)
        self.weight_ = {}

        for index, word in enumerate(words):

            for i in range(len(word) + 1):
                self.prefix_[word[:i]].add(word)

            for i in reversed(range(len(word) + 1)):
                self.suffix_[word[i:]].add(word)

            self.weight_[word] = index

    def f(self, prefix, suffix):
        """
        :type prefix: str
        :type suffix: str
        :rtype: int
        """
        weight = -1
        for word in self.prefix_[prefix] & self.suffix_[suffix]:
            weight = max(weight, self.weight_[word])

        return weight





# Method 2
# Directly save the prefix and suffix combinations for a word, where the value is the weight. 
# For a word such as 'bat', store all the prefix + suffix combinations in a dictionary, delimited by a non-alphabet character such as '.'. 
# The delimiter is important so as to distinguish between prefix/suffix pairs that would have been concatenated 
# to give the same result if without - ab + c and a + bc would both give abc if there wasn’t a delimiter present.

# {
#  '.': 0,
#  '.t': 0,
#  '.at': 0,
#  '.bat': 0,
#  'b.': 0,
#  'b.t': 0,
#  'b.at': 0,
#  'b.bat': 0,
#  'ba.': 0,
#  'ba.t': 0,
#  'ba.at': 0,
#  'ba.bat': 0,
#  'bat.': 0,
#  'bat.t': 0,
#  'bat.at': 0,
#  'bat.bat': 0,
# }
# Later occurrences of the prefix + suffix combi will have its weight overwritten,
# so we can simply look up the dictionary and return the answer.

class WordFilter(object):

    def __init__(self, words):
        """
        :type words: List[str]
        """
        self.inputs = {}
        for index, word in enumerate(words):
            prefix = ''
            for char in [''] + list(word):
                prefix += char
                suffix = ''
                for char in [''] + list(word[::-1]):
                    suffix += char
                    self.inputs[prefix + '.' + suffix[::-1]] = index

    def f(self, prefix, suffix):
        """
        :type prefix: str
        :type suffix: str
        :rtype: int
        """
        return self.inputs.get(prefix + '.' + suffix, -1)




if __name__ == "__main__":

    obj = WordFilter(["apple"])

    res = obj.f('a', 'e')
    res = obj.f('b', '')

    caller = ["WordFilter", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f"]


    inputs_rv = [[["pop"]], ["", ""], ["", "p"], ["", "op"], ["", "pop"], ["p", ""], ["p", "p"], ["p", "op"], ["p", "pop"], ["po", ""], ["po", "p"], ["po", "op"], ["po", "pop"], ["pop", ""], ["pop", "p"], ["pop", "op"], ["pop", "pop"],
     ["", ""], ["", "p"], ["", "gp"], ["", "pgp"], ["p", ""], ["p", "p"], ["p", "gp"], ["p", "pgp"], ["pg", ""],
     ["pg", "p"], ["pg", "gp"], ["pg", "pgp"], ["pgp", ""], ["pgp", "p"], ["pgp", "gp"], ["pgp", "pgp"]]

    inputs = inputs_rv[0]
    obj = WordFilter(inputs[0])

    inputs = [[["cabaabaaaa", "ccbcababac", "bacaabccba", "bcbbcbacaa", "abcaccbcaa", "accabaccaa", "cabcbbbcca", "ababccabcb",
       "caccbbcbab", "bccbacbcba"]], ["bccbacbcba", "a"], ["ab", "abcaccbcaa"], ["a", "aa"], ["cabaaba", "abaaaa"],
     ["cacc", "accbbcbab"], ["ccbcab", "bac"], ["bac", "cba"], ["ac", "accabaccaa"], ["bcbb", "aa"],
     ["ccbca", "cbcababac"]]





    pass







