import os
#import headpq


# leetcode 207. Course Schedule

# There are a total of n courses you have to take, labeled from 0 to n - 1.
# Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
# Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?


class canFinish(object):


    # DFS way
    def doit1(self, numCourses, prerequisites):
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
            else:
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
        i = 0
        while i < numCourses:
            if C[i]:
                i += 1
                continue

            C[i] = search(i, C, D, set())
            if not C[i]:
                return False
            i += 1

        return all(C)

        # i, res = 0, True
        # while i < numCourses and res:
        #    C[i] = search(i, C, D, set())
        #    res = C[i]
        #    i += 1

        #return res

    # dfs 
    def doit3(self, numCourses, prerequisties):
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

        G = {x : [] for x in range(numCourses)}
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
        

    #  BFS
    def doit2(self, numCourses, prerequisites):
        """
        :type numCourses: int
        :type prerequisites: List[List[int]]
        :rtype: bool
        """
        G = {x : [] for x in range(numCourses)}
        indegrees = [0 for x in range(numCourses)]
        for i in prerequisites:
            G[i[1]].append(i[0])
            indegrees[i[0]] += 1

        i = 0
        while i < numCourses:
            j = 0
            while j < numCourses:
                if indegrees[j] == 0:
                    break
                j += 1
            
            if j == numCourses:
                return False

            indegrees[j] = -1 # make it as touched
            for c in G[j]:
                indegrees[c] -= 1

            i += 1

        return True        


    # Best way BFS
    def doit(self, numCourses, prerequisites):

        g = {x : [] for x in range(numCourses)}
        ind = [0 for i in range(numCourses)]
        
        for i in range(len(prerequisites)):
            g[prerequisites[i][0]].append(prerequisites[i][1])
            ind[prerequisites[i][1]] += 1
            
        q = []
        for i in range(len(ind)):
            if ind[i] == 0:
                q.append(i)

        cnt = 0
        while q:
            n = q.pop()
            cnt += 1
            for e in g[n]:
                ind[e] -= 1
                if ind[e] == 0:
                    q.append(e)

        return numCourses == cnt
                


# leetcode 210. Course Schedule II        

         
# There are a total of n courses you have to take, labeled from 0 to n - 1.
# Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
# Given the total number of courses and a list of prerequisite pairs, 

#return the ordering of courses you should take to finish all courses.

# There may be multiple correct orders, you just need to return one of them. 
# If it is impossible to finish all courses, return an empty array.

# For example:

class findOrder(object):
    def doit(self, numCourses, prerequisites):
        """
        :type numCourses: int
        :type prerequisites: List[List[int]]
        :rtype: List[int]
        """
        G = [[] for _ in range(numCourses)]
        S = [0 for _ in range(numCourses)]
        for item in prerequisites:
            G[item[1]].append(item[0])
            S[item[0]] += 1

        q = []
        for i, C in enumerate(S):
            if C == 0:
                q.append(i)

        num, path = 0, []
        while q:
            path += q
            tmp = []
            while q:
                i = q.pop()
                num += 1
                for j in G[i]:
                    S[j] -= 1
                    if S[j] == 0:
                        tmp.append(j)
            q = tmp

        return [] if num != numCourses else path



    def doit2(self, numCourses, prerequisites):
        """
        :type courses: int
        :type prerequisites: List[List[int]]
        :rtype: List[int]
        """
        def move_vertex(v, from_set, to_set):
            from_set.remove(v)
            to_set.add(v)

        def cycle_present(graph, v, white, grey, black, res):
            if v in grey:
                return True
            elif v in black:
                return False

            move_vertex(v, white, grey)
            for edge in graph[v]:
                if cycle_present(graph, edge, white, grey, black, res):
                    return True

            move_vertex(v, grey, black)
            res.insert(0, v)
            return False
        
        from collections import defaultdict
        def construct_graph(edges):
            graph = defaultdict(list)
            for pair in edges:
                v,u = pair
                graph[u].append(v)
            return graph
        
        if not courses:
            return []

        if not prerequisites:
            return range(courses)

        graph = construct_graph(prerequisites)
        white_set, grey_set, black_set = set(), set(), set()
        res = []

        for vertex in xrange(courses):
            white_set.add(vertex)

        for vertex in xrange(courses):
            if cycle_present(graph, vertex, white_set, grey_set, black_set, res):
                return []

        return res


# leetcode 630. Course Schedule III

# There are n different online courses numbered from 1 to n. 
# Each course has some duration(course length) t and closed on dth day. 
# A course should be taken continuously for t days and must be finished before or on the dth day. You will start at the 1st day.
# Given n online courses represented by pairs (t,d), your task is to find the maximal number of courses that can be taken.

# Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
# Output: 3
# Explanation:

# There're totally 4 courses, but you can take 3 courses at most:
# First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
# Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
# Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
# The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.

class scheduleCourse(object):
    def doit(self, courses):
        """
        :type courses: List[List[int]]
        :rtype: int
        """
        heap = []
        cur = 0
        courses.sort(key = lambda x : x[1])
        for x in courses:
            if cur + x[0] <= x[1]:
                heapq.heappush(heap, (-x[0], x[1]))
                cur += x[0]
            else:
                if heap and -heap[0][0] > x[0]:
                    cur += x[0] + heap[0][0]
                    heapq.heappushpop(heap, (-x[0], x[1]))
        return len(heap)

        #queue = []
        #sortedCourses = sorted(courses, key=lambda item : item[1])
        #times = 0

        #for i, C in enumerate(sortedCourses):
            
        #    end = C[1]
        #    if times + C[0] <= end:
        #        times += C[0]
        #        headpq.headpush(C, (-C[0], C[1])

        #    else:

        #        if queue and C[0] > - queue[0][0]:
        #            times += C[0] - queue[0][0]
        #            headpq.headpushpop(queue, (-C[0], C[1]))

        #return len(queue)
        

if __name__=="__main__":


    res = canFinish().doit(4, [[0,1],[3,1],[1,3],[3,2]]) # false

    res = canFinish().doit(3, [[0,1],[0,2],[1,2]]) # true

    res = canFinish().doit(2, [[1, 0]]) # true

    res = canFinish().doit(2, [[1, 0], [0, 1]]) # false


    res = findOrder().doit(2, [[1,0]])

    res = findOrder().doit(4, [[1,0],[2,0],[3,1],[3,2]])


    res = scheduleCourse().doit([[100, 200], [200, 1300], [1000, 1250], [2000, 3200]])

    res = scheduleCourse().doit([[5,5],[4,6],[2,6]])


    pass