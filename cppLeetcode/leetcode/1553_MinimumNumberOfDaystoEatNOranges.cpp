/*

1553. Minimum Number of Days to Eat N Oranges

There are n oranges in the kitchen and you decided to eat some of these oranges every day as follows:

Eat one orange.
If the number of remaining oranges (n) is divisible by 2 then you can eat  n/2 oranges.
If the number of remaining oranges (n) is divisible by 3 then you can eat  2*(n/3) oranges.
You can only choose one of the actions per day.

Return the minimum number of days to eat n oranges.

 

Example 1:

Input: n = 10
Output: 4
Explanation: You have 10 oranges.
Day 1: Eat 1 orange,  10 - 1 = 9.  
Day 2: Eat 6 oranges, 9 - 2*(9/3) = 9 - 6 = 3. (Since 9 is divisible by 3)
Day 3: Eat 2 oranges, 3 - 2*(3/3) = 3 - 2 = 1. 
Day 4: Eat the last orange  1 - 1  = 0.
You need at least 4 days to eat the 10 oranges.
Example 2:

Input: n = 6
Output: 3
Explanation: You have 6 oranges.
Day 1: Eat 3 oranges, 6 - 6/2 = 6 - 3 = 3. (Since 6 is divisible by 2).
Day 2: Eat 2 oranges, 3 - 2*(3/3) = 3 - 2 = 1. (Since 3 is divisible by 3)
Day 3: Eat the last orange  1 - 1  = 0.
You need at least 3 days to eat the 6 oranges.
Example 3:

Input: n = 1
Output: 1
Example 4:

Input: n = 56
Output: 6


Constraints:

1 <= n <= 2*10^9

*/
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using std::unordered_set;
using std::queue;
using std::unordered_map;
using std::vector;

class MinimumDaysToEatAllOrange {

/*
Key point of this test is the data constraints, 1 <= n <= 2*10^9. if it is n <= 10^6, it could be O(n). but if data is 10^7 or up, O(n) is not enough.

so DP_bottomup get tle, because it needs to go all n nodes. and also memory is a big concern in this data constraint. 

*/


public:

    /*
        Solution 1: BFS
        Shortest path from n to 0 in a unweighted directed graph.

        Time comlexity: O(n)
        Space complexity: O(n)

        It is O(n) but still can pass the test, because in bfs, not all number 0~n has been calculate. Only very small group has been calculated. 
        if depth 100, only 300 object has been reached, like log(n)
    */
    int doit_bfs(int n) {

        queue<int> q{{n}};
        unordered_set<int> seen;
        int steps = 0;

        while (!q.empty()) {

            int size = q.size();
            while (size--) {
                
                int cur = q.front();
                q.pop();

                if (cur == 0) return steps;

                /*
                    if x % 2 == 0, push x/2 onto the queue
                    if x % 3 == 0, push x/3 onto the queue
                    always push x – 1 onto the queue
                */

                if (cur % 2 == 0 && seen.insert(cur/2).second) q.push(cur/2);

                if (cur % 3 == 0 && seen.insert(cur/3).second) q.push(cur/3);

                if (seen.insert(cur-1).second) q.push(cur-1);
            } 

            steps++;
        }

        return -1;
    }

    /*
    Solution 3: Optimized DP + Greedy

    ALways eat one at a time is definitely not the best option. 
    We can eat k in k steps such that n-k is a multiple of 2 or 3 such that we can eat 1/2 or 2/3 in one step.
    dp(i) := min stesps to eat i oragnes.

    dp(n) = 1 + min{n%2 + dp(n/2), n%3 + dp(n/3)}

    Time complexity: O(logn)^2
    Space complexity: O(logn)^2

    Never take more than 2 consecutive -1 operations.
    Proog: suppose we need 3 consecuitve -1 operations to reach the optimal solution.

    days(n) -> days(n-3) in 3 steps

    Option 1: /2 => we reach days((n-3)/2) = days((n-1)/2 -1) in (3 + 1) = 4 steps
    However, days(n) -> days(n-1) -> days((n-1)/2) -> days((n-1)/2-1) in 3 steps

    Option 2: /3 => we reach days((n-3)/3) = days(n/3-1) in (3+1) = 4 steps
    Hpwever, days(n) -> days(n/3) -> days(n/3 -1) in 2 steps

    This can be extended to k consecutive -1 operations (k>=3)
    */
    int doit_dp_topdown(int n) {

        unordered_map<int, int> cache;

        std::function<int(int)> search = [&](int s) -> int {
            if (s < 2)
                return s;

            if (cache.count(s) > 0)
                return cache[s];

            return cache[s] = 1 + std::min(s%2 + search(s/2), s%3 + search(s/3));
        };

        return search(n);
    }

    /*
    DP: Bottom up, not fast solution, because it is hard to reach n so fast and direct. you have to get n/3, n/2, n-1, first. 
    data like this 2*10^9, needs O(log(N))
    */
    int doit_dp_tle(int n) {
        if (n < 2)
            return 1;

        vector<int> dp(n+1, INT_MAX);
        dp[0] = dp[1] = 1;

        for (int i = 0; i < n+1; i++) {

            dp[i+1] = std::min(dp[i+1], dp[i] + 1);
            if (i*2 <= n)
                dp[i*2] = std::min(dp[i * 2], dp[i] + 1);
            if (i*3<= n)
                dp[i*3] = std::min(dp[i * 3], dp[i] + 1);
        }

        return dp[n];
    }
};