/*
866. Prime Palindrome

Find the smallest prime palindrome greater than or equal to N.

Recall that a number is prime if it's only divisors are 1 and itself, and it is greater than 1. 

For example, 2,3,5,7,11 and 13 are primes.

Recall that a number is a palindrome if it reads the same from left to right as it does from right to left. 

For example, 12321 is a palindrome.

 

Example 1:

Input: 6
Output: 7
Example 2:

Input: 8
Output: 11
Example 3:

Input: 13
Output: 101
 

Note:

1 <= N <= 10^8
The answer is guaranteed to exist and be less than 2 * 10^8.

*/

#include <string>

using std::string;

class PrimePalindrome {

    /*
        866.Prime-Palindrome
        我们有两种思路，一种是搜寻所有大于N的质数，然后查看它们是否是回文数。另一种方案是反过来，搜寻所有大于N的回文数，然后查看它们是否是质数。显然后者更高效，因为我们只需要确定回文数的前缀，就能通过翻转构造出完整的回文数。考虑到答案的上限是2e8（也就是9位数字），说明我们可以直接遍历大约1e4种回文数（即确定回文数的前五个数字），时间复杂度是可以接受的。

        有一个需要注意的，假设我们确定了回文数的前半部分xyz，理论上我们可以构造出两种回文数:xyzzyx和xyzyx。但前者肯定不是质数，因为能被11整除。所以对于任意的前缀，我们只需要构造奇数位的回文数即可。因此搜索的时间复杂度可以进一步减半。

        因为答案上限是2e8，所以我们遍历的前缀可以从1（对应的回文数是1）到20000（对应的回文数是200000002）。或者我们可以将下限设置的更精确些。如果N的位数是n，那么我们可以从前缀为pow(10,n/2)开始搜索。

        但是有一个corner case，那么就是当N==11的时候，不能通过上面的步骤得到正确的答案。这是因为11虽然有偶数位，根据上面的分析可知它能被11整除，但恰好它本身就是质数。
    */
    int primePalindrome(int N) 
    {
        if (N>7 && N<=11) return 11;
        
        string M = std::to_string(N);
        int n = M.size()/2;
        
        int a = pow(10,n);
        
        for (int i=a; i<=20000; i++)
        {
            string s = std::to_string(i);
            string s1 = s.substr(0, s.size()-1);
            reverse(s1.begin(),s1.end());
            s = s+s1;
            
            int k = stoi(s);
            if (k>=N && isPrime(k)) return k;
        }
        
        return -1;
    }
    
    bool isPrime(int k)
    {
        if (k==1) return false;
        if (k%2==0) return k==2;
        for (int i=3; i*i<=k; i+=2)
        {
            if (k%i==0) return false;
        }
        return true;
    }

    int doit_math(int N) {
        
        auto isPrime = [](int x) {
            if (x < 2 || x%2 == 0) return x == 2;
            for (int i = 3; i*i <= x; i += 2) {
                if (x % i == 0) return false;
            }
            return true;
        };
        
        if (N > 7 && N <= 11) return 11; 
        
        for (int i = 1; i < 1e8; i++) {
            
            string s = std::to_string(i);
            string r(rbegin(s), rend(s));
            
            int num = std::stoi(s + r.substr(1));
            
            if (num >= N && isPrime(num)) return num;
        }
        
        return -1;
    }


public:

    /*
        Intuition
        Write some example, you find all even length palindromes are divisible by 11.
        So we need to search only palindrome with odd length.

        We can prove as follow:
        11 % 11 = 0
        1111 % 11 = 0
        111111 % 11 = 0
        11111111 % 11 = 0

        So:
        1001 % 11 = (1111 - 11 * 10) % 11 = 0
        100001 % 11 = (111111 - 1111 * 10) % 11 = 0
        10000001 % 11 = (11111111 - 111111 * 10) % 11 = 0

        For any palindrome with even length:
        abcddcba % 11
        = (a * 10000001 + b * 100001 * 10 + c * 1001 * 100 + d * 11 * 1000) % 11
        = 0

        All palindrome with even length is multiple of 11.
        So among them, 11 is the only one prime
        if (8 <= N <= 11) return 11

        For other cases, we consider only palindrome with odd dights.


        More Generally
        Explanation from @chuan-chih:
        A number is divisible by 11 if sum(even digits) - sum(odd digits) is divisible by 11.
        Base case: 0
        Inductive step:
        If there is no carry when we add 11 to a number, both sums +1.
        Whenever carry happens, one sum -10 and the other +1.
        The invariant holds in both cases.


        Time Complexity
        O(10000) to check all numbers 1 - 10000.
        isPrime function is O(sqrt(x)) in worst case.
        But only sqrt(N) worst cases for 1 <= x <= N
        In general it's O(logx)
    */
    int primePalindrome(int N) {
        if (8 <= N && N <= 11) return 11;
        for (int x = 1; x < 100000; ++x) {
            string s = std::to_string(x), r(s.rbegin(), s.rend());
            int y = stoi(s + r.substr(1));
            if (y >= N && isPrime(y)) return y;
        }
        return -1;
    }
    bool isPrime(int num) {
        if (num < 2 || num % 2 == 0) return num == 2;
        for (int i = 3; i * i <= num; i += 2)
            if (num % i == 0) return false;
        return true;
    }
};