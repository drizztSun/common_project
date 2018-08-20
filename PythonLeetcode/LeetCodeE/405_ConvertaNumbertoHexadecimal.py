


# 405. Convert a Number to Hexadecimal

# Given an integer, write an algorithm to convert it to hexadecimal.
# For negative integer, two’s complement method is used.

#Note:

# All letters in hexadecimal (a-f) must be in lowercase.
# The hexadecimal string must not contain extra leading 0s. If the number is zero, it is represented by a single zero character '0'; otherwise, the first character in the hexadecimal string will not be the zero character.
# The given number is guaranteed to fit within the range of a 32-bit signed integer.
# You must not use any method provided by the library which converts/formats the number to hex directly.

# Example 1:
# Input:
# 26

# Output:
# "1a"

# Example 2:

# Input:
# -1

# Output:
# "ffffffff"

class toHex:


    def doit(self, num):
        """
        :type num: int
        :rtype: str
        """
        if num == 0:
            return '0'

        hexKey = '0123456789abcdef'
        ans = ''
        
        for _ in range(8):
            ans = hexKey[num & 15] + ans
            num >>= 4

        return ans.lstrip('0')

    def doit(self, num):
        """
        :type num: int
        :rtype: str
        """
        if num == 0:
            return '0'

        if num < 0:
            num = ~(0xffffffff ^ num)

        ans = ''
        while num:
            ans = '0123456789abcdef'[num % 16] + ans
            num >>= 4

        return ans

    def doit(self, num):
        """
        :type num: int
        :rtype: str
        """
        ans = []
        dic = {10:"a", 11:"b", 12:"c", 13:"d", 14:"e", 15:"f"}

        if num == 0:
            return "0"

        if num < 0:
            num = num + 2**32

        while num > 0:

            digit = num % 16
            num = num // 16

            if digit > 9 and digit < 16:
                digit = dic[digit]
            else:
                digit = str(digit)

            ans.append(digit)

        return "".join(ans[::-1])
            
        



if __name__=="__main__":

    res = toHex(26)

    res = toHex(-1)



    
        