"""
839. Similar String Groups

# Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y.

# For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar,
# but "star" is not similar to "tars", "rats", or "arts".

# Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.

# Notice that "tars" and "arts" are in the same group even though they are not similar.
# Formally, each group is such that a word is in the group if and only if it is similar
# to at least one other word in the group.

# We are given a list A of unique strings.  Every string in A is an anagram of every other string in A.
# How many groups are there?

# Example 1:

# Input: ["tars","rats","arts","star"]
# Output: 2
# Note:

# A.length <= 2000
# A[i].length <= 1000
# A.length * A[i].length <= 20000
# All words in A consist of lowercase letters only.
# All words in A have the same length and are anagrams of each other.
# The judging time limit has been increased for this question.



# Explanation
# Union Find solution. Also I have a sub function similar to compare two string.
# Tricky in A.length * A[i].length <= 20000
# For short A, just O(N^2) brute force on every two word. O(MN^2) in total.
# For short words, check all possible similar words. O(NM^2) in total.

"""
import itertools
import collections


class SimilarStringGroups:

    """
    Approach #1: Piecewise [Accepted]
    Intuition

    Let W = A[0].length. It is clear that we can determine in O(W)O(W) time, whether two words from A are similar.

    One attempt is a standard kind of brute force: for each pair of words, let's draw an edge between these words if they are similar. We can do this in O(N^2 W)O(N
    2
     W) time. After, finding the connected components can be done in O(N^2)O(N
    2
     ) time naively (each node may have up to N-1N−1 edges), (or O(N)O(N) with a union-find structure.) The total complexity is O(N^2 W)O(N
    2
     W).

    Another attempt is to enumerate all neighbors of a word. A word has up to \binom{W}{2}(
    2
    W
    ​
     ) neighbors, and if that neighbor is itself a given word, we know that word and neighbor are connected by an edge. In this way, we can build the graph in O(N W^3)O(NW
    3
     ) time, and again take O(N^2)O(N
    2
     ) or O(N)O(N) time to analyze the number of connected components.

    One insight is that between these two approaches, we can choose which approach works better. If we have very few words, we want to use the first approach; if we have very short words, we want to use the second approach. We'll piecewise add these two approaches (with complexity O(N^2 W)O(N
    2
     W) and O(N W^3)O(NW
    3
     )), to create an approach with O(NW\min(N, W^2))O(NWmin(N,W
    2
     )) complexity.

    Algorithm

    We will build some underlying graph with N nodes, where nodes i and j are connected if and only if A[i] is similar to A[j], then look at the number of connected components.

    There are a few challenges involved in this problem, but each challenge is relatively straightforward.

    Use a helper function similar(word1, word2) that is true if and only if two given words are similar.

    Enumerate all neighbors of a word, and discover when it is equal to a given word.

    Use either a union-find structure or a depth-first search, to calculate the number of connected components of the underlying graph. We've showcased a union-find structure in this solution, with notes of a depth-first search in the comments.

    For more details, see the implementations below.

    Complexity Analysis

    Time Complexity: O(NW \min(N, W^2))O(NWmin(N,W
    2
     )), where NN is the length of A, and WW is the length of each given word.

    Space Complexity: O(NW^3)O(NW
    3
     ). If N < W^2N<W
    2
     , the space complexity is O(N)O(N). Otherwise, the space complexity is O(NW^3)O(NW
    3
     ): for each of NW^2NW
    2
      neighbors we store a word of length WW. (Plus, we store O(NW^2)O(NW
    2
     ) node indices ("buckets") which is dominated by the O(NW^3)O(NW
    3
     ) term.) Because W^2 <= NW
    2
     <=N in this case, we could also write the space complexity as O(N^2 W)O(N
    2
     W).

    """

    class DSU:
        def __init__(self, N):
            self.par = list(range(N))

        def find(self, x):
            if self.par[x] != x:
                self.par[x] = self.find(self.par[x])
            return self.par[x]

        def union(self, x, y):
            self.par[self.find(x)] = self.find(y)

    def doit_disjoint(self, A):
        N, W = len(A), len(A[0])

        def similar(word1, word2):
            diff = 0
            for x, y in zip(word1, word2):
                if x != y:
                    diff += 1
            return diff <= 2

        dsu = SimilarStringGroups.DSU(N)

        if N < W * W:  # If few words, then check for pairwise similarity: O(N^2 W)
            for (i1, word1), (i2, word2) in itertools.combinations(enumerate(A), 2):
                if similar(word1, word2):
                    dsu.union(i1, i2)

        else:  # If short words, check all neighbors: O(N W^3)
            buckets = collections.defaultdict(set)
            for i, word in enumerate(A):
                L = list(word)
                for j0, j1 in itertools.combinations(range(W), 2):
                    L[j0], L[j1] = L[j1], L[j0]
                    buckets["".join(L)].add(i)
                    L[j0], L[j1] = L[j1], L[j0]

            for i1, word in enumerate(A):
                for i2 in buckets[word]:
                    dsu.union(i1, i2)

        return sum(dsu.par[x] == x for x in range(N))

    # <Union-Find>
    def doit(self, A):
        """
        :type A: List[str]
        :rtype: int
        """
        import itertools
        parent = {x: x for x in A}
        A = list(set(A))
        count = len(A)
        N, M = len(A), len(A[0])

        def Find(i):
            if parent[i] != i:
                parent[i] = Find(parent[i])
            return parent[i]

        def Union(i, j):
            nonlocal count
            i, j = Find(i), Find(j)
            if i != j:
                parent[i] = j
                count -= 1

        def similar(a, b):
            return sum(i != j for i, j in zip(a, b)) == 2

        if N < M:
            for i, j in itertools.combinations(A, 2):
                if similar(i, j):
                    Union(i, j)
        else:
            for x in A:
                for i, j in itertools.combinations(range(M), 2):
                    y = x[:i] + x[j] + x[i+1:j] + x[i] + x[j+1:]
                    if y in parent:
                        Union(x, y)
        return count

    """
    First create a Graph by creating bidirectional edge between two strings if they are similar under given constraint.
    Then the problem is simple, just count the number of connected components by performing dfs.
    """
    def doit_dfs(self, strs: list) -> int:
        count = 0
        n = len(strs);
        vis = [0] * n

        def similar(s, a):
            A = []
            for i in range(len(s)):
                if s[i] != a[i]:
                    A.append((s[i], a[i]))
                if len(A) > 2:
                    return False
            return len(A) == 2 and A[0] == A[1][::-1]

        def dfs(i):
            for j in G[i]:
                if vis[j] == 0:  # perform dfs if not visited
                    vis[j] = 1
                    dfs(j)

        G = collections.defaultdict(list)  # Graph
        for i in range(n):
            s = strs[i]
            for j in range(i + 1, n):
                if s == strs[j] or similar(s, strs[j]):  # if ith string and jth string are similar connect two strings
                    G[i].append(j)
                    G[j].append(i)

        for i in range(n):
            if vis[i] == 0:  # perform dfs if not visited
                vis[i] = 1
                dfs(i)
                count += 1  # new component found so increment count
        return count


