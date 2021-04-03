/*
1272. Remove Interval

A set of real numbers can be represented as the union of several disjoint intervals, where each interval is in the form [a, b). A real number x is in the set if one of its intervals [a, b) contains x (i.e. a <= x < b).

You are given a sorted list of disjoint intervals intervals representing a set of real numbers as described above, where intervals[i] = [ai, bi] represents the interval [ai, bi). You are also given another interval toBeRemoved.

Return the set of real numbers with the interval toBeRemoved removed from intervals. 

In other words, return the set of real numbers such that every x in the set is in intervals but not in toBeRemoved. Your answer should be a sorted list of disjoint intervals as described above.

 

Example 1:


Input: intervals = [[0,2],[3,4],[5,7]], toBeRemoved = [1,6]
Output: [[0,1],[6,7]]
Example 2:


Input: intervals = [[0,5]], toBeRemoved = [2,3]
Output: [[0,2],[3,5]]
Example 3:

Input: intervals = [[-5,-4],[-3,-2],[1,2],[3,5],[8,9]], toBeRemoved = [-1,4]
Output: [[-5,-4],[-3,-2],[4,5],[8,9]]
 

Constraints:

1 <= intervals.length <= 10^4
-10^9 <= ai < bi <= 10^9
*/
#include <vector>

using std::vector;


class RemoveInterval {

    /*
                1272.Remove-Interval
        此题考查了对于两个区间相对关系的代码描述。假设有我们考察的区间是a，toBeRemoved的区间是b：

        如果a和b不相交：if (a[1]<=b[0] || a[0]>=b[1]，那么就将a加入结果。
        剩下的情况就是a和b相交。我们需要加入结果的是a在b前面的部分，和a在b后面的部分。前者需要if (a[0]<b[0])，然后加入{a[0], min(a[1],b[0])}；后者需要if (a[1]>b[1])，然后加入{max(a[1],b[1]), a[1]}；
    */
    vector<vector<int>> doit_greedy(vector<vector<int>>& intervals, vector<int>& toBeRemoved) 
    {
        vector<vector<int>>rets;
        for (auto v: intervals)
        {
            if (v[1]<=toBeRemoved[0] || v[0]>=toBeRemoved[1])
                rets.push_back(v);
            else
            {
                if (v[0] < toBeRemoved[0])
                    rets.push_back({v[0], min(v[1], toBeRemoved[0])});
                if (v[1] > toBeRemoved[1])
                    rets.push_back({max(v[0], toBeRemoved[1]), v[1]});
            }
        }
        return rets;
    }

public:
    
    vector<vector<int>> doit_search(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        
        vector<vector<int>> ans;
        
        
        for (auto& interval : intervals) {
            
            if (interval[1] <= toBeRemoved[0] || interval[0] >= toBeRemoved[1]){
                ans.push_back({interval[0], interval[1]});    
                continue;
            } else if (toBeRemoved[0] <= interval[0] && interval[1] <= toBeRemoved[1])
                continue;
            
            if (interval[0] < toBeRemoved[0]) 
                ans.push_back({interval[0], toBeRemoved[0]});
            if (interval[1] > toBeRemoved[1])
                ans.push_back({toBeRemoved[1], interval[1]});
        }
        
        return ans;
    }

    vector<vector<int>> doit_greedy(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        
        vector<vector<int>> ans;
        
        for (auto& interval : intervals) {
            
            if (interval[1] <= toBeRemoved[0] || interval[0] >= toBeRemoved[1]){
                ans.push_back({interval[0], interval[1]});    
                continue;
            } else {
                if (interval[0] < toBeRemoved[0]) 
                    ans.push_back({interval[0], toBeRemoved[0]});
                if (interval[1] > toBeRemoved[1])
                    ans.push_back({toBeRemoved[1], interval[1]});
            }
        }
        
        return ans;
    }
};