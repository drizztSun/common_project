



# 400. Nth Digit

# Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...

# Note:
# n is positive and will fit within the range of a 32-bit signed integer (n < 231).

# Example 1:
# Input:
# 3
# Output:
# 3

# Example 2:
# Input:
# 11
# Output:
# 0

# Explanation:
# The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.


class findNthDigit(object):

    # Check the same-length ranges 1-9, 10-99, 100-999, 1000-9999, etc.
    # 
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        n -= 1
        for digits in range(1, 11):

            base = 10 ** (digits - 1)
        
            if n < 9 * digits * base:

                return int(str(base + int(n//digits))[n % digits])

            n -= 9 * digits * base
    

    # O(n)
    def doit1(self, n):
        """
        :type n: int
        :rtype: int
        """
        i = 1
        sequence = ''

        while len(sequence) < n:
            sequence += str(i)
            i += 1

        return int(sequence[n-1])




if __name__=="__main__":



    res = findNthDigit().doit(3)

    res = findNthDigit().doit(10)

    res = findNthDigit().doit(11)

    res = findNthDigit().doit(100)

    res = findNthDigit().doit(100000000)

    pass
        