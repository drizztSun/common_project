# 843. Guess the Word

# This problem is an interactive problem new to the LeetCode platform.

# We are given a word list of unique words, each word is 6 letters long, and one word in this list is chosen as secret.

# You may call master.guess(word) to guess a word.  The guessed word should have type string and must be from the original list with 6 lowercase letters.

# This function returns an integer type, representing the number of exact matches (value and position) of your guess to the secret word.  Also, if your guess is not in the given wordlist, it will return -1 instead.

# For each test case, you have 10 guesses to guess the word. At the end of any number of calls, if you have made 10 or less calls to master.guess and at least one of these guesses was the secret, you pass the testcase.

# Besides the example test case below, there will be 5 additional test cases, each with 100 words in the word list.  The letters of each word in those testcases were chosen independently at random from 'a' to 'z', such that every word in the given word lists is unique.

# Example 1:
# Input: secret = "acckzz", wordlist = ["acckzz","ccbazz","eiowzz","abcczz"]

# Explanation:

# master.guess("aaaaaa") returns -1, because "aaaaaa" is not in wordlist.
# master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6 matches.
# master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
# master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
# master.guess("abcczz") returns 4, because "abcczz" has 4 matches.

# We made 5 calls to master.guess and one of them was the secret, so we pass the test case.
# Note:  Any solutions that attempt to circumvent the judge will result in disqualification.

# """
# This is Master's API interface.
# You should not implement it, or speculate about its implementation
# """
class Master:
    
    def __init__(self, w):
        self.w_ = w


    def guess(self, word):
        """
        :type word: str
        :rtype int
        """
        return sum(i == j for i, j in zip(word, self.w_))




import random

class FindSecretWord:
    
    # incorrect
    def doit2(self, wordlist, master):
        """
        :type wordlist: List[Str]
        :type master: Master
        :rtype: None
        """
        checked = []
        num = 0
        while True:
            word = random.choice(wordlist)
            choice = True
            for w, n in checked:
                if sum([0, 1][i == j] for i, j in zip(word, w)) != n:
                    choice = False
                    break
            
            if choice:
                checked += [(word, master.guess(word))]

            num += 1
            if checked[-1][1] == 6:
                break

    # Great! Finally we have an interactive problem new to the LeetCode platform.

    # The description emphasize that the wordlist is generated randomly and it's does have a reason.

    # There is no solution that can guarantee to find a secret word in 10 tries. If I make up a test case with wordlist like 
    # ["aaaaaa", "bbbbbb" ...., "zzzzzz"], it need 26 tries to find the secret.

    # So 10 tries is just a limit to test reasonable solution. And this problem is more than finding right output for given input, it's more about a strategy.

    # Intuition:
    # Take a word from wordlist and guess it.
    # Get the matches of this word
    # Update our wordlist and keep only the same matches to our guess.

    # For example we guess "aaaaaa" and get matches x = 3, we keep the words with exactly 3 a.

    # Also we need to know the matches between two words, so a sub function as following will be helpful.

    def doit1(self, wordlist, master):
        """
        :type wordlist: List[Str]
        :type master: Master
        :rtype: None
        """
        n = 0
        while n < 6:
            word = random.choice(wordlist)
            n = master.guess(word)
            wordlist = [w for w in wordlist if sum(i == j for i, j in zip(word, w)) == n]

    # This process is straight forward.
    # However, the key point is, which word should we guess from all of the wordlist?

    # Explanation:

    # First of all, I guessed the first word from wordlist.
    # Unfortunately, I didn't get a lucky pass.
    # This problem has only 5 test cases but they are good.

    # But I didn't give up this idea. All words are generated randomly.
    # So why not we also guess a random word and let it be whatever will be.
    # So here it is this idea and it can get accepted.     
    def doit(self, wordlist, master):
        """
        :type wordlist: List[Str]
        :type master: Master
        :rtype: None
        """
        import itertools
        def match(w1, w2):
            return sum(i == j for i, j in zip(w1, w2))

        n = 0
        while n < 6:
            count = collections.Counter(w1 for w1, w2 in itertools.permutations(wordlist, 2) if match(w1, w2) == 0)
            guess = min(wordlist, key=lambda w: count[w])
            n = master.guess(guess)
            wordlist = [w for w in wordlist if self.match(w, guess) == n]

    # Time Complexity and Result Analyse

    # To be more convincing, I test each approach with 1000 test cases.
    # For the random approach, time complexity O(N), average 6.5 guess, worst case 14 guess.
    # For the minimax approach, time complexity O(N^2), average 5.5 guess, worst case 10 guess.
    # I draw this diagram to visualize the result:



if __name__ == "__main__":

    res = FindSecretWord().doit(["acckzz","ccbazz","eiowzz","abcczz"], Master("acckzz"))

    pass