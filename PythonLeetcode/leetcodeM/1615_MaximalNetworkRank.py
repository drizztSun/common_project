"""
1615. Maximal Network Rank

There is an infrastructure of n cities with some number of roads connecting these cities. Each roads[i] = [ai, bi] indicates
that there is a bidirectional road between cities ai and bi.

The network rank of two different cities is defined as the total number of directly connected roads to either city.
If a road is directly connected to both cities, it is only counted once.

The maximal network rank of the infrastructure is the maximum network rank of all pairs of different cities.

Given the integer n and the array roads, return the maximal network rank of the entire infrastructure.



Example 1:



Input: n = 4, roads = [[0,1],[0,3],[1,2],[1,3]]
Output: 4
Explanation: The network rank of cities 0 and 1 is 4 as there are 4 roads that are connected to either 0 or 1. The road between 0 and 1 is only counted once.
Example 2:



Input: n = 5, roads = [[0,1],[0,3],[1,2],[1,3],[2,3],[2,4]]
Output: 5
Explanation: There are 5 roads that are connected to cities 1 or 2.
Example 3:

Input: n = 8, roads = [[0,1],[1,2],[2,3],[2,4],[5,6],[5,7]]
Output: 5
Explanation: The network rank of 2 and 5 is 5. Notice that all the cities do not have to be connected.


Constraints:

2 <= n <= 100
0 <= roads.length <= n * (n - 1) / 2
roads[i].length == 2
0 <= ai, bi <= n-1
ai != bi
Each pair of cities has at most one road connecting them.



"""


class MaximalNetworkRank:

    """
        How many different edges Two nodes has.
    """

    def doit_(self, N: int, roads: list) -> int:

        g = [[False for _ in range(N)] for _ in range(N)]
        ans = 0

        for x, y in roads:
            g[x][y] = g[y][x] = True

        for i in range(N):
            for j in range(i + 1, N):

                current = 0

                for k in range(N):
                    if k != i and k != j:
                        if g[i][k]:
                            current += 1
                        if g[j][k]:
                            current += 1

                if g[i][j]:
                    current += 1

                ans = max(ans, current)

        return ans

    def doit_(self, n: int, roads: list) -> int:
        from collections import defaultdict

        r = [0] * n
        con = defaultdict(set)
        for s, e in roads:
            r[s] += 1
            r[e] += 1
            con[s].add(e)
            con[e].add(s)

        # sort node, by degree
        r = [[v, i] for i, v in enumerate(r)]
        r.sort()

        # get the ones with most degrees
        br = [[i, x] for x, i in r if x == r[-1][0]]

        if len(br) == 1:
            # if there is one, put with second most degrees nodes.
            br += [[i, x] for x, i in r if x == r[-2][0]]
            iran = 1
        else:
            # two more ones has most degrees
            iran = len(br)

        # candidate one, supposed they are connected
        re = br[0][1] + br[1][1] - 1

        for i in range(iran):
            for j in range(i+1, len(br)):
                # if there are two not connected, plus one
                if br[i][0] not in con[br[j][0]]:
                    return re+1
        return re