# 1032. Stream of Characters

# Implement the StreamChecker class as follows:

# StreamChecker(words): Constructor, init the data structure with the given words.
# query(letter): returns true if and only if for some k >= 1, the last k characters queried (in order from oldest to newest, including this letter just queried) spell one of the words in the given list.


# Example:

# StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // init the dictionary.
# streamChecker.query('a');          // return false
# streamChecker.query('b');          // return false
# streamChecker.query('c');          // return false
# streamChecker.query('d');          // return true, because 'cd' is in the wordlist
# streamChecker.query('e');          // return false
# streamChecker.query('f');          // return true, because 'f' is in the wordlist
# streamChecker.query('g');          // return false
# streamChecker.query('h');          // return false
# streamChecker.query('i');          // return false
# streamChecker.query('j');          // return false
# streamChecker.query('k');          // return false
# streamChecker.query('l');          // return true, because 'kl' is in the wordlist


# Note:

# 1 <= words.length <= 2000
# 1 <= words[i].length <= 2000
# Words will only consist of lowercase English letters.
# Queries will only consist of lowercase English letters.
# The number of queries is at most 40000.

from collections import deque


class TNode:
    def __init__(self):
        self.d, self.trie = False, {}


class StreamChecker:
    def __init__(self, words):
        self.stream = deque([])
        self.max_length = max(map(len, words))
        self.root = TNode()

        for word in words:
            cur = self.root
            for i in range(len(word) - 1, -1, -1):
                if word[i] not in cur.trie:
                    cur.trie[word[i]] = TNode()
                cur = cur.trie[word[i]]
            cur.d = True

    def query(self, letter):
        self.stream.appendleft(letter)
        if len(self.stream) > self.max_length:
            self.stream.pop()

        n = self.root
        for l in self.stream:
            if l not in n.trie:
                return False
            n = n.trie[l]
            if n.d:
                return True

        return False


# Your StreamChecker object will be instantiated and called as such:
# obj = StreamChecker(words)
# param_1 = obj.query(letter)

if __name__ == "__main__":

    obj = StreamChecker(["cd", "f", "kl"])

    for s in "abcdefghijkl":

        print(obj.query(s))

    pass

