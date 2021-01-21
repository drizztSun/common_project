"""
288. Unique Word Abbreviation


The abbreviation of a word is a concatenation of its first letter, the number of characters between the first and last letter, and its last letter. 
If a word has only two characters, then it is an abbreviation of itself.

For example:

dog --> d1g because there is one letter between the first letter 'd' and the last letter 'g'.
internationalization --> i18n because there are 18 letters between the first letter 'i' and the last letter 'n'.
it --> it because any word with only two characters is an abbreviation of itself.
Implement the ValidWordAbbr class:

ValidWordAbbr(String[] dictionary) Initializes the object with a dictionary of words.
boolean isUnique(string word) Returns true if either of the following conditions are met (otherwise returns false):
There is no word in dictionary whose abbreviation is equal to word's abbreviation.
For any word in dictionary whose abbreviation is equal to word's abbreviation, that word and word are the same.
 

Example 1:

Input
["ValidWordAbbr", "isUnique", "isUnique", "isUnique", "isUnique"]
[[["deer", "door", "cake", "card"]], ["dear"], ["cart"], ["cane"], ["make"]]
Output
[null, false, true, false, true]

Explanation
ValidWordAbbr validWordAbbr = new ValidWordAbbr(["deer", "door", "cake", "card"]);
validWordAbbr.isUnique("dear"); // return false, dictionary word "deer" and word "dear" have the same abbreviation
                                // "d2r" but are not the same.
validWordAbbr.isUnique("cart"); // return true, no words in the dictionary have the abbreviation "c2t".
validWordAbbr.isUnique("cane"); // return false, dictionary word "cake" and word "cane" have the same abbreviation 
                                // "c2e" but are not the same.
validWordAbbr.isUnique("make"); // return true, no words in the dictionary have the abbreviation "m2e".
validWordAbbr.isUnique("cake"); // return true, because "cake" is already in the dictionary and no other word in the dictionary has "c2e" abbreviation.
 

Constraints:

1 <= dictionary.length <= 3 * 104
1 <= dictionary[i].length <= 20
dictionary[i] consists of lowercase English letters.
1 <= word.length <= 20
word consists of lowercase English letters.
At most 5000 calls will be made to isUnique.

"""
from collections import defaultdict


"""
    Approach #2 (Hash Table) [Accepted]
    Note that isUnique is called repeatedly for the same set of words in the dictionary each time. We should pre-process the dictionary to speed it up.

    Ideally, a hash table supports constant time look up. What should the key-value pair be?

    Well, the idea is to group the words that fall under the same abbreviation together. For the value, we use a Set instead of a List to guarantee uniqueness.

    The logic in isUnique(word) is tricky. You need to consider the following cases:

    Does the word's abbreviation exists in the dictionary? If not, then it must be unique.
    If above is yes, then it can only be unique if the grouping of the abbreviation contains no other words except word.

    Approach #3 (Hash Table) [Accepted]
    Let us consider another approach using a counter as the table's value. For example, assume the dictionary = ["door", "deer"], we have the mapping of {"d2r" -> 2}. 
    However, this mapping alone is not enough, because we need to consider whether the word exists in the dictionary. This can be easily overcome by inserting the entire dictionary into a set.

    When an abbreviation's counter exceeds one, we know this abbreviation must not be unique because at least two different words share the same abbreviation. Therefore, we can further simplify the counter to just a boolean.

    Complexity analysis

    Time complexity : O(n) pre-processing, O(1) for each isUnique call. Both Approach #2 and Approach #3 above take O(n) pre-processing time in the constructor. This is totally worth it if isUnique is called repeatedly.

    Space complexity : O(n). We traded the extra O(n) space storing the table to reduce the time complexity in isUnique.
"""
class ValidWordAbbr:

    def __init__(self, dictionary: list):
        
        self._unique = defaultdict(set)
        for c in dictionary:
            self._unique[self.encode(c)].add(c)

    def isUnique(self, word: str) -> bool:
        encoding = self.encode(word)
        if encoding not in self._unique:
            return True
        return word in self._unique[encoding] and len(self._unique[encoding]) == 1
        
    def encode(self, word: str) -> str:
        return ''.join(word[0] + str(len(word) - 2) + word[-1])


class ValidWordAbbr:

    def __init__(self, dictionary: list):
        self.dic = {}
        for word in set(dictionary):
            abbr = self.abbrev(word)
            if abbr not in self.dic:
                self.dic[abbr] = word
            else:
                self.dic[abbr] = False
                
    def isUnique(self, word: str) -> bool:
        abbr = self.abbrev(word)
        if abbr not in self.dic:
            return True
        else:
            return self.dic[abbr] == word
            
    def abbrev(self, word):
            if len(word) < 3:
                return word
            else:
                return word[0] + str(len(word)-2) + word[-1]