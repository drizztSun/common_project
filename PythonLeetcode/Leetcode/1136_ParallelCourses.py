"""
1136. Parallel Courses

There are N courses, labelled from 1 to N.

We are given relations[i] = [X, Y], representing a prerequisite relationship between course X and course Y: course X has to be studied before course Y.

In one semester you can study any number of courses as long as you have studied all the prerequisites for the course you are studying.

Return the minimum number of semesters needed to study all courses.  If there is no way to study all the courses, return -1.



Example 1:



Input: N = 3, relations = [[1,3],[2,3]]
Output: 2
Explanation:
In the first semester, courses 1 and 2 are studied. In the second semester, course 3 is studied.
Example 2:



Input: N = 3, relations = [[1,2],[2,3],[3,1]]
Output: -1
Explanation:
No course can be studied because they depend on each other.


Note:

1 <= N <= 5000
1 <= relations.length <= 5000
relations[i][0] != relations[i][1]
There are no repeated relations in the input.
"""


class MinimumSemesters:

    def doit_dp_dfs(self, N, relations):
        """
        :type N: int
        :type relations: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict, deque
        graph = defaultdict(list)
        indegree = defaultdict(int)

        for u, v in relations:
            graph[u].append(v)  # Build Graph.
            indegree[v] += 1  # Count Indegree of v for u -> v.

        q = deque([(1, i) for i in range(1, N + 1) if indegree[i] == 0])  # Put all (level, vertex) in Q, whose indegree is 0. level = 1
        visited = set()
        answer = 0

        while q:
            level, u = q.popleft()
            visited.add(u)  # Keep track of levels.
            answer = max(level, answer)  # Since answer we are looking is maximum levels to complete all the courses.
            for v in graph[u]:
                if indegree[v] > 0:
                    indegree[v] -= 1
                if indegree[v] == 0:
                    q.append((level + 1, v))  # If Indegree of a vertex v is 0, put (level+1, v) in the q.

        return answer if len(visited) == N else -1  # Return answer only if we can complete all courses, else -1


if __name__ == "__main__":

    MinimumSemesters().doit_dp(N = 3, relations = [[1,3],[2,3]])

    MinimumSemesters().doit_dp(N = 3, relations = [[1,2],[2,3],[3,1]])