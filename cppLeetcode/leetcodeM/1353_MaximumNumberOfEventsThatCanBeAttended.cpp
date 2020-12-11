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


using std::vector;
using std::set;


class MaximumNumberEventsBeAttended {
    
public:
    
    /*
     Solution: Greedy
     Sort events by end time, for each event find the first available day to attend.

     Time complexity: O(sum(endtime – starttime)) = O(10^10)
     Space complexity: O(max(endtime – starttime) = O(10^5)
     
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
        //itoa(begin(days), end(days), min_d);
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
    
};
