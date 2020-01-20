# 886. Possible Bipartition

# Given a set of N people (numbered 1, 2, ..., N), we would like to split everyone into two groups of any size.

# Each person may dislike some other people, and they should not go into the same group.

# Formally, if dislikes[i] = [a, b], it means it is not allowed to put the people numbered a and b into the same group.

# Return true if and only if it is possible to split everyone into two groups in this way.


# Example 1:

# Input: N = 4, dislikes = [[1,2],[1,3],[2,4]]
# Output: true
# Explanation: group1 [1,4], group2 [2,3]

# Example 2:

# Input: N = 3, dislikes = [[1,2],[1,3],[2,3]]
# Output: false

# Example 3:

# Input: N = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
# Output: false


# Note:

# 1 <= N <= 2000
# 0 <= dislikes.length <= 10000
# 1 <= dislikes[i][j] <= N
# dislikes[i][0] < dislikes[i][1]
# There does not exist i != j for which dislikes[i] == dislikes[j].

class PossibleBipartition:

    """
    Approach 1: Depth-First Search
    Intuition

    It's natural to try to assign everyone to a group. Let's say people in the first group are red, and people in the second group are blue.

    If the first person is red, anyone disliked by this person must be blue. Then, anyone disliked by a blue person is red,
    then anyone disliked by a red person is blue, and so on.

    If at any point there is a conflict, the task is impossible, as every step logically follows from the first step.
    If there isn't a conflict, then the coloring was valid, so the answer would be true.

    Algorithm

    Consider the graph on N people formed by the given "dislike" edges. We want to check that each connected component of this graph is bipartite.

    For each connected component, we can check whether it is bipartite by just trying to coloring it with two colors.
    How to do this is as follows: color any node red, then all of it's neighbors blue, then all of those neighbors red, and so on.
    If we ever color a red node blue (or a blue node red), then we've reached a conflict.

    Complexity Analysis
        Time Complexity: O(N + E)O(N+E), where EE is the length of dislikes.
        Space Complexity: O(N + E)O(N+E).
    """

    def doit(self, N, dislikes):

        graph = [[] for _ in range(N+1)]
        for s, e in dislikes:
            graph[s].append(e)
            graph[e].append(s)

        color = {}

        def dfs(n, c=0):
            if n in color:
                return color[n] == c
            color[n] = c

            return all(dfs(e, c ^ 1) for e in graph[n])

        return all(dfs(n) for n in range(1, N+1) if n not in color)

    def doit(self, N, dislikes):

        enemies = [[] for _ in range(N + 1)]

        for dislike in dislikes:
            enemies[dislike[0]].append(dislike[1])
            enemies[dislike[1]].append(dislike[0])

        colors = [0] * (N + 1)
        for person in range(1, N + 1):
            if colors[person]:
                continue

            stack = [person]
            colors[person] = 1
            while stack:
                p = stack.pop()
                for enemy in enemies[p]:
                    if colors[enemy] == colors[p]:
                        return False
                    if not colors[enemy]:
                        colors[enemy] = 1 if colors[p] == 2 else 2
                        stack.append(enemy)
        return True


if __name__ == '__main__':

    res = PossibleBipartition().doit(
        N=4, dislikes=[[1, 2], [1, 3], [2, 4]])  # true

    res = PossibleBipartition().doit(
        N=3, dislikes=[[1, 2], [1, 3], [2, 3]])  # false

    res = PossibleBipartition().doit(
        N=5, dislikes=[[1, 2], [2, 3], [3, 4], [4, 5], [1, 5]])  # false

    pass
