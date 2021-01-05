/*
526. Beautiful Arrangement

Suppose you have n integers from 1 to n. We define a beautiful arrangement as an array that is constructed by these n numbers successfully if one of the following is true for the ith position (1 <= i <= n) in this array:

The number at the ith position is divisible by i.
i is divisible by the number at the ith position.
Given an integer n, return the number of the beautiful arrangements that you can construct.



Example 1:

Input: n = 2
Output: 2
Explanation:
The first beautiful arrangement is [1, 2]:
Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).
Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).
The second beautiful arrangement is [2, 1]:
Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).
Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.
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
