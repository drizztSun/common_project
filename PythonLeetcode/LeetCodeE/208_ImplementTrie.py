
import os



# Implement a trie with insert, search, and startsWith methods.
# Note:
# You may assume that all inputs are consist of lowercase letters a-z

class TrieNode(object):
    def __init__(self):
        self.frequency = 0
        self.nodes = [None for _ in range(26)]

class Trie(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._root = TrieNode()
        

    def insert(self, word):
        """
        Inserts a word into the trie.
        :type word: str
        :rtype: void
        """
        node, aNum = self._root, ord('a')
        for ch in word:
            num = ord(ch) - aNum
            if not node.nodes[num]:
                node.nodes[num] = TrieNode()

            node = node.nodes[num]
        node.frequency += 1

    def search(self, word):
        """
        Returns if the word is in the trie.
        :type word: str
        :rtype: bool
        """
        node, aNum = self._root, ord('a')
        for i in range(len(word)):
            num = ord(word[i]) - aNum
            if not node.nodes[num]:
                return False
            node = node.nodes[num]

        return False if not node else node.frequency > 0

    def startsWith(self, prefix):
        """
        Returns if there is any word in the trie that starts with the given prefix.
        :type prefix: str
        :rtype: bool
        """
        node, aNum = self._root, ord('a')
        for ch in prefix:
            num = ord(ch) - aNum
            if not node.nodes[num]:
                return False
            node = node.nodes[num]
        return True



# leetcode 211. Add and Search Word - Data structure design
# Design a data structure that supports the following two operations:
# search(word) can search a literal word or a regular expression string
# containing only letters a-z or .. A . means it can represent any one letter.


class WordDictionary(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._root = TrieNode()

    def addWord(self, word):
        """
        Adds a word into the data structure.
        :type word: str
        :rtype: void
        """
        node, aNum = self._root, ord('a')
        for ch in word:
            num = ord(ch) - aNum
            if not node.nodes[num]:
                node.nodes[num] = TrieNode()

            node = node.nodes[num]
        node.frequency += 1
        

    def search(self, word):
        """
        Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter.
        :type word: str
        :rtype: bool
        """
        def subSearch(word, s, node):
            if not node:
                return False

            if s == len(word):
                return node.frequency > 0

            if word[s] == '.':
                for item in node.nodes:
                    if item and subSearch(word, s+1, item):
                        return True
                return False
            else:
                return subSearch(word, s+1, node.nodes[ord(word[s])-ord('a')])
                        


        return subSearch(word, 0, self._root)




class WordDictionary2(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.word_dict = collections.defaultdict(list)
        
        

    def addWord(self, word):
        """
        Adds a word into the data structure.
        :type word: str
        :rtype: void
        """
        if word:
            self.word_dict[len(word)].append(word)
        

    def search(self, word):
        """
        Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter.
        :type word: str
        :rtype: bool
        """
        if not word:
            return False
        if '.' not in word:
            return word in self.word_dict[len(word)]
        for v in self.word_dict[len(word)]:
            for i, ch in enumerate(word):
                if ch != v[i] and ch != '.':
                    break
            else:
                return True
        return False


if __name__=="__main__":



    obj3 = Trie()
    res = obj3.search('a')


    obj2 = Trie()
    obj2.insert("word")
    param_2 = obj2.search("word")
    param_3 = obj2.startsWith("wor")


    obj1 = Trie()
    obj1.insert("ab")
    param_2 = obj1.search("a")
    param_3 = obj1.startsWith("a")


    obj = Trie()
    res = obj.insert('abc')
    res = obj.search('abc')

    res = obj.search('ab')
    res = obj.insert('ab')

    res = obj.search('ab')
    res = obj.insert('ab')    
    res = obj.search('ab')



    obj = WordDictionary()
    res = obj.addWord("bad")
    res = obj.addWord("dad")
    res = obj.addWord("mad")
    res = obj.search("pad") #-> false
    res = obj.search("bad") #-> true
    res = obj.search(".ad") #-> true
    res = obj.search("b..") #-> true


    pass