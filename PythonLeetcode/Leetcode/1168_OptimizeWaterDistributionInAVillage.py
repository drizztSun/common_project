"""
1168. Optimize Water Distribution in a Village

There are n houses in a village. We want to supply water for all the houses by building wells and laying pipes.

For each house i, we can either build a well inside it directly with cost wells[i], or pipe in water from another well to it.
The costs to lay pipes between houses are given by the array pipes, where each pipes[i] = [house1, house2, cost]
represents the cost to connect house1 and house2 together using a pipe. Connections are bidirectional.

Find the minimum total cost to supply water to all houses.



Example 1:



Input: n = 3, wells = [1,2,2], pipes = [[1,2,1],[2,3,1]]
Output: 3
Explanation:
The image shows the costs of connecting houses using pipes.
The best strategy is to build a well in the first house with cost 1 and connect the other houses to it with cost 2 so the total cost is 3.


Constraints:

1 <= n <= 10000
wells.length == n
0 <= wells[i] <= 10^5
1 <= pipes.length <= 10000
1 <= pipes[i][0], pipes[i][1] <= n
0 <= pipes[i][2] <= 10^5
pipes[i][0] != pipes[i][1]

"""


class OptimizeWaterDistributionVillage:

    """
    This solution uses Group by ID which is my work-around to union-find problems.
    In most cases (like here) Group by ID performs better than union-find.
    The end result is similar to the result from Kruskal's algorithm after path compression.
    But ~I think~ Group by ID is much easier to implement.

    Here are a few other problems where Group by ID performs better than union-find:

    1061. lexicographically-smallest-equivalent-string (100% runtime and memory)
    0547. friend-circles (100% runtime) # if this is your first time seeing this method, start here, this is the easiest problem to use it on
    1319. number-of-operations-to-make-network-connected (100% runtime)
    0737. sentence-similarity-ii (100% runtime, 80% memory)
    1579. remove-max-number-of-edges-to-keep-graph-fully-traversable (100% runtime)
    0721. accounts-merge (99% runtime and 97% memory)
    1258. synonymous-sentences (97.5% runtime 75% memory)
    1101. the-earliest-moment-when-everyone-become-friends

    """
    def doit_kruskal(self, n: int, wells: 'list', pipes: 'list') -> int:

        # 1. Treat each well like a pipe to house number 0 (props to @mhelvens for this awesome idea)
        for i, c in enumerate(wells, 1):
            pipes.append([0, i, c])

        # 2. Sort pipes according to the cost to lay the pipe
        pipes.sort(key=lambda p: p[2])

        # 3. Use group by id to create a Minimum Spanning Tree
        group_id = 0
        group = {}
        node_id = {}
        res = 0

        for a, b, c in pipes:

            # 3.1 If house a and house b are in a group:
            if (a in node_id) and (b in node_id):
                # House a and house b are in the same group, no pipe needed.
                if node_id[a] == node_id[b]:
                    continue
                # House a and house b are in different groups, merge the two groups (at the cost of 1 pipe).
                else:
                    target_id, obsolete_id = sorted((node_id[a], node_id[b]))
                    for node in group[obsolete_id]:
                        node_id[node] = target_id
                    group[target_id] |= group[obsolete_id]
                    del group[obsolete_id]
                    res += c

            # 3.2 If house a OR house b are in a group, add the new house into the group (at the cost of 1 pipe).
            elif (a in node_id) or (b in node_id):
                a, b = (a, b) if a in node_id else (b, a)
                target_id = node_id[a]
                group[target_id] |= set([b])
                node_id[b] = target_id
                res += c

            # 3.3 If neither house a or house b has a group, make a new group just for them (at the cost of 1 pipe).
            else:
                group[group_id] = set([a, b])
                node_id[a] = node_id[b] = group_id
                group_id += 1
                res += c

        return res


if __name__ == '__main__':

    OptimizeWaterDistributionVillage().doit(n = 3, wells = [1,2,2], pipes = [[1,2,1],[2,3,1]])
