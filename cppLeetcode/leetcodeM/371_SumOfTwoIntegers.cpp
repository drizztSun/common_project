/*
371. Sum of Two Integers

Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example 1:

Input: a = 1, b = 2
Output: 3
Example 2:

Input: a = -2, b = 3
Output: 1

*/
#include <stdlib.h>
#include <numeric>

class SumOfTwoInteger {

public:
    /*
            371.Sum-of-Two-Integers
        将a+b改造为m+n，其中m=a^b不进位的加法，n=(a&b)<<1将有进位的bit置为1。反复这样的操作直至所有的进位为零，得到的m即为结果。
    */
    int getSum(int a, int b) 
    {     
        long mask = 0xFFFFFFFF;
        while (b!=0)
        {
            int aa= (a^b) & mask;  // 不进位的加法
            int bb= ((a&b) & mask) <<1; // 各个位上的进位值
            a = aa;
            b = bb;
        }
        return a;
    }

    /*
        Approach 2: Bit Manipulation: Short Language-Specific Solution
        Approach 1 is easy to attack during the follow-up:

        Please don't use multiplication to manage negative numbers and make a clean bitwise solution.

        Let's be honest, it's a trap. Once you start to manage negative numbers using bit manipulation, your solution becomes language-specific.

        Different languages represent negative numbers differently.

        Java

        For example, Java integer is a number of 32 bits. 31 bits are used for the value. The first bit is used for the sign: if it's equal to 1, the number is negative, if it's equal to 0, the number is positive.

        And now the fun starts. Does it mean that

        The main goal of "two's complement" is to decrease the complexity of bit manipulations. How does Java compute "two's complement" and manage 32-bits limit? Here is how:

        After each operation we have an invisible & mask, where mask = 0xFFFFFFFF, i.e. bitmask of 32 1-bits.

        The overflow, i.e. the situation of x > 0x7FFFFFFF (bitmask of 31 1-bits), is managed as x --> ~(x ^ 0xFFFFFFFF).

        At this point, we could come back to approach 1 and, surprisingly, all management of negative numbers, signs, and subtractions Java already does for us. That simplifies the solution to the computation of a sum of two positive integers. 
        That's how the magic of "two's complement" works!

        Python

        Now let's go back to real life. Python has no 32-bits limit, and hence its representation of negative integers is entirely different.

        There is no Java magic by default, and if you need a magic - just do it:

        After each operation we have an invisible & mask, where mask = 0xFFFFFFFF, i.e. bitmask of 32 1-bits.

        The overflow, i.e. the situation of x > 0x7FFFFFFF (bitmask of 31 1-bits), is managed as x --> ~(x ^ 0xFFFFFFFF).


        Implementation

        Each language has its beauty.


        Complexity Analysis

        Time complexity: O(1).

        Space complexity: O(1).

    */
    int doit_(int a, int b) {

        // mask is bit to handle negetive value. or there is error about left shift of negative value -2147483648 for -1.
        long mask = 0xFFFFFFFF;
        
        while (b != 0) {
            int answer = (a ^ b) & mask;
            int carry = ((a & b) & mask) << 1;
            a = answer;
            b = carry;
        }
         
        return a < INT_MAX ? a : ~(a ^ mask);
    }
};