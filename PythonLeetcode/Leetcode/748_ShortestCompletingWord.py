# 748. Shortest Completing Word

# Find the minimum length word from a given dictionary words, which has all the letters from the string licensePlate. 
# Such a word is said to complete the given string licensePlate

# Here, for letters we ignore case. For example, "P" on the licensePlate still matches "p" on the word.

# It is guaranteed an answer exists. If there are multiple answers, return the one that occurs first in the array.

# The license plate might have the same letter occurring multiple times. 
# For example, given a licensePlate of "PP", the word "pair" does not complete the licensePlate, but the word "supper" does.

# Example 1:
# Input: licensePlate = "1s3 PSt", words = ["step", "steps", "stripe", "stepple"]
# Output: "steps"
# Explanation: The smallest length word that contains the letters "S", "P", "S", and "T".
# Note that the answer is not "step", because the letter "s" must occur in the word twice.
# Also note that we ignored case for the purposes of comparing whether a letter exists in the word.

# Example 2:
# Input: licensePlate = "1s3 456", words = ["looks", "pest", "stew", "show"]
# Output: "pest"
# Explanation: There are 3 smallest length words that contains the letters "s".
# We return the one that occurred first.

class ShortestCompletingWord:
    def doit(self, licensePlate: 'str', words: 'List[str]') -> 'str':
        
        platemap = {}
        for n in licensePlate.lower():
            if n.isalpha():
                platemap[n] = platemap.get(n, 0) + 1
        
        ans = ''    
        for w in words:
            data = platemap.copy()
            
            for n in w.lower():
                if n in data:
                    data[n] -= 1
                    if data[n] == 0:
                        del data[n]
                        
            if not data and (not ans or len(w) < len(ans)):
                ans = w
                    
        return ans


if __name__ == "__main__":

    res = ShortestCompletingWord().doit("1s3 PSt", ["step","steps","stripe","stepple"])