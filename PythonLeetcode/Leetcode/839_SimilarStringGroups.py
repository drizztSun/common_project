# 839. Similar String Groups

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
class NumSimilarGroups:
    
    # <Union-Find>
    def doit(self, A):
        """
        :type A: List[str]
        :rtype: int
        """
        import itertools
        parent = {x: x for x in A}
        self.count = len(A)
        N, M = len(A), len(A[0])

        def Find(i):
            if parent[i] != i:
                parent[i] = Find(parent[i])
            return parent[i]

        def Union(i, j):
            i, j = Find(i), Find(j)
            if i != j:
                parent[i] = j
                self.count -= 1
                return True
            return False

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

        return self.count

        
if __name__ == "__main__":

    res = NumSimilarGroups().doit(["koqnn","knnqo","noqnk","nqkon"])

    res = NumSimilarGroups().doit(["tars","rats","arts","star"])

    pass


            