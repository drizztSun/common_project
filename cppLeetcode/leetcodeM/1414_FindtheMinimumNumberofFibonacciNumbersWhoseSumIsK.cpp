/*
1414. Find the Minimum Number of Fibonacci Numbers Whose Sum Is K


Given an integer k, return the minimum number of Fibonacci numbers whose sum is equal to k. The same Fibonacci number can be used multiple times.

The Fibonacci numbers are defined as:

F1 = 1
F2 = 1
Fn = Fn-1 + Fn-2 for n > 2.
It is guaranteed that for the given constraints we can always find such Fibonacci numbers that sum up to k.
 

Example 1:

Input: k = 7
Output: 2 
Explanation: The Fibonacci numbers are: 1, 1, 2, 3, 5, 8, 13, ... 
For k = 7 we can use 2 + 5 = 7.
Example 2:

Input: k = 10
Output: 2 
Explanation: For k = 10 we can use 2 + 8 = 10.
Example 3:

Input: k = 19
Output: 3 
Explanation: For k = 19 we can use 1 + 5 + 13 = 19.
 

Constraints:

1 <= k <= 10^9

*/
#include <vector>
#include <algorithm>

using std::vector;


class MinFibonacciNumbers {

    /*
        1414.Find-the-Minimum-Number-of-Fibonacci-Numbers-Whose-Sum-Is-K
        直观上，我们构造出所有小于k的斐波那契数列的元素，然后依次贪心地从大到小选取即可（选完一个就从k里面减去它）。我们发现这个方法似乎总是成立的。
    */
    int findMinFibonacciNumbers(int k) 
    {
        using ll = long long;

        vector<ll>a = {1,1};
        while (a.back() < k)
        {
            int n = a.size();
            a.push_back(a[n-1]+a[n-2]);
        }
        int ret = 0;
        while (k>0)
        {
            auto iter = upper_bound(a.begin(), a.end(), k) - 1;
            ret++;
            k-=*iter;
        }
        return ret;
    }

public:

    int doit_greedy(int k) {
        
        int l = 1, ll = 1;
        
        while (l + ll < k) {
            int tmp = l + ll;
            ll = l;
            l = tmp;
        }
        
        if (l + ll == k) return 1;
        
        int ans = 1;
        k -= l;
        
        while (k != 0) {
            
            if (k >= l) {
                ans++;
                k -= l;
            }
            
            int tmp = l - ll;
            l = ll;
            ll = tmp;
        }
        
        return ans;
    }
};