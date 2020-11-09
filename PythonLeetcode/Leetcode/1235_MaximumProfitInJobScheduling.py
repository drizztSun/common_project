"""
1235. Maximum Profit in Job Scheduling

We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

You're given the startTime , endTime and profit arrays, you need to output the maximum profit you can take such that
there are no 2 jobs in the subset with overlapping time range.

If you choose a job that ends at time X you will be able to start another job that starts at time X.



Example 1:



Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
Output: 120
Explanation: The subset chosen is the first and fourth job.
Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
Example 2:




Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
Output: 150
Explanation: The subset chosen is the first, fourth and fifth job.
Profit obtained 150 = 20 + 70 + 60.
Example 3:



Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
Output: 6


Constraints:

1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
1 <= startTime[i] < endTime[i] <= 10^9
1 <= profit[i] <= 10^4

"""


class JobScheduling:

    """
    The main idea to solve this problem is that:
    After sort the jobs by endTime, define F(t) as the max profit made till time t
    F(endTime[i]) = max(F(endTime[i - 1]), F(startTime[i]) + profit[i])
    that is, the max profit should be the max value between NOT choose the job and choose the job.
    This is a very common idea when it comes to dp or finding the relation between f(i) and f(i-1).
    """
    def doit_dp(self, startTime: list, endTime: list, profit: list) -> int:
        ans = [(0,0)]
        a = sorted(zip(startTime, endTime, profit), key=lambda x: (x[1], x[0]))
        for s, e, p in a:
            profit = ans[-1][1]
            for last_end, last_profit in reversed(ans):
                if last_end <= s:
                    ans.append((e, max(profit, last_profit + p)))
                    break
        return ans[-1][1]

    def doit_greedy(self, startTime: list, endTime: list, profit: list) -> int:

        # max profit ending at time t
        dp = [(0, 0)]
        task = [(startTime[i], endTime[i], profit[i]) for i in range(len(startTime))]
        task = sorted(task, key=lambda x: x[1])

        for s, e, p in task:
            noTaskProf = dp[-1][1]
            for end, pro in reversed(dp):
                # end, pro = dp[i]
                if end <= s:
                    doTaskProf = pro + p
                    break
            if doTaskProf > noTaskProf:
                dp.append((e, doTaskProf))
        return dp[-1][1]


if __name__ == '__main__':

    JobScheduling().doit_dp(startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70])

    JobScheduling().doit_dp(startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60])

    JobScheduling().doit_dp(startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4])