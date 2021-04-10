/*
343. Integer Break

Given an integer n, break it into the sum of k positive integers, where k >= 2, and maximize the product of those integers.

Return the maximum product you can get.

 

Example 1:

Input: n = 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.
Example 2:

Input: n = 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
 

Constraints:

2 <= n <= 58
*/
#include <algorithm>
#include <vector>
#include <functional>

using std::vector;


class IntegerBreak {

    /*
        343.Integer-Break
        此题最傻的方法是DFS，挨个尝试所有将n拆分为若干数之和的组合形式。

        稍微聪明点的可以想到递归。先将n拆分为两个数之和，找出它们乘积最大的一种拆分形式。而每个数又可以递归往下继续拆分为两个数，规模越来越小。所以记忆化搜索或者DP都是比较好写的算法。

        最好的想法是利用数学上的技巧。在限定和一定的条件下，我们尽量拆分成接近自然对数e的整数，也就是2或者3，就能使总乘积最大。考虑到以6为例子，3*3>2*2*2，所以我们的目标还是尽量拆成3.所以我们只要计算n除以3的各种情况就行。

        1. n能被3整除，则结果就是pow(3,n/3)
        2. n被3除余2，则结果就是pow(3,n/3)*2
        3. n被3除余1，稍微有些变化，因为pow(3,n/3)*1并不合算，我们就退一步，写成pow(3,n/3-1)*4会得到更大的结果。
    */
    int integerBreak(int n) 
    {
        if (n==2) return 1;
        if (n==3) return 2;
        vector<int>dp(n+1,0);
        dp[2] = 2;
        dp[3] = 3;
        for (int i=4; i<=n; i++)
        {
            int temp = 0;
            for (int j=2; j<=i/2; j++)
            {
                if (dp[j]*dp[i-j]>temp)
                    temp = dp[j]*dp[i-j];
            }
            dp[i] = temp;
        }
        return dp[n];
    }

    int integerBreak(int n) 
    {
        if (n==2) return 1*1;
        if (n==3) return 1*2;
        if (n==4) return 2*2;
        if (n%3==0) return pow(3,n/3);
        else if (n%3==1) return pow(3,n/3-1)*4;
        else return pow(3,n/3)*2;
    }

public:

    int doit_dp_bottomup(int n) {
        
        vector<int> ans(n+1, -1);
        ans[2] = 1;
        
        for (int i = 3; i <= n; i++) {
            
            for (int j = 1; j < i; j++) {
             
                ans[i] = std::max({ans[i], j*(i-j), ans[j]*(i-j)});
            }
        }

        return ans[n];
    }

    int doit_dp_bottomup(int n) {
        if (n == 2) return 1;
        if (n == 3) return 2;
        
        vector<int> ans(n+1, -1);
        ans[2] = 2;
        ans[3] = 3;
        
        for (int i = 4; i <= n; i++) {
            
            for (int j = 2; j < i; j++) {
             
                ans[i] = std::max({ans[i], ans[j]*ans[i-j]});
            }
        }

        return ans[n];
    }

    int doit_dp_topdown(int n) {

        if (n == 2) return 1;
        if (n == 3) return 2;
        
        vector<int> ans(n+1, -1);
        ans[2] = 2;
        ans[3] = 3;

        std::function<int(int)> dfs = [&](int num) {

            if (ans[num] != -1) return ans[num];

            int res = 0;
            for (int i = 2; i < num; i++) {
                res = std::max(res, dfs(i) * dfs(num-i));
            }

            return ans[num] = res;
        };

        return dfs(n);
    }
};