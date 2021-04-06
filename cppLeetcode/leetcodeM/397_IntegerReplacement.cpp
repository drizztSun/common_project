/*
397. Integer Replacement

Given a positive integer n, you can apply one of the following operations:

If n is even, replace n with n / 2.
If n is odd, replace n with either n + 1 or n - 1.
Return the minimum number of operations needed for n to become 1.

 

Example 1:

Input: n = 8
Output: 3
Explanation: 8 -> 4 -> 2 -> 1
Example 2:

Input: n = 7
Output: 4
Explanation: 7 -> 8 -> 4 -> 2 -> 1
or 7 -> 6 -> 3 -> 2 -> 1
Example 3:

Input: n = 4
Output: 2
 

Constraints:

1 <= n <= 231 - 1

*/

#include <vector>
#include <functional>

using std::vector;


class IntegerReplacement {

    /*
                397.Integer-Replacement
        仔细分析一下就能发现，这题无法用DP做，因为对DP数组无法找到合适的遍历顺序。

        用递归做就能通过，也非常简单。但要注意 n=INT_MAX时的越界问题。
    */
     int integerReplacement(int n) 
    {
        return DFS(n);
    }
    
    long long DFS(long long n) 
    {
        if (n==1) return 0;
        
        if (n%2==0)
            return DFS(n/2)+1;
        else
            return min(DFS(n+1),DFS(n-1))+1;
    }

public:

    int doit_recursive(int n) {
        
        vector<int> dp(n+1, -1);
        
        std::function<int(int)> search = [&](long long s) {
            
            if (s == 1) return 0;
            
            if (dp[s] != -1) return dp[s];
            
            if (s % 2 == 0) {
                dp[s] = 1 + search(s/2);
            } else {
                dp[s] =  1 + std::min(search(s+1), search(s-1));
            }
            
            return dp[s];
        };
        
        return search(n);
    }
};