# 476. Number Complement

# Given a positive integer, output its complement number. The complement strategy is to flip the bits of its binary representation.

# Note:
# The given integer is guaranteed to fit within the range of a 32-bit signed integer.
# You could assume no leading zero bit in the integer’s binary representation.

# Example 1:
# Input: 5
# Output: 2
# Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.

# Example 2:
# Input: 1
# Output: 0
# Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.

class NumberComplement:

    def doit(self, num):
        """
        :type num: int
        :rtype: int
        """
        n = 2
        while n <= num:
            n <<= 1

        return (n - 1) - num # better than (n-1) ^ num 
        


    def doit1(self, num):
        """
        :type num: int
        :rtype: int
        """
        bits = bin(num)[2:]
        res = 0
        n = 0
        for c in bits[::-1]:
            
            res += 0 if c == '1' else 2 ** n
        
            n += 1
            
        return res


if __name__ == "__main__":

    res = NumberComplement().doit(5)

    res = NumberComplement().doit(1)