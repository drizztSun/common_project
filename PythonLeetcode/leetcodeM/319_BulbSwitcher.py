"""
319. Bulb Switcher

There are n bulbs that are initially off. You first turn on all the bulbs, then you turn off every second bulb.

On the third round, you toggle every third bulb (turning on if it's off or turning off if it's on). 

For the ith round, you toggle every i bulb. For the nth round, you only toggle the last bulb.

Return the number of bulbs that are on after n rounds.

 

Example 1:


Input: n = 3
Output: 1
Explanation: At first, the three bulbs are [off, off, off].
After the first round, the three bulbs are [on, on, on].
After the second round, the three bulbs are [on, off, on].
After the third round, the three bulbs are [on, off, off]. 
So you should return 1 because there is only one bulb is on.
Example 2:

Input: n = 0
Output: 0
Example 3:

Input: n = 1
Output: 1
 

Constraints:

0 <= n <= 109
"""


class BulbSwitch:

    """
        The sqrt(n) solution can be explained using following matrix.

        1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        2,4,6,8,10,12,14,16,18,20,
        3,6,9,12,15,18,
        4,8,12,16,20,
        5,10,15,20,
        6,12,18,
        7,14,
        8,16,
        9,18,
        10,20,
        11,
        12,
        13,
        14,
        15,
        16,
        17,
        18,
        19,
        20,
        Each line in this matrix indicates which bulb should be switched. This is a Symmetric Matrices, so only the diagonal elements will be visited odd. The non-diagonal elements will be visited twice. 
        So only the diagonal elements will be "true" after all. The length of the diagonal elements is sqrt(n). The number of "true" also will be the length of the diagonal elements.
    """
    def doit_(self, n: int) -> int:
        from math import sqrt
        return int(sqrt(n))

    def doit_(self, n: int) -> int:
        
        count = 0
        i = 1
        c = 1
        while c <= n:
            count += 1
            i += 1
            c = i ** 2
                
        return count
        