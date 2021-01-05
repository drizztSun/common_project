"""
616. Add Bold Tag in String

Given a string s and a list of strings dict, you need to add a closed pair of bold tag <b> and </b> to wrap the substrings in s that exist in dict. 
If two such substrings overlap, you need to wrap them together by only one pair of closed bold tag. Also, if two substrings wrapped by bold tags are consecutive, you need to combine them.
Example 1:

Input: 
s = "abcxyz123"
dict = ["abc","123"]
Output:
"<b>abc</b>xyz<b>123</b>"
 

Example 2:

Input: 
s = "aaabbcc"
dict = ["aaa","aab","bc"]
Output:
"<b>aaabbc</b>c"
 

Constraints:

The given dict won't contain duplicates, and its length won't exceed 100.
All the strings in input have length in range [1, 1000].
Note: This question is the same as 758: https://leetcode.com/problems/bold-words-in-string/

"""


class AddBoldTag:



    def addBoldTag(self, s: str, dict: List[str]) -> str:
        status = [False] * len(s)
        for word in dict:
            start = s.find(word)
            length = len(word)
            while start != -1:
                status[start:start + length] = [True] * length
                start = s.find(word,start + 1)

        i, result = 0, ""
        while i < len(s):
            if status[i]:
                result += "<b>"
                while i < len(s) and status[i]:
                    result += s[i]
                    i += 1
                result += "</b>"
            else:
                result += s[i]
                i += 1
        return result

    """
    Approach #1: Brute Force [Accepted]
    Intuition

    Let's try to learn which letters end up bold, since the resulting answer will just be the canonical one - we put bold tags around each group of bold letters.

    To do this, we'll check for all occurrences of each word and mark the corresponding letters bold.

    Algorithm

    Let's work on first setting mask[i] = true if and only if the i-th letter is bold. For each starting position i in S, for each word, if S[i] starts with word, we'll set the appropriate letters bold.

    Now armed with the correct mask, let's try to output the answer. A letter in position i is the first bold letter of the group if mask[i] && (i == 0 || !mask[i-1]), and is the last bold letter if mask[i] && (i == N-1 || !mask[i+1]). Alternatively, we could use itertools.groupby in Python.

    Once we know which letters are the first and last bold letters of a group, we know where to put the "<b>" and "</b>" tags.

    Complexity Analysis

    Time Complexity: O(N∑wi), where NN is the length of S and w_i is the sum of W.

    Space Complexity: O(N).

    """
    def doit_(self, S, words):
        N = len(S)
        mask = [False] * N
        for i in xrange(N):
            prefix = S[i:]
            for word in words:
                if prefix.startswith(word):
                    for j in xrange(i, min(i+len(word), N)):
                        mask[j] = True

        ans = []
        for incl, grp in itertools.groupby(zip(S, mask), lambda z: z[1]):
            if incl: ans.append("<b>")
            ans.append("".join(z[0] for z in grp))
            if incl: ans.append("</b>")
        return "".join(ans)

    class TrieNode:

        def __init__(self):
            self._children = {}
            self._done = False
    
    def doit_trie(self, s: str, keys: list) -> str:
        
        def buildtrie(node, w):
            for c in w:
                if c not in node._children:
                    node._children[c] = AddBoldTag.TrieNode()
                node = node._children[c]
            node._done = True

        def walk(j):
            node, start = root, j
            while j < len(s) and s[j] in node._children:
                node = node._children[s[j]]
                if node._done:
                    status[start: j+1] = [True] * (j-start+1)
                    start = j+1
                j += 1

        root = AddBoldTag.TrieNode()

        for w in keys:
            buildtrie(root, w)

        status = [False] * len(s)
        for i in range(len(s)):
            walk(i)

        res, in_out = '', False
        for i, p in enumerate(status):
            if not in_out and p:
                res, in_out = res + '<b>', not in_out
            
            elif in_out and not p:
                res, in_out = res + '</b>', not in_out
            
            res += s[i]

        return res + '</b>' if in_out else res


if __name__ == '__main__':

    AddBoldTag().doit_trie("aaabbcc", ["aaa","aab","bc"])
        


        
