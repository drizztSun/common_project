# 481. Magical String

# A magical string S consists of only '1' and '2' and obeys the following rules:

# The string S is magical because concatenating the number of contiguous occurrences of characters '1' and '2' generates the string S itself.

# The first few elements of string S is the following: S = "1221121221221121122……"

# If we group the consecutive '1's and '2's in S, it will be:

# 1 22 11 2 1 22 1 22 11 2 11 22 ......

# and the occurrences of '1's or '2's in each group are:

# 1 2	2 1 1 2 1 2 2 1 2 2 ......

# You can see that the occurrence sequence above is the S itself.

# Given an integer N as input, return the number of '1's in the first N number in the magical string S.

# Note: N will not exceed 100,000.

# Example 1:
# Input: 6
# Output: 3
# Explanation: The first 6 elements of magical string S is "12211" and it contains three 1's, so return 3.

class MagicalString:


    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """ 
        cnt, s, two = 0, "1", True

        for i in range(n - 1):

            if s[i] == "1":
                cnt += 1
                s += two and "2" or "1"
            else: 
                s += two and "22" or "11"

            two = not two
        
        return cnt if n != 1 else 1


    def doit1(self, n):
        """
        :type n: int
        :rtype: int
        """        
        mapping = {'1':'22', '11': '2', '22': '11', '2': '1'}
        s, last, length = '1', '1', 1

        while len(s) < n:
            
            new = mapping[last]
            if new in ('11', '1'):
                length += len(new)

            s += new
            last = new

        return length - s[n:].count('1')


if __name__ == "__main__":

    res = MagicalString().doit(6) # 3 '12211'

    res = MagicalString().doit(4)
