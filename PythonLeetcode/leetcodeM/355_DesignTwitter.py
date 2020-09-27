"""
355. Design Twitter

Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:

postTweet(userId, tweetId): Compose a new tweet.
getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
follow(followerId, followeeId): Follower follows a followee.
unfollow(followerId, followeeId): Follower unfollows a followee.
Example:

Twitter twitter = new Twitter();

// User 1 posts a new tweet (id = 5).
twitter.postTweet(1, 5);

// User 1's news feed should return a list with 1 tweet id -> [5].
twitter.getNewsFeed(1);

// User 1 follows user 2.
twitter.follow(1, 2);

// User 2 posts a new tweet (id = 6).
twitter.postTweet(2, 6);

// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.getNewsFeed(1);

// User 1 unfollows user 2.
twitter.unfollow(1, 2);

// User 1's news feed should return a list with 1 tweet id -> [5],
// since user 1 is no longer following user 2.
twitter.getNewsFeed(1);

"""
from collections import defaultdict, deque
from heapq import heappush, heappop

class Twitter:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.follower = defaultdict(set)
        self.timestamp = 0
        self.post = defaultdict(deque)

    def postTweet(self, userId: int, tweetId: int):
        """
        Compose a new tweet.
        """
        self.post[userId].append((self.timestamp, tweetId))
        if len(self.post[userId]) > 10:
            self.post[userId].popleft()
        self.timestamp += 1

    def getNewsFeed(self, userId: int):
        """
        Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself.
        Tweets must be ordered from most recent to least recent.
        """
        followee = [c for c in self.follower[userId]] + [userId]
        buf = []

        for c in set(followee):
            if self.post[c]:
                heappush(buf, (self.post[c][0], 0, c))

        res = []
        while buf:
            t, i, c = heappop(buf)
            res.append(t[1])

            if i + 1 < len(self.post[c]):
                i += 1
                heappush(buf, (self.post[c][i], i, c))

        return res[-1:-11:-1]

    def follow(self, followerId: int, followeeId: int):
        """
        Follower follows a followee. If the operation is invalid, it should be a no-op.
        """
        if followerId != followeeId:
            self.follower[followerId].add(followeeId)

    def unfollow(self, followerId: int, followeeId: int):
        """
        Follower unfollows a followee. If the operation is invalid, it should be a no-op.
        """
        if followerId != followeeId and followeeId in self.follower[followerId]:
            self.follower[followerId].remove(followeeId)


if __name__ == '__main__':

    tw = Twitter()

    tw.postTweet(1, 5)

    print( tw.getNewsFeed(1) )

    tw.follow(1, 2)

    tw.postTweet(2, 6)

    print( tw.getNewsFeed(1) )

    tw.unfollow(1, 2)

    print( tw.getNewsFeed(1) )

    tw = Twitter()

    tw.postTweet(1, 4)

    tw.postTweet(2, 5)

    tw.unfollow(1, 2)

    tw.getNewsFeed(1)

    tw = Twitter()

    tw.postTweet(1, 5)
    tw.postTweet(1, 3)
    tw.postTweet(1, 101)
    tw.postTweet(1, 13)
    tw.postTweet(1, 10)
    tw.postTweet(1, 2)
    tw.postTweet(1, 94)
    tw.postTweet(1, 505)
    tw.postTweet(1, 333)
    tw.postTweet(1, 22)
    tw.postTweet(1, 11)

    print(tw.getNewsFeed(1))