from collections import Counter


class UnionFind:
    def __init__(self, n):
        self.root = [i for i in range(n)]

    def find(self, node):
        if node != self.root[node]:
            self.root[node] = self.find(self.root[node])
        return self.root[node]

    def union(self, node1, node2):
        p1 = self.find(node1)
        p2 = self.find(node2)
        if p1 != p2:
            self.root[min(p1, p2)] = self.root[max(p1, p2)]
            return True
        return False

    def rootAll(self):
        for i in range(len(self.root)):
            self.find(i)


class Solution:
    def numSimilarGroups(self, A: list) -> int:

        def isSimilar(a, b):
            if len(a) != len(b): return False

            count = 0
            k = -1
            w = -1
            for i in range(len(a)):
                if a[i] != b[i]:
                    count += 1
                    if count > 2:
                        return False
                    if count == 1:
                        k = i
                    if count == 2:
                        w = i

            return a[k] == b[w] and a[w] == b[k]

        uf = UnionFind(len(A))

        for i in range(len(A)):
            for j in range(i - 1, -1, -1):
                if isSimilar(A[i], A[j]):
                    uf.union(i, j)

        uf.rootAll()
        return len(Counter(uf.root))


if __name__ == "__main__":

    res = SimilarStringGroups().doit(["abs", "abs", "abs", "abs"])

    res = SimilarStringGroups().doit(["koqnn","knnqo","noqnk","nqkon"])

    res = SimilarStringGroups().doit(["tars","rats","arts","star"])