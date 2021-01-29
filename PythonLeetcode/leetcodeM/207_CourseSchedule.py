"""
207. Course Schedule

There are a total of numCourses courses you have to take, labeled from 0 to numCourses-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?



Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take.
             To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take.
             To take course 1 you should have finished course 0, and to take course 0 you should
             also have finished course 1. So it is impossible.


Constraints:

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.
1 <= numCourses <= 10^5

"""


class CourseScheduleI:

    def doit_topsort(self, numCourses: int, prerequisites: list) -> bool:
        from collections import deque
        
        g = [set() for _ in range(numCourses)]
        indegree = [0 for _ in range(numCourses)]

        for c in prerequisites:
            g[c[1]].add(c[0])
            indegree[c[0]] += 1

        q = deque([i for i in range(numCourses) if indegree[i] == 0])

        while q:
            c = q.popleft()

            for n in g[c]:
                indegree[n] -= 1
                if indegree[n] == 0:
                    q.append(n)

        return all(indegree[i] == 0 for i in range(numCourses))

    def doit_topsort_1(self, numCourses: int, prerequisites: list) -> bool:

        #visited is not required, because it is top graph, when edge from zero.
        from collections import deque
        g = [set() for _ in range(numCourses)]
        indegree = [0 for _ in range(numCourses)]

        for c in prerequisites:
            g[c[1]].add(c[0])
            indegree[c[0]] += 1

        q = deque([i for i in range(numCourses) if indegree[i] == 0])
        visited = set(q)
        while q:
            c = q.popleft()
            for n in g[c]:
                indegree[n] -= 1
                if indegree[n] == 0 and n not in visited:
                    q.append(n)
                    visited.add(n)

        return len(visited) == numCourses

    def doit_backtracking(self, numCourses, prerequisites):
        """
        :type numCourses: int
        :type prerequisites: List[List[int]]
        :rtype: bool
        """
        def isCyclic(currCourse, courseDict, path):
            """
            backtracking method to check that no cycle would be formed starting from currCourse
            """
            if path[currCourse]:
                # come across a previously visited node, i.e. detect the cycle
                return True

            # before backtracking, mark the node in the path
            path[currCourse] = True

            # backtracking
            ret = False
            for child in courseDict[currCourse]:
                ret = isCyclic(child, courseDict, path)
                if ret:
                    break

            # after backtracking, remove the node from the path
            path[currCourse] = False
            return ret

        from collections import defaultdict
        courseDict = defaultdict(list)

        for relation in prerequisites:
            nextCourse, prevCourse = relation[0], relation[1]
            courseDict[prevCourse].append(nextCourse)

        path = [False] * numCourses
        for currCourse in range(numCourses):
            if isCyclic(currCourse, courseDict, path):
                return False

        return True

    def doit_dfs(self, numCourses, prerequisites):
        """
        :type numCourses: int
        :type prerequisites: List[List[int]]
        :rtype: bool
        """

        def isCyclic(currCourse, courseDict, checked, path):
            """   """
            # 1). bottom-cases
            if checked[currCourse]:
                # this node has been checked, no cycle would be formed with this node.
                return False
            if path[currCourse]:
                # came across a marked node in the path, cyclic !
                return True

            # 2). postorder DFS on the children nodes
            # mark the node in the path
            path[currCourse] = True

            ret = False
            # postorder DFS, to visit all its children first.
            for child in courseDict[currCourse]:
                ret = isCyclic(child, courseDict, checked, path)
                if ret:
                    break

            # 3). after the visits of children, we come back to process the node itself
            # remove the node from the path
            path[currCourse] = False

            # Now that we've visited the nodes in the downstream,
            #   we complete the check of this node.
            checked[currCourse] = True
            return ret

        from collections import defaultdict
        courseDict = defaultdict(list)

        for relation in prerequisites:
            nextCourse, prevCourse = relation[0], relation[1]
            courseDict[prevCourse].append(nextCourse)

        checked = [False] * numCourses
        path = [False] * numCourses

        for currCourse in range(numCourses):
            if isCyclic(currCourse, courseDict, checked, path):
                return False
        return True

    def doit_(self, numCourses: int, prerequisites):
        """
        :type numCourses: int
        :type prerequisites: List[List[int]]
        :rtype: bool
        """
        def cycled(i, G, path, visited):
            if visited[i]:
                return False

            path[i] = True
            visited[i] = True
            for j in G[i]:
                if path[j] or cycled(j, G, path, visited):
                    return True

            path[i] = False
            return False

        G = {x: [] for x in range(numCourses)}
        for i in prerequisites:
            G[i[1]].append(i[0])

        onPath = [False for x in range(numCourses)]
        visited = [False for x in range(numCourses)]

        i = 0
        while i < numCourses:
            if not visited[i] and cycled(i, G, onPath, visited):
                return False
            i += 1

        return True

    def doit_dfs(self, numCourses, prerequisites):
        """
        :type numCourses: int
        :type prerequisites: List[List[int]]
        :rtype: bool
        """
        def search(i, c, d, buff):

            if c[i]:
                return True

            if i in buff:
                return False
            buff.add(i)

            res = True
            for j in D[i]:
                res &= search(j, c, d, buff)
                if not res:
                    break

            if res:
                c[i] = res
                buff.remove(i)

            return c[i]

        D = [[] for _ in range(numCourses)]
        for item in prerequisites:
            D[item[0]].append(item[1])

        C = [True if len(D[x]) == 0 else False for x in range(numCourses)]
        i, res = 0, True

        while i < numCourses and res:
            C[i] = search(i, C, D, set())
            res = C[i]
            i += 1

        return res


if __name__ == '__main__':

    CourseScheduleI().doit_dfs(numCourses = 2, prerequisites = [[1,0]])



