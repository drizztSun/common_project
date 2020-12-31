/*
253. Meeting Rooms II


Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

Example 1:

Input: [[0, 30],[5, 10],[15, 20]]
Output: 2
Example 2:

Input: [[7,10],[2,4]]
Output: 1

*/
#include <vector>
#include <queue>
#include <algorithm>

using std::priority_queue;
using std::vector;


class MinimumMeetingRooms {

public:
    
    int doit_heap(vector<vector<int>>& intervals) {
        
        priority_queue<int, vector<int>, std::greater<int>> qu;

        std::sort(begin(intervals), end(intervals));

        for (int i = 0; i < intervals.size(); i++) {

            if (!qu.empty() && qu.top() <= intervals[i][0])
                qu.pop();

            qu.push(intervals[i][1]);
        }
        
        return qu.size();
    }
};