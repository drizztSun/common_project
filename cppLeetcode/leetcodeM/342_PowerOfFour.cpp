/*
342. Power of Four

Given an integer n, return true if it is a power of four. Otherwise, return false.

An integer n is a power of four, if there exists an integer x such that n == 4x.

 

Example 1:

Input: n = 16
Output: true
Example 2:

Input: n = 5
Output: false
Example 3:

Input: n = 1
Output: true
 

Constraints:

-2^31 <= n <= 2^31 - 1

*/

class isPowerOfFour {

public:

    /*
        342.Power-of-Four
        满足power of 4的条件是：1.大于零；2.是power of 2；3.num-1之后是3的倍数。

        其中满足power of 2的条件是：除了最高bit位是1，其余位都是0，所以 num & (num-1) ==0

        为什么num-1一定会是3的倍数呢？(4^k-1)=(2^k+1)(2^k-1)，其中2^k一定不能被3整除，余数可能是1，也可能是2，无论哪一种，(2^k+1)和(2^k-1)里必然有一个能被3整除。


        num == 4^k => 1000000, so num - 1 = 111111, so 1000000 ^ 111111 == 0

        4^k % 3 = (3+1) * 4^(k-1) % 3 = 4^(k-1) => k == 1, it is 1.
        so (num - 1) % 3 == 0 
    */
    bool doit_bitmask(int num) 
    {
        if (num==1) return true;

        return (num>0 && (num&(num-1))==0 && (num-1)%3==0);
    }

};