# 820. Short Encoding of Words

# Given a list of words, we may encode it by writing a reference string S and a list of indexes A.

# For example, if the list of words is ["time", "me", "bell"], we can write it as S = "time#bell#" and indexes = [0, 2, 5].

# Then for each index, we will recover the word by reading from the reference string from that index until we reach a "#" character.

# What is the length of the shortest reference string S possible that encodes the given words?

# Example:

# Input: words = ["time", "me", "bell"]
# Output: 10
# Explanation: S = "time#bell#" and indexes = [0, 2, 5].


# Note:

# 1 <= words.length <= 2000.
# 1 <= words[i].length <= 7.
# Each word has only lowercase letters.


"""
Approach #1: Store Prefixes [Accepted]
Intuition

If a word X is a suffix of Y, then it does not need to be considered, as the encoding of Y in the reference string will also encode X. For example, if "me" and "time" is in words, we can throw out "me" without changing the answer.

If a word Y does not have any other word X (in the list of words) that is a suffix of Y, then Y must be part of the reference string.

Thus, the goal is to remove words from the list such that no word is a suffix of another. The final answer would be sum(word.length + 1 for word in words).

Algorithm

Since a word only has up to 7 suffixes (as words[i].length <= 7), let's iterate over all of them. For each suffix, we'll try to remove it from our words list. For efficiency, we'll make words a set.

Complexity Analysis

Time Complexity: O(∑w[i]**2), where w[i] is the length of words[i].

Space Complexity: O(∑w[i]), the space used in storing suffixes.



Approach #2: Trie [Accepted]
Intuition

As in Approach #1, the goal is to remove words that are suffixes of another word in the list.

Algorithm

To find whether different words have the same suffix, let's put them backwards into a trie (prefix tree). For example, if we have "time" and "me", we will put "emit" and "em" into our trie.

After, the leaves of this trie (nodes with no children) represent words that have no suffix, and we will count sum(word.length + 1 for word in words).

Complexity Analysis

Time Complexity: O(∑w[i]), where w[i] is the length of words[i].

Space Complexity: O(∑w[i]), the space used by the trie.

"""


class Trie:
    class TrieNode:
        def __init__(self, data):
            self.data, self.children, self.is_terminal = data, {}, False

    def __init__(self):
        self.root = self.TrieNode(chr(0))

    def insert_word_helper(self, node: TrieNode, word):
        if not len(word):
            node.is_terminal = True
            return
        index = int(ord(word[0]) - ord('a'))
        if index not in node.children:
            node.children[index] = self.TrieNode(chr(index + ord('a')))
        self.insert_word_helper(node.children[index], word[1:])

    def insert_word(self, word):
        self.insert_word_helper(self.root, word)

    def get_words_helper(self, node, length, result):
        if not len(node.children):
            if node.is_terminal:
                result.append(length)
            return
        for index in node.children:
            self.get_words_helper(node.children[index], length + 1, result)

    def get_words(self):
        lengths = []
        self.get_words_helper(self.root, 0, lengths)
        return lengths


class ShortEncodingWords:

    # approach #1
    def doit(self, words):
        good = set(words)
        for word in words:
            for i in range(len(word)):
                good.discard(word[i:])

        return sum(len(w) + 1 for w in good)

    # approach #2
    def doit(self, words):
        words, trie = list(set(words)), Trie()
        for word in words:
            trie.insert_word(word[::-1])
        return sum([a + 1 for a in trie.get_words() if a])

    def doitxxx(self, words):
        index = [0]
        S = words[0]
        lastword = words[0]
        lastindex = len(lastword)
        for i in range(1, len(words)):
            if lastword.endswith(words[i]):
                index.append(lastindex - len(words[i]))
                continue

            S = S + '#' + words[i]
            lastword = words[i]
            lastindex = len(S)
        else:
            S += '#'

        return len(S)


if __name__ == '__main__':

    res = ShortEncodingWords().doit(words=["time", "me", "bell"])

    res = ShortEncodingWords().doit(words=["me", "time"])

    pass
