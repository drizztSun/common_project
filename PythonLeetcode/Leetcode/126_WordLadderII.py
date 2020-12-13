"""
126. Word Ladder II

Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
Note:

Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.

Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]

Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: []

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.

"""


class WordLadderII:

    def doit_bfs(self, beginWord, endWord, wordList):
        import collections
        import string

        if endWord not in wordList:
            return []

        def construct_paths(source, dest, tree):
            if source == dest:
                return [[source]]
            return [[source] + path for succ in tree[source] for path in construct_paths(succ, dest, tree)]

        def add_path(tree, word, neigh, is_forw):
            if is_forw:
                tree[word] += neigh,
            else:
                tree[neigh] += word,

        def bfs_level(this_lev, oth_lev, tree, is_forw, words_set):
            if not this_lev:
                return False

            if len(this_lev) > len(oth_lev):
                return bfs_level(oth_lev, this_lev, tree, not is_forw, words_set)

            for word in (this_lev | oth_lev):
                words_set.discard(word)

            next_lev, done = set(), False
            while this_lev:
                word = this_lev.pop()
                for c in string.ascii_lowercase:
                    for index in range(len(word)):
                        neigh = word[:index] + c + word[index + 1:]
                        if neigh in oth_lev:
                            done = True
                            add_path(tree, word, neigh, is_forw)
                        if not done and neigh in words_set:
                            next_lev.add(neigh)
                            add_path(tree, word, neigh, is_forw)

            return done or bfs_level(next_lev, oth_lev, tree, is_forw, words_set)

        tree, path, paths = collections.defaultdict(list), [beginWord], []
        bfs_level(set([beginWord]), set([endWord]), tree, True, set(wordList))

        return construct_paths(beginWord, endWord, tree)

    def doit_bfs(self, beginWord, endWord, wordList):
        from collections import defaultdict
        tree, words, n = defaultdict(set), set(wordList), len(beginWord)
        if endWord not in wordList:
            return []

        found, bq, eq, nq, rev = False, {beginWord}, {endWord}, set(), False
        while bq and not found:
            words -= set(bq)
            for x in bq:
                for i in range(n):
                    first, second = x[:i], x[i + 1:]
                    for c in 'qwertyuiopasdfghjklzxcvbnm':
                        y = first + c + second
                        if y in words:
                            if y in eq:
                                found = True
                            else:
                                nq.add(y)
                            tree[y].add(x) if rev else tree[x].add(y)
            bq, nq = nq, set()
            if len(bq) > len(eq):
                bq, eq, rev = eq, bq, not rev

        def bt(x):
            return [[x]] if x == endWord else [[x] + rest for y in tree[x] for rest in bt(y)]

        return bt(beginWord)

    def doit_bfs_1(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: List[List[str]]
        """
        from collections import defaultdict

        beginset, endset, tree = set([beginWord]), set([endWord]), defaultdict(set)
        wl = set(wordList)

        if endWord not in wl:
            return []

        found, reverse = False, False
        while beginset and not found:

            wl -= beginset
            nextset = set()

            for w in beginset:

                for i in range(len(w)):
                    for c in 'abcdefghijklmnopqrstuvwxyz':
                        nw = w[:i] + c + w[i + 1:]
                        if nw in wl:
                            if nw in endset:
                                found = True
                            else:
                                nextset.add(nw)

                            if reverse:
                                tree[nw].add(w)
                            else:
                                tree[w].add(nw)

            beginset = nextset
            if len(beginset) > len(endset):
                beginset, endset = endset, beginset
                reverse = not reverse

        def build(x):
            if x == endWord:
                return [[x]]
            else:
                res = []
                for c in tree[x]:
                    for r in build(c):
                        res.append([x] + r)
                return res

        return build(beginWord)


if __name__ == '__main__':

    WordLadderII().doit_bfs_1("hit", "cog", ["hot","dot","dog","lot","log","cog"])