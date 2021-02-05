"""
676. Implement Magic Dictionary


Design a data structure that is initialized with a list of different words. Provided a string, you should determine if you can change exactly one character in this string to match any word in the data structure.

Implement the MagicDictionary class:

MagicDictionary() Initializes the object.
void buildDict(String[] dictionary) Sets the data structure with an array of distinct strings dictionary.
bool search(String searchWord) Returns true if you can change exactly one character in searchWord to match any string in the data structure, otherwise returns false.


Example 1:

Input
["MagicDictionary", "buildDict", "search", "search", "search", "search"]
[[], [["hello", "leetcode"]], ["hello"], ["hhllo"], ["hell"], ["leetcoded"]]
Output
[null, null, false, true, false, false]

Explanation
MagicDictionary magicDictionary = new MagicDictionary();
magicDictionary.buildDict(["hello", "leetcode"]);
magicDictionary.search("hello"); // return False
magicDictionary.search("hhllo"); // We can change the second 'h' to 'e' to match "hello" so we return True
magicDictionary.search("hell"); // return False
magicDictionary.search("leetcoded"); // return False


Constraints:

1 <= dictionary.length <= 100
1 <= dictionary[i].length <= 100
dictionary[i] consists of only lower-case English letters.
All the strings in dictionary are distinct.
1 <= searchWord.length <= 100
searchWord consists of only lower-case English letters.
buildDict will be called only once before search.
At most 100 calls will be made to search.
Accepted


"""


"""
Approach #1: Brute Force with Bucket-By-Length [Accepted]
Intuition and Algorithm

Call two strings neighbors if exactly one character can be changed in one to make the strings equal (ie. their hamming distance is 1.)

Strings can only be neighbors if their lengths are equal. When searching a new word, let's check only the words that are the same length.

Complexity Analysis

Time Complexity: O(S)O(S) to build and O(NK)O(NK) to search, where NN is the number of words in our magic dictionary, SS is the total number of letters in it, and KK is the length of the search word.

Space Complexity: O(S)O(S), the space used by buckets.

"""
from collections import defaultdict


class MagicDictionary(object):
    def __init__(self):
        self.buckets = defaultdict(list)

    def buildDict(self, words):
        for word in words:
            self.buckets[len(word)].append(word)

    def search(self, word):
        return any(sum(a!=b for a,b in zip(word, candidate)) == 1
                   for candidate in self.buckets[len(word)])


"""
Approach #2: Generalized Neighbors [Accepted]
Intuition

Recall in Approach #1 that two words are neighbors if exactly one character can be changed in one word to make the strings equal.

Let's say a word 'apple' has generalized neighbors '*pple', 'a*ple', 'ap*le', 'app*e', and 'appl*'. When searching for whether a word like 'apply' has a neighbor like 'apple', 
we only need to know whether they have a common generalized neighbor.

Algorithm

Continuing the above thinking, one issue is that 'apply' is not a neighbor with itself, yet it has the same generalized neighbor '*pply'. 
To remedy this, we'll count how many sources generated '*pply'. 
1) If there are 2 or more, then one of them won't be 'apply'. If there is exactly one, we should check that it wasn't 'apply'. 
2) In either case, we can be sure that there was some magic word generating '*pply' that wasn't 'apply'.

Complexity Analysis

Time Complexity: O(\sum w_i^2)O(∑w 
i
2
​	
 ) to build and O(K^2)O(K 
2
 ) to search, where w_iw 
i
​	
  is the length of words[i], and KK is the length of our search word.

Space Complexity: O(\sum w_i^2)O(∑w 
i
2
​	
 ), the space used by count. We also use O(K^2)O(K 
2
 ) space when generating neighbors to search.

"""
from collections import Counter


class MagicDictionary(object):

    def _genneighbors(self, word):
        for i in range(len(word)):
            yield word[:i] + '*' + word[i+1:]

    def buildDict(self, words):
        self.words = set(words)
        self.count = Counter(nei for word in words for nei in self._genneighbors(word))

    def search(self, word):
        # Continuing the above thinking, one issue is that 'apply' is not a neighbor with itself, yet it has the same generalized neighbor '*pply'. 
        # To remedy this, we'll count how many sources generated '*pply'. If there are 2 or more, then one of them won't be 'apply'. 
        # If there is exactly one, we should check that it wasn't 'apply'. In either case, we can be sure that there was some magic word generating '*pply' that wasn't 'apply'.
        return any(self.count[nei] > 1 or self.count[nei] == 1 and word not in self.words for nei in self._genneighbors(word))