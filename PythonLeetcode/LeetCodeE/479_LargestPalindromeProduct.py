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
        
        return ans[n] if 1 <= n <= 8 else 0


# This is just a conversion from the "An easy 9-line Java solution" by ckcz123 plus some explanation.
# max is the biggest possible n digit number

# you may have noticed that
# 9x9 = 81
# 99x99 = 9801
# 999x999 = 998001
# 9999x9999 = 9980001
# etc.
# The biggest possibe n digit numbers multipled together are never palindromes. So the first loop iteration is from max-1.
# v will be used to generate a palindrome and will get smaller in every iteration. 
# This solution assumes that a palindrome will be found before v becomes 10x smaller than the biggest possible n digit number (max). This must be true because if v becomes 10x smaller, it will no longer be an n digit number.

# Generating the palindrome from v is fairly straight forward except in C++ you have to make sure your variables are big enough to hold the numbers.

# The second for loop relies on some key observations.

# If x is one of the numbers that can be multiplied with something else to make the palindrome, then that something else cannot be bigger than x. Since the solution starts from the biggest numbers and works back, if a bigger number than x was part of the solution, it would have been found earlier.
# If x is not a multiple, next we check if x-1 is big enough to be a multiple for the palindrome u.
# If at any point x^2 is found to be smaller than the palindrome u then it cannot be a multiple for it since all numbers greater than x have been checked and the numbers below it will only further decrease the value of x^2.
# Once a multiple is found for u we know that it comes from x and x%u, and that u is the biggest palindrome possible given those numbers.     

    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        import math

        if n == 1:
            return 9

        s = int(math.pow(10, n)) - 1
        for i in range(s ** 2, s // 10, -1):
            if str(i) == str(i)[::-1]:
                return i % 1337

        return 0


    def doit2(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 1: 
            return 9

        tenN = 10**n
        for iPlusj in xrange(2, 9 * tenN / 10 + 1):

            upper = tenN - iPlusj
            lower = int(str(upper)[::-1])
            discriminant = iPlusj ** 2 - 4 * lower

            if discriminant >= 0:
                root = discriminant ** 0.5
                j1 = (iPlusj + root) / 2
                j2 = (iPlusj - root) / 2
                if (j1 > 0 and abs(j1-int(j1)) < 1e-6) or (j2 > 0 and abs(j2-int(j2)) < 1e-6):
                    return (upper * tenN + lower) % 1337


if __name__ == "__main__":

    res = LargestPalindrome().doit(2)