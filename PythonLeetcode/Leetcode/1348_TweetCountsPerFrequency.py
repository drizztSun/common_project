"""
1348. Tweet Counts Per Frequency

Implement the class TweetCounts that supports two methods:

1. recordTweet(string tweetName, int time)

Stores the tweetName at the recorded time (in seconds).
2. getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime)

Returns the total number of occurrences for the given tweetName per minute, hour, or day (depending on freq) starting from the startTime (in seconds) and ending at the endTime (in seconds).
freq is always minute, hour or day, representing the time interval to get the total number of occurrences for the given tweetName.
The first time interval always starts from the startTime, so the time intervals are [startTime, startTime + delta*1>,
[startTime + delta*1, startTime + delta*2>, [startTime + delta*2, startTime + delta*3>, ... , [startTime + delta*i, min(startTime + delta*(i+1), endTime + 1)> for some non-negative number i and delta (which depends on freq).


Example:

Input
["TweetCounts","recordTweet","recordTweet","recordTweet","getTweetCountsPerFrequency","getTweetCountsPerFrequency","recordTweet","getTweetCountsPerFrequency"]
[[],["tweet3",0],["tweet3",60],["tweet3",10],["minute","tweet3",0,59],["minute","tweet3",0,60],["tweet3",120],["hour","tweet3",0,210]]

Output
[null,null,null,null,[2],[2,1],null,[4]]

Explanation
TweetCounts tweetCounts = new TweetCounts();
tweetCounts.recordTweet("tweet3", 0);
tweetCounts.recordTweet("tweet3", 60);
tweetCounts.recordTweet("tweet3", 10);                             // All tweets correspond to "tweet3" with recorded times at 0, 10 and 60.
tweetCounts.getTweetCountsPerFrequency("minute", "tweet3", 0, 59); // return [2]. The frequency is per minute (60 seconds), so there is one interval of time: 1) [0, 60> - > 2 tweets.
tweetCounts.getTweetCountsPerFrequency("minute", "tweet3", 0, 60); // return [2, 1]. The frequency is per minute (60 seconds), so there are two intervals of time: 1) [0, 60> - > 2 tweets, and 2) [60,61> - > 1 tweet.
tweetCounts.recordTweet("tweet3", 120);                            // All tweets correspond to "tweet3" with recorded times at 0, 10, 60 and 120.
tweetCounts.getTweetCountsPerFrequency("hour", "tweet3", 0, 210);  // return [4]. The frequency is per hour (3600 seconds), so there is one interval of time: 1) [0, 211> - > 4 tweets.


Constraints:

There will be at most 10000 operations considering both recordTweet and getTweetCountsPerFrequency.
0 <= time, startTime, endTime <= 10^9
0 <= endTime - startTime <= 10^4
"""
from bisect import insort, bisect_left, bisect_right
from math import ceil


class TweetCounts_bisect:

    def __init__(self):
        self.tweets={}

    def recordTweet(self, tweetName: str, time: int) -> None:
        if tweetName not in self.tweets:
            self.tweets[tweetName] = []
        insort(self.tweets[tweetName], time)

    def getTweetCountsPerFrequency(self, freq: str, tweetName: str, startTime: int, endTime: int):
        entry = self.tweets[tweetName]
        diff = endTime - startTime

        factor = 86400
        if freq == 'minute':
            factor = 60
        elif freq == 'hour':
            factor = 3600

        buckets = ceil((diff + 1) / factor)
        ans = [0]*buckets

        start = bisect_left(entry, startTime)
        end = bisect_right(entry, endTime)

        for i in range(start, end):
            time = entry[i]
            d = (time - startTime) // factor
            ans[d] += 1
        return ans


class TweetCounts:

    def __init__(self):
        self._buf = []
        self._timestep = {'minute': 60, 'hour': 3600, 'day': 3600 * 24}

    def search(self, time, left=True):

        low, high = 0, len(self._buf)
        while low < high:

            mid = (low + high) // 2

            if self._buf[mid][0] > time or (left and self._buf[mid][0] == time):
                high = mid
            else:
                low = mid + 1

        return low

    def recordTweet(self, tweetName: str, time: int) -> None:

        i = self.search(time)
        if i < len(self._buf) and self._buf[i][0] == time:
            self._buf[i][1][tweetName] = self._buf[i][1].get(tweetName, 0) + 1
        else:
            self._buf.insert(i, (time, {tweetName: 1}))

    def getTweetCountsPerFrequency(self, freq: str, tweetName: str, startTime: int, endTime: int):
        if freq not in self._timestep:
            return []
        step, res = self._timestep[freq], []
        for s in range(startTime, endTime+1, step):
            l, r = self.search(s), self.search(min(s+step, endTime+1))
            res.append(sum(self._buf[i][1][tweetName] for i in range(l, r) if tweetName in self._buf[i][1]))
        return res


if __name__ == '__main__':

    obj = TweetCounts()

    obj.recordTweet("tweet3", 0)

    obj.recordTweet("tweet3", 60)

    obj.recordTweet("tweet3", 10)

    obj.getTweetCountsPerFrequency("minute", "tweet3", 0, 59)

    obj.getTweetCountsPerFrequency("minute", "tweet3", 0, 60)

    obj.recordTweet("tweet3", 120)

    obj.getTweetCountsPerFrequency("hour", "tweet3", 0, 120)