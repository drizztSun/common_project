/*
 1353. Maximum Number of Events That Can Be Attended

 Given an array of events where events[i] = [startDayi, endDayi]. Every event i starts at startDayi and ends at endDayi.

 You can attend an event i at any day d where startTimei <= d <= endTimei. Notice that you can only attend one event at any time d.

 Return the maximum number of events you can attend.

  

 Example 1:


 Input: events = [[1,2],[2,3],[3,4]]
 Output: 3
 Explanation: You can attend all the three events.
 One way to attend them all is as shown.
 Attend the first event on day 1.
 Attend the second event on day 2.
 Attend the third event on day 3.
 Example 2:

 Input: events= [[1,2],[2,3],[3,4],[1,2]]
 Output: 4
 Example 3:

 Input: events = [[1,4],[4,4],[2,2],[3,4],[1,1]]
 Output: 4
 Example 4:

 Input: events = [[1,100000]]
 Output: 1
 Example 5:

 Input: events = [[1,1],[1,2],[1,3],[1,4],[1,5],[1,6],[1,7]]
 Output: 7
  

 Constraints:

 1 <= events.length <= 105
 events[i].length == 2
 1 <= startDayi <= endDayi <= 105
 
 */
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <set>
#include <string>
#include <queue>

using std::priority_queue;
using std::vector;
using std::set;


class MaximumNumberEventsBeAttended {
    
public:

    int doit_heap_sort(vector<vector<int>>& events) {
        
        int maxendtime = 0;
        for (auto& c: events)
            maxendtime = std::max(maxendtime, c[1]);
        
        std::sort(begin(events), end(events), [](auto& a, auto& b) {
           return a[0] < b[0]; 
        });
        
        priority_queue<int, vector<int>, std::greater<int>> heap;
        int i = 0, ret = 0, startday = events[0][0];
        
        for (int day = startday; day <= maxendtime; day++) {
            
            while (i < events.size() && events[i][0] <= day)
                heap.push(events[i++][1]);
            
            while (!heap.empty() && heap.top() < day)
                heap.pop();
            
            if (!heap.empty()) {
                heap.pop();
                ret++;
            }
        }
        
        return ret;
    }

    /*
        We can use a TreeSet to maintain the open days and do a binary search to find the first available day.

        Time complexity: O(nlogd)
        Space complexity: O(d)
    */
    int doit_sort_1(vector<vector<int>>& events) {
        
        std::sort(begin(events), end(events), [](const auto&a, const auto& b) {
            return a[1] < b[1];
        });
        
        int min_d = INT_MAX, max_d = INT_MIN;
        
        for (const auto& e: events) {
            min_d = std::min(min_d, e[0]);
            max_d = std::max(max_d, e[1]);
        }
        
        vector<int> days(max_d - min_d + 1);
        std::iota(begin(days), end(days), min_d);
        // alldays use to join the meetings, sorted with "priority_queue". set could be the best choice of priority_queue.
        set<int> s(begin(days), end(days));
        
        int ans = 0;
        for (const auto& e :events) {
            auto it = s.lower_bound(e[0]);
            if (it == s.end() || *it > e[1])
                continue;
            s.erase(it);
            ++ans;
        }
        
        return ans;
    }

    /*
        1353.Maximum-Number-of-Events-That-Can-Be-Attended
        我们将所有的events按照开始时间来排序。然后维护一个按照时间结束时间从早到晚顺序的PQ。

        我们遍历所有的日期day（从1到最大的100000）。对于每一天，我们将所有起始日期在day的事件加入PQ，同时将PQ里已经过期的时间排除掉。此时PQ里面的所有events就是当天可以参加的。
        我们选择今天参加哪一个呢？我们自然是“贪心地”选择结束时间最早的那个，把机会用在“刀刃”上；至于deadline晚的事件都可以“拖一拖”，说不定以后总有机会去参加的。
    */
    static bool cmp(vector<int>&a, vector<int>&b)
    {
        return a[0] < b[0];
    }

    int maxEvents(vector<vector<int>>& events) 
    {
        sort(events.begin(), events.end(), cmp);
        priority_queue<int, vector<int>, std::greater<int>> pq;
        int i = 0;
        int ret = 0;

        for (int day=1; day<=100000; day++)
        {
            while (i<events.size() && events[i][0]<=day)
            {
                pq.push(events[i][1]);
                i++;
            }
            while (!pq.empty() && pq.top() < day)
                pq.pop();
            if (!pq.empty())
            {
                pq.pop();
                ret++;
            }
        }
        return ret;
    }
    
    /*
     Solution: Greedy
     Sort events by end time, for each event find the first available day to attend.

     Time complexity: O(sum(endtime – starttime)) = O(10^10)
     Space complexity: O(max(endtime – starttime) = O(10^5)
     TLE
     */
    int doit_sort(vector<vector<int>>& events) {
        
        std::sort(begin(events), end(events), [](const auto&a, const auto& b) {
            return a[1] < b[1];
        });
        
        char seen[100001] = {0};
        int ans = 0;
        for (const auto& e : events) {
            for (int i = e[0]; i <= e[1]; i++) {
                if (seen[i]) continue;
                
                ++seen[i];
                ++ans;
                break;
            }
        }
        
        return ans;
    }
};
