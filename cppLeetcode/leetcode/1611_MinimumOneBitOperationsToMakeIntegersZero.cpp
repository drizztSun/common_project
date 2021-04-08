/*

1611. Minimum One Bit Operations to Make Integers Zero

Given an integer n, you must transform it into 0 using the following operations any number of times:

Change the rightmost (0th) bit in the binary representation of n.
Change the ith bit in the binary representation of n if the (i-1)th bit is set to 1 and the (i-2)th through 0th bits are set to 0.
Return the minimum number of operations to transform n into 0.

 

Example 1:

Input: n = 0
Output: 0
Example 2:

Input: n = 3
Output: 2
Explanation: The binary representation of 3 is "11".
"11" -> "01" with the 2nd operation since the 0th bit is 1.
"01" -> "00" with the 1st operation.
Example 3:

Input: n = 6
Output: 4
Explanation: The binary representation of 6 is "110".
"110" -> "010" with the 2nd operation since the 1st bit is 1 and 0th through 0th bits are 0.
"010" -> "011" with the 1st operation.
"011" -> "001" with the 2nd operation since the 0th bit is 1.
"001" -> "000" with the 1st operation.
Example 4:

Input: n = 9
Output: 14
Example 5:

Input: n = 333
Output: 393
 

Constraints:

0 <= n <= 109

*/
#include <functional>
#include <unordered_map>

using std::unordered_map;

class MinimumOneBitOperationsToMakeZero {

public:

    /*
    For 1XXXXXXX,
    we need to transfer it
    1XXXXXXX -> ... -> 11000000 -> 1000000 -> ... -> 0


    Observation 1
    The two operations are undo-able.
    If a -> b needs k operation,
    b -> a also needs k operation.


    Observation 2
    1 -> 0 needs 1 operation,
    2 -> 0 needs 3 operations,
    4 -> 0 needs 7 operations,
    2^k needs 2^(k+1)-1 operations.

    This can be easily proved.


    Solution 1: Recursion
    1XXXXXX -> 1100000 -> 100000 -> 0

    1XXXXXX -> 1100000 needs minimumOneBitOperations(1XXXXXX ^ 1100000),
    because it needs same operations 1XXXXXX ^ 1100000 -> 1100000 ^ 1100000 = 0.

    1100000 -> 100000 needs 1 operation.
    100000 -> 0, where 100000 is 2^k, needs 2^(k+1) - 1 operations.

    In total,
    f(n) = f((b >> 1) ^ b ^ n) + 1 + b - 1,
    where b is the maximum power of 2 that small or equals to n.

    Time O(logn)
    Space O(logn)
    */
    int doit_recursive(int n) {
        unordered_map<int, int> dp{{0, 0}};

        std::function<int(int)> search = [&](int num) {
        
            if (dp.count(num) > 0)
                return dp[num];

            int b = 1;
            while ((b << 1) <= num) {
                b <<= 1;
            }

            return dp[num] = (search(num ^ b ^ (b >> 1)) + 1 + b - 1);
        };

        return search(n);
    } 

    /*

    Note that the number of operations for n to become 0 is the same as the number of operations for 0 to become n...

    Let's see how it can be done for numbers that are powers of 2.
    1 -> 0 => 1
    10 -> 11 -> 01 -> ... => 2 + 1
    100 -> 101 -> 111 -> 110 -> 010 -> ... => 4 + 2 + 1
    1000 -> 1001 -> 1011 -> 1010 -> 1110 -> 1111 -> 1101 -> 1100 -> 0100 -> ... => 8 + 4 + 2 + 1
    We can find that for 2^n, it needs 2^(n+1) - 1 operations to become 0.

    Now suppose we want to know the number of operations for 1110 to become 0. We know it takes 15 operations for 0 to become 1000, and it takes 4 operations for 1000 to become 1110. We get the solution by 15 - 4.
    Note that 4 here is the number of operations from 1000 to become 1110, which is the same as the number of operations from 000 to 110 (ignoring the most significant bit), and it can be computed recursively. The observation gives us: minimumOneBitOperations(1110) + minimumOneBitOperations(0110) = minimumOneBitOperations(1000).

    From the above intuition, we can reduce n bit by bit, starting from the most significant bit.
    */
    int minimumOneBitOperations(int n) {
        if (n <= 1)
            return n;
        int bit = 0;
        while ((1 << bit) <= n)
            bit++;
        return ((1 << bit) - 1) - minimumOneBitOperations(n - (1 << (bit-1)));
    }

    /*
        Observation 1
        The two operations are undo-able.
        If a -> b needs k operation,
        b -> a also needs k operation.
    */
    int doit(int num) {

        int mask = num;
        
        while(mask) {
            mask >>= 1;
            num ^= mask;
        }
        
        return num;
    }

};