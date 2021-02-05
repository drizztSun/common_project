"""
1404. Number of Steps to Reduce a Number in Binary Representation to One


Given a number s in their binary representation. Return the number of steps to reduce it to 1 under the following rules:

If the current number is even, you have to divide it by 2.

If the current number is odd, you have to add 1 to it.

It's guaranteed that you can always reach to one for all testcases.

 

Example 1:

Input: s = "1101"
Output: 6
Explanation: "1101" corressponds to number 13 in their decimal representation.
Step 1) 13 is odd, add 1 and obtain 14. 
Step 2) 14 is even, divide by 2 and obtain 7.
Step 3) 7 is odd, add 1 and obtain 8.
Step 4) 8 is even, divide by 2 and obtain 4.  
Step 5) 4 is even, divide by 2 and obtain 2. 
Step 6) 2 is even, divide by 2 and obtain 1.  
Example 2:

Input: s = "10"
Output: 1
Explanation: "10" corressponds to number 2 in their decimal representation.
Step 1) 2 is even, divide by 2 and obtain 1.  
Example 3:

Input: s = "1"
Output: 0
 

Constraints:

1 <= s.length <= 500
s consists of characters '0' or '1'
s[0] == '1'

"""


class NumStepsReduce:

    """
        for exsample, 111100001

        For '1', add 1 and divide 2, +2, 111100010 => 11110001, then remove a 0 by 2 step
        
        if there is 11110000, no 1, remove '0' needs by 1 step 


    """
    def doit_(self, s: str) -> int:
        
        return len(s) - 1 if s.count('1') == 1 else s.count('0') + s.rfind('1') + 2

    def doit_(self, s: str) -> int:

        carry = 0
        ret = 0
        n = len(s)
        for i in range(n-1, 0, -1):
            ret += 1
            if int(s[i]) + carry == 1:
                carry = 1
                ret += 1
        return ret + carry

    def doit_(self, s: str) -> int:

        count = 0
        handle = False

        for c in reversed(s):

            if handle:
                if c == '0':
                    count += 2
                    handle = True
                else:
                    count += 1
                    handle = True
            else:
                if c == '0':
                    count += 1
                    handle = False
                else:
                    count += 2
                    handle = True
        
        return (count + 1) if handle else count

