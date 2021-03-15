/*
204. Count Primes

Count the number of prime numbers less than a non-negative number, n.

 

Example 1:

Input: n = 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
Example 2:

Input: n = 0
Output: 0
Example 3:

Input: n = 1
Output: 0
 

Constraints:

0 <= n <= 5 * 10^6

*/
#include <vector>

using std::vector;


class CountPrimes {

    /*
        204.Count-Primes
        用倍数筛除法去除所有已知质数的倍数。最高效的容器是bool型的vector

        vector<bool>q(n,true);
        for (x=2; x<=sqrt(n); x++)
        {
        if (q[x]==false) continue; 
        for (int i=2; x*i<n; i++)
            q[x*i]=false;
        }
        然后检查从2到n-1里仍然标记为true的元素数目。

        注意，x的判断范围是从2到sqrt(n)即可，不需要遍历到n。
            
    */
    int countPrimes(int n) 
    {
        if (n<=2) return 0;
        
        vector<bool> num(n - 1, true);
        
        for (int x = 2; x <= sqrt(n); x++) 
        {
            if (num[x]==false) continue;
            
            for (int j=2; x*j < n; j++) 
                num[x*j] = false;
        }
        
        int count=0;
        for (int j = 2; j < n; ++j) 
        {
            if (num[j]) count++;
        }
        
        return count;
    }
};