/*
7. Reverse Integer


Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.

Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

 

Example 1:

Input: x = 123
Output: 321
Example 2:

Input: x = -123
Output: -321
Example 3:

Input: x = 120
Output: 21
Example 4:

Input: x = 0
Output: 0
 

Constraints:

-231 <= x <= 231 - 1

*/

class Reverse {

    /*
        007.Reverse-Integer
        这是一道简单题，但是依然有两个知识点需要掌握。

        首先，要记住INT_MIN=-2^31，对它去绝对值的话是会溢出整形的。所以对一个任意整形取绝对值的时候一定要考虑它是否可能是INT_MIN。

        其次，如果快速判断一个数字在进位的过程中是否溢出？比如说如何判断x*10 > INT_MAX？其实交换一下位置，用if (x > INT_MAX/10)就巧妙地规避溢出报错的问题。
    */
    int reverse(int x) 
    {
        if (x==INT_MIN) return 0;
        
        int sign = 1;
        if (x<0) sign = -1;
        
        x = abs(x); 
        
        int ret = 0;
        while (x>0)
        {
            if (ret > INT_MAX/10) return 0;
            if (ret*10 > INT_MAX - x%10 ) return 0;
            
            ret = ret*10 + x%10;
            x = x/10;
        }
        
        return ret*sign;
    }

    int reverse(int x) {
        
        if (x == INT_MIN) return 0;
        bool sign = x > 0;
        if (x < 0) x = -x;
        int ans = 0;
        
        while (x > 0) {
            if (ans > INT_MAX/10) return 0;
            if (ans*10 > INT_MAX - x%10) return 0;
            ans = ans * 10 + x % 10;
            x /= 10;
        }
        
        return sign ? ans : -ans;
    }
};