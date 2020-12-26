/*

1642. Furthest Building You Can Reach


You are given an integer array heights representing the heights of buildings, some bricks, and some ladders.

You start your journey from building 0 and move to the next building by possibly using bricks or ladders.

While moving from building i to building i+1 (0-indexed),

If the current building's height is greater than or equal to the next building's height, you do not need a ladder or bricks.
If the current building's height is less than the next building's height, you can either use one ladder or (h[i+1] - h[i]) bricks.
Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricks optimally.

 

Example 1:


Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
Output: 4
Explanation: Starting at building 0, you can follow these steps:
- Go to building 1 without using ladders nor bricks since 4 >= 2.
- Go to building 2 using 5 bricks. You must use either bricks or ladders because 2 < 7.
- Go to building 3 without using ladders nor bricks since 7 >= 6.
- Go to building 4 using your only ladder. You must use either bricks or ladders because 6 < 9.
It is impossible to go beyond building 4 because you do not have any more bricks or ladders.
Example 2:

Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
Output: 7
Example 3:

Input: heights = [14,3,19,3], bricks = 17, ladders = 0
Output: 3
 

Constraints:

1 <= heights.length <= 105
1 <= heights[i] <= 106
0 <= bricks <= 109
0 <= ladders <= heights.length

*/
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

using std::priority_queue;
using std::vector;

class ReachFurthestBuilding {

public:
    
    /*
    O(2^n)
    */
    int doit_dfs_brtute_force(vector<int>& heights, int bricks, int ladders) {
        
        const int n = heights.size();
        vector<int> diffs(n);
        for (int i = 1; i < heights.size(); i++) {
            diffs[i-1] = std::max(0, heights[i] - heights[i-1]);
        }

        int ans = 0;

        std::function<void(int, int, int)> dfs = [&](int s, int b, int l) {

            if (ans == n-1) return;

            if (s == n-1) {
                ans = n-1;
                return;
            }

            for (int i = s; i < n; i++) {
                
                ans = std::max(ans, i);

                if (diffs[i] == 0)
                    continue;

                if (diffs[i] <= b)
                    dfs(i+1, b - diffs[i], l);
                
                if (l > 0)
                    dfs(i+1, b, l-1);
                
                break;
            }
        };

        dfs(0, bricks, ladders);
        return ans;
    }

    /*
    Observations:

    1. ladders >= n-1, ans = n-1
    2. bricks >= sum(diffs), ans = n-1
    3. we want to use laders to largest gains and bricks fro smallest ones.

    Solutions 1 binary search

    check whether we can reach to m by:
    1. Sort all the differences.
    2. Use ladders for the largest ones
    3. check the sum of the rest one is <= bricks


    Trick: find the smallest index L that we cannot reach, Ans = L - 1

    Time complexity: O(nlogn)

    Space complexity: O(n)
    */
    int doit_binary_search(vector<int>& heights, int bricks, int ladders) {

        const int n = heights.size();
        vector<int> diffs(n, 0);

        if (ladders > n-1)
            return n-1;

        for (int i = 1; i < n; i++) {
            diffs[i-1] = std::max(0, heights[i] - heights[i-1]);
        }

        int l = ladders, r = n;

        while (l < r) {
            int m = (l + r) / 2;

            vector<int> d(begin(diffs), begin(diffs)+m);

            std::nth_element(begin(d), end(d) - ladders, end(d));

            if (std::accumulate(begin(d), end(d)- ladders, 0) > bricks)
                r = m;
            else
                l = m+1;
        }

        return l - 1;
    }

    /*
    Solution 2: Min Heap

    Use a min heap for track all the differences so far.

    Delay decision
    Always "use" ladder first until we are out of ladders service, than find the smallest one replace it with brick.
    online method: Heights can be a stream

    Time complexity: O(nlogL)
    Space complexity: O(L)

    */
    int doit_heap(vector<int>& heights, int bricks, int ladders) {

        const int n = heights.size();
        priority_queue<int, vector<int>, std::greater<int>> q;

        for (int i = 1; i < n; i++) {

            const int diff = heights[i] - heights[i-1];

            if (diff <= 0)
                continue;

            q.push(diff);

            if (q.size() <= ladders)
                continue;

            bricks -= q.top();
            q.pop();

            if (bricks < 0)
                return i - 1;
        }
        return n-1;
    }
};


