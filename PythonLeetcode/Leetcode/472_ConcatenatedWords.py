


# 472. Concatenated Words


# Given a list of words (without duplicates),
# please write a program that returns all concatenated words in the given list of words.
# A concatenated word is defined as a string that is comprised
# entirely of at least two shorter words in the given array.

# Example:
# Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

# Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]

# Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
# "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
# "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
# Note:
# The number of elements of the given array will not exceed 10,000
# The length sum of elements in the given array will not exceed 600,000.
# All the input string will only include lower case letters.
# The returned elements order does not matter.

class findAllConcatenatedWordsInADict:

    # <dfs>
    def doit(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        ans = []
        words_map = set(words)

        def help(w, cur, length):
            if cur == len(w):
                return length > 1

            for i in range(cur + 1, len(w)+1):

                if w[cur:i] in words_map and help(w, i, length+1):
                    return True

            return False


        for w in words:
            if help(w, 0, 0):
                ans.append(w)

        return ans


    def doit(self, words):
        """
        : type list[str]:
        """
        def search(w):
            if w in wordsMap:
                return True

            for i in range(len(w), 0, -1):
                if w[:i] in wordsMap and search(w[i:]):
                    return True

            return False

        wordsMap = set(words)
        ans = []

        for w in wordsMap:

            wordsMap.remove(w)

            if search(w):
                ans.append(w)

            wordsMap.add(w)
        
        return ans        
        


if __name__=="__main__":

    obj = findAllConcatenatedWordsInADict()

    res = obj.doit(["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"])


    pass
        