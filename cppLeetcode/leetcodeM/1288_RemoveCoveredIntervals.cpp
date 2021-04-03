/*
1288. Remove Covered Intervals

Given a list of intervals, remove all intervals that are covered by another interval in the list.

Interval [a,b) is covered by interval [c,d) if and only if c <= a and b <= d.

After doing so, return the number of remaining intervals.

 

Example 1:

Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
Example 2:

Input: intervals = [[1,4],[2,3]]
Output: 1
Example 3:

Input: intervals = [[0,10],[5,12]]
Output: 2
Example 4:

Input: intervals = [[3,10],[4,10],[5,11]]
Output: 2
Example 5:

Input: intervals = [[1,2],[1,4],[3,4]]
Output: 1
 

Constraints:

1 <= intervals.length <= 1000
intervals[i].length == 2
0 <= intervals[i][0] < intervals[i][1] <= 10^5
All the intervals are unique.

*/
#include <vector>
#include <algorithm>

using std::vector;

class RemoveCoveredIntervals {

public:

    /*
    Approach 1: Greedy Algorithm
    Solution Pattern

    The idea of greedy algorithm is to pick the locally optimal move at each step, which would lead to the globally optimal solution.

    Typical greedy solution has \mathcal{O}(N \log N)O(NlogN) time complexity and consists of two steps:

    Figure out how to sort the input data. That would take \mathcal{O}(N \log N)O(NlogN) time, and could be done directly by sorting or indirectly by using heap data structure. 
    Usually sorting is better than heap usage because of gain in space.

    Parse the sorted input in \mathcal{O}(N)O(N) time to construct a solution.

    In the case of already sorted input, the greedy solution could have \mathcal{O}(N)O(N) time complexity, here is an example.

    Intuition

    Let us figure out how to sort the input. The idea to sort by start point is pretty obvious, because it simplifies further parsing:
    
    Complexity Analysis

    Time complexity : \mathcal{O}(N \log N)O(NlogN) since the sorting dominates the complexity of the algorithm.

    Space complexity : \mathcal{O}(N)O(N) or \mathcal{O}(\log{N})O(logN)

    The space complexity of the sorting algorithm depends on the implementation of each program language.

    For instance, the sorted() function in Python is implemented with the Timsort algorithm whose space complexity is \mathcal{O}(N)O(N).

    In Java, the Arrays.sort() is implemented as a variant of quicksort algorithm whose space complexity is \mathcal{O}(\log{N})O(logN).
    */
    int doit_sort(vector<vector<int>>& intervals) {

        std::sort(begin(intervals), end(intervals), [](auto& a, auto&b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
        });
        
        int curend = 0, count = 0;

        for (auto& c : intervals) {
            
            if (c[1] > curend) {
                curend = c[1];
                count++;
            }
        }

        return count;
    }

    /*
    1288.Remove-Covered-Intervals
    将所有的区间按照左端点排序，如果左端点相同的话，优先处理大区间。

    我们顺序处理某个区间i，假设为[a,b]：后面的区间j的左端点一定都比a晚，如果j的右端点也比b早的话，那么j一定就是被包含在i里面的。
    我们可能会遇到若干个这样的j，但区间j会越来越靠右。直至发现j的右端点比b晚，说明j已经跑出了i的覆盖范围，那么我们就把j当作i，重复之前的操作。
    */
    int doit_sort(vector<vector<int>>& intervals) {

        sort(intervals.begin(), intervals.end(), [](auto& a, auto&b) {
            if (a[0] != b[0]) return a[0] < b[0];
            return a[1] > b[1];
        });

        int i = 0;
        int count = 0;
        while (i < intervals.size())
        {
            count++;
            int j=i+1;
            while (j<intervals.size() && intervals[j][1] <= intervals[i][1])
                j++;
            i = j;
        }
        return count;
    }
};