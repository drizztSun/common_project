/*
1780. Check if Number is a Sum of Powers of Three


Given an integer n, return true if it is possible to represent n as the sum of distinct powers of three. Otherwise, return false.

An integer y is a power of three if there exists an integer x such that y == 3x.

 

Example 1:

Input: n = 12
Output: true
Explanation: 12 = 31 + 32
Example 2:

Input: n = 91
Output: true
Explanation: 91 = 30 + 32 + 34
Example 3:

Input: n = 21
Output: false
 

Constraints:

1 <= n <= 10^7

*/


class CheckPowersOfThree {

public:

    /*
        All integers are 3*n, 3*n+1, 3*n+2. So if it is like 3^0 + 3^1 + .... + 3^n.
        Keep divide 3, if remainder is 2, it means 3*n+2, so it is not.
        3*n+1 has 3^0, 3*n has no 3^0 
    */
    bool doit_math(int n) {
        while (n) {
            if (n % 3 == 2) return false;
            n /= 3;
        }
        return true;
    }
};