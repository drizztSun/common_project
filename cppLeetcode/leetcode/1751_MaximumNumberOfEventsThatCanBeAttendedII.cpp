/*
1751. Maximum Number of Events That Can Be Attended II

You are given an array of events where events[i] = [startDayi, endDayi, valuei]. 
The ith event starts at startDayi and ends at endDayi, and if you attend this event, you will receive a value of valuei. 
You are also given an integer k which represents the maximum number of events you can attend.

You can only attend one event at a time. If you choose to attend an event, you must attend the entire event. 
Note that the end day is inclusive: that is, you cannot attend two events where one of them starts and the other ends on the same day.

Return the maximum sum of values that you can receive by attending events.

 

Example 1:



Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
Output: 7
Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.
Example 2:



Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
Output: 10
Explanation: Choose event 2 for a total value of 10.
Notice that you cannot attend any other event as they overlap, and that you do not have to attend k events.
Example 3:



Input: events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
Output: 9
Explanation: Although the events do not overlap, you can only attend 3 events. Pick the highest valued three.
 

Constraints:

1 <= k <= events.length
1 <= k * events.length <= 10^6
1 <= startDayi <= endDayi <= 10^9
1 <= valuei <= 10^6

*/
#include <vector>
#include <algorithm>

using std::vector;

class MaximumNumberOfEvents {

    /*
        1751.Maximum-Number-of-Events-That-Can-Be-Attended-II
        本题和1235.Maximum-Profit-in-Job-Scheduling非常相似。差别是dp状态多了一个维度来表示可以取多少个区间。

        我们首先要将所有events按照endTime排序。令dp[i][j]表示前i个events里面我们取j个events能得到的最大收益。计算dp[i][j]时有两种决策：

        我们不选择events[i]，那么dp[i][j]就等于在前i-1个events里面取j个的最大收益，即dp[i][j]=dp[i-1][j]
        我们选择events[i]作为第j个选中的项目，那么我们需要考虑第j-1个项目在哪里？显然这个项目的endTime必须必events[i][0]要小.

        于是我们可以用二分法，在所有endTimes里找到截止时间恰好早于events[i][0]的项目t，于是dp[i][j]就转化为考察在前t个项目里选取j-1个的最大收益，然后再加上events[i][2]本身。
        最终的答案就是max(dp[m][x])，其中m是events的总数。注意答案不一定是dp[m][k]，因为强制取k件不重叠的区间，不见得是最大的利润.
    */
public:

    int doit_dp(vector<vector<int>>& events, int k) 
    {        
        auto cmp = [](vector<int>&a, vector<int>&b){
            return a[1] < b[1];
        };
        
        std::sort(events.begin(), events.end(), cmp);
        int m = events.size();
        vector<vector<int>> dp(m+1, vector<int>(k+1,INT_MIN/2));
        
        // add placeholder for index starting from 1
        events.insert(events.begin(), events[0]); 
        vector<int> endTime({0});
        
        int ret = 0;        
        for (int i = 0; i <= m; i++)
            dp[i][0] = 0;
        
        for (int i = 1; i <= m; i++)
        {
            auto iter = lower_bound(endTime.begin(), endTime.end(), events[i][0]);
            int t = iter-endTime.begin()-1;
            
            for (int j = 1; j <= k; j++)
            {
                // don't pick ith or pick ith and j-1 from first t.
                dp[i][j] = std::max(dp[i-1][j], dp[t][j-1] + events[i][2]);                                
                ret = std::max(ret, dp[i][j]);
            }
            endTime.push_back(events[i][1]);
        }
        
        return ret;   
    }   
};