"""
1432. Max Difference You Can Get From Changing an Integer


You are given an integer num. You will apply the following steps exactly two times:

Pick a digit x (0 <= x <= 9).
Pick another digit y (0 <= y <= 9). The digit y can be equal to x.
Replace all the occurrences of x in the decimal representation of num by y.
The new integer cannot have any leading zeros, also the new integer cannot be 0.
Let a and b be the results of applying the operations to num the first and second times, respectively.

Return the max difference between a and b.

 

Example 1:

Input: num = 555
Output: 888
Explanation: The first time pick x = 5 and y = 9 and store the new integer in a.
The second time pick x = 5 and y = 1 and store the new integer in b.
We have now a = 999 and b = 111 and max difference = 888
Example 2:

Input: num = 9
Output: 8
Explanation: The first time pick x = 9 and y = 9 and store the new integer in a.
The second time pick x = 9 and y = 1 and store the new integer in b.
We have now a = 9 and b = 1 and max difference = 8
Example 3:

Input: num = 123456
Output: 820000
Example 4:

Input: num = 10000
Output: 80000
Example 5:

Input: num = 9288
Output: 8700
 

Constraints:

1 <= num <= 10^8
"""


class MaxDifferenceYouCanGetFromChargingAnInteger:

    def doit_(self, num: int) -> int:

        s1 = str(num)
        r = '9'
        for i in range(len(s1)):
            if s1[i] != '9':
                r = s1[i]
                break

        high = int(s1.replace(r, '9'))

        s2 = str(num)
        v = None
        if s2[0] == '1':
            for i in range(1, len(s2)):
                if s2[i] != '0' and s2[i] != '1':
                    r, v = s2[i], '0'
                    break
            else:
                pass
        else:
            r, v = s2[0], '1'
        
        if v:
            low = int(s2.replace(r, v))
        else:
            low = int(s2)
                
        return high - low


if __name__ == '__main__':

    MaxDifferenceYouCanGetFromChargingAnInteger().doit_(555)

    MaxDifferenceYouCanGetFromChargingAnInteger().doit_(123456)

    MaxDifferenceYouCanGetFromChargingAnInteger().doit_(111)

        
        

