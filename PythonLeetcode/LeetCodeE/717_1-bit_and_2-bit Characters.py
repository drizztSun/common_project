# 717. 1-bit and 2-bit Characters

# We have two special characters. The first character can be represented by one bit 0. 
# The second character can be represented by two bits (10 or 11).

# Now given a string represented by several bits. Return whether the last character must be a one-bit character or not. 
# The given string will always end with a zero.

# Example 1:
# Input: 
# bits = [1, 0, 0]
# Output: True
# Explanation: 
# The only way to decode it is two-bit character and one-bit character. So the last character is one-bit character.
# Example 2:
# Input: 
# bits = [1, 1, 1, 0]
# Output: False
# Explanation: 
# The only way to decode it is two-bit character and two-bit character. 
# So the last character is NOT one-bit character.

class OneBitOrTwoBitCharaters:

    def doit(self, bits):
        """
        :type bits: List[int]
        :rtype: bool
        """
        i, last = 0, 0
        while i < len(bits):
            last = i
            if bits[i] == 1:
                i += 1
            i += 1
        
        return last == len(bits) - 1

    def doit1(self, bits):
        """
        :type bits: List[int]
        :rtype: bool
        """
        """
        
        0,0,0]  one
        0,1,0]  two
        1,0,0]  one
        1,1,0]  one or two
        
        if you c
even  1,1,0]  

        
        0,1,1,0]

        if you come to zero, and the number of 1's is odd => two
        
  odd   0,1,1,1,0] two
        if # ones is odd, gotta be two
        otherwise
        
        if you come to zero, and number of 1's is even => one
        0,1,1,1,1,0]
        
        if you don't come to zero
        
  even  [1,1,1,1,0] one
  odd   [1,1,1,0]   two
        """
        
        n = len(bits)
        
        if n == 1:
            return True
        if n == 2:
            return bits[0] != 1
        
        # Reverse the array. 
        bits = bits[::-1]
        
        first = str(bits[0])
        second = str(bits[1])
        third = str(bits[2])
        
        first_three = first + second + third
        
        if first_three == "000":
            return True
        elif first_three == "010":
            return False
        elif first_three == "001":
            return True
        else:
            num_ones = 0
            for i, bit in enumerate(bits):
                if i == 0:
                    continue

                if i > 0 and bit == 1:
                    num_ones += 1

                if bit == 0:
                    break

            if num_ones % 2 == 1:
                return False
            else:
                return True
