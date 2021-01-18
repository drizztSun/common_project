"""
371. Sum of Two Integers

Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example 1:

Input: a = 1, b = 2
Output: 3
Example 2:

Input: a = -2, b = 3
Output: 1


Solution
Overview
Approach 1 is a detailed explanation of bit manipulation basics. 
Approach 2 is a language-specific discussion of a possible follow-up and mainly written for fun.

Approach 1: Bit Manipulation: Easy and Language-Independent
That's an extremely popular Facebook problem designed to check your knowledge of bitwise operators:

x + y that means bitwise XOR

x & y that means bitwise AND

∼x that means bitwise NOT

Reduce the Number of Use Cases

First of all, there are too many use cases here: both aa and bb could be positive or negative, abs(a) could be greater or less than abs(b). 
In total, that results in 2 × 2 × 2 = 8 use cases.

Let's start by reducing the problem down to two simple cases:

Sum of two positive integers: x + y, where x > y.

Difference of two positive integers: x - y, where x > y.

"""


class SumOfTwoIntegers:

    """
        Algorithm

        Simplify problem down to two cases: sum or subtraction of two positive integers: x \pm yx±y, where x > yx>y. Save down the sign of the result.

        If one has to compute the sum:

        While carry is nonzero: y != 0:

        Current answer without carry is XOR of x and y: answer = x^y.

        Current carry is left-shifted AND of x and y: carry = (x & y) << 1.

        Job is done, prepare the next loop: x = answer, y = carry.

        Return x * sign.

        If one has to compute the difference:

        While borrow is nonzero: y != 0:

        Current answer without borrow is XOR of x and y: answer = x^y.

        Current borrow is left-shifted AND of NOT x and y: borrow = ((~x) & y) << 1.

        Job is done, prepare the next loop: x = answer, y = borrow.

        Return x * sign.

        Implementation

        Complexity Analysis

        Time complexity: O(1) because each integer contains 3232 bits.

        Space complexity: O(1) because we don't use any additional data structures.
    """
    def getSum(self, a: int, b: int) -> int:

        x, y = abs(a), abs(b)
        # ensure that abs(a) >= abs(b)
        if x < y:
            return self.getSum(b, a)
        
        # abs(a) >= abs(b) --> 
        # a determines the sign
        sign = 1 if a > 0 else -1
        
        if a * b >= 0:
            # sum of two positive integers x + y
            # where x > y
            while y:
                answer = x ^ y
                carry = (x & y) << 1
                x, y = answer, carry
        else:
            # difference of two integers x - y
            # where x > y
            while y:
                answer = x ^ y
                borrow = ((~x) & y) << 1
                x, y = answer, borrow
        
        return x * sign

    def getSum(self, a: int, b: int) -> int:

        x, y = abs(a), abs(b)
        # ensure x >= y
        if x < y:
            return self.getSum(b, a)  
        sign = 1 if a > 0 else -1
        
        if a * b >= 0:
            # sum of two positive integers
            while y:
                x, y = x ^ y, (x & y) << 1
        else:
            # difference of two positive integers
            while y:
                x, y = x ^ y, ((~x) & y) << 1
        
        return x * sign
    """
        Approach 2: Bit Manipulation: Short Language-Specific Solution
        Approach 1 is easy to attack during the follow-up:

        Please don't use multiplication to manage negative numbers and make a clean bitwise solution.

        Let's be honest, it's a trap. Once you start to manage negative numbers using bit manipulation, your solution becomes language-specific.

        Different languages represent negative numbers differently.


        Python

        Now let's go back to real life. Python has no 32-bits limit, and hence its representation of negative integers is entirely different.

        There is no Java magic by default, and if you need a magic - just do it:

        After each operation we have an invisible & mask, where mask = 0xFFFFFFFF, i.e. bitmask of 32 1-bits.

        The overflow, i.e. the situation of x > 0x7FFFFFFF (bitmask of 31 1-bits), is managed as x --> ~(x ^ 0xFFFFFFFF).

        Complexity Analysis

        Time complexity: O(1).

        Space complexity: O(1).
    """
    def doit_bit(self, a: int, b: int) -> int:
        mask = 0xFFFFFFFF
        
        while b != 0:
            a, b = (a ^ b) & mask, ((a & b) << 1) & mask
        
        max_int = 0x7FFFFFFF
        return a if a < max_int else ~(a ^ mask)

    def doit_bit(self, a: int, b: int) -> int:
        mask = 0xFFFFFFFF
        
        while b != 0:
            a, b = (a ^ b) & mask, ((a & b) << 1) & mask
        
        max_int = 0x7FFFFFFF
        return a if a < max_int else ~(a ^ mask)

    def doit_bit(self, a, b):
        """
        :type a: int
        :type b: int
        :rtype: int
        """

        MAX = 0x7FFFFFFF
        MIN = 0x80000000
        mask = 0xFFFFFFFF
        
        while b :
            a, b = (a ^ b) & mask, ((a & b) << 1) & mask

        return a if a <= MAX else ~(a ^ mask)    

    def doit_(self, a: int, b: int) -> int:

        def add(addor1, addor2):

            shareones = addor1 & addor2
            onlyones = addor1 ^ addor2

            if shareones == 0:
                return onlyones

            return add(onlyones, shareones<<1)
        
        return add(a, b)

        