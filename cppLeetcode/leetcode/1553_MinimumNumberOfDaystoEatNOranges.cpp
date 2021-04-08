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
#include <functional>

using std::unordered_set;
using std::queue;
using std::unordered_map;
using std::vector;


class MinimumDaysToEatAllOrange {

/*
Key point of this test is the data constraints, 1 <= n <= 2*10^9. if it is n <= 10^6, it could be O(n). but if data is 10^7 or up, O(n) is not enough.

so DP_bottomup get tle, because it needs to go all n nodes. and also memory is a big concern in this data constraint. 

*/

    /*
        1553.Minimum-Number-of-Days-to-Eat-N-Oranges
        本题并没有严格的数学解，只能通过递归探索。通常而言，每一步我们都有三个分支：-1，/2（如果能被2整除），/3（如果能被3整除）。但事实上，一直往1这条分支走下去的话，肯定不是效率高的解。我们需要探索的其实尽可能地去/2或者/3.能“早做除法”肯定不会比“晚做除法”吃亏。

        举个例子，当n=11时，你可以先减一，就能除以2，这样2步得到5，再减1能得到4. 你也可以先减3次1，在除以2，这样4步得到4，但这比之前相比效率是低的。所以，直观上来说，能早做除法就尽量早出除法，不能做除法的时候，就做一些减法，再去做除法。

        但是，/2和/3相比较，并没有更加优势的操作。比如说n=11，你是先打算减1再除以2呢，还是打算减2再除以3呢？很难判断。事实上最优方案是先实现/3：11,10,9,3,1,0. 但对于n=17，反而是先实现/2更优：17,16,8,4,2,1,0。所以我们需要对于/2和/3并行的探索。

        所以递归方程其实就是：

        f(n) = min(n%2+1+f(n/2), n%3+1+f(n/3))
        那么时间复杂度如何计算呢？我们可以知道，从n递归到底的过程中，每层递归都会将参数/2(或者/3)，那么大致的层数就是logN。

        对于第k层，意味着我们做了k次除法，这k次除法中/2的个数可能有0次，1次，2次...，直至有k次，这对应了k+1种不同状态。举个例子，我们从n开始做了5次除法，假设有2次是/2，另外3次是/3，考虑到除法的顺序不影响递归的结果。只要n经过了两次/2和三次/3，剩下来的n'肯定都是一样。因此我们从n开始，经过第k层递归后，得到的只会是k+1种不同的n'。所以这是一个公差为1的等差数列。所以递归完所有的状态，需要记录总的状态就是 1+2+...+logN ~ o(logN^2)
    */
    unordered_map<int,int>ans;

    int minDays(int n) 
    {
        if (n==1) return 1;
        if (n==2) return 2;
        if (n==3) return 2;

        if (ans.find(n)!=ans.end())
            return ans[n];
        
        int ret = std::min(n%2+1+minDays(n/2), n%3+1+minDays(n/3));
        ans[n] = ret;

        return ret;
    }

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
    int doit_dp_topdown_greedy(int n) {

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
    int doit_dp_tle_bottomup(int n) {
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