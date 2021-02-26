/*
1499. Max Value of Equation

Given an array points containing the coordinates of points on a 2D plane, sorted by the x-values, 
where points[i] = [xi, yi] such that xi < xj for all 1 <= i < j <= points.length. You are also given an integer k.

Find the maximum value of the equation yi + yj + |xi - xj| where |xi - xj| <= k and 1 <= i < j <= points.length. 
It is guaranteed that there exists at least one pair of points that satisfy the constraint |xi - xj| <= k.

 

Example 1:

Input: points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
Output: 4
Explanation: The first two points satisfy the condition |xi - xj| <= 1 and if we calculate the equation we get 3 + 0 + |1 - 2| = 4. Third and fourth points also satisfy the condition and give a value of 10 + -10 + |5 - 6| = 1.
No other pairs satisfy the condition, so we return the max of 4 and 1.
Example 2:

Input: points = [[0,0],[3,0],[9,2]], k = 3
Output: 3
Explanation: Only the first two points have an absolute difference of 3 or less in the x-values, and give the value of 0 + 0 + |0 - 3| = 3.
 

Constraints:

2 <= points.length <= 10^5
points[i].length == 2
-10^8 <= points[i][0], points[i][1] <= 10^8
0 <= k <= 2 * 10^8
points[i][0] < points[j][0] for all 1 <= i < j <= points.length
xi form a strictly increasing sequence.

*/
#include <queue>
#include <vector>
#include <deque>

using std::deque;
using std::vector;
using std::priority_queue;


class MaxValueOfEquation {

    /*
        1499.Max-Value-of-Equation
        如果我们固定j点，那么原题就是求max{yi+yj+xj-xi} = max{-xi+yi} + xj+yj .也就是要在|xi-xj|<k的范围内，找到一个i点，使得-xi+yj最大。这就是一个典型的sliding window maximum，标准解法使用双端队列，时间复杂度是o(N).

        注意，这里的sliding window并不是固定长度的，我们保持的是一个满足首尾元素|xi-xj|<k的窗口。队列中保持递减的序列。任何新进来的元素，如果-x+y比队尾元素要大，说明队尾的元素就不再有任何利用的价值（又旧又小，永远不会被用到），那么队尾元素都可以弹出。
    */
    int doit_(vector<vector<int>>& points, int k) 
    {
        int ret = INT_MIN;
        deque<int>q;
        for (int i=0; i<points.size(); i++)
        {
            while (q.size()>0 && points[q.front()][0] < points[i][0]-k)
                q.pop_front();
            
        	if (q.size() > 0)
        	    ret = std::max(ret, -points[q.front()][0]+points[q.front()][1] + points[i][0]+points[i][1]);

            while (q.size()>0 && -points[q.back()][0]+points[q.back()][1] < -points[i][0]+points[i][1])
                q.pop_back();
            
            q.push_back(i);
        }
        return ret;
    }

    int doit_monotonicqueue(vector<vector<int>>& points, int k) {
        int ans = INT_MIN;
        deque<std::pair<int, int>> qu;
        
        for (const auto& c : points) {
            int x = c[0], y = c[1];
            
            while (!qu.empty() && x - qu.front().second > k)
                qu.pop_front();
            
            if (! qu.empty())
                ans = std::max(ans, x + y + qu.front().first);
            
            while (!qu.empty() && (y - x) > qu.back().first)
                qu.pop_back();
            
            qu.push_back({y- x, x});
        }
        
        return ans;
    }

public:
    /*
    Solution 1: Priority Queue / Heap
    Put all the points processed so far onto the heap as (y-x, x) sorted by y-x in descending order.
    Each new point (x_j, y_j), find the largest y-x such that x_j – x <= k.

    Time complexity: O(nlogn)
    Space complexity: O(n)
    */
    int doit_heap(vector<vector<int>>& points, int k) {
        
        std::priority_queue<std::pair<int, int>> qu; // y - x, x
        int ans = INT_MIN;

        for (const auto& c : points) {

            int x = c[0], y = c[1];

            while(!qu.empty() && x - qu.top().second > k)
                qu.pop();

            if (!qu.empty())
                ans = std::max(ans, y + x + qu.top().first);

            qu.emplace(y-x, x);
        }

        return ans;
    }

    /*
    Solution 2: Monotonic Queue

    Maintain a monotonic queue:
    1. The queue is sorted by y – x in descending order.
    2. Pop then front element when xj – x_front > k, they can’t be used anymore.
    3. Record the max of {xj + yj + (y_front – x_front)}
    4. Pop the back element when yj – xj > y_back – x_back, they are smaller and lefter. Won’t be useful anymore.
    5. Finally, push the j-th element onto the queue.

    Time complexity: O(n)
    Space complexity: O(n)

    */
    int doit_monotonic_queue(vector<vector<int>>& points, int k) {    
        deque<std::pair<int, int>> q; // {y - x, x} Sort by y - x.
        int ans = INT_MIN;

        for (const auto& p : points) {
            const int xj = p[0];
            const int yj = p[1];
            // Remove invalid points, e.g. xj - xi > k
            while (!q.empty() && xj - q.front().second > k)
                q.pop_front();
            if (!q.empty())
                ans = std::max(ans, xj + yj + q.front().first);      
            while (!q.empty() && yj - xj >= q.back().first) 
                q.pop_back();
            q.emplace_back(yj - xj, xj);
        }
        return ans;
    }
};

