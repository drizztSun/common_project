"""
208. Implement Trie (Prefix Tree)

Implement a trie with insert, search, and startsWith methods.

Example:

Trie trie = new Trie();

trie.insert("apple");
trie.search("apple");   // returns true
trie.search("app");     // returns false
trie.startsWith("app"); // returns true
trie.insert("app");
trie.search("app");     // returns true
Note:

You may assume that all inputs are consist of lowercase letters a-z.
All inputs are guaranteed to be non-empty strings.
"""


class Trie:

    class node:

        def __init__(self):
            self.table = {}
            self.hasWord = False

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._root = Trie.node()

    def insert(self, word: str) -> None:
        """
        Inserts a word into the trie.
        """
        n = self._root

        for c in word:
            if c not in n.table:
                n.table[c] = Trie.node()
            n = n.table[c]
        n.hasWord = True

    def search(self, word: str) -> bool:
        """
        Returns if the word is in the trie.
        """
        n = self._root
        for c in word:
            if c not in n.table:
                return False

            n = n.table[c]
        return n.hasWord

    def startsWith(self, prefix: str) -> bool:
        """
        Returns if there is any word in the trie that starts with the given prefix.
        """
        n = self._root
        for c in prefix:
            if c not in n.table:
                return False
            n = n.table[c]

        return True