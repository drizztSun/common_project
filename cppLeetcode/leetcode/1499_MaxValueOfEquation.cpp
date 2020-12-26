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
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {    
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

