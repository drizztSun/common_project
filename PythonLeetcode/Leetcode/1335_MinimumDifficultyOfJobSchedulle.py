"""
1335. Minimum Difficulty of a Job Schedule

You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the i-th job, you have to finish all the jobs j where 0 <= j < i).

You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days.
The difficulty of a day is the maximum difficulty of a job done in that day.

Given an array of integers jobDifficulty and an integer d. The difficulty of the i-th job is jobDifficulty[i].

Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.

Example 1:


Input: jobDifficulty = [6,5,4,3,2,1], d = 2
Output: 7
Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
Second day you can finish the last job, total difficulty = 1.
The difficulty of the schedule = 6 + 1 = 7
Example 2:

Input: jobDifficulty = [9,9,9], d = 4
Output: -1
Explanation: If you finish a job per day you will still have a free day. you cannot find a schedule for the given jobs.
Example 3:

Input: jobDifficulty = [1,1,1], d = 3
Output: 3
Explanation: The schedule is one job per day. total difficulty will be 3.
Example 4:

Input: jobDifficulty = [7,1,7,1,7,1], d = 3
Output: 15
Example 5:

Input: jobDifficulty = [11,111,22,222,33,333,44,444], d = 6
Output: 843


Constraints:

1 <= jobDifficulty.length <= 300
0 <= jobDifficulty[i] <= 1000
1 <= d <= 10
"""


class MinDifficulty:

    def doit_dp(self, jobs: list, d: int):

        m = len(jobs)

        maxv = [[0 for _ in range(m)] for _ in range(m)]

        for i in range(m):
            for j in reversed(range(i + 1)):
                if i == j:
                    maxv[j][i] = jobs[i]
                else:
                    maxv[j][i] = max(jobs[j], maxv[j + 1][i])

        dp = [[float('inf') for _ in range(m)] for _ in range(d)]

        for i in range(d):
            for j in range(i, m): #
                if i == 0:
                    dp[i][j] = maxv[i][j]
                else:
                    for k in range(i-1, j):
                        dp[i][j] = min(dp[i][j], dp[i - 1][k] + maxv[k+1][j])

        return -1 if dp[d-1][m-1] == float('inf') else dp[d-1][m-1]

    def doit_dp_1(self, jobs, d):

        n = len(jobs)
        dp, dp2 = [float('inf')] * n, [0] * n
        if n < d:
            return -1

        for d in range(d):
            stack = []
            for i in range(d, n):
                dp2[i] = dp[i - 1] + jobs[i] if i else jobs[i]
                while stack and jobs[stack[-1]] <= jobs[i]:
                    j = stack.pop()
                    dp2[i] = min(dp2[i], dp2[j] - jobs[j] + jobs[i])
                if stack:
                    dp2[i] = min(dp2[i], dp2[stack[-1]])
                stack.append(i)
            dp, dp2 = dp2, [0] * n
        return dp[-1]


if __name__ == '__main__':

    MinDifficulty().doit_dp_1(jobs = [6,5,4,3,2,1], d = 2)

    MinDifficulty().doit_dp(jobs = [9,9,9], d = 4)

    MinDifficulty().doit_dp(jobs = [1,1,1], d = 3)

    MinDifficulty().doit_dp(jobs = [7,1,7,1,7,1], d = 3)

    MinDifficulty().doit_dp(jobs = [11,111,22,222,33,333,44,444], d = 6)