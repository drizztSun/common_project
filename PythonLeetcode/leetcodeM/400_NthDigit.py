"""
400. Nth Digit

Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...

Note:
n is positive and will fit within the range of a 32-bit signed integer (n < 231).

Example 1:

Input:
3

Output:
3
Example 2:

Input:
11

Output:
0

Explanation:
The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
"""


class NthDigit:

    def doit_(self, n: int) -> int:
        
        n -= 1
        for digits in range(1, 11):

            base = 10 ** (digits - 1) # ones=1, tens=10, hundred=100, thousand=1000
        
            if n < 9 * digits * base:
                
                return int(str(base + int(n//digits))[n % digits]) # 1000 + (200)//4, 1050[0]

            n -= 9 * digits * base # 0~9,9  10~99,90*2 100~999, 900*3