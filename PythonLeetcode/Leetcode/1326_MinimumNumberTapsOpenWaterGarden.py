"""
1326. Minimum Number of Taps to Open to Water a Garden

There is a one-dimensional garden on the x-axis. The garden starts at the point 0 and ends at the point n. (i.e The length of the garden is n).

There are n + 1 taps located at points [0, 1, ..., n] in the garden.

Given an integer n and an integer array ranges of length n + 1 where ranges[i] (0-indexed) means the i-th tap can water the area [i - ranges[i], i + ranges[i]] if it was open.

Return the minimum number of taps that should be open to water the whole garden, If the garden cannot be watered return -1.



Example 1:


Input: n = 5, ranges = [3,4,1,1,0,0]
Output: 1
Explanation: The tap at point 0 can cover the interval [-3,3]
The tap at point 1 can cover the interval [-3,5]
The tap at point 2 can cover the interval [1,3]
The tap at point 3 can cover the interval [2,4]
The tap at point 4 can cover the interval [4,4]
The tap at point 5 can cover the interval [5,5]
Opening Only the second tap will water the whole garden [0,5]
Example 2:

Input: n = 3, ranges = [0,0,0,0]
Output: -1
Explanation: Even if you activate all the four taps you cannot water the whole garden.
Example 3:

Input: n = 7, ranges = [1,2,1,0,2,1,0,1]
Output: 3
Example 4:

Input: n = 8, ranges = [4,0,0,0,0,0,0,0,4]
Output: 2
Example 5:

Input: n = 8, ranges = [4,0,0,0,4,0,0,0,4]
Output: 1
"""


class MinimumNumberTips:

    def doit_dp_best(self, n, ranges):

        jumps = [0]*(n+1)
        for i, v in enumerate(ranges):
            j = max(0, i-v)
            jumps[j] = max(jumps[j], i + v)

        c = l = r = 0
        while r < n:
            l, r = r+1, max(jumps[l:r+1])  # move right as far as possbile
            if l > r:
                return -1
            c += 1
        return c

    def doit_dp(self, n, ranges):

        dp = [0] * (n+1)

        for i in range(len(ranges)):
            if ranges[i] == 0:
                continue
            l, r = max(0, i - ranges[i]), min(n, i + ranges[i])
            dp[l] = max(dp[l], r)

        ans, i, l, e = 0, 0, 0, 0

        while l < n:

            while i <= l:
                e = max(e, dp[i])
                i += 1

            if l == e:
                return -1

            l = e
            ans += 1

        return ans

    """


    """
    def doit_greedy(self, n, ranges):

        buff = sorted([(max(i - ranges[i], 0), min(i + ranges[i], n)) for i in range(n+1)])

        ans, l, i, e = 0, 0, 0, 0

        while e < n:

            while i <= n and buff[i][0] <= l:
                e = max(e, buff[i][1])
                i += 1

            if e == l:
                return -1

            ans += 1
            l = e

        return ans

    """
    First let me explain why dp is very suitable for this problem. The idea is this, if we know the min number of taps to water from 0 to i, we can use this to extrapolate the min number of taps to water from 1 to i+j.
    ok let me explain what i mean by this.

    So we loop through every tap which is represented by the ranges array. Since the tap spouts water in the left and right directions,
    it can water the garden from [left,right] of course the gardens limit should be taken into account, we cant water a negative length, neither can we water outside the garden length.
    if we know the min number of taps needed to water from 0 to left then its easy to see that we can possiby water the garden from left to right using the minimum number of taps to water uptil left + 1 since we use the current tap.
    We initialise dp[0] = 0 since no taps are needed to water a garden with 0 length.

    dp is effective in storing previously known results and building up from these previously known results.
    In this case, we want to store the min number of taps to water up from 0 to i where i < n. There, we broke down the requirement to get the min number of taps to water up from 0 to n to simpler sub problems.
    The first one being to water up to a 0 length and building up incrementally to n.

    """
    def doit_dp_1(self, n, ranges):

        dp = [0] + [n+2] * n

        for i, x in enumerate(ranges):

            for j in range(max(0, i-x+1), min(i+x, n)+1):

                dp[j] = min(dp[j], dp[max(0, i-x) + 1])

        return dp[n] if dp[n] < n + 2 else -1

    def doit(self, n: int, ranges):

        for i, r in enumerate(ranges):
            l = max(0, i - r)
            ranges[l] = max(i + r, ranges[l])

        res = lo = hi = 0
        while hi < n:
            lo, hi = hi, max(ranges[lo:hi + 1])
            if hi == lo:
                return -1
            res += 1
        return res

    def doit_heap(self, n: int, ranges):
        from heapq import heappush, heappop
        opens, closes, closed = [[] for _ in range(n)], [[] for _ in range(n)], set()
        for i in range(len(ranges)):
            idx = 0
            if i - ranges[i] > 0:
                idx = i - ranges[i]
            if idx < len(opens):
                opens[idx].append(i)
            if i + ranges[i] < n:
                closes[i + ranges[i]].append(i)
        heap, cur_open_tap, res = [], None, 0
        for i in range(n):
            for op in opens[i]:
                heappush(heap, [-(op + ranges[op]), op])
            for cl in closes[i]:
                closed.add(cl)
                if cl == cur_open_tap:
                    cur_open_tap = None
            while cur_open_tap is None:
                if not heap:
                    return -1
                if heap[0][1] in closed:
                    heappop(heap)
                else:
                    cur_open_tap = heap[0][1]
                    res += 1
        return res


if __name__ == '__main__':

    MinimumNumberTips().doit_dp(n = 5, ranges = [3,4,1,1,0,0])

    MinimumNumberTips().doit_dp(n = 3, ranges = [0,0,0,0])

    MinimumNumberTips().doit_dp(n = 7, ranges = [1,2,1,0,2,1,0,1])

    MinimumNumberTips().doit_dp(n = 8, ranges = [4,0,0,0,0,0,0,0,4])

    MinimumNumberTips().doit_dp(n = 8, ranges = [4,0,0,0,4,0,0,0,4])