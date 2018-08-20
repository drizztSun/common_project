
# 441. Arranging Coins

# You have a total of n coins that you want to form in a staircase shape, where every k-th row must have exactly k coins.

# Given n, find the total number of full staircase rows that can be formed.

# n is a non-negative integer and fits within the range of a 32-bit signed integer.

# Example 1:

# n = 5

# The coins can form the following rows:
#¤
#¤ ¤
#¤ ¤

# Because the 3rd row is incomplete, we return 2.
# Example 2:

# n = 8

# The coins can form the following rows:
#¤
#¤ ¤
#¤ ¤ ¤
#¤ ¤

# Because the 4th row is incomplete, we return 3.

class arrangeCoins:
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        i = 1
        while n >= i:
            n -= i
            i += 1

        return i - 1

    def doit(sellf, n):
        """
        :type n: int
        :rtype: int
        """
        from math import sqrt
        return int((sqrt(1+8*n) - 1) / 2)

if __name__=="__main__":


    res = arrangeCoins().doit(8)

    pass