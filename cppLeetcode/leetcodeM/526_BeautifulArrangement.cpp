/*
526. Beautiful Arrangement

Suppose you have n integers labeled 1 through n. A permutation of those n integers perm (1-indexed) is considered a beautiful arrangement if for every i (1 <= i <= n), 
either of the following is true:

    . perm[i] is divisible by i.
    . i is divisible by perm[i].

Given an integer n, return the number of the beautiful arrangements that you can construct.

 Example 1:

Input: n = 2
Output: 2
Explanation: 
The first beautiful arrangement is [1,2]:
    - perm[1] = 1 is divisible by i = 1
    - perm[2] = 2 is divisible by i = 2
The second beautiful arrangement is [2,1]:
    - perm[1] = 2 is divisible by i = 1
    - i = 2 is divisible by perm[2] = 1

Example 2:

Input: n = 1
Output: 1
 

Constraints:

1 <= n <= 15

*/

#include <vector>
#include <numeric>
#include <unordered_map>
#include <functional>

using std::unordered_map;
using std::vector;

class BeautifulArrangement {

public:

    /*
        Approach #3 Backtracking [Accepted]
        Algorithm

        The idea behind this approach is simple. We try to create all the permutations of numbers from 1 to N. We can fix one number at a particular position and check for the divisibility criteria of that number at the particular position. 
        But, we need to keep a track of the numbers which have already been considered earlier so that they aren't reconsidered while generating the permutations. 
        If the current number doesn't satisfy the divisibility criteria, we can leave all the permutations that can be generated with that number at the particular position. This helps to prune the search space of the permutations to a great extent. We do so by trying to place each of the numbers at each position.

        We make use of a visited array of size NN. Here, visited[i]visited[i] refers to the ith number being already placed/not placed in the array being formed till now(True indicates that the number has already been placed).

        We make use of a calculate function, which puts all the numbers pending numbers from 1 to N(i.e. not placed till now in the array), indicated by a FalseFalse at the corresponding visited[i]visited[i] position, and tries to create all the permutations with those numbers starting from the pospos index onwards in the current array. 
        While putting the pos^{th}pos number, we check whether the i^{th} number satisfies the divisibility criteria on the go i.e. we continue forward with creating the permutations with the number ii at the pos^{th}pos 
        th
        position only if the number ii and pospos satisfy the given criteria. Otherwise, we continue with putting the next numbers at the same position and keep on generating the permutations.

        Look at the animation below for a better understanding of the methodology:

        Current
        1 / 26
        Below code is inspired by @shawngao

        **Complexity Analysis**
        Time complexity : O(k). kk refers to the number of valid permutations.

        Space complexity : O(n). visitedvisited array of size nn is used. The depth of recursion tree will also go upto n. Here, nn refers to the given integer nn.
    */
    int doit_backtracking(int n) {

        std::function<int(int, vector<bool>&)> search = [&](int s, vector<bool>& status) {
            
            if (s == 1)
                return 1;
            
            int ans = 0;
            for (int i = 1; i <= n; i++) {
                if (status[i] && (i % s == 0 || s % i == 0)) {
                    status[i] = false;
                    ans += search(s-1, status);
                    status[i] = true;
                }
            }
            return ans;
        };
        vector<bool> buff(n+1, true);

        return search(n, buff);
    }

    int doit_dp(int n) {

        vector<int> dp(1<<n, -1);
        dp[(1<<n)-1] = 1;

        std::function<int(int, int)> dfs = [&](int status, int index) {
            
            if (dp[status] != -1) return dp[status];
            
            int ans = 0;
            for (int i = 0; i < n; i++) {
                if ( (status & (1 << i)) == 0 && ((i+1)%index == 0 || index%(i+1) == 0)) {
                    ans += dfs(status | (1 << i), index + 1);
                }
            }
            dp[status] = ans;
            return ans;
        };

        return dfs(0, 1);
    }

    int doit_dp(int n) {

        vector<vector<int>> dp(n+1, vector<int>(1<<n, -1));

        std::function<int(int, int)> search = [&](int p, int status) {

            if (p == 1)
                return 1;

            if (dp[p][status] != -1)
                return dp[p][status];

            int& ans = dp[p][status];
            for (int i = 1; i <= n; i++) {

                if (!(i % p == 0 || p % i == 0)) continue;
                if (status >> i & 1) continue;

                ans += search(p-1, status | (1 << i));
            }

            return ans;
        };

        return search(n, 0);
    }
};
