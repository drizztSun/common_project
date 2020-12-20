"""
1202. Smallest String With Swaps

You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.

You can swap the characters at any pair of indices in the given pairs any number of times.

Return the lexicographically smallest string that s can be changed to after using the swaps.



Example 1:

Input: s = "dcab", pairs = [[0,3],[1,2]]
Output: "bacd"
Explaination:
Swap s[0] and s[3], s = "bcad"
Swap s[1] and s[2], s = "bacd"
Example 2:

Input: s = "dcab", pairs = [[0,3],[1,2],[0,2]]
Output: "abcd"
Explaination:
Swap s[0] and s[3], s = "bcad"
Swap s[0] and s[2], s = "acbd"
Swap s[1] and s[2], s = "abcd"
Example 3:

Input: s = "cba", pairs = [[0,1],[1,2]]
Output: "abc"
Explaination:
Swap s[0] and s[1], s = "bca"
Swap s[1] and s[2], s = "bac"
Swap s[0] and s[1], s = "abc"


Constraints:

1 <= s.length <= 10^5
0 <= pairs.length <= 10^5
0 <= pairs[i][0], pairs[i][1] < s.length
s only contains lower case English letters.

"""


class SmallestStringWithSwaps:

    def doit_dfs(self, s: str, pairs: list) -> str:
        from collections import defaultdict

        graph = defaultdict(list)
        for c1, c2 in pairs:
            graph[c1].append(c2)
            graph[c2].append(c1)

        seen = set()
        idx, tmp = [], []

        def dfs(n):
            if n in seen:
                return

            seen.add(n)
            idx.append(n)
            tmp.append(s[n])
            for nx in graph[n]:
                dfs(nx)

        group = [w for w in s]
        for i in range(len(s)):
            if i in seen or i not in graph:
                continue
            idx.clear()
            tmp.clear()
            dfs(i)
            idx.sort()
            tmp.sort()
            for j in range(len(idx)):
                group[idx[j]] = tmp[j]

        return ''.join(group)

    def doit_disjoint(self, s: str, pairs: list) -> str:

        from collections import defaultdict
        parent = [i for i in range(len(s))]

        def find(i):
            while parent[i] != i:
                parent[i] = parent[parent[i]]
                i = parent[i]
            return parent[i]

        for c1, c2 in pairs:
            parent[find(c1)] = find(c2)

        letters = [w for w in s]
        indexes = defaultdict(list)
        tmp = defaultdict(list)

        for i, c in enumerate(parent):
            id = find(i)
            indexes[id].append(i)
            tmp[id].append(s[i])

        for k in indexes.keys():
            indexes[k].sort()
            tmp[k].sort()
            for i in range(len(indexes[k])):
                letters[indexes[k][i]] = tmp[k][i]

        return ''.join(letters)


if __name__ == '__main__':

    SmallestStringWithSwaps().doit_disjoint("dcab", [[0,3],[1,2],[0,2]])