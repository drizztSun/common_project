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

    def doit(self, words):

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



if __name__ == '__main__':


