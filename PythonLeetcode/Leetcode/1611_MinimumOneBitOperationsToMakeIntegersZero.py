"""
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

0 <= n <= 10^9


"""

"""
Intuition
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

"""


class MinimumOneBitOperations:

    """
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
    """
    def doit_(self, n: int) -> int:

        dp = {0: 0}

        def recursive(num):

            if num not in dp:
                b = 1
                while (b << 1) <= num:
                    b <<= 1

                # 1XXXXXX -> 1100000, recursive need to call this
                # 1 + b - 1 is for 1100000 - > 100000 -> 0
                dp[num] = recursive(num ^ b ^ (b >> 1)) + 1 + b - 1

            return dp[num]

        return recursive(n)

    """
    Solution 2: Tail Recursion
    Time O(logn)
    Space O(1)
    
    """
    def doit_2(self, n: int) -> int:

        def recursive(num, res):
            if num == 0:
                return res

            b = 1
            while (b << 1) <= num:
                b <<= 1

            return recursive(num ^ b ^ (b << 1), res + 1 + b -1)

        return recursive(n, 0)

    """
    Solution 3: Iterative Solution
    Inspired by @endlesscheng, can be proved based on solution 2.
    
    We iterate the binary format of n,
    whenever we meet bit 1 at ith position,
    we increment the result by (1 << (i + 1)) - 1.
    
    Time O(logn)
    Space O(1)
    """
    def doit_(self, n: int) -> int:
        res = 0
        while n:
            res = -res - (n ^ (n - 1))
            n &= n - 1
        return abs(res)


