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
 
    int _timestamp = 0;
    std::unordered_map<int, std::set<int>> _follower;
    std::unordered_map<int, std::vector<pair<int, int>>> _posts;
    
    
public:
    /** Initialize your data structure here. */
    Twitter() {}
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        _posts[userId].push_back({_timestamp, tweetId});
        _timestamp++;
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        std::vector<int> people(_follower[userId].begin(), _follower[userId].end());
        people.push_back(userId);
        
        std::priority_queue<std::pair<int, std::pair<int, int>>> buf;
        for (auto c : people) {
            if (_posts[c].size() > 0)
                buf.push({_posts[c].back().first, {_posts[c].size()-1, c}});
        }
        
        vector<int> res;
        int n = 10;
        while (buf.size() && n--) {
            
            auto c = buf.top();
            buf.pop();
            
            auto index = c.second.first, id = c.second.second;
            res.push_back(_posts[id][index].second);
            
            index--;
            
            if (index >= 0) {
                buf.push({_posts[id][index].first, {index, id}});
            }
        }
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

class Twitter {
    
    int _timestamp = 0;
    std::unordered_map<int, std::set<int>> _follower;
    std::unordered_map<int, std::vector<pair<int, int>>> _posts;
    
    
public:
    /** Initialize your data structure here. */
    Twitter() {}
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        _posts[userId].push_back({_timestamp, tweetId});
        _timestamp++;
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        std::vector<int> people(_follower[userId].begin(), _follower[userId].end());
        people.push_back(userId);
        
        std::priority_queue<std::pair<int, std::pair<int, int>>> buf;
        for (auto c : people) {
            if (_posts[c].size() > 0)
                buf.push({-_posts[c][0].first, {0, c}});
        }
        
        vector<int> allposts;
        while (buf.size()) {
            
            auto c = buf.top();
            auto index = c.second.first, one = c.second.second;
            
            allposts.push_back(_posts[one][index].second);
            buf.pop();
            index++;
            
            if (index < _posts[one].size()) {
                buf.push({-_posts[one][index].first, {index, one}});
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


/*
355.Design-Twitter
设计如下的数据结构：
unordered_map<int,set>Friends; //记录每个用户的好友（包括自己）
int global_id; // 全局变量，记录所有推文的时间顺序。
unordered_map<int,vector<pair<int,int>>>Tweets; // 记录每个用户发推的global_id和tweetID。

在getNewsFeed时，遍历所有好友的推文记录，寻找最近的10个。
基本思路是构造一个数据结构news，每次放进一个推文，news能够自动保持根据global_id保持有序。什么数据结构能实现这个功能呢？有两个方案：priority_queue，或者有序set。考虑到set里的元素已经是pair，并且其自动排序就是依照pair的第一个key从小到大，在这里更为方便。

        set<pair<int,int>>news;  //第一个key是推文的global_id，第二个才是其tweetId
        for (auto i:friends[userId]) //遍历所有userId的好友
        {
            for (int j=tweets[i].size()-1; j>=0; j--) //遍历该好友的所有推文，从最近的开始
            {
                if (news.size()<10)
                    news.insert(tweets[i][j]);   // 加入新元素后，news会自动排序
                else if (tweets[i][j].first> news.begin()->first)  //如果新元素比news的首元素更新，说明可以入列
                {
                    news.erase(news.begin());  //删除map的首元素
                    news.insert(tweets[i][j]);  //在map里加入元素
                }
                else
                    break;
            }
        }
*/
class Twitter {
    unordered_map<int,set<int>>friends;
    unordered_map<int,vector<pair<int,int>>>tweets;
    int global_id;

public:
    /** Initialize your data structure here. */
    Twitter() 
    {
        global_id = 0;
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) 
    {
        follow(userId,userId);
        tweets[userId].push_back({global_id,tweetId});
        global_id++;
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) 
    {
        set<pair<int,int>>news;
        for (auto i:friends[userId])
        {
            for (int j=tweets[i].size()-1; j>=0; j--)
            {
                if (news.size()<10)
                    news.insert(tweets[i][j]);
                else if (tweets[i][j].first > news.begin()->first)
                {
                    news.erase(news.begin());
                    news.insert(tweets[i][j]);
                }
                else
                    break;
            }
        }
        
        vector<int>results;
        for (auto a:news)
        {
            results.push_back(a.second);
        }
        reverse(results.begin(),results.end());
        return results;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) 
    {
        friends[followerId].insert(followeeId);
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) 
    {
        if (followerId!=followeeId)
            friends[followerId].erase(followeeId);
    }
};
