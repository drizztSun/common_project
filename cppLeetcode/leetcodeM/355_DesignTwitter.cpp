/*
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
 */

#include <stdio.h>
#include <queue>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Twitter {
    
    std::unordered_map<int, std::set<int>> _follower;
    int _timestamp = 0;
    std::unordered_map<int, std::vector<pair<int, int>>> _posts;
    
    
public:
    /** Initialize your data structure here. */
    Twitter() {
        
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        _posts[userId].push_back(make_pair(_timestamp, tweetId));
        _timestamp++;
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        std::vector<int> people(_follower[userId].begin(), _follower[userId].end());
        people.push_back(userId);
        
        std::priority_queue<std::pair<int, std::pair<int, int>>> buf;
        for (auto c : people) {
            if (_posts[c].size() > 0)
                buf.push({-_posts[c][0].first, std::make_pair(0, c)});
        }
        
        vector<int> allposts;
        while (buf.size()) {
            
            auto c = buf.top();
            auto index = c.second.first, one = c.second.second;
            
            allposts.push_back(_posts[one][index].second);
            buf.pop();
            index++;
            
            if (index < _posts[one].size()) {
                buf.push({-_posts[one][index].first, std::make_pair(index, one)});
            }
        }
        
        vector<int> res;
        int n = 10;
        
        for (auto it = allposts.rbegin(); n > 0 && it != allposts.rend(); it++, n--)
            res.push_back(*it);
        
        return res;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            _follower[followerId].insert(followeeId);
        }
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            _follower[followerId].erase(followeeId);
        }
    }
};


void test_355_design_twitter() {
    
    Twitter obj1;
    
    obj1.postTweet(1, 5);
    
    obj1.postTweet(1, 3);
    
    obj1.getNewsFeed(1);
    
    Twitter obj;
    obj.postTweet(1, 5);
    auto a = obj.getNewsFeed(1);
    obj.follow(1, 2);
    
    obj.postTweet(2, 6);
    obj.getNewsFeed(1);
    
    obj.unfollow(1, 2);
    auto b = obj.getNewsFeed(1);
    

}
