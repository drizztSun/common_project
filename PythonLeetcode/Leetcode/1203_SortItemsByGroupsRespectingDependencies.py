"""
1203. Sort Items by Groups Respecting Dependencies

There are n items each belonging to zero or one of m groups where group[i] is the group that the i-th item belongs to
and it's equal to -1 if the i-th item belongs to no group. The items and the groups are zero indexed. A group can have no item belonging to it.

Return a sorted list of the items such that:

The items that belong to the same group are next to each other in the sorted list.
There are some relations between these items where beforeItems[i] is a list containing all the items that should come
before the i-th item in the sorted array (to the left of the i-th item).
Return any solution if there is more than one solution and return an empty list if there is no solution.



Example 1:

Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
Output: [6,3,4,1,5,2,0,7]

Example 2:

Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]]
Output: []
Explanation: This is the same as example 1 except that 4 needs to be before 6 in the sorted list.


Constraints:

1 <= m <= n <= 3*10^4
group.length == beforeItems.length == n
-1 <= group[i] <= m-1
0 <= beforeItems[i].length <= n-1
0 <= beforeItems[i][j] <= n-1
i != beforeItems[i][j]
beforeItems[i] does not contain duplicates elements.


"""
from collections import deque, defaultdict
from heapq import heappush, heappop


class SortItemsByDependency:

    """
    for case Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]

    Item        beforeItems        Group        BeforeGroups
    0                               2
    1               6               3               0
    2               5               1               1(x)
    3               6               0               0(x)
    4               3,6             0               0,0(x)
    5                               1
    6                               0
    7                               4

    for item's group is -1, we give it bigger group number (not equal to any known group number ) to each one
    then it becomes sort(groups) first, in the same group, sort(items)

    Algorithem
    topological sorting + backtracking (bad idea, hard to implement, because backtracking is DFS, topsort is BFS)
    topsort sorting of groups + topsort sorting of items


    """

    def doit_topsort(self, n: int, m: int, group: list, beforeItems: list) -> list:
        #
        for i in range(len(group)):
            if group[i] == -1:
                group[i] = m
                m += 1

        groupgraph, itemgraph = [[] for _ in range(m)], [[] for _ in range(n)]
        groupindegree, itemindegree = [0] * m, [0] * n

        for d in range(n):
            for c in beforeItems[d]:
                itemgraph[c].append(d)
                itemindegree[d] += 1
                if group[d] == group[c]:
                    continue
                groupgraph[group[c]].append(group[d])
                groupindegree[group[d]] += 1

        groupqueue = deque([i for i in range(m) if groupindegree[i] == 0])
        grouporder = {}
        order = 0
        while groupqueue:
            c = groupqueue.popleft()
            grouporder[c] = order
            order += 1
            for nc in groupgraph[c]:
                groupindegree[nc] -= 1
                if groupindegree[nc] == 0:
                    groupqueue.append(nc)


        if len(grouporder) < m:
            return []

        itemqueue, order = [], 0
        for i in range(n):
            if itemindegree[i] == 0:
                heappush(itemqueue, (grouporder[group[i]], order, i))
                order += 1

        res = []
        while itemqueue:

            c = heappop(itemqueue)
            res.append(c[2])

            for nc in itemgraph[c[2]]:

                itemindegree[nc] -= 1
                if itemindegree[nc] == 0:
                    heappush(itemqueue, (grouporder[group[nc]], order, nc))
                    order += 1

        return res if len(res) == n else []

    def sortItems(self, n: int, m: int, group: list, beforeItems: list) -> list:
        def topo_sort(graph, indegrees):
            result = []
            stack = [i for i, indegree in enumerate(indegrees) if indegree == 0]
            while stack:
                src = stack.pop()
                result.append(src)
                for dest in graph[src]:
                    indegrees[dest] -= 1
                    if indegrees[dest] == 0:
                        stack.append(dest)
            return result if len(result) == len(indegrees) else []

        for i, g in enumerate(group):
            if g == -1:
                group[i] = m
                m += 1

        item_graph = [[] for _ in range(n)]
        item_indegrees = [0] * n
        group_graph = [[] for _ in range(m)]
        group_indegrees = [0] * m

        for i in range(n):
            for dep in beforeItems[i]:
                item_graph[dep].append(i)
                item_indegrees[i] += 1
                if group[i] != group[dep]:
                    group_graph[group[dep]].append(group[i])
                    group_indegrees[group[i]] += 1

        item_order = topo_sort(item_graph, item_indegrees)
        group_order = topo_sort(group_graph, group_indegrees)

        if not item_order or not group_order:
            return []

        order_within_groups = defaultdict(list)
        for item in item_order:
            order_within_groups[group[item]].append(item)

        result = []
        for g in group_order:
            result += order_within_groups[g]

        return result


if __name__ == '__main__':

    SortItemsByDependency().doit_topsort(5, 3, [0, 0, 2, 1, 0], [[3], [], [], [], [1, 3, 2]])

    SortItemsByDependency().doit_topsort(n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]])

    SortItemsByDependency().doit_topsort(n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]])


