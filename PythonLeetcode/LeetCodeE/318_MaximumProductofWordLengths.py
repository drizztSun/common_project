


# 318. Maximum Product of Word Lengths

# Given a string array words, find the maximum value of length(word[i]) * length(word[j])
# where the two words do not share common letters. 
# You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

# Example 1:
# Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
# Return 16
# The two words can be "abcw", "xtfn".

# Example 2:
# Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
# Return 4
# The two words can be "ab", "cd".

# Example 3:
# Given ["a", "aa", "aaa", "aaaa"]
# Return 0
# No such pair of words.


class maxProduct:

    def doit(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        index = {}
        for w in words:
            mark = 0
            for c in set(w):
                mark |= 1 << ord(c) - ord('a')

            index[mark] = max(index.get(mark, 0), len(w))

        return max([index[x] * index[y] for x in index for y in index if not x & y] + [0])

                        

    def doit1(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        index = []
        for c in words:
            index.append(set(c))

        maxv
        for i in range(len(index)):

            for j in range(i+1, len(index)):

                if not index[i] & index[j]:

                    maxv = max(len(words[i]) * len(words[j]))

        return maxv

        
        




if __name__=="__main__":

    res = maxProduct().doit(["a", "aa", "aaa", "aaaa"])

    res = maxProduct().doit(["a", "ab", "abc", "d", "cd", "bcd", "abcd"])

    res = maxProduct().doit(["abcw", "baz", "foo", "bar", "xtfn", "abcdef"])


    pass