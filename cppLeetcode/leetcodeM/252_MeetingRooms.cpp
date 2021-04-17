/*
252. Meeting Rooms

Given an array of meeting time intervals where intervals[i] = [starti, endi], determine if a person could attend all meetings.

 

Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: false
Example 2:

Input: intervals = [[7,10],[2,4]]
Output: true
 

Constraints:

0 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti < endi <= 106

*/

#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using std::multiset;
using std::vector;
using std::priority_queue;


class CanAttendMeetings {

    /*
        252.Meeting-Rooms
        遍历所有的ｉｎｔｅｒｖａｌ，将这样所有的{start,1}和{end,-1}加入一个数组ｑ．然后将ｑ排序．注意，对于同一个时刻，{end,-1}会比{start,1}先处理．这在本题是合理的，因为所有的有效区间的长度都至少为１，这样的话类似[t,t]这样的区间就不会被包括进来．

        我们依次遍历这个ｑ的元素，将第二个ｌａｂｅｌ的值累加进ｃｏｕｎｔ．发现当count>1时，即说明有两个重合的区间，返回ｆａｌｓｅ
    */
    bool canAttendMeetings(vector<Interval>& intervals) 
    {
        vector<std::pair<int,int>>q;
        for (int i=0; i<intervals.size(); i++)
        {
            q.push_back({intervals[i].start,1});
            q.push_back({intervals[i].end,-1});
        }
        
        sort(q.begin(),q.end());
        
        int count = 0;
        for (int i=0; i<q.size(); i++)
        {
            count+=q[i].second;
            if (count>1) return false;
        }
        return true;
    }

public:

    /*
        Approach 2: Sorting
        The idea here is to sort the meetings by starting time. Then, go through the meetings one by one and make sure that each meeting ends before the next one starts.

        Complexity Analysis

        Time complexity : O(nlogn). The time complexity is dominated by sorting. Once the array has been sorted, only O(n)O(n) time is taken to go through the array and determine if there is any overlap.

        Space complexity : O(1). Since no additional space is allocated.
    */
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return true;
        }

        // Note: C++ sort function automatically sorts a vector first
        // by the 1st element, then by the 2nd element and so on.
        std::sort(intervals.begin(), intervals.end());
        for (size_t i = 0; i < intervals.size() - 1; i++) {
            if (intervals[i][1] > intervals[i + 1][0]) {
                return false;
            }
        }
        return true;
    }

    bool doit_(vector<vector<int>>& intervals) {
        std::sort(begin(intervals), end(intervals));
        int last = -1;
        
        for (auto& c : intervals) {
            if (c[0] < last) return false;    
            last = c[1];
        }
        return true;
    }
};

/*
253. Meeting Rooms II

Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.

Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2
Example 2:

Input: intervals = [[7,10],[2,4]]
Output: 1
 

Constraints:

1 <= intervals.length <= 104
0 <= starti < endi <= 106
*/


class MeetingRoomsII {

    struct Interval {
        int start, end;
    }
    /*
        253.Meeting-Rooms-II
        解法1:
        此题用到了sort和pq的组合拳，是一类题目的典型。

        先将intervals按照start进行从先到后排序。注意，这是解此类问题的一个常见步骤。

        然后我们构建一个pq，这个队列里按照end自动排序，end小的排在栈顶。我们令pq里面存装的是当前正在同时进行的会议。

        在遍历intervals元素的过程中，如果pq.top().end>intervals[i].start，说明正在进行的会议里，即使最早结束的那个，也都晚于当前考虑的会议intervals[i]的开始时间。没办法，但当前会议必须开，所以要将intervals[i]加入pq里面。pq的size因此变大。然后考虑下一个i，直至pq.top().end<=intervals[i].start。

        然后将pq弹出最早结束的一个会议，重复之前的操作，会有新的会议加入需要同时举行。

        输出结果就是pq在整个遍历过程中的最大size。

        对于pq的数据结构，我们在C++中还可以用multiset来实现，因为它也是自动有序的。

        解法2:
        将所有{startTime,1}和{endTime,-1}加入一个数组,然后将这个数组按照时间戳排序.注意,本题中所有的有效区间的长度必须大于0,所以,{time,-1}要比{time,1}排序更靠前.

        使用一个count依时间顺序将所有的+1/-1进行累加.当count>0的时候标志着一个会议的开始,重新归为0的时候标着一个会议的结束.
    */
    static bool cmp1(Interval a, Interval b)
    {
        return a.start<b.start;
    }
    struct cmp2
    {
        bool operator()(Interval a, Interval b)
        {
            return a.end>b.end;
        }            
    };
    
public:
    int minMeetingRooms(vector<Interval>& intervals) 
    {
        sort(intervals.begin(),intervals.end(),cmp1);
        
        priority_queue<Interval,vector<Interval>,cmp2>pq;
        
        int count=0;
        int i=0;
        while (i<intervals.size())
        {
            while (pq.empty() || i<intervals.size() && pq.top().end>intervals[i].start)
            {
                pq.push(intervals[i]);
                i++;
            }                
            int n=pq.size();
            count=max(count,n);
            pq.pop();
        }
        return count;
    }

public:

    static bool cmp1(Interval a, Interval b)
    {
        return a.start<b.start;
    }

    int minMeetingRooms(vector<Interval>& intervals) 
    {
        sort(intervals.begin(),intervals.end(),cmp1);
        multiset<int>Set;
        int count=0;
        int i=0;
        while (i<intervals.size())
        {            
            while (Set.size()==0 || i<intervals.size() && *Set.begin()>intervals[i].start)    
            {
                Set.insert(intervals[i].end);
                count = max(count,int(Set.size()));
                i++;                                
            }                                    
            Set.erase(Set.begin());                                     
        }
        return count;
    }


public:
    
    int doit_interval(vector<vector<int>>& intervals) {
        
        std::sort(begin(intervals), end(intervals));
        
        priority_queue<int, vector<int>, std::greater<>> pq;
        int res = 0;
        
        for (auto& c: intervals) {
            
            if (!pq.empty() && pq.top() <= c[0]) {
                pq.pop();
            }
            
            pq.push(c[1]);
            res = std::max(res, static_cast<int>(pq.size()));
        }
        
        return res;
    }
};