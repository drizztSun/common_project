# 738. Monotone Increasing Digits

#Given a non-negative integer N, find the largest number that is less than or equal to N with monotone increasing digits.

#(Recall that an integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.)

#Example 1:
#Input: N = 10
#Output: 9
#Example 2:
#Input: N = 1234
#Output: 1234
#Example 3:
#Input: N = 332
#Output: 299

import functools

class MonotoneIncreasingDigits:
    def doit(self, N: 'int') -> 'int':
        
        bits = [int(c) for c in str(N)]
        pre = 0
        for i in range(len(bits) - 1):

            if bits[i] != bits[pre]:
                pre = i
                
            if bits[i] > bits[i+1]:
                bits[pre] -= 1
                bits[pre + 1:] = [9] * (len(bits) - pre - 1)
 
        return functools.reduce((lambda x, y: x * 10 + y), bits)                   
            
        
