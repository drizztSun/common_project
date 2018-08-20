


# 639. Word Abbreviation


# Given an array of n distinct non-empty strings, you need to generate minimal possible abbreviations for every word following rules below.

# 1. Begin with the first character and then the number of characters abbreviated, which followed by the last character.

# 2. If there are any conflict, that is more than one words share the same abbreviation, 
# a longer prefix is used instead of only the first character until making the map from word to abbreviation become unique.
# In other words, a final abbreviation cannot map to more than one original words.

# 3. If the abbreviation doesn't make the word shorter, then keep it as original.

# Notice
# Both n and the length of each word will not exceed 400.
# The length of each word is greater than 1.
# The words consist of lowercase English letters only.
# The return answers should be in the same order as the original array.


class WordsAbbreviation:
    """
    @param dict: an array of n distinct non-empty strings
    @return: an array of minimal possible abbreviations for every word
    """
    def doit(self, dict):
        # write your code here
        pass





if __name__ == "__main__":

    # ["l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"]
    res = WordsAbbreviation().doit(["like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion"])

    