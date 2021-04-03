/*

435. Non-overlapping Intervals


Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

 

Example 1:

Input: [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.
Example 2:

Input: [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.
Example 3:

Input: [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
 

Note:

You may assume the interval's end point is always bigger than its start point.
Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.



*/
#include <vector>
#include <algorithm>

using std::vector;



class EraseOverlapIntervals {

    /*
        435.Non-overlapping-Intervals
        此题和452. Minimum Number of Arrows to Burst Balloons非常类似，都是利用一个排序解决问题．

        将所有的区间按照右边界进行排序．

        我们来到当前右边界最小（成为right）的那个区间，从排序后的interval中找到所有start小于当前这个右边界right的区间．这些区间都是可以删掉的！这是因为这些区间都互相重合，必然只能保留一个．
        而保留哪一个呢？就是保留当前这个右边界最小的区间，因为其他区间的右边界都较大，可能会造成对后面区间的重合，有潜在的风险，去掉他们最保险．

        或者我们这样理解：为了保留更多的区间数目，在众多重合的区间里面，我们会优先选择右端点靠前的区间。因为它对后续的影响最小，有更大的概率让更多的区间出现。


        Interval questions
            Greedy

            1. Sweepline / diff
            2. Sort

                sort by start points => the minimum number of intervals to cover the whole range.
                sort by ending points => the maximum number of intervals that are non-overlapping.
    */

public:
    
    int doit_sort(vector<vector<int>>& intervals) {
        std::sort(begin(intervals), end(intervals), [](const auto& a, const auto& b) {
           return a[1] < b[1]; 
        });
        
        int endtime = INT_MIN, removed = 0;
        for (const auto& c : intervals) {
            if (c[0] >= endtime)
                endtime = c[1];
            else
                removed++;
        }
        
        return removed;
    }

    int doit_sort_1(vector<vector<int>>& intervals) 
    {
        std::sort(begin(intervals), end(intervals), [](const auto& a, const auto& b) {
           return a[1] < b[1]; 
        });

        int i = 0, count = 0;

        while (i<intervals.size())
        {
            count++;
            int j = i+1;
            while (j<intervals.size() && intervals[j][0] < intervals[i][1])
                j++;
            i = j;
        }
        return intervals.size()-count;
    }
};