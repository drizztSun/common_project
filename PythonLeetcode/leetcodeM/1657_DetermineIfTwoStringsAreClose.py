"""
1657. Determine if Two Strings Are Close

Two strings are considered close if you can attain one from the other using the following operations:

Operation 1: Swap any two existing characters.
For example, abcde -> aecdb
Operation 2: Transform every occurrence of one existing character into another existing character, and do the same with the other character.
For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)
You can use the operations on either string as many times as necessary.

Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.

 

Example 1:

Input: word1 = "abc", word2 = "bca"
Output: true
Explanation: You can attain word2 from word1 in 2 operations.
Apply Operation 1: "abc" -> "acb"
Apply Operation 1: "acb" -> "bca"
Example 2:

Input: word1 = "a", word2 = "aa"
Output: false
Explanation: It is impossible to attain word2 from word1, or vice versa, in any number of operations.
Example 3:

Input: word1 = "cabbba", word2 = "abbccc"
Output: true
Explanation: You can attain word2 from word1 in 3 operations.
Apply Operation 1: "cabbba" -> "caabbb"
Apply Operation 2: "caabbb" -> "baaccc"
Apply Operation 2: "baaccc" -> "abbccc"
Example 4:

Input: word1 = "cabbba", word2 = "aabbss"
Output: false
Explanation: It is impossible to attain word2 from word1, or vice versa, in any amount of operations.
 

Constraints:

1 <= word1.length, word2.length <= 105
word1 and word2 contain only lowercase English letters.


"""


class DetermineIfTwoStringsAreClose:

    def doit_(self, word1: str, word2: str) -> bool:
        from collections import Counter
        """
        Given two strings, word1 and word2, this program determines
        whether the two strings are close to each other based
        on the definition of "close" in the problem statement.

        :param word1: first string
        :type word1: str
        :param word2: second string
        :type word2: str
        :return: True if word1 and word2 are close, else False
        :rtype: bool
        """

        """
        Base Cases:
        - Return False if the strings are of different lengths.
        - Return False if the strings have different sets of
          letters.
        """
        if len(word1) != len(word2):
            return False

        if set(word1) != set(word2):
            return False

        """
        Determine whether the strings are close.
        - Use Counter to get the frequency counts for each letter
          in each string (counts_1, counts_2).
        - Use counts_1 and counts_2 to create arrays of frequency
          counts freqs_1 and freqs_2, respectively.
        - Return True if the sorted frequency counts are equal,
          otherwise return False.
        """
        counts_1 = Counter(word1)
        counts_2 = Counter(word2)

        freqs_1 = []
        freqs_2 = []

        for char in counts_1:
            freqs_1.append(counts_1[char])
            freqs_2.append(counts_2[char])
            
        return sorted(freqs_1) == sorted(freqs_2)
        