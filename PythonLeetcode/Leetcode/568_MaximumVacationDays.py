"""
568. Maximum Vacation Days

LeetCode wants to give one of its best employees the option to travel among N cities to collect algorithm problems. But all work and no play makes Jack a dull boy, you could take vacations in some particular cities and weeks. Your job is to schedule the traveling to maximize the number of vacation days you could take, but there are certain rules and restrictions you need to follow.

Rules and restrictions:
You can only travel among N cities, represented by indexes from 0 to N-1. Initially, you are in the city indexed 0 on Monday.
The cities are connected by flights. The flights are represented as a N*N matrix (not necessary symmetrical), called flights representing the airline status from the city i to the city j. If there is no flight from the city i to the city j, flights[i][j] = 0; Otherwise, flights[i][j] = 1. Also, flights[i][i] = 0 for all i.
You totally have K weeks (each week has 7 days) to travel. You can only take flights at most once per day and can only take flights on each week's Monday morning. Since flight time is so short, we don't consider the impact of flight time.
For each city, you can only have restricted vacation days in different weeks, given an N*K matrix called days representing this relationship. For the value of days[i][j], it represents the maximum days you could take vacation in the city i in the week j.
You're given the flights matrix and days matrix, and you need to output the maximum vacation days you could take during K weeks.

Example 1:
Input:flights = [[0,1,1],[1,0,1],[1,1,0]], days = [[1,3,1],[6,0,3],[3,3,3]]
Output: 12
Explanation:
Ans = 6 + 3 + 3 = 12.

One of the best strategies is:
1st week : fly from city 0 to city 1 on Monday, and play 6 days and work 1 day.
(Although you start at city 0, we could also fly to and start at other cities since it is Monday.)
2nd week : fly from city 1 to city 2 on Monday, and play 3 days and work 4 days.
3rd week : stay at city 2, and play 3 days and work 4 days.
Example 2:
Input:flights = [[0,0,0],[0,0,0],[0,0,0]], days = [[1,1,1],[7,7,7],[7,7,7]]
Output: 3
Explanation:
Ans = 1 + 1 + 1 = 3.

Since there is no flights enable you to move to another city, you have to stay at city 0 for the whole 3 weeks.
For each week, you only have one day to play and six days to work.
So the maximum number of vacation days is 3.
Example 3:
Input:flights = [[0,1,1],[1,0,1],[1,1,0]], days = [[7,0,0],[0,7,0],[0,0,7]]
Output: 21
Explanation:
Ans = 7 + 7 + 7 = 21

One of the best strategies is:
1st week : stay at city 0, and play 7 days.
2nd week : fly from city 0 to city 1 on Monday, and play 7 days.
3rd week : fly from city 1 to city 2 on Monday, and play 7 days.
Note:
N and K are positive integers, which are in the range of [1, 100].
In the matrix flights, all the values are integers in the range of [0, 1].
In the matrix days, all the values are integers in the range [0, 7].
You could stay at a city beyond the number of vacation days, but you should work on the extra days, which won't be counted as vacation days.
If you fly from the city A to the city B and take the vacation on that day, the deduction towards vacation days will count towards the vacation days of city B in that week.
We don't consider the impact of flight hours towards the calculation of vacation days.

"""
import heapq
import collections


class MaxVacationDays:

    def doit_dp(self, flights, days):

        """
        :type flights: List[List[int]]
        :type days: List[List[int]]
        :rtype: int
        """
        N, K = len(days), len(days[0])
        dp = [[0 for _ in range(K + 1)] for _ in range(N + 1)]

        connect = collections.defaultdict(list)

        for i in range(N):
            for j in range(N):
                if flights[i][j] == 1:
                    connect[j].append(i)

        for j in range(K):
            for i in range(N):
                if j == 0:
                    dp[i][j] = days[i][j] if flights[0][i] == 1 else 0
                    if i == 0:
                        dp[0][0] = days[0][0]
                    continue

                if dp[i][j-1]:
                    dp[i][j] = dp[i][j - 1] + days[i][j]

                for c in connect[i]:
                    dp[i][j] = max(dp[i][j], days[i][j] + dp[c][j - 1])

        return max(dp[i][K - 1] for i in range(N))

    def doit_dp_1(self, flights, days):

        """
        :type flights: List[List[int]]
        :type days: List[List[int]]
        :rtype: int
        """

        """
         key = {@ city i on week j, i = 0 .. (N-1), j = 0 .. (K-1);
         memo[i][j] = maximum vacation days can get from week j to (K-1) if currently @ city i;
         memo[i][j] = max{days[i][j]+memo[i][j+1], days[i2][j] + memo[i2][j+1], for all cities i2 where flights[i][i2] = 1};
         memo[i][K] = {0};
        """
        N, K = len(days), len(days[0])
        dp = [[0 for _ in range(K + 1)] for _ in range(N + 1)]

        connect = collections.defaultdict(list)

        for i in range(N):
            for j in range(N):
                if flights[i][j] == 1:
                    connect[i].append(j)

        for j in range(K - 1, -1, -1):

            for i in range(N):

                dp[i][j] = days[i][j] + dp[i][j + 1]

                for c in connect[i]:
                    dp[i][j] = max(dp[i][j], days[c][j] + dp[c][j + 1])

        return dp[0][0]

    def doit_bfs(self, flights, days):
        """
        :type flights: List[List[int]]
        :type days: List[List[int]]
        :rtype: int
        """
        res = 0
        N, K = len(days), len(days[0])  # (N) number of cities, (K) number of weeks allowed

        #####################################################################################################
        # 1. Optimization: Convert flights from a matrix to a hash map of (city) -> (cities you can fly to) #
        #    For the remaining code, this reduces the run time from 2776 ms down to 1512 ms                 #
        #####################################################################################################

        sparse_flights = collections.defaultdict(list)
        for r in range(N):
            for c in range(N):
                if flights[r][c]:
                    sparse_flights[r].append(c)

        #####################################################################
        # 2. BFS to find the travel path that yields the most vacation days #
        #####################################################################

        q = [(0, -1, 0)]  # priority queue = (d) vacation days taken, (k) week (city) current city
        visited = [[-1] * N for _ in range(K)]  # visited[k][city] = max vacation days when in (city) on week (k)
        while q:

            d, k, city = heapq.heappop(q)
            d = -d  # Make days (d) negative when adding it to (q) so queue behave like a max-heap instead of a min-heap

            if k == K - 1:
                res = max(res, d)
                continue

            # 2.1 Try flying to another city ~ only if we have not been to new_city in week (k+1) and had more vacation days
            for new_city in sparse_flights[city]:
                if d + days[new_city][k + 1] > visited[k + 1][new_city]:
                    visited[k + 1][new_city] = d + days[new_city][k + 1]
                    heapq.heappush(q, (-(d + days[new_city][k + 1]), k + 1, new_city))

            # 2.2 Stay in same city
            if d + days[city][k + 1] > visited[k + 1][city]:
                visited[k + 1][city] = d + days[city][k + 1]
                heapq.heappush(q, (-(d + days[city][k + 1]), k + 1, city))

        return res


if __name__ == '__main__':

    MaxVacationDays().doit_dp([[0,1,1],[1,0,1],[1,1,0]], [[1,3,1],[6,0,3],[3,3,3]])

    MaxVacationDays().doit_dp([[0,0,0],[0,0,0],[0,0,0]], [[1,1,1],[7,7,7],[7,7,7]])
