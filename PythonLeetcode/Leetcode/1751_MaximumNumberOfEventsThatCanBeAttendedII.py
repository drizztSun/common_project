"""
1751. Maximum Number of Events That Can Be Attended II



You are given an array of events where events[i] = [startDayi, endDayi, valuei].
The ith event starts at startDayi and ends at endDayi, and if you attend this event, you will receive a value of valuei.
You are also given an integer k which represents the maximum number of events you can attend.

You can only attend one event at a time. If you choose to attend an event, you must attend the entire event.
Note that the end day is inclusive: that is, you cannot attend two events where one of them starts and the other ends on the same day.

Return the maximum sum of values that you can receive by attending events.



Example 1:



Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
Output: 7
Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.
Example 2:



Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
Output: 10
Explanation: Choose event 2 for a total value of 10.
Notice that you cannot attend any other event as they overlap, and that you do not have to attend k events.
Example 3:



Input: events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
Output: 9
Explanation: Although the events do not overlap, you can only attend 3 events. Pick the highest valued three.


Constraints:

1 <= k <= events.length
1 <= k * events.length <= 10^6
1 <= startDayi <= endDayi <= 10^9
1 <= valuei <= 10^6


"""


class MaximumNumberOfEvents:

    def doit_dp(self, events: list, k: int) -> int:

        from bisect import bisect_left

        n = len(events)
        dp = [[0 for _ in range(k + 1)] for _ in range(n + 1)]

        events.sort(key=lambda x: x[1])
        events.insert(0, events[0])
        endtimes = [0]
        ans = 0

        for i in range(1, n + 1):

            t = bisect_left(endtimes, events[i][0]) - 1

            for j in range(1, k + 1):
                dp[i][j] = max(dp[i - 1][j], dp[t][j - 1] + events[i][2])
                ans = max(ans, dp[i][j])

            endtimes.append(events[i][1])

        return ans

    def doit_dp(self, events: list, k: int) -> int:
        from bisect import bisect_right
        from heapq import heappush, heappop

        events.sort(key=lambda x: x[1])
        n = len(events)

        # end times sorted array
        ends = [events[i][1] for i in range(n)]
        # best value for each index, all non-overlapping values make best sums
        bests = [[] for _ in range(n)]
        #
        best, maxVal = [], 0

        for i in range(n):
            beg, end, val = events[i]
            # best
            j = bisect_right(ends, beg - 1)
            # option = bests[j-1].copy()
            option = [v for v in bests[j - 1]]

            # put value into the heap of position j-1
            heappush(option, val)

            #
            if len(option) > k:
                heappop(option)

            # sum of
            Val = sum(option)
            if Val > maxVal:
                maxVal = Val
                best = option
            bests[i] = best

        return maxVal