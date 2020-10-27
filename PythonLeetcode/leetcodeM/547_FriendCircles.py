"""
547. Friend Circles

There are N students in a class. Some of them are friends, while some are not. Their friendship is transitive in nature.
For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C.
And we defined a friend circle is a group of students who are direct or indirect friends.

Given a N*N matrix M representing the friend relationship between students in the class.
If M[i][j] = 1, then the ith and jth students are direct friends with each other, otherwise not.
And you have to output the total number of friend circles among all the students.

Example 1:

Input:
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend circle.
The 2nd student himself is in a friend circle. So return 2.


Example 2:

Input:
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends,
so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.



Constraints:

1 <= N <= 200
M[i][i] == 1
M[i][j] == M[j][i]

"""


class FindCircleNum:

    """
    Approach #1 Using Depth First Search[Accepted]
    Algorithm

    The given matrix can be viewed as the Adjacency Matrix of a graph. By viewing the matrix in such a manner,
    our problem reduces to the problem of finding the number of connected components in an undirected graph.
    In order to understand the above statement, consider the example matrix below:

    M= [1 1 0 0 0 0

        1 1 0 0 0 0

        0 0 1 1 1 0

        0 0 1 1 0 0

        0 0 1 0 1 0

        0 0 0 0 0 1]

    If we view this matrix M as the adjancency matrix of a graph, the following graph is formed:
    In this graph, the node numbers represent the indices in the matrix M and an edge exists between the nodes numbered ii and jj, if there is a 1 at the corresponding M[i][j]M[i][j].

    In order to find the number of connected components in an undirected graph, one of the simplest methods is to make use of Depth First Search starting from every node.
    We make use of visitedvisited array of size NN(MM is of size NxNNxN).
    This visited[i]visited[i] element is used to indicate that the i^{th} node has already been visited while undergoing a Depth First Search from some node.

    To undergo DFS, we pick up a node and visit all its directly connected nodes.
    But, as soon as we visit any of those nodes, we recursively apply the same process to them as well.
    Thus, we try to go as deeper into the levels of the graph as possible starting from a current node first, leaving the other direct neighbour nodes to be visited later on.

    The depth first search for an arbitrary graph is shown below:
    From the graph, we can see that the components which are connected can be reached starting from any single node of the connected group.
    Thus, to find the number of connected components, we start from every node which isn't visited right now and apply DFS starting with it.
    We increment the countcount of connected components for every new starting node.

    Complexity Analysis

    Time complexity : O(n^2). The complete matrix of size n^2 is traversed.

    Space complexity : O(n). visited array of size nn is used.

    """
    def doit_dfs(self, M):
        """
        :type M: List[List[int]]
        :rtype: int
        """
        circles = 0
        visited = set()
        l = len(M)  # number of people

        # breadth-first-search from 0, removed visited in sets, breadth first search again
        for i in range(l):
            if i not in visited:
                visited.add(i)
                circles += 1

                q = [i]  # BFS from 0
                while q:
                    node = q.pop()  # who do we need to check their friends of?
                    for j in range(l):
                        if j not in visited and M[node][j]:  # friends with node
                            q.append(j)
                            visited.add(j)
        return circles


    """
    Approach #2 Using Breadth First Search[Accepted]
    Algorithm
    
    As discussed in the above method, if we view the given matrix as an adjacency matrix of a graph, we can use graph algorithms easily to find the number of connected components.
    This approach makes use of Breadth First Search for a graph.
    
    In case of Breadth First Search, we start from a particular node and visit all its directly connected nodes first. 
    After all the direct neighbours have been visited, we apply the same process to the neighbour nodes as well. 
    Thus, we exhaust the nodes of a graph on a level by level basis. An example of Breadth First Search is shown below:
    
    Complexity Analysis

    Time complexity : O(n^2). The complete matrix of size n^2 is traversed.
    Space complexity : O(n). A queue and visitedvisited array of size nn is used.
    """
    def doit_dfs(self, M):
        """
        :type M: List[List[int]]
        :rtype: int
        """
        from collections import deque

        circles = 0
        visited = set()
        N = len(M)

        for i in range(N):

            if i not in visited:
                visited.add(i)
                qu = deque([i])

                while qu:
                    c = qu.popleft()
                    for j in range(N):
                        if M[c][j] == 1 and j not in visited:
                            qu.append(j)
                            visited.add(j)
                circles += 1

        return circles


    def doit_disjoint_2(self, M):
        """
        :type M: List[List[int]]
        :rtype: int
        """
        def parent(i):
            if circle[i] != i:
                circle[i] = parent(circle[i])
            return circle[i]

        circle = [x for x in range(len(M))]

        for i in range(len(M)):

            for j in range(i+1, len(M)):

                if M[i][j] == 1 and parent(i) != parent(j):
                    circle[parent(j)] = parent(i)

        return sum(1 for i in range(len(circle)) if i == circle[i])

    def doit_disjoint(self, M):

        n = len(M)
        groups = [i for i in range(n)]

        def parent(i):
            if i != groups[i]:
                groups[i] = parent(groups[i])
            return groups[i]

        def union(i, j):
            pi, pj = parent(i), parent(j)
            if pi != pj:
                groups[pj] = pi

        for i in range(n):
            for j in range(i+1, n):
                if M[i][j] == 1:
                    union(i, j)

        #return len(set(groups))
        return sum(1 for i in range(len(groups)) if i == groups[i])


if __name__ == '__main__':

    FindCircleNum().doit_disjoint([[1,1,0],
                                 [1,1,0],
                                 [0,0,1]])

    FindCircleNum().doit_disjoint([[1,1,0],
                                 [1,1,1],
                                 [0,1,1]])

    FindCircleNum().doit_disjoint_2([[1,0,0,1],
                                   [0,1,1,0],
                                   [0,1,1,1],
                                   [1,0,1,1]])
