"""
1348. Tweet Counts Per Frequency

Implement the class TweetCounts that supports two methods:

1. recordTweet(string tweetName, int time)

Stores the tweetName at the recorded time (in seconds).
2. getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime)

Returns the total number of occurrences for the given tweetName per minute, hour, or day (depending on freq) starting from the startTime (in seconds) and ending at the endTime (in seconds).
freq is always minute, hour or day, representing the time interval to get the total number of occurrences for the given tweetName.
The first time interval always starts from the startTime, so the time intervals are [startTime, startTime + delta*1>,  [startTime + delta*1, startTime + delta*2>, [startTime + delta*2, startTime + delta*3>, ... , [startTime + delta*i, min(startTime + delta*(i+1), endTime + 1)> for some non-negative number i and delta (which depends on freq).


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
from collections import defaultdict
from bisect import bisect_right, insort, bisect


class TweetCounts:

    def __init__(self):
        self.T = defaultdict(list)
        self.delta = {'minute': 60, 'hour': 3600, 'day': 24 * 3600}

    def recordTweet(self, tweetName: str, time: int) -> None:
        insort(self.T[tweetName], time)

    def getTweetCountsPerFrequency(self, freq: str, tweetName: str, startTime: int, endTime: int) -> list:
        j = -1
        out = []
        for t in list(range(startTime - 1, endTime, self.delta[freq])) + [endTime]:
            k = bisect(self.T[tweetName], t)
            if j >= 0: out.append(k - j)
            j = k
        return out


class TweetCounts1:

    def __init__(self):
        self._freq = {'day': 24 * 3600, 'hour': 3600, 'minute': 60, 'second': 1}
        self._time_record = defaultdict(list)

    def recordTweet(self, tweetName: str, time: int) -> None:

        insort(self._time_record[tweetName], time)

    def getTweetCountsPerFrequency(self, freq: str, tweetName: str, startTime: int, endTime: int) -> list:

        if tweetName not in self._time_record:
            return []

        j = -1
        scope = list[range(startTime-1, endTime, self._freq[freq])] + [endTime]
        ans = []

        for c in scope:
            k = bisect_right(self._time_record[tweetName], c)
            if j >= 0:
                ans.append(k - j)
            j = k
        return ans


if __name__ == '__main__':

    tw = TweetCounts()

    tw.recordTweet("tweet3", 0)
    tw.recordTweet("tweet3", 60)
    tw.recordTweet("tweet3", 10)
    tw.getTweetCountsPerFrequency("minute", "tweet3", 0, 59)
    tw.getTweetCountsPerFrequency("minute", "tweet3", 0, 60)
    tw.recordTweet("tweet3", 120)
    tw.getTweetCountsPerFrequency("hour", "tweets", 0, 120)
