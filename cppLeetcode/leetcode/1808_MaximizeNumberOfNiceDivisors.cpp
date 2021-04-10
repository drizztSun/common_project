/*
1808. Maximize Number of Nice Divisors

You are given a positive integer primeFactors. You are asked to construct a positive integer n that satisfies the following conditions:

    . The number of prime factors of n (not necessarily distinct) is at most primeFactors.
    . The number of nice divisors of n is maximized. Note that a divisor of n is nice if it is divisible by every prime factor of n. 
        For example, if n = 12, then its prime factors are [2,2,3], then 6 and 12 are nice divisors, while 3 and 4 are not.

Return the number of nice divisors of n. Since that number can be too large, return it modulo 109 + 7.

Note that a prime number is a natural number greater than 1 that is not a product of two smaller natural numbers. The prime factors of a number n is a list of prime numbers such that their product equals n.

 

Example 1:

Input: primeFactors = 5
Output: 6
Explanation: 200 is a valid value of n.
It has 5 prime factors: [2,2,2,5,5], and it has 6 nice divisors: [10,20,40,50,100,200].
There is not other value of n that has at most 5 prime factors and more nice divisors.
Example 2:

Input: primeFactors = 8
Output: 18
 

Constraints:

1 <= primeFactors <= 109

*/


class MaxNiceDivisors {

public:

    /*
        1808.Maximize-Number-of-Nice-Divisors
        本题的意思是说，如果一个数的分解质因数是a^k1*b^k2*c^k3*...的形式，并且质因数总个数是primefactors = k1+k2+k3+.... 问有多少个它的因数能同时被a,b,c...整除。

        显然这种的因数的个数是 k1*k2*k3*...，也就是说每种质因数最少取1个，最多取k个。那么总的组合数就是用乘法原理。于是本题就转化为，已知一堆数的和是固定值，求如何分配这堆数，使得这堆数的乘积的最大值。
        这道题本质就是343.Integer Break.我们断言当这堆数都相等的时候乘积能最大。那么这堆数究竟分成几份呢？我们想求f = (a/n)^n的最大值，令其导函数等于零，可以得到n等于自然对数e=2.718. 所以结论是，我们尽量将这些数切分出为3和2，其中3越多越好。

        假设primeFactor能切分为a个3与b个2的和，那么答案就是``pow(3,a)*pow(2,b)```。注意这个幂可能非常大并且会越界，所以我们需要手工加载快速幂的代码，并在其中嵌入对1e9+7的取模。
    */
    int maxNiceDivisors(int primeFactors) 
    {
        if (primeFactors==1) return 1;
        if (primeFactors==2) return 2;
        if (primeFactors==3) return 3;
        if (primeFactors==4) return 4;
        int a,b;
        if (primeFactors%3==0)
        {
            a = primeFactors/3;
            b = 0;
        }
        else if (primeFactors%3==2)
        {
            a = (primeFactors-2)/3;
            b = 1;
        }
        else
        {
            a = (primeFactors-4)/3;
            b = 2;
        }
        long long ret = 1;
        ret = ret * quickMul(3, a) % M;
        ret = ret * quickMul(2, b) % M;
        return ret;

    }

    long long M = 1e9+7;

    long long quickMul(long long x, long long N) {
        if (N == 0) {
            return 1.0;
        }
        long long y = quickMul(x, N / 2);
        return N % 2 == 0 ? y * y % M: y * y * x % M;
    }

public:

    int doit_(int primeFactors) {
        
    }
};
