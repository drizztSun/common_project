/*
 
 1606. Find Servers That Handled Most Number of Requests
 
 You have k servers numbered from 0 to k-1 that are being used to handle multiple requests simultaneously.
 Each server has infinite computational capacity but cannot handle more than one request at a time.
 The requests are assigned to servers according to a specific algorithm:

 The ith (0-indexed) request arrives.
 If all servers are busy, the request is dropped (not handled at all).
 If the (i % k)th server is available, assign the request to that server.
 Otherwise, assign the request to the next available server (wrapping around the list of servers and starting from 0 if necessary).
 For example, if the ith server is busy, try to assign the request to the (i+1)th server, then the (i+2)th server, and so on.
 You are given a strictly increasing array arrival of positive integers, where arrival[i] represents the arrival time of the ith request,
 and another array load, where load[i] represents the load of the ith request (the time it takes to complete).
 
 Your goal is to find the busiest server(s). A server is considered busiest if it handled the most number of requests successfully among all the servers.

 Return a list containing the IDs (0-indexed) of the busiest server(s). You may return the IDs in any order.

  

 Example 1:


 Input: k = 3, arrival = [1,2,3,4,5], load = [5,2,3,3,3]
 Output: [1]
 Explanation:
 All of the servers start out available.
 The first 3 requests are handled by the first 3 servers in order.
 Request 3 comes in. Server 0 is busy, so it's assigned to the next available server, which is 1.
 Request 4 comes in. It cannot be handled since all servers are busy, so it is dropped.
 Servers 0 and 2 handled one request each, while server 1 handled two requests. Hence server 1 is the busiest server.
 Example 2:

 Input: k = 3, arrival = [1,2,3,4], load = [1,2,1,2]
 Output: [0]
 Explanation:
 The first 3 requests are handled by first 3 servers.
 Request 3 comes in. It is handled by server 0 since the server is available.
 Server 0 handled two requests, while servers 1 and 2 handled one request each. Hence server 0 is the busiest server.
 Example 3:

 Input: k = 3, arrival = [1,2,3], load = [10,12,11]
 Output: [0,1,2]
 Explanation: Each server handles a single request, so they are all considered the busiest.
 Example 4:

 Input: k = 3, arrival = [1,2,3,4,8,9,10], load = [5,2,10,3,1,2,2]
 Output: [1]
 Example 5:

 Input: k = 1, arrival = [1], load = [1]
 Output: [0]
  

 Constraints:

 1 <= k <= 105
 1 <= arrival.length, load.length <= 105
 arrival.length == load.length
 1 <= arrival[i], load[i] <= 109
 arrival is strictly increasing.

 
 
 */

#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <map>

using std::multimap;
using std::priority_queue;
using std::set;
using std::vector;


class BusiestServers {
    
public:

    /*
        1606.Find-Servers-That-Handled-Most-Number-of-Requests
        我们希望能有一个集合free，里面存放当前空闲的服务器id。如果这个集合是有序的，那么显然我们就很容易用二分法找到我们想要操作的服务器（也就是第一个大于等于i%k的机器，如果没有，就找id最小的机器）。然后我们会将这个机器从集合中删除。然后处理下一个任务。

        那么如何往free里面添加已经完成任务的呢？我们可以在处理任务i的时候，将所有arrival[i]之前就已经完工的机器加入到free里面。因此我们可以维护一个busy的优先队列，存放的都是正在工作的机器，并且按照预期完工时间从早到晚排序。因此每次我们找到处理任务i的机器时，记得将它加入busy队列。

        最终我们将每台机器被指派的任务累加起来找到最大值即可。

        时间复杂度分析：外层的循环是o(N)。内层对于free而言，每层循环有固定一次的查找、删除；对于busy而言，有固定一次的弹出。考虑到free和busy最长是K，所以最终时间复杂度大概是O(N*logK)
    
    */
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) 
    {
        priority_queue<std::pair<int,int>, vector<std::pair<int,int>>, std::greater<std::pair<int,int>>>busy;
        set<int>free;
        for (int i=0; i<k; i++)
            free.insert(i);
        vector<int>count(k,0);
        
        for (int i=0; i<arrival.size(); i++)
        {
            while (!busy.empty() && busy.top().first <= arrival[i])
            {                
                free.insert(busy.top().second);
                busy.pop();
            }
            
            if (free.empty()) continue;
            
            auto iter = free.lower_bound(i%k);
            if (iter == free.end())
                iter = free.begin();
            
            int id = *iter;
            count[id] += 1;
            free.erase(id);
            busy.push({arrival[i]+load[i], id});            
        }
        
        vector<int>ret;
        int maxCount = *max_element(count.begin(), count.end());
        for (int i=0; i<k; i++)
            if (count[i]==maxCount)
                ret.push_back(i);
        return ret;
    }

    vector<int> doit_heap_1(int k, vector<int>& arrival, vector<int>& load) {
        
        multimap<int, int> running;
        vector<int> res(k);
        set<int> idles;
        
        for (int i = 0; i < k; i++) {
            idles.insert(i);
        }
        
        for (int i = 0; i < arrival.size(); i++) {
            
            int start = arrival[i], end = arrival[i] + load[i];
            while (!running.empty() && running.begin()->first <= start) {
                auto it = running.begin();
                idles.insert(it->second);
                running.erase(it);
            }
            
            
            if (idles.empty()) continue;
            
            auto it = idles.lower_bound(i % k);
            if (it == idles.end())
                it = idles.begin();
            
            int id = *it;
            idles.erase(it);
            res[id]++;
            running.insert({end, id});
        }
        
        int busiest = *max_element(begin(res), end(res));
        vector<int> ans;
        for (int i = 0; i < res.size(); i++)
            if (res[i] == busiest) ans.push_back(i);
        
        return ans;
    }

    
    vector<int> doit_heap(int k, vector<int>&& arrival, vector<int>&& load) {
     
        priority_queue<std::pair<int, int>, vector<std::pair<int,int>>, std::greater<>> q;
        
        set<int> idle_servers;
        vector<int> tasks(k);
        
        for (int i = 0; i < k; i++) {
            idle_servers.insert(i);
        }
        
        for (int i = 0; i < arrival.size(); i++) {
            
            int s = arrival[i], e = arrival[i] + load[i];
            
            // Release servers has done its jobs
            while (!q.empty() && q.top().first <= s) {
                idle_servers.insert(q.top().second);
                q.pop();
            }
            
            // No servers available
            if (idle_servers.empty())
                continue;
            
            auto id = idle_servers.lower_bound(i%k);
            if (id == idle_servers.end())
                id = begin(idle_servers);
            
            const int server_id = *id;
            
            q.push({e, server_id});
            tasks[server_id]++;
            idle_servers.erase(id);
        }
        
        const int max_req = *max_element(begin(tasks), end(tasks));
        vector<int> ans;
        
        for (int i = 0; i < k; i++) {
            if (tasks[i] == max_req)
                ans.push_back(i);
        }
        
        return ans;
    }
};

void test_1606_find_buiest_server() {
    
    BusiestServers().doit_heap(3, vector<int>{1,2,3,4,8,9,10}, vector<int>{5,2,10,3,1,2,2});
}
