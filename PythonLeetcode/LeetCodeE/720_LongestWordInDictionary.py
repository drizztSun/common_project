


import os


# 720. Longest Word in Dictionary
# Given a list of strings words representing an English Dictionary, 
# find the longest word in words that can be built one character at a time by other words in words. 
# If there is more than one possible answer, return the longest word with the smallest lexicographical order.

# If there is no answer, return the empty string.

# Example 1:
# Input: 
# words = ["w","wo","wor","worl", "world"]
# Output: "world"
# Explanation: 
# The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".

# Example 2:
# Input: 
# words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
# Output: "apple"
# Explanation: 
# Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographically smaller than "apply


class node:

    def __init__(self, num=0):
        
        self.num = num

        self.group = {}


class longestWord:
    def doit(self, words):
        """
        :type words: List[str]
        :rtype: str
        """
        words = sorted(words)
        root = node(1)
        longest = 0
        res = ''
        for c in words:
            pt = root
            flag = False
            length = 0

            for i, f in enumerate(c):
                if f not in pt.group:
                    pt.group[f] = node()
                
                pt = pt.group[f]
                if i == len(c)-1:
                    pt.num += 1

                if pt.num != 0:
                    length += 1
                else:
                    length = 0
                    break

            if length > longest:
                res = c
                longest = len(c)
            elif length == longest:
                res = min(res, c)

        return res


    def doit1(self, words):
        """
        :type words: List[str]
        :rtype: str
        """
        words.sort()
        longest = ''
        A = set([""])

        for c in words:
            if c[:len(c)-1] in A:
                A.add(c)

                if len(c) > len(longest):
                    longest = c

        return longest
         
                
                


if __name__ == "__main__":

    res = longestWord().doit(["w","wo","wor","worl", "world"])

    res = longestWord().doit(["a", "banana", "app", "appl", "ap", "apply", "apple"])

    pass
