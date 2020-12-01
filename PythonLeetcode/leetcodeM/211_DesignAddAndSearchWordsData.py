"""
211. Design Add and Search Words Data Structure

Design a data structure that supports adding new words and finding if a string matches any previously added string.

Implement the WordDictionary class:

WordDictionary() Initializes the object.
void addWord(word) Adds word to the data structure, it can be matched later.
bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise.
word may contain dots '.' where dots can be matched with any letter.


Example:

Input
["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
Output
[null,null,null,null,false,true,true,true]

Explanation
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("bad");
wordDictionary.addWord("dad");
wordDictionary.addWord("mad");
wordDictionary.search("pad"); // return False
wordDictionary.search("bad"); // return True
wordDictionary.search(".ad"); // return True
wordDictionary.search("b.."); // return True


Constraints:

1 <= word.length <= 500
word in addWord consists lower-case English letters.
word in search consist of  '.' or lower-case English letters.
At most 50000 calls will be made to addWord and search.
"""


class WordDictionary:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._trie = {}

    def addWord(self, word: str) -> None:
        """
        Adds a word into the data structure.
        """
        self.build_trie(word)

    def search(self, word: str) -> bool:
        """
        Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter.
        """
        def dfs(i, node):

            if i == len(word):
                return '#' in node

            if word[i] in node:
                return dfs(i+1, node[word[i]])
            elif word[i] == '.':
                for c in node.keys():
                    if dfs(i+1, node[c]):
                        return True
            return False
        return dfs(0, self._trie)

    def build_trie(self, word):

        node = self._trie
        key = '#'
        for w in word:

            if w not in node:
                node[w] = {}

            node = node[w]

        if '#' not in node:
            node['#'] = {}


if __name__ == '__main__':

    obj = WordDictionary()

    obj.addWord("bad")
    obj.addWord("dad")
    obj.addWord("mad")

    obj.search("pad")
    obj.search(".ad")
    obj.search("b..")

    obj1 = WordDictionary()
    obj1.addWord('a')
    obj1.addWord('a')
    obj1.search('.')
    obj1.search('a')
    obj1.search('aa')
    obj1.search('a')
    obj1.search('.a')
    obj1.search('a.')