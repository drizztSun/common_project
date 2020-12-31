/*

57. Insert Interval

Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

 

Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
Example 3:

Input: intervals = [], newInterval = [5,7]
Output: [[5,7]]
Example 4:

Input: intervals = [[1,5]], newInterval = [2,3]
Output: [[1,5]]
Example 5:

Input: intervals = [[1,5]], newInterval = [2,7]
Output: [[1,7]]
 

Constraints:

0 <= intervals.length <= 104
intervals[i].length == 2
0 <= intervals[i][0] <= intervals[i][1] <= 105
intervals is sorted by intervals[i][0] in ascending order.
newInterval.length == 2
0 <= newInterval[0] <= newInterval[1] <= 105

*/
#include <vector>
#include <queue>

using std::priority_queue;
using std::vector;


class InsertIntervals {

public:

    vector<vector<int>> doit_greedy_1(vector<vector<int>>& intervals, vector<int>& newInterval) {

        vector<vector<int>> ans;
        bool merged = false;

        for (const auto& c : intervals) {

            if (!merged && !(c[0] > newInterval[1] || c[1] < newInterval[0])) {
                newInterval[1] = std::max(newInterval[1], c[1]);
                newInterval[0] = std::min(newInterval[0], c[0]);
                continue;
            }

            if (!merged && c[0] > newInterval[1]) {
                merged = true;
                ans.push_back(newInterval);
            }

            ans.push_back(c);
        }

        if (!merged)
            ans.push_back(newInterval);
            
        return ans;
    }

    /*
    057.Insert-Interval
    解法1：标准的插入
    将intervals的所有元素全部遍历一遍，可以想见会依次遇到这些情况：

    intervals[i]如果整体都在newInterval之前，则可以直接将intervals[i]加入results;
    intervals[i]如果和newInterval有交集，则与之融合生成新的newInterval；这样的融合可能会有若干次；
    while (i<intervals.size() && !(intervals[i].start>newInterval.end))
    {
        newInterval.start = min(newInterval.start,intervals[i].start);
        newInterval.end = max(newInterval.end,intervals[i].end);
        i++;
    }
    intervals[i]如果整体都在newInterval之后，则将newInterval（可能经历了融合）加入results，并把未遍历的intervals[i]也都加入results;

    解法2：priority_queue
    将所有intervals都放入一个priority_queue里，使其能按照start从小到大自动排序。
    每次取出栈顶元素，如果它与栈顶的第二个元素不重合，则将其加入结果数组；如果栈顶元素与栈顶的第二个元素区间重合，则将二者融合之后再次扔进这个priority_queue里。如此循环直至队列空。

    */    
    vector<vector<int>> doit_greedy(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        
        int i=0;
        
        while (i<intervals.size() && intervals[i][1] < newInterval[0])
        {
            result.push_back(intervals[i]);
            i++;
        }
        
        while (i<intervals.size() && !(intervals[i][0] > newInterval[1]))
        {
            newInterval[0] = std::min(newInterval[0],intervals[i][0];
            newInterval[1] = std::max(newInterval[1],intervals[i][1]);
            i++;
        }

        result.push_back(newInterval);
        
        while (i<intervals.size())
        {
            result.push_back(intervals[i]);
            i++;
        }   
        
        return result;
    }

    struct cmp
    {
        bool operator()(const vector<int>& a, const vector<int>& b)
        {
            return a[0] > b[0];
        }
    };

    vector<vector<int>> doit_greedy(vector<vector<int>>& intervals, vector<int> newInterval) 
    {
        priority_queue<vector<int>,vector<vector<int>>,cmp>q;

        for (int i=0; i<intervals.size(); i++)
            q.push(intervals[i]);
        q.push(newInterval);
        
        vector<vector<int>>results;
        while (!q.empty())
        {
            vector<int> x = q.top();
            q.pop();
            if (q.empty())
            {
                results.push_back(x);
                break;
            }
            
            vector<int> y = q.top();
            if (x[1] < y[0])
                results.push_back(x);
            else
            {
                q.pop();
                x[1] = std::max(x[1], y[1]);
                q.push(x);
            }
        }
        
        return results;
    }
};