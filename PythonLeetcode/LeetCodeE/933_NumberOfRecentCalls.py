# 933. Number of Recent Calls

# Write a class RecentCounter to count recent requests.

# It has only one method: ping(int t), where t represents some time in milliseconds.

# Return the number of pings that have been made from 3000 milliseconds ago until now.

# Any ping with time in [t - 3000, t] will count, including the current ping.

# It is guaranteed that every call to ping uses a strictly larger value of t than before.


# Example 1:

# Input: inputs = ["RecentCounter","ping","ping","ping","ping"], inputs = [[],[1],[100],[3001],[3002]]
# Output: [null,1,2,3,3]


# Note:

# Each test case will have at most 10000 calls to ping.
# Each test case will call ping with strictly increasing values of t.
# Each call to ping will have 1 <= t <= 10^9.

class RecentCounter:

    def __init__(self):
        self._buff = []

    def ping(self, t):

        s = max(t - 3000, 0)
        self._buff.append(t)

        l, h = 0, len(self._buff)
        while l < h:
            mid = (l + h) // 2

            if self._buff[mid] > s:
                h = mid
            elif self._buff[mid] < s:
                l = mid + 1
            else:
                l = mid
                break

        self._buff = self._buff[l:]
        return len(self._buff)


class RecentCounter1:

    def __init__(self):
        self.queue = []

    def ping(self, t):
        while self.queue and t - self.queue[0] > 3000:
            self.queue.pop(0)
        self.queue.append(t)
        return len(self.queue)

class RecentCounter2:
    import collections

    def __init__(self):
        self.slide=collections.deque()

    def ping(self, t: int) -> int:
        self.slide.append(t)
        while self.slide[0]+3000<t:
            self.slide.popleft()
        return len(self.slide)


if __name__ == '__main__':

    obj = RecentCounter()

    res = obj.ping(1)

    res = obj.ping(100)

    res = obj.ping(3001)

    res = obj.ping(3002)

    pass
