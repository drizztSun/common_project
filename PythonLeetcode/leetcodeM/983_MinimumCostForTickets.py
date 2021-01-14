# 983. Minimum Cost For Tickets

# In a country popular for train travel, you have planned some train travelling one year in advance.
# The days of the year that you will travel is given as an array days.  Each day is an integer from 1 to 365.

# Train tickets are sold in 3 different ways:

# a 1-day pass is sold for costs[0] dollars;
# a 7-day pass is sold for costs[1] dollars;
# a 30-day pass is sold for costs[2] dollars.
# The passes allow that many days of consecutive travel.
#
# For example, if we get a 7-day pass on day 2, then we can travel for 7 days: day 2, 3, 4, 5, 6, 7, and 8.

# Return the minimum number of dollars you need to travel every day in the given list of days.


# Example 1:

# Input: days = [1,4,6,7,8,20], costs = [2,7,15]
# Output: 11
# Explanation:
# For example, here is one way to buy passes that lets you travel your travel plan:
# On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
# On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
# On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
# In total you spent $11 and covered all the days of your travel.

# Example 2:

# Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
# Output: 17
# Explanation:
# For example, here is one way to buy passes that lets you travel your travel plan:
# On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2, ..., 30.
# On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
# In total you spent $17 and covered all the days of your travel.


# Note:

# 1 <= days.length <= 365
# 1 <= days[i] <= 365
# days is in strictly increasing order.
# costs.length == 3
# 1 <= costs[i] <= 1000

class MincostTickets:

    """
    Approach 1: Dynamic Programming (Day Variant)
    Intuition and Algorithm

    For each day, if you don't have to travel today, then it's strictly better to wait to buy a pass. If you have to travel today, you have up to 3 choices: you must buy either a 1-day, 7-day, or 30-day pass.

    We can express those choices as a recursion and use dynamic programming. Let's say dp(i) is the cost to fulfill your travel plan from day i to the end of the plan. Then, if you have to travel today, your cost is:

    \text{dp}(i) = \min(\text{dp}(i+1) + \text{costs}[0], \text{dp}(i+7) + \text{costs}[1], \text{dp}(i+30) + \text{costs}[2])dp(i)=min(dp(i+1)+costs[0],dp(i+7)+costs[1],dp(i+30)+costs[2])

    Complexity Analysis

    Time Complexity: O(W), where W = 365 is the maximum numbered day in your travel plan.

    Space Complexity: O(W).

    """

    def doit_dp_topdown_1(self, days, costs):
        from functools import lru_cache
        dayset = set(days)
        durations = [1, 7, 30]

        @lru_cache(None)
        def dp(i):
            if i > 365:
                return 0
            elif i in dayset:
                return min(dp(i + d) + c for c, d in zip(costs, durations))
            else:
                return dp(i + 1)

        return dp(1)

    """
        Approach 2: Dynamic Programming (Window Variant)
        Intuition and Algorithm

        As in Approach 1, we only need to buy a travel pass on a day we intend to travel.

        Now, let dp(i) be the cost to travel from day days[i] to the end of the plan. If say, j1 is the largest index such that days[j1] < days[i] + 1, j7 is the largest index such that days[j7] < days[i] + 7, and j30 is the largest index such that days[j30] < days[i] + 30, then we have:

        dp(i) = min(dp(j1) + cost[0], dp(j7) + cost[1], dp(j30) + cost[2])

        Complexity Analysis

        Time Complexity: O(N)O(N), where NN is the number of unique days in your travel plan.

        Space Complexity: O(N)O(N).

    """
    def doit_do_topdown(self, days, costs):
        from functools import lru_cache

        daysCost = [(1, costs[0]), (7, costs[1]), (30, costs[2])]
        @lru_cache(None)
        def dp(i):
            if i >= len(days): return 0

            ans = float('inf')
            j = i
            for d, c in daysCost:
                while j < len(days) and days[j] - days[i] < d:
                    j += 1
                ans = min(ans, dp(j) + c)

            return ans

        return dp(0)  


    def doit(self, days, costs):

        days = set(days)
        costs = [(1, costs[0]), (7, costs[1]), (30, costs[2])]
        memo = [0] * (366 + 30)

        def dp(i):

            if i > 365:
                return 0

            if memo[i]:
                return memo[i]

            elif i in days:
                memo[i] = min(dp(i + d) + c for d, c in costs)

            else:
                memo[i] = dp(i+1)

            return memo[i]

        return dp(1)

    def doit1(self, days, costs):

        dp = [0] * 366
        j = 0

        for i in range(1, len(dp)):

            if j < len(days) and i == days[j]:

                dp[i] = dp[i-1] + costs[0]

                dp[i] = min(dp[i], dp[min(i-7, 0)] + costs[1])

                dp[i] = min(dp[i], dp[min(i-30, 0)] + costs[2])

                j += 1
            else:
                dp[i] = dp[i-1]

        return dp[-1]


if __name__ == '__main__':

    res = MincostTickets().doit_do_topdown(days=[1, 4, 6, 7, 8, 20], costs=[2, 7, 15])  # 11

    res = MincostTickets().doit_do_topdown(days=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31], costs=[2, 7, 15])  # 17

    res = MincostTickets().doit_do_topdown([1, 4, 6, 7, 8, 20], [7, 2, 15])  # 6

