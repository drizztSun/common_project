"""
139. Word Break

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
Example 1:

Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
             Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false
"""


class WordBreak:

    def doit(self, s: str, wordDict):

        DP = [False] * len(s)

        for i in range(len(s)):
            for w in wordDict:
                if w == s[i - len(w) + 1: i + 1] and (DP[i - len(w)] or i - len(w) == -1):
                    DP[i] = True

        return DP[-1]


"""
140. Word Break II

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.

Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
Example 1:

Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]
Example 2:

Input:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
Output:
[
  "pine apple pen apple",
  "pineapple pen apple",
  "pine applepen apple"
]
Explanation: Note that you are allowed to reuse a dictionary word.
Example 3:

Input:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
Output:
[]

"""


class WordBreakII:

    """
    Approach 1: Top-Down Dynamic Programming
    Intuition

    Let us start with the top-down approach, which is more efficient compared to bottom-up approach in this case.

    Given an input string \text{s} = \text{`catsanddog'}s=‘catsanddog’, we define the results of breaking it into words with the function \text{F(s)}F(s).

    For any word (denoted as \text{w}w) in the dictionary, if it matches with a prefix of the input string, we then can divide the string into two parts: the word and the postfix, i.e. s = \text{w} + \text{postfix}s=w+postfix.

    Consequently, the solution for the input string can be represented as follows:

    \forall \text{w} \in \text{dict}, \quad s = \text{w} + \text{postfix} \implies \{ \text{w} + \text{F(postfix)} \} \subseteq \text{F(s)}∀w∈dict,s=w+postfix⟹{w+F(postfix)}⊆F(s)

    i.e. we add the matched word to the solutions from the postfix.

    For example, the word cat matches with a prefix of the string. As a result, we can divide the string into s = \text{`cat'} + \text{`sanddog'}s=‘cat’+‘sanddog’.

    For the postfix of sanddog, we could obtain the results by recursively applying our function, i.e. \text{F(`sanddog')} = \{ \text{`sand dog'} \}F(‘sanddog’)={‘sand dog’}. By adding the prefix word to the solutions of the postfix, we then obtain one of the solutions for the original string, i.e. \text{`cat sand dog'} \in \text{F(s)}‘cat sand dog’∈F(s).

    The above approach can be considered as a top-down DP. The reason lies in the part that we adopt the laissez-faire strategy, i.e. we simply take a first step, while assuming the subsequent steps will figure out on their owns.

    In our case, we first find a match to a prefix of the string, while assuming that we would eventually obtain the results for the corresponding postfix.

    In the following graph, we illustrate how the top-down approach works with a concrete example, i.e. with the input string as s="catsanddogo" and the word dictionary as wordDict=["cat", "cats", "and", "sand", "dog", "do", "go"].

    """
    def doit_dp_topdown(self, s: str, wordDict: list) -> list:
        from collections import defaultdict
        wordSet = set(wordDict)
        # table to map a string to its corresponding words break
        # {string: [['word1', 'word2'...], ['word3', 'word4', ...]]}
        memo = defaultdict(list)

        # @lru_cache(maxsize=None)    # alternative memoization solution
        def _wordBreak_topdown(s):
            """ return list of word lists """
            if not s:
                return [[]]  # list of empty list

            if s in memo:
                # returned the cached solution directly.
                return memo[s]

            for endIndex in range(1, len(s) + 1):
                word = s[:endIndex]
                if word in wordSet:
                    # move forwards to break the postfix into words
                    for subsentence in _wordBreak_topdown(s[endIndex:]):
                        memo[s].append([word] + subsentence)
            return memo[s]

        # break the input string into lists of words list
        _wordBreak_topdown(s)

        # chain up the lists of words into sentences.
        return [" ".join(words) for words in memo[s]]


    """
    Approach 2: Bottom-Up Dynamic Programming
    Intuition
    
    As opposed to the top-down approach, the bottom-up dynamic programming progressively builds up the solutions for the sub-problems upfront, rather than delaying them to the end.
    
    We will demonstrate the difference between the two approaches with a concrete example later.
    
    Following the same definition in the top-down approach, given an input string \text{s}s, e.g. \text{s} = \text{`catsanddog'}s=‘catsanddog’, we define the results of breaking it into words with the function \text{F(s)}F(s).
    
    For any word (denoted as \text{w}w) in the dictionary, if it matches with a postfix of the input string, we then can divide the string into two parts: the prefix and the word, i.e. s = \text{prefix} + \text{w}s=prefix+w.
    
    Consequently, the solution for the input string can be represented as follows:
    
    \forall \text{w} \in \text{dict}, \quad s = \text{prefix} + \text{w} \implies \{ \text{F(prefix)} + \text{w} \} \subseteq \text{F(s)}∀w∈dict,s=prefix+w⟹{F(prefix)+w}⊆F(s)
    
    i.e. we add the matched word to the solutions from the prefix.
    
    We start from an empty prefix (i.e. the bottom case), to progressively extend the solutions to a larger prefix. Eventually, the extended prefix would grow to be the original string.
    
    In the following graph, we demonstrate how the bottom-up approach works for the same example in the top-down approach, i.e. with the input string as s="catsanddogo" and the word dictionary as wordDict=["cat", "cats", "and", "sand", "dog", "do", "go"].
    """

    def doit_dp_bottomup(self, s: str, wordDict: list) -> list:
        from collections import Counter
        # quick check on the characters,
        #   otherwise it would exceed the time limit for certain test cases.
        if set(Counter(s).keys()) > set(Counter("".join(wordDict)).keys()):
            return []

        wordSet = set(wordDict)

        dp = [[]] * (len(s) + 1)
        dp[0] = [""]

        for endIndex in range(1, len(s) + 1):
            sublist = []
            # fill up the values in the dp array.
            for startIndex in range(0, endIndex):
                word = s[startIndex:endIndex]
                if word in wordSet:
                    for subsentence in dp[startIndex]:
                        sublist.append((subsentence + ' ' + word).strip())

            dp[endIndex] = sublist

        return dp[len(s)]

    # There is an issue that code repeat doing some intermedia result
    # we have to cache the position in the middle
    def doit_dp(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: List[str]
        """
        def searchContent(s, start, wordDict, buff):
            if start in buff:
                return buff[start]

            if start == len(s):
                return [""]

            res = []
            for word in wordDict:
                if word == s[start: start + len(word)]:
                     for i in searchContent(s, start + len(word), wordDict, buff):
                        if i:
                            res.append(word + " " + i)
                        else:
                            res.append(word)
            buff[start] = res
            return res

        buff = {}
        return searchContent(s, 0, wordDict, buff)

    def wordBreak(self, s: str, wordDict):
        from collections import defaultdict

        d = set(wordDict)
        mem = defaultdict(list)

        def breakw(s):
            if not s:
                return [[]]

            if s in mem:
                return mem[s]

            for i in range(1, len(s) + 1):
                if s[:i] in d:
                    for w in breakw(s[i:]):
                        mem[s].append([s[:i]] + w)
            return mem[s]

        breakw(s)
        return [" ".join(words) for words in mem[s]]

    def doit1(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: List[str]
        """
        def search(s, wordDict, buff):
            if s in buff:
                return buff[s]

            if len(s) == 0:
                return [""]

            res = []
            for word in wordDict:
                tmp = []
                if word == s[0:len(word)]:
                    tmp = search(s[len(word):], wordDict, buff)

                for i in tmp:
                    c = word
                    if i :
                        c += ' ' + i
                    res.append(c)
            
            buff[s] = res
            return res
        
        buff = {} 
        return search(s, wordDict, buff)


    def doit2(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: List[str]
        """
        if not wordDict: 
            return []

        MaxLen = max(len(w) for w in wordDict)
        
        def FindAll(s, start, trie, dp):
            if start == len(s): 
                return []
            if start in dp and not dp[start]: 
                return []

            result = []
            for i in range(start, len(s)):
                if i - start > MaxLen: 
                    break
                
                if s[start:i+1] in trie:
                    if i + 1 == len(s):
                        result.append(s[start:i+1])
                    else:
                        for rest in FindAll(s, i+1, trie, dp):
                            result.append(s[start:i+1]+" " +rest)
            
            if not result:
                dp[start] = False

            return result
        

        if not s: return []
        trie = set(wordDict)
        dp = dict()
        
        return FindAll(s, 0, trie, dp)


    def doit4(self, s, wordDict):
        memo = {len(s): ['']}
        def sentences(i):
            if i not in memo:
                memo[i] = [s[i:j] + (tail and ' ' + tail)
                           for j in range(i+1, len(s)+1)
                           if s[i:j] in wordDict
                           for tail in sentences(j)]
            return memo[i]
        return sentences(0)

if __name__=="__main__":

    res = WordBreak().doit4("catsanddog", ["cat","cats","and","sand","dog"])

    res = WordBreak().doit("catsanddog", ["cat","cats","and","sand","dog"])

    res = WordBreak().doit("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", ["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"])