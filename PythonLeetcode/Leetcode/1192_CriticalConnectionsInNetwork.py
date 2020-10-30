"""
1192. Critical Connections in a Network

There are n servers numbered from 0 to n-1 connected by undirected server-to-server connections forming a network
where connections[i] = [a, b] represents a connection between servers a and b. Any server can reach any other server directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some server unable to reach some other server.

Return all critical connections in the network in any order.

Example 1:


Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.


Constraints:

1 <= n <= 10^5
n-1 <= connections.length <= 10^5
connections[i][0] != connections[i][1]
There are no repeated connections.


"""


class CriticalConnections:


    """
    if an edge is on a circle, that will not be a critical section
    Use DFS to find the possible circle of k nodes, and rank each node to see if there is low rank node, old node could be see.
    """

    def doit_dfs(self, n: int, connections):

        def dfs(cur: int, parent: int, level: int, res: list):

            jump[cur] = level + 1

            for child in graph[cur]:

                if child == parent:
                    continue
                elif jump[child] == -1:
                    jump[cur] = min(jump[cur], dfs(child, cur, level+1, res))
                elif jump[child] < jump[cur]:
                    jump[cur] = jump[child]

            if jump[cur] == level + 1 and cur != 0:
                res.append([parent, cur])

            return jump[cur]

        graph = [[] for _ in range(n)]
        jump = [-1] * n
        res = []
        for c in connections:
            graph[c[0]].append(c[1])
            graph[c[1]].append(c[0])

        dfs(0, -1, -1, res)
        return res


if __name__ == '__main__':

    CriticalConnections().doit_dfs(n = 4, connections = [[0,1],[1,2],[2,0],[1,3]])

