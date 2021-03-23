/*
774. Minimize Max Distance to Gas Station

You are given an integer array stations that represents the positions of the gas stations on the x-axis. You are also given an integer k.

You should add k new gas stations. You can add the stations anywhere on the x-axis, and not necessarily on an integer position.

Let penalty() be the maximum distance between adjacent gas stations after adding the k new stations.

Return the smallest possible value of penalty(). Answers within 10-6 of the actual answer will be accepted.

 

Example 1:

Input: stations = [1,2,3,4,5,6,7,8,9,10], k = 9
Output: 0.50000
Example 2:

Input: stations = [23,24,36,39,46,56,57,65,84,98], k = 1
Output: 14.00000
 

Constraints:

10 <= stations.length <= 2000
0 <= stations[i] <= 10^8
stations is sorted in a strictly increasing order.
1 <= k <= 10^6


*/
#include <vector>
#include <queue>


using std::priority_queue;
using std::vector;


class MinMaxGasDist {

public:
    /*
        774.Minimize-Max-Distance-to-Gas-Station

        解法1：贪心法
        
        贪心法有非常巧妙的思想，这里用到了pq.

        首先我们将所有老加油站之间的间隔距离放入pq，默认是大顶堆，这些老加油站的间隔都没有新加油站插入。那么，对于队首的这个间距最大，说明我们要对其下手，先尝试将这个间距除以2，这里除以2表明原本是没有新加油站的，现在加入一个。然后将这个新间隔放入队列。

        每次我们取队首元素，总是得到的是（当前最大的）某两个老加油站之间的新间隔，以及这两个老加油站之间插入的新加油站数量m。我们需要做的，是重新规划这两个老加油站之间的间隔，改成插入的新加油站数量为m+1.

        重复上述过程，直至加入新加油站的总是达到了K。此时队首的老加油站之间的新间距，就是整体最大的间距。

        这个方法非常巧妙，只可惜仍然超时。

        解法2：二分法
        
        可以得到的最大间距d，下限是0，上限是原本最大的老加油站之间的间距。

        不断二分尝试这个d，计算为了使得每个老加油站之间的新间距变为d，需要新加入多少新加油站。如果新加油站总数超过了K，说明这个d太小；否则可以继续尝试减小d，

        最后知道二分的搜索精度小于1e-6.
    */

    double doit_heap_tle(vector<int>& stations, int K) {

        priority_queue<std::pair<double,int>> pq;

        for (int i=1; i<stations.size(); i++)
            pq.push({stations[i]-stations[i-1],1});
        
        for (int i = 0; i < K; i++)
        {
            auto [space, insertNum] = pq.top();
            pq.pop();
            
            pq.push({space * insertNum / (insertNum+1), insertNum + 1});
        }
        
        return pq.top().first;
    }

    double doit_binary_search(vector<int>& stations, int K) 
    {
        double left = 0;
        double right = 0;
        for (int i=1; i<stations.size(); i++)
            right = fmax(right,stations[i]-stations[i-1]);
        
        double mid;
        while (right-left>1e-6)
        {
            mid = (right+left)/2;
            int count = 0;
            for (int i=1; i<stations.size(); i++)
            {
                double k = (stations[i]-stations[i-1])/mid;
                count += ceil(k)-1;               
            }

            if (count > K)
                left = mid;
            else
                right = mid;            
        }
        return mid;
    }

    /*
        Approach #4: Binary Search [Accepted]
        Intuition

        Let's ask possible(D): with K (or less) gas stations, can we make every adjacent distance between gas stations at most D? This function is monotone, so we can apply a binary search to find D

        Algorithm

        More specifically, there exists some D* (the answer) for which possible(d) = False when d < D* and possible(d) = True when d > D*. Binary searching a monotone function is a typical technique, so let's focus on the function possible(D).

        When we have some interval like X = stations[i+1] - stations[i], we'll need to use (X/D) gas stations to ensure every subinterval has size less than D. This is independent of other intervals, so in total we'll need to use 
        
        gas stations. If this is at most K, then it is possible to make every adjacent distance between gas stations at most D.

        Complexity Analysis

        Time Complexity: O(NlogW), where N is the length of stations, and W = 10^{14} is the range of possible answers (10^8), divided by the acceptable level of precision (10^{-6}).

        Space Complexity: O(1) in additional space complexity.
    */
    double doit_binary_search(vector<int>& stations, int k) {
        
        double lo = 0, hi = 1e8;
        
        auto possible = [&](double x) {
            
            int cnt = 0;
            for (int i = 0; i < stations.size()-1; i++) {
                
                if (stations[i+1] - stations[i] > x)
                    cnt += int((stations[i+1] - stations[i]) / x);
                
                if (cnt > k) return false; 
            }
            
            return true;
        };
        
        while (hi - lo > 1e-6) {
            
            double mid = (lo + hi) / 2.0;
            
            if (possible(mid))
                hi = mid;
            else
                lo = mid;
        }
        
        return lo;
    }
};