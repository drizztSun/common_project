"""
1494. Parallel Courses II

Given the integer n representing the number of courses at some university labeled from 1 to n, and the array dependencies
where dependencies[i] = [xi, yi]  represents a prerequisite relationship, that is, the course xi must be taken before the course yi.
Also, you are given the integer k.

In one semester you can take at most k courses as long as you have taken all the prerequisites for the courses you are taking.

Return the minimum number of semesters to take all courses. It is guaranteed that you can take all courses in some way.



Example 1:



Input: n = 4, dependencies = [[2,1],[3,1],[1,4]], k = 2
Output: 3
Explanation: The figure above represents the given graph. In this case we can take courses 2 and 3 in the first semester,
then take course 1 in the second semester and finally take course 4 in the third semester.
Example 2:



Input: n = 5, dependencies = [[2,1],[3,1],[4,1],[1,5]], k = 2
Output: 4
Explanation: The figure above represents the given graph. In this case one optimal way to take all courses is:
take courses 2 and 3 in the first semester and take course 4 in the second semester,
then take course 1 in the third semester and finally take course 5 in the fourth semester.

Example 3:

Input: n = 11, dependencies = [], k = 2
Output: 6


Constraints:

1 <= n <= 15
1 <= k <= n
0 <= dependencies.length <= n * (n-1) / 2
dependencies[i].length == 2
1 <= xi, yi <= n
xi != yi
All prerequisite relationships are distinct, that is, dependencies[i] != dependencies[j].
The given graph is a directed acyclic graph.


"""


class MinNumberOfSemesters:

    def doit_dp_bitmask(self, n: int, dependencies: list, k: int) -> int:

        total = 1 << n
        precourses = [0 for _ in range(n)]
        for c1, c2 in dependencies:
            precourses[c2-1] |= 1 << (c1-1)

        prestate = [0 for _ in range(total)]
        for i in range(total):
            for j in range(0, n):
                if ((i >> j) & 1) == 1:
                    prestate[i] |= precourses[j]

        dp = [n for _ in range(total)]
        dp[0] = 0

        for state in range(total):

            subset = state
            while subset >= 0:
                if bin(state).count("1") - bin(subset).count("1") <= k and (subset & prestate[state]) == prestate[state]:
                    dp[state] = min(dp[state], dp[subset] + 1)
                subset = ((subset - 1) & state)
                if subset == 0:
                    break

        return dp[total-1]


if __name__ == '__main__':

    MinNumberOfSemesters().doit_dp_bitmask(n = 4, dependencies = [[2,1],[3,1],[1,4]], k = 2)

    MinNumberOfSemesters().doit_dp_bitmask(n = 5, dependencies = [[2,1],[3,1],[4,1],[1,5]], k = 2)

    MinNumberOfSemesters().doit_dp_bitmask(n = 11, dependencies = [], k = 2)
