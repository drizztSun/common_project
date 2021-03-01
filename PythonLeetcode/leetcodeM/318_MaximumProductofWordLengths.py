"""
318. Maximum Product of Word Lengths

Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. 
You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:

Input: ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16 
Explanation: The two words can be "abcw", "xtfn".
Example 2:

Input: ["a","ab","abc","d","cd","bcd","abcd"]
Output: 4 
Explanation: The two words can be "ab", "cd".
Example 3:

Input: ["a","aa","aaa","aaaa"]
Output: 0 
Explanation: No such pair of words.
 

Constraints:

0 <= words.length <= 10^3
0 <= words[i].length <= 10^3
words[i] consists only of lowercase English letters.

"""

class MaximumProduct:

    """
        Approach 2: Optimise Number of Comparisons : Bitmasks + Precomputation + Hashmap
        Now, when the comparison itself is optimised, one could optimise the number of comparisons. There is no need to always perform \mathcal{O}(N^2)O(N 
        2
        ) comparisons. Among all the strings with the same set of letters (abab, aaaaabaabaaabbaaaaabaabaaabb, bbabbabbabbabbabba) it's enough to keep the longest one (aaaaabaabaaabbaaaaabaabaaabb).

        For that, instead of two arrays of length NN as in the Approach 1, one could use a hashmap : bitmask -> max word length with that bitmask.

        fig

        This way the total number of word comparisons could be reduced, that speeds up the solution in Python. Note, that for Java this way is not the optimal one because of known problems with HashMap performance.

        Algorithm

        Precompute bitmasks for all words and save them in the hashmap bitmask -> max word length with such a bitmask. (There could be several words with the same bitmask, for example, "a" and "aaaaaaa").

        Compare each word with all the following words one by one. If two words have no common letters, update the maximum product maxProd. Perform "no common letters" check in a constant time with the help of precomputed hashmap of bitmasks: (x & y) == 0.

        Return maxProd.

        Implementation


        Complexity Analysis

        Time complexity : \mathcal{O}(N^2 + L)O(N 
        2
        +L) where N is a number of words and L is a total length of all words together. If you want to have some fun, here is a bloody discussion that all this is for "small" N only, when N < 2^{26}N<2 
        26
        . The idea is that the number of bitmasks is not more than 2^{26}2 
        26
        and hence for N > 2^{26}N>2 
        26
        the complexity is \mathcal{O}(L)O(L).

        Space complexity : \mathcal{O}(N)O(N) to keep a hashmap of N elements if N < 2^{26}N<2 
        26
        . Otherwise, it's \mathcal{O}(2^{26})O(2 
        26
        ) = \mathcal{O}(1)O(1).

        Bitmasks + Precomputation : Comparison in \mathcal{O}(1)O(1) time

        In the previous approach one computes a bitmask of each word N times. In fact, each bitmask could be precomputed just once, memorised and then used for the runtime comparison in a constant time.

        Let's use two integer arrays to store bitmasks and string lengths. That's Java-optimised way, since in general Java works faster with arrays than with hashmaps.

        Algorithm

        Precompute bitmasks for all words and save them in the array masks. Use array lens to keep the lengths for all words.

        Compare each word with all the following words one by one. If two words have no common letters, update the maximum product maxProd. Perform "no common letters" check in a constant time with the help of precomputed masks array: (masks[i] & masks[j]) == 0.

        Return maxProd.

        Implementation


        Complexity Analysis

        Time complexity : \mathcal{O}(N^2 + L) where N is a number of words and LL is a total length of all words together. The precomputation takes \mathcal{O}(L)O(L) time because we iterate over all characters in all words. The runtime word comparison takes \mathcal{O}(N^2)O(N 
        2
        ) time. In total, that results in \mathcal{O}(N^2 + L)O(N 
        2
        +L) time complexity.

        Space complexity : \mathcal{O}(N)O(N) to keep two arrays of N elements.

    """
    def maxProduct(self, words: List[str]) -> int:
        from collections import defaultdict
        hashmap = defaultdict(int)
        bit_number = lambda ch : ord(ch) - ord('a')
        
        for word in words:
            bitmask = 0
            for ch in word:
                # add bit number bit_number in bitmask
                bitmask |= 1 << bit_number(ch)
            # there could be different words with the same bitmask
            # ex. ab and aabb
            hashmap[bitmask] = max(hashmap[bitmask], len(word))
        
        max_prod = 0
        for x in hashmap:
            for y in hashmap:
                if x & y == 0:
                    max_prod = max(max_prod, hashmap[x] * hashmap[y])
        return max_prod

    def maxProduct(self, words: List[str]) -> int:
        n = len(words)
        masks = [0] * n
        lens = [0] * n
        bit_number = lambda ch : ord(ch) - ord('a')
        
        for i in range(n):
            bitmask = 0
            for ch in words[i]:
                # add bit number bit_number in bitmask
                bitmask |= 1 << bit_number(ch)
            masks[i] = bitmask
            lens[i] = len(words[i])
            
        max_val = 0
        for i in range(n):
            for j in range(i + 1, n):
                if masks[i] & masks[j] == 0:
                    max_val = max(max_val, lens[i] * lens[j])
        return max_val

    def doit_(self, words: list) -> list:

        index = []
        for c in words:
            index.append(set(c))

        maxv = 0
        for i in range(len(index)):

            for j in range(i+1, len(index)):

                if not index[i] & index[j]:

                    maxv = max(maxv, len(words[i]) * len(words[j]))

        return maxv

    def doit_(self, words: list) -> int:

        index = {}
        for w in words:
            mark = 0
            for c in w:
                mark |= 1 << ord(c) - ord('a')
            index[mark] = max(index.get(mark, 0), len(w))
            
        return max([index[i] * index[j] for i in index for j in index if not i & j] + [0])
        