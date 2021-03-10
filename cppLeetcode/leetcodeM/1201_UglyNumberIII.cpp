/*
1201. Ugly Number III

Given four integers n, a, b, and c, return the nth ugly number.

Ugly numbers are positive integers that are divisible by a, b, or c.

 

Example 1:

Input: n = 3, a = 2, b = 3, c = 5
Output: 4
Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3rd is 4.
Example 2:

Input: n = 4, a = 2, b = 3, c = 4
Output: 6
Explanation: The ugly numbers are 2, 3, 4, 6, 8, 9, 10, 12... The 4th is 6.
Example 3:

Input: n = 5, a = 2, b = 11, c = 13
Output: 10
Explanation: The ugly numbers are 2, 4, 6, 8, 10, 11, 12, 13... The 5th is 10.
Example 4:

Input: n = 1000000000, a = 2, b = 217983653, c = 336916467
Output: 1999999984
 

Constraints:

1 <= n, a, b, c <= 10^9
1 <= a * b * c <= 10^18
It is guaranteed that the result will be in range [1, 2 * 10^9].
*/
#include <cmath>


class NthUglyNumber {

    /*
        1201.Ugly-Number-III
        我们回想一道小学奥数题。问从1～120以内能被2或3或5整除的自然数有几个？这涉及到了容斥原理的一些知识。假设答案是k。那么我们反问，第k个能被2或3或5整除的自然数是谁？因为120恰好就是一个能被2或3或5整除的自然数，所以第k个这样的数一定就是120.

        所以，我们对于这道题，我们就是希望猜测这样一个数M，使得1～M之间能被a或b或c整除的自然数恰好有n个。言下之意，1～(M-1)之间能被a或b或c整除的自然数就只有n-1个了。对于这样的数，显然我们又可以利用二分法的策略去猜:反馈依据就是M以内能被a或b或c整除的自然数的个数，通过与n的比较来调整搜索区间。

        最后如何写count(M)来计算M以内能被a或b或c整除的自然数的个数的个数呢？依据容斥原理：

        count(M) = M/a+M/b+M/c-M/lcm(a,b)-M/lcm(a,c)-M/lcm(b,c)+M/lcm(lcm(a,b),c);
        其中最小公倍数：lcm(a,b) = a*b/gcd(a,b)，最大公约数则用辗转相除法：

            ll gcd(ll a, ll b)
            {
                if (b==0)
                    return a;
                return gcd(b, a%b);
            }
    */
    typedef long long ll;
    
    int nthUglyNumber(int n, int a, int b, int c) 
    {
        ll left = 1;
        ll right = INT_MAX;
        
        while (left<right)
        {
            ll mid = left+(right-left)/2;
            if (count(mid, a,b,c) < n )
                left = mid+1;
            else
                right = mid;
        }
        
        return left;
    }
    
    int count(ll M, ll a, ll b, ll c)
    {
        return M/a+M/b+M/c-M/lcm(a,b)-M/lcm(a,c)-M/lcm(b,c)+M/lcm(lcm(a,b),c);
    }
    
    ll lcm(ll a, ll b)
    {
        return a*b/gcd(a,b);
    }
    
    ll gcd(ll a, ll b)
    {
        if (b==0)
            return a;
        return gcd(b, a%b);
    }

public:

    int doit_binary_search(int n, int a, int b, int c) {
        
        int low = 1, high = INT_MAX;
        long A = long(a), B = long(b), C = long(c);
        long AB = lcm(A, B);
        long BC = lcm(B, C);
        long AC = lcm(A, C);
        long ABC = lcm(A, BC);
            
        
        while (low < high) {
            // keep this way, if high and low are all greater than INT_MAX/2, it will be over-flow.
            int mid = low + (high - low) / 2;
            int count = mid/A + mid/B + mid/C - mid/AB - mid/AC - mid/BC + mid/ABC;
            
            if (count >= n)
                high = mid;
            else
                low = mid + 1;
        }
        
        return low;

    }
};