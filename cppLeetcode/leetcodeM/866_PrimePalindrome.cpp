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


public:
    
    int doit_math(int N) {
        


    }
};