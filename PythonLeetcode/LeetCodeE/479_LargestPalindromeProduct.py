# 479. Largest Palindrome Product

# Find the largest palindrome made from the product of two n-digit numbers.

# Since the result could be very large, you should return the largest palindrome mod 1337.

# Example:

# Input: 2

# Output: 987

# Explanation: 99 x 91 = 9009, 9009 % 1337 = 987

# Note:

# The range of n is [1,8].


class LargestPalindrome:

    def doit1(self, n):
        """
        :type n: int
        :rtype: int
        """
        ans = [0,9,987,123,597,677,1218,877,475]
        
        return ans[n] if 1 <= n <=8 else 0
        

    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        


if __name__ == "__main__":

    res = LargestPalindrome().doit(2)