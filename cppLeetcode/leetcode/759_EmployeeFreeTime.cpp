/*
759. Employee Free Time

We are given a list schedule of employees, which represents the working time for each employee.

Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.

Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.

(Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays. 
For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined).  Also, we wouldn't include intervals like [5, 5] in our answer, as they have zero length.

 

Example 1:

Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation: There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.
Example 2:

Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]
 

Constraints:

1 <= schedule.length , schedule[i].length <= 50
0 <= schedule[i].start < schedule[i].end <= 10^8

*/

/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

#include <vector>
#include <unordered_map>
#include <map>

using std::map;
using std::unordered_map;
using std::vector;

class EmployeeFreeTime {

    class Interval {
    public:
        int start;
        int end;

        Interval() {}

        Interval(int _start, int _end) {
            start = _start;
            end = _end;
        }
    };

public:

    // Data scope is so big, if travels from minv to maxv, it is gonna TLE. so each meaningful point will be count.
    vector<Interval> doit_sweepline(vector<vector<Interval>> schedule) {
        
        int minv = INT_MAX, maxv = INT_MIN;
        
        map<int, int> points;

        for (const auto& s: schedule) {
            
            for (const auto& c: s) {
                int s = c.start, e = c.end;
                minv = std::min(minv, s);
                maxv = std::max(maxv, e);
                
                points[s]++;
                points[e]--;
            }
        }
        
        vector<Interval> ans;
        int count = 0, start = INT_MIN;

        for (auto it: points) {
            
            int p = it.first, cnt = it.second;
            int last = count;
            count += cnt;
            
            if (last != 0 && count == 0) {
                start = p;
            }
            
            if (last == 0 && count != 0 && start != INT_MIN) {
                ans.push_back(Interval(start, p));
            }
        }
    
        return ans;
    }

    /*
        Approach #1: Events (Line Sweep) [Accepted]
        Intuition

        If some interval overlaps any interval (for any employee), then it won't be included in the answer. So we could reduce our problem to the following: given a set of intervals, find all places where there are no intervals.

        To do this, we can use an "events" approach present in other interval problems. For each interval [s, e], we can think of this as two events: balance++ when time = s, and balance-- when time = e. We want to know the regions where balance == 0.

        Algorithm

        For each interval, create two events as described above, and sort the events. Now for each event occuring at time t, if the balance is 0, then the preceding segment [prev, t] did not have any intervals present, where prev is the previous value of t.


        Complexity Analysis

        Time Complexity: O(ClogC), where CC is the number of intervals across all employees.

        Space Complexity: O(C).
    */
    vector<Interval> doit_(vector<vector<Interval>> schedule) {

        int OPEN = 1, CLOSE = -1;

        vector<vector<int>> events;
        for (const auto& c : schedule) {
            for (const auto& interval: c) {
                events.push_back({interval.start, OPEN});
                events.push_back({interval.end, CLOSE});
            }
        }

        std::sort(begin(events), end(events), [](auto& a, auto& b){
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
        });

        vector<Interval> ans;
        int prev = -1, bal = 0;
        for (auto& event: events) {

            if (bal == 0 && prev >= 0)
                ans.push_back(Interval(prev, event[0]));

            bal += event[1] == OPEN ? 1 : -1;
            prev = event[0];
        }

        return ans;
    }

};