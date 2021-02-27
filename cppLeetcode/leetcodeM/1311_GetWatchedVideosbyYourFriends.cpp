/*
1311. Get Watched Videos by Your Friends


There are n people, each person has a unique id between 0 and n-1. Given the arrays watchedVideos and friends, where watchedVideos[i] and friends[i] contain the list of watched videos and the list of friends respectively for the person with id = i.

Level 1 of videos are all watched videos by your friends, level 2 of videos are all watched videos by the friends of your friends and so on. 
In general, the level k of videos are all watched videos by people with the shortest path exactly equal to k with you. Given your id and the level of videos, return the list of videos ordered by their frequencies (increasing). 
For videos with the same frequency order them alphabetically from least to greatest.  

Example 1:

Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
Output: ["B","C"] 
Explanation: 
You have id = 0 (green color in the figure) and your friends are (yellow color in the figure):
Person with id = 1 -> watchedVideos = ["C"] 
Person with id = 2 -> watchedVideos = ["B","C"] 
The frequencies of watchedVideos by your friends are: 
B -> 1 
C -> 2

Example 2:

Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
Output: ["D"]
Explanation: 
You have id = 0 (green color in the figure) and the only friend of your friends is the person with id = 3 (yellow color in the figure).
 

Constraints:

n == watchedVideos.length == friends.length
2 <= n <= 100
1 <= watchedVideos[i].length <= 100
1 <= watchedVideos[i][j].length <= 8
0 <= friends[i].length < n
0 <= friends[i][j] < n
0 <= id < n
1 <= level < n
if friends[i] contains j, then friends[j] contains i
*/

#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <deque>

using std::deque;
using std::unordered_map;
using std::unordered_set;
using std::queue;
using std::string;
using std::vector;


class WatchedVideosByFriends {

    /*
        1311.Get-Watched-Videos-by-Your-Friends
        假设某人是自己的好友的好友，同时也是自己的直接好友，那么只能记做是level为1的好友。因此此题注定用BFS的效率更高。

        我们先用BFS找到level为k的好友，然后取出他们所看过的视频。再统计这些视频的观看次数。最后排序。
    */
    vector<string> doit_bfs(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) 
    {
        int n = watchedVideos.size();
        vector<int>visited(n,0);

        queue<int>q;        
        q.push(id);
        visited[id] = 1;

        int step = 0;
        vector<int>persons;
        while (!q.empty())
        {
            int len = q.size();
            step += 1;
            while (len--)
            {
                int cur = q.front();
                q.pop();

                for (auto f: friends[cur])
                {
                    if (visited[f]==1) continue;
                    visited[f] = 1;
                    q.push(f);
                    if (step==level)
                        persons.push_back(f);
                }
            }
            if (step==level) break;
        }

        unordered_set<string>VideoSet;
        for (auto p: persons)
            for (auto v: watchedVideos[p])
                VideoSet.insert(v);

        unordered_map<string,int>freq;
        for (auto p: persons)
            for (auto v: watchedVideos[p])
                freq[v] += 1;
        
        vector<std::pair<int,string>>temp;
        for (auto v: VideoSet)
            temp.push_back({freq[v], v});

        sort(temp.begin(), temp.end());

        vector<string>rets;
        for (auto x: temp)
            rets.push_back(x.second);
        return rets;
    }

public:

    vector<string> doit_(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
 
        deque<int> que;
        que.push_back(id);
        
        unordered_set<int> visited;
        visited.insert(id);
        
        unordered_map<string, int> levelorders;
        
        while (!que.empty() && level != -1) {
            
            int size = que.size();
            while (size--) {
                
                int person = que.front();
                que.pop_front();
                
                if (level == 0)
                    for (auto video : watchedVideos[person])
                        levelorders[video]++;
                    
                for (auto child : friends[person]) {
                    if (visited.count(child) > 0) continue;
                    que.push_back(child);
                    visited.insert(child);
                }
            }
            
            level--;
        }
        
        if (levelorders.empty()) return {};
        
        vector<std::pair<int, string>> ans;
        for (auto c: levelorders) {
            ans.push_back({c.second, c.first});
        }
        
        sort(begin(ans), end(ans));
        
        vector<string> res;
        for (auto c: ans) {
            res.push_back(c.second);
        }
        
        return res;
    }
};