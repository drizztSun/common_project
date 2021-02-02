/*
630. Course Schedule III

There are n different online courses numbered from 1 to n. Each course has some duration(course length) t and closed on dth day. A course should be taken continuously for t days and must be finished before or on the dth day. 
You will start at the 1st day.

Given n online courses represented by pairs (t,d), your task is to find the maximal number of courses that can be taken.

Example:

Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
Output: 3
Explanation: 
There're totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
 

Note:

The integer 1 <= d, t, n <= 10,000.
You can't take two courses simultaneously.


*/
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;

class CourseScheduleIII {
    /*
        630.Course-Schedule-III
        本题本质是贪心法，需要人工设计出最优策略。应用层面上用到了数组排序+PQ的组合，很像502.IPO，但是本题的最优策略要独立思考出来更有难度。

        我们尝试按照时间先后顺序来看这些课程．毕竟哪个deadline在前我们就先处理谁，也是非常合情合理的．我们假设在某个课程的deadline之前，手头有一堆的备选课程，我们做其中哪些呢？显然我们做哪些时长要求最少的，从最短的做起，
        做一个扔掉一个，能做多少做多少，做不完的就扔了，这就是最优的方案了．注意，做不完的不用保留在pool里，因为过了当前的这个deadline之后这些未做的课程就失效了．

        假设我们当前已经修了Ｎ门．那么接下来又到了下一个deadline，也就是deadline放宽了，但我们又新添了一门课变成N+1门．如果能赶在新deadline之前搞定这门新课，我们自然就是能上就上（那样就是N+1门）．
        如果不能呢？我们自然怪罪当前N+1课程列表里最长的那门，我们只要把那门最长的踢掉就一定满足deadline的要求．(为什么？因为我们之前保证了Ｎ门可以满足上一个deadline，那么现在的Ｎ门一定也可以满足当前的deadline．)于是，
        如今虽然同样还是只能修Ｎ门，但是踢掉了一个最长的课程，也算是把已修课程列表在时间上给优化了．

        于是我们一个接一个的处理deadline,这样得到的就是总的最优方案．

    */
    static bool cmp(vector<int>a,vector<int>b) {
        return a[1] < b[1];
    }

public:
    int scheduleCourse(vector<vector<int>>& courses) 
    {
        sort(courses.begin(),courses.end(),cmp);        
        
        priority_queue<int> pq;        
        
        int day = 0;
        
        for (int i = 0; i < courses.size(); i++)
        {
            if (day + courses[i][0] <= courses[i][1])
            {
                day += courses[i][0];
                pq.push(courses[i][0]);
            }
            else
            {
                if (!pq.empty() && pq.top() > courses[i][0])
                {
                    day = day - pq.top() + courses[i][0];
                    pq.pop();
                    pq.push(courses[i][0]);
                }
            }
        }
        
        return pq.size();
    }
    
    int doit_(vector<vector<int>>& courses) {
        
        // sort array by end time, so we can handle the one has earyly end time, then means we can handle more,
        // if end time is same, we handle smaller duration one first.
        std::sort(begin(courses), end(courses), [](const auto& a, const auto& b) {
           return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]); 
        });
        
        int start = 0;
        std::priority_queue<int> heap; // It is max heap, it is gonna sort the item by duration time.
        for (auto& c : courses) {
            // base on current time handle new tasks, starttime will be increasing c[0]
            start += c[0];
            heap.push(c[0]);
            
            // after that, if we it is bigger than end time, we have to remove some items.
            // it always put biggest duration one on the top, so it should be ok to remove one, to satisfy the requirement.
            // because it would be top[0] >= c[0]
            while (start > c[1]){
                start -= heap.top();
                heap.pop();
            }
        }
        
        return heap.size();
    }
};