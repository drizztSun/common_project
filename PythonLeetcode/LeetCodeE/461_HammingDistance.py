# 461. Hamming Distance

# The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

# Given two integers x and y, calculate the Hamming distance.

# Note:
# 0 ≤ x, y < 231.

# Example:

# Input: x = 1, y = 4

# Output: 2

# Explanation:
# 1   (0 0 0 1)
# 4   (0 1 0 0)
#        ↑   ↑

# The above arrows point to positions where the corresponding bits are different.

class HammingDistance:
    def doit(self, x, y):
        """
        :type x: int
        :type y: int
        :rtype: int
        """
        distance = 0        
        while x + y != 0:

            if x & 1 != y & 1:
                distance += 1

            x >>= 1
            y >>= 1

        return distance

    
    def doit1(self, x, y):

        a = bin(x)[2:].zfill(32)
        b = bin(y)[2:].zfill(32)

        return sum([1 if a[i] != b[i] else 0 for i in range(32)])

        # n=0
        # i=0
        # a=bin(x)[2:].zfill(32)
        # b=bin(y)[2:].zfill(32)
        # for i in range(32):
        #    if a[i]!=b[i]:
        #        n+=1      
        # return n
        ans = 0
        while x + y != 0:
            if x % 2 != y % 2:
                ans += 1
            x >>= 1
            y >>= 1

        return ans


    def doit2(self, x, y):
        r = x ^ y;
        result = 0
    
        while r!=0:
            r = r & (r-1)    
            result += 1

        return result


if __name__ == "__main__":

    res = HammingDistance().doit(1, 4)

