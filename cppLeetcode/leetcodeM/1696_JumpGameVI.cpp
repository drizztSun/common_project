/*
1696. Jump Game VI


You are given a 0-indexed integer array nums and an integer k.

You are initially standing at index 0. In one move, you can jump at most k steps forward without going outside the boundaries of the array. That is, you can jump from index i to any index in the range [i + 1, min(n - 1, i + k)] inclusive.

You want to reach the last index of the array (index n - 1). Your score is the sum of all nums[j] for each index j you visited in the array.

Return the maximum score you can get.

 

Example 1:

Input: nums = [1,-1,-2,4,-7,3], k = 2
Output: 7
Explanation: You can choose your jumps forming the subsequence [1,-1,4,3] (underlined above). The sum is 7.
Example 2:

Input: nums = [10,-5,-2,4,0,3], k = 3
Output: 17
Explanation: You can choose your jumps forming the subsequence [10,4,3] (underlined above). The sum is 17.
Example 3:

Input: nums = [1,-5,-20,4,-1,3,-6,-3], k = 2
Output: 0
 

Constraints:

 1 <= nums.length, k <= 10^5
-104 <= nums[i] <= 10^4


Solution

Overview

You probably can guess from the problem title, this is the sixth problem in the series of Jump Game problems. Those problems are similar, but have considerable differences, making their solutions quite different.

In this problem, for each move, we are allowed to advance k steps, and our target is to maximize the scores we collect.

One example:

Figure 0.1

Below, five approaches are introduced.

Generally, we recommend Approach 1: Dynamic Programming + Deque and Approach 4: Dynamic Programming + Deque (Compressed) since they have the best performance.

Also, because it is a medium level problem, we allow some relevant slower approaches: Approach 2: Dynamic Programming + Priority Queue and Approach 3: Segment Tree.

Note that Approach 4: Dynamic Programming + Deque (Compressed) and Approach 5: Dynamic Programming + Priority Queue (Compressed) are the state compressed version of Approach 1 and Approach 2.


*/
#include <vector>
#include <queue>
#include <deque>

using std::deque;
using std::queue;
using std::vector;

class JumpGameVI {

public:

    /*
        1696.Jump-Game-VI
        本题初看很像第二类序列型DP，令dp[i]表示跳到第i个位置所能得到的最大得分。很容易写出状态转移方程：

        dp[i] = max(dp[j] + nums[i]) for j=i-k, i-k+1, ... i-1
        这样的话时间复杂度是o(NK)，根据数据范围可以判断会超时。如何改进呢？我们发现，dp[i]的关键是在[i-k,i-1]这个区间里找最大的dp值；类似地，dp[i+1]的关键是在[i-k+1,i]这个区间里找最大的dp值。
        
        这两步的两个区间是大部分重叠的，因此应该有高效地方法来分享这些信息，将取区间最大值的操作耗时均摊变小。

        显然，这本质就是一个sliding window maximum的问题。我们关注一个长度为k的滑动窗口，里面的最大值就用来更新窗口后的第一个元素的dp值。sliding window maximum的标准解法是用deque，
        维护一个单调递减的队列。如果有新元素比队尾元素更大，那么它就更有竞争力（更新、更大）被用来更新后面的dp值，故队尾元素就可以舍弃而加入新元素。此外，如果队首元素脱离了这个滑动窗口的范围，也就可以将其舍弃。在每一个回合，deque里面的最大元素就是队首元素。

        所以本题最优解的时间复杂度是o(N)

        monotonic queue
    */
    int doit_dp_monotonicqueue_slidingwindow(vector<int>& nums, int k) 
    {
        int n = nums.size();
        deque<std::pair<int,int>> dq;
        dq.push_back({nums[0],0});

        for (int i=1; i<n; i++) {

            while (!dq.empty() && i - dq.front().second > k)
                dq.pop_front();

            int curSteps = dq.front().first + nums[i];

            while (!dq.empty() && curSteps > dq.back().first)
                dq.pop_back();

            dq.push_back({curSteps,i});
        }
        
        return dq.back().first;
    }

    /*
        Solution 1: DP + Monotonic Queue

        max(dp(j)), (max(0, i - k) <= j < i) find a "Maximum sliding window of size k"

        leetcode 239 Sliding window maximum

        Method          Time            Space
        Brute Force     (n-k)*k         1
        BST/Multimap    (n-k)*log(k)    k
        Monotonic Queue   n             k
    */
    int doit_dp_1(vector<int>& nums, int k) {
        vector<int> dp(nums.size());
        deque<int> qu{{0}};
        dp[0] = nums[0];

        for (int i = 1; i < nums.size(); i++) {

            dp[i] = nums[i] + dp[qu.front()];

            while (!qu.empty() && dp[qu.back()] <= dp[i])
                qu.pop_back();

            while (!qu.empty() && i - qu.front() >= k)
                qu.pop_front();

            qu.push_back(i);
        }

        return dp[nums.size() - 1];
    }
};