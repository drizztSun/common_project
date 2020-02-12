# 997. Find the Town Judge

# In a town, there are N people labelled from 1 to N.  There is a rumor that one of these people is secretly the town judge.

# If the town judge exists, then:

# The town judge trusts nobody.
# Everybody (except for the town judge) trusts the town judge.
# There is exactly one person that satisfies properties 1 and 2.
# You are given trust, an array of pairs trust[i] = [a, b] representing that the person labelled a trusts the person labelled b.

# If the town judge exists and can be identified, return the label of the town judge.  Otherwise, return -1.


# Example 1:

# Input: N = 2, trust = [[1,2]]
# Output: 2

# Example 2:

# Input: N = 3, trust = [[1,3],[2,3]]
# Output: 3

# Example 3:

# Input: N = 3, trust = [[1,3],[2,3],[3,1]]
# Output: -1

# Example 4:

# Input: N = 3, trust = [[1,2],[2,3]]
# Output: -1

# Example 5:

# Input: N = 4, trust = [[1,3],[1,4],[2,3],[2,4],[4,3]]
# Output: 3


# Note:

# 1 <= N <= 1000
# trust.length <= 10000
# trust[i] are all different
# trust[i][0] != trust[i][1]
# 1 <= trust[i][0], trust[i][1] <= N

class FindJudge:

    def doit(self, N, trust):

        g = [0] * (N + 1)

        for p, j in trust:
            g[j] += 1
            g[p] -= 1

        for i in range(1, N + 1):
            if g[i] == N-1:
                return i

        return -1

    """
    We create an inDegree array that tracks the amount of incoming "trusts" for the corresponding people.
    The index of the array will keep track of the current person.
    So inDegree[1] == 2, indicates that person 1 has two people that "trust" them.
    If an element is equal to N-1 then we know its receiving "trust" from the entire town.
    We then proceed to check if its has any outgoing edges by checking if the adjList is "null" at the current vertex.
    """

    def doit(self, N, trust):
        from collections import defaultdict
        if not trust:
            return -1

        g = defaultdict(list)

        for p, j in trust:
            g[p].append(j)

        inDegree = [0] * (N+1)

        for n in g:
            for v in g[n]:

                inDegree[v] += 1

        for i in range(1, N+1):
            if inDegree[i] == N-1 and not g[i]:
                return i

        return -1


if __name__ == '__main__':

    res = FindJudge().doit(N=2, trust=[[1, 2]])

    res = FindJudge().doit(N=3, trust=[[1, 3], [2, 3]])

    res = FindJudge().doit(N=3, trust=[[1, 3], [2, 3], [3, 1]])

    res = FindJudge().doit(N=3, trust=[[1, 2], [2, 3]])

    res = FindJudge().doit(N=4, trust=[[1, 3], [1, 4], [2, 3], [2, 4], [4, 3]])

    pass
