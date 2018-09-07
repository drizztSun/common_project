# 500. Keyboard Row

# Given a List of words, return the words that can be typed using letters of 
# alphabet on only one row's of American keyboard like the image below.

# American

# Example 1:
# Input: ["Hello", "Alaska", "Dad", "Peace"]
# Output: ["Alaska", "Dad"]


class FindWords:


    def doit1(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        keyboard = ['qwertyuiop', 'asdfghjkl', 'zxcvbnm']
        out = []
        for word in words:
            for keyline in keyboard:
                for ch in word.lower():
                    if not ch in keyline:
                        break
                if ch in keyline:
                    out.append(word)
        return out

    def doit(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        keyboards = {}
        for i, line in enumerate(["qwertyuiopQWERTYUIOP", "asdfghjklASDFGHJKL", "zxcvbnmZXCVBNM"]):
            for c in line:
                keyboards[c] = i

        res = []
        for word in words:
            line = -1
            for c in word:
                if line != -1 and line != keyboards[c]:
                    line = -1
                    break
                line = keyboards[c]

            if line != -1:
                res.append(word)

        return res


if __name__ == "__main__":

    res = FindWords().doit(["Hello", "Alaska", "Dad", "Peace"])
            
                    

        