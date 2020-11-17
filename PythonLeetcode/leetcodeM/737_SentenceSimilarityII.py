"""
737. Sentence Similarity II

Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.

For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].

Note that the similarity relation is transitive. For example, if "great" and "good" are similar, and "fine" and "good" are similar, then "great" and "fine" are similar.

Similarity is also symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.

Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are no specified similar word pairs.

Finally, sentences can only be similar if they have the same number of words. So a sentence like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].

Note:

The length of words1 and words2 will not exceed 1000.
The length of pairs will not exceed 2000.
The length of each pairs[i] will be 2.
The length of each words[i] and pairs[i][j] will be in the range [1, 20].


"""


class SentenceSimilarityII:

    def doit_disjoint(self, words1: list, words2: list, pairs: list) -> bool:

        if len(words1) != len(words2):
            return False

        parents = {}

        def find(a):

            if a not in parents:
                parents[a] = a

            while parents[a] != a:
                parents[a] = parents[parents[a]]
                a = parents[a]

            return parents[a]

        def union(a, b):
            pa = find(a)
            pb = find(b)

            if pa != pb:
                parents[pa] = pb

        for c1, c2 in pairs:
            union(c1, c2)

        for w1, w2 in zip(words1, words2):
            if find(w1) != find(w2):
                return False

        return True

    """
    Approach #1: Depth-First Search [Accepted]
    Intuition
    
    Two words are similar if they are the same, or there is a path connecting them from edges represented by pairs.
    
    We can check whether this path exists by performing a depth-first search from a word and seeing if we reach the other word. The search is performed on the underlying graph specified by the edges in pairs.
    
    Algorithm
    
    We start by building our graph from the edges in pairs.
    
    The specific algorithm we go for is an iterative depth-first search. The implementation we go for is a typical "visitor pattern": when searching whether there is a path from w1 = words1[i] to w2 = words2[i], 
    stack will contain all the nodes that are queued up for processing, while seen will be all the nodes that have been queued for processing (whether they have been processed or not).
    
    Complexity Analysis

    Time Complexity: O(NP)O(NP), where NN is the maximum length of words1 and words2, and PP is the length of pairs. Each of NN searches could search the entire graph.
    
    Space Complexity: O(P)O(P), the size of pairs.
    """
    def doit_dfs(self, words1, words2, pairs):
        from collections import defaultdict
        if len(words1) != len(words2):
            return False

        graph = defaultdict(list)
        for w1, w2 in pairs:
            graph[w1].append(w2)
            graph[w2].append(w1)

        for w1, w2 in zip(words1, words2):
            stack, seen = [w1], {w1}
            while stack:
                word = stack.pop()
                if word == w2:
                    break
                for nei in graph[word]:
                    if nei not in seen:
                        seen.add(nei)
                        stack.append(nei)
            else:
                return False
        return True

    """
    Approach #2: Union-Find [Accepted]
    Intuition
    
    As in Approach #1, we want to know if there is path connecting two words from edges represented by pairs.
    
    Our problem comes down to finding the connected components of a graph. This is a natural fit for a Disjoint Set Union (DSU) structure.
    
    Algorithm
    
    Draw edges between words if they are similar. For easier interoperability between our DSU template, we will map each word to some integer ix = index[word]. Then, dsu.find(ix) will tell us a unique id representing what component that word is in.
    
    For more information on DSU, please look at Approach #2 in the article here. For brevity, the solutions showcased below do not use union-by-rank.
    
    After putting each word in pairs into our DSU template, we check successive pairs of words w1, w2 = words1[i], words2[i]. We require that w1 == w2, or w1 and w2 are in the same component. This is easily checked using dsu.find.


    """

    class DSU:
        def __init__(self, N):
            self.par = range(N)

        def find(self, x):
            if self.par[x] != x:
                self.par[x] = self.find(self.par[x])
            return self.par[x]

        def union(self, x, y):
            self.par[self.find(x)] = self.find(y)

    def doit_disjoint_1(self, words1, words2, pairs):
        import itertools

        if len(words1) != len(words2):
            return False

        index = {}
        count = itertools.count()
        dsu = SentenceSimilarityII.DSU(2 * len(pairs))
        for pair in pairs:
            for p in pair:
                if p not in index:
                    index[p] = next(count)
            dsu.union(index[pair[0]], index[pair[1]])

        return all(w1 == w2 or
                   w1 in index and w2 in index and
                   dsu.find(index[w1]) == dsu.find(index[w2])
                   for w1, w2 in zip(words1, words2))


if __name__ == '__main__':

    SentenceSimilarityII().doit(["great","acting","skills"], ["fine","drama","talent"], [["great","good"],["fine","good"],["drama","acting"],["skills","talent"]])