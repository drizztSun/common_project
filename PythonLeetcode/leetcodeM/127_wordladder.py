"""
127. Word Ladder

Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list.
Note:

Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.
Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: 0

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.

"""


class LadderLength:

    def doit_bfs_bidirect(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """
        wl = set(wordList)
        if endWord not in wl:
            return 0
        wl.remove(endWord)

        if beginWord in wl:
            wl.remove(beginWord)

        ladder = 2
        preWord, nextWord = set([beginWord]), set([endWord])

        while preWord and nextWord:
            if len(preWord) < len(nextWord):
                preWord, nextWord = nextWord, preWord

            temp = set()
            for t in nextWord:
                # iter word
                i = 0
                while i < len(t):
                    for j in 'abcdefghijklmnopqrstuvwxyz':
                        word = t[:i] + j + t[i + 1:]
                        if word in preWord:
                            return ladder

                        if word in wl:
                            temp.add(word)
                            wl.remove(word)
                    i += 1
            nextWord, temp = temp, nextWord
            ladder += 1

        return 0

    def doit_bfs(self, beginWord: str, endWord: str, wordList):

        from collections import defaultdict, deque

        if endWord not in wordList or not endWord or not beginWord or not wordList:
            return 0

        # Since all words are of same length.
        L = len(beginWord)

        # Dictionary to hold combination of words that can be formed,
        # from any given word. By changing one letter at a time.
        all_combo_dict = defaultdict(list)
        for word in wordList:
            for i in range(L):
                # Key is the generic word
                # Value is a list of words which have the same intermediate generic word.
                all_combo_dict[word[:i] + "*" + word[i + 1:]].append(word)

        # Queue for BFS
        queue = deque([(beginWord, 1)])
        # Visited to make sure we don't repeat processing same word.
        visited = {beginWord: True}
        while queue:
            current_word, level = queue.popleft()
            for i in range(L):
                # Intermediate words for current word
                intermediate_word = current_word[:i] + "*" + current_word[i + 1:]

                # Next states are all the words which share the same intermediate state.
                for word in all_combo_dict[intermediate_word]:
                    # If at any point if we find what we are looking for
                    # i.e. the end word - we can return with the answer.
                    if word == endWord:
                        return level + 1
                    # Otherwise, add it to the BFS Queue. Also mark it visited
                    if word not in visited:
                        visited[word] = True
                        queue.append((word, level + 1))
                all_combo_dict[intermediate_word] = []
        return 0

    # <bfs> <tle>
    def doit_bfs_tle(self, beginWord: str, endWord: str, wordList):
        from collections import defaultdict, deque
        # from heapq import

        wordset = set(wordList)
        if endWord not in wordset:
            return 0

        def word_diff(a, b):
            if len(a) != len(b):
                return False

            res = 0
            for i in range(len(a)):
                if a[i] != b[i]:
                    res += 1
                if res == 2:
                    return False
            return res == 1

        path = defaultdict(set)
        for i in range(len(wordList)):
            for j in range(i+1, len(wordList)):
                if word_diff(wordList[i], wordList[j]):
                    path[i].add(j)
                    path[j].add(i)

        qu = deque([i for i in range(len(wordList)) if word_diff(beginWord, wordList[i])])
        visited = set(qu)
        level = 0

        while qu:
            level += 1
            for _ in range(len(qu)):
                c = qu.pop()
                if wordList[c] == endWord:
                    return level + 1

                for n in path[c]:
                    if n not in visited:
                        qu.appendleft(n)
                        visited.add(n)
        return 0