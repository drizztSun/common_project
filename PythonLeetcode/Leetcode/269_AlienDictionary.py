"""
269. Alien Dictionary

There is a new alien language which uses the latin alphabet.
However, the order among letters are unknown to you. You receive a list of non-empty words from the dictionary,
where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

Example 1:

Input:
[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]

Output: "wertf"
Example 2:

Input:
[
  "z",
  "x"
]

Output: "zx"
Example 3:

Input:
[
  "z",
  "x",
  "z"
]

Output: ""

Explanation: The order is invalid, so return "".
Note:

You may assume all letters are in lowercase.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return any one of them is fine.

"""


class AlienOrder:

    def doit_bfs_topsort(self, words) -> str:
        from collections import defaultdict, Counter, deque

        # Step 0: create data structures + the in_degree of each unique letter to 0.
        adj_list = defaultdict(set)
        in_degree = Counter({c: 0 for word in words for c in word})

        # Step 1: We need to populate adj_list and in_degree.
        # For each pair of adjacent words...
        for first_word, second_word in zip(words, words[1:]):
            for c, d in zip(first_word, second_word):
                if c != d:
                    if d not in adj_list[c]:
                        adj_list[c].add(d)
                        in_degree[d] += 1
                    break
            else:  # Check that second word isn't a prefix of first word.
                if len(second_word) < len(first_word):
                    return ""

        # Step 2: We need to repeatedly pick off nodes with an indegree of 0.
        output = []
        queue = deque([c for c in in_degree if in_degree[c] == 0])
        while queue:
            c = queue.popleft()
            output.append(c)
            for d in adj_list[c]:
                in_degree[d] -= 1
                if in_degree[d] == 0:
                    queue.append(d)

        # If not all letters are in output, that means there was a cycle and so
        # no valid ordering. Return "" as per the problem description.
        if len(output) < len(in_degree):
            return ""
        # Otherwise, convert the ordering we found into a string and return it.
        return "".join(output)

    def doit_dfs(self, words):

        # Step 0: Put all unique letters into the adj list.
        reverse_adj_list = {c: [] for word in words for c in word}

        # Step 1: Find all edges and put them in reverse_adj_list.
        for first_word, second_word in zip(words, words[1:]):
            for c, d in zip(first_word, second_word):
                if c != d:
                    reverse_adj_list[d].append(c)
                    break
            else:  # Check that second word isn't a prefix of first word.
                if len(second_word) < len(first_word):
                    return ""

        # Step 2: Depth-first search.
        seen = {}  # False = grey, True = black.
        output = []

        def visit(node):  # Return True iff there are no cycles.
            if node in seen:
                return seen[node]  # If this node was grey (False), a cycle was detected.
            seen[node] = False  # Mark node as grey.
            for next_node in reverse_adj_list[node]:
                result = visit(next_node)
                if not result:
                    return False  # Cycle was detected lower down.
            seen[node] = True  # Mark node as black.
            output.append(node)
            return True

        if not all(visit(node) for node in reverse_adj_list):
            return ""

        return "".join(output)

    def doit(self, words):

        from collections import defaultdict, deque, Counter

        g = defaultdict(set)
        indegree = Counter({c:0 for word in words for c in word})

        for i in range(1, len(words)):
            for j in range(min(len(words[i]), len(words[i - 1]))):
                c, b = words[i - 1][j], words[i][j]
                if c != b:
                    if b not in g[c]:
                        g[c].add(b)
                        indegree[b] += 1
                    break
            else:
                if len(words[i]) < len(words[i-1]):
                    return ""

        output = []
        queue = deque([k for k in indegree.keys() if indegree[k] == 0])

        while queue:

            c = queue.popleft()
            output.append(c)
            for n in g[c]:
                indegree[n] -= 1
                if indegree[n] == 0:
                    queue.appendleft(n)

        if len(output) < len(indegree):
            return ""

        return ''.join(output)


if __name__ == '__main__':

    AlienOrder().doit(["wrt", "wrf", "er", "ett", "rftt", "te"])

    AlienOrder().doit(["wrt","wrf","er","ett","rftt"])

    AlienOrder().doit(["abc","ab"])

