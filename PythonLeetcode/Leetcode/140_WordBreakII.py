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


class WordBreak(object):

    # There is an issue that code repeat doing some intermedia result
    # we have to cache the position in the middle
    def doit(self, s, wordDict):
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
                if word == s[start : start + len(word)]:
                     tmp = searchContent(s, start + len(word), wordDict, buff)
                    
                     for i in tmp:
                        if i:
                            res.append( word + " " + i)
                        else:
                            res.append(word)


            buff[start] = res
            return res

        buff = {}
        return searchContent(s, 0, wordDict, buff)


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
            for i in xrange(start, len(s)):
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


    pass