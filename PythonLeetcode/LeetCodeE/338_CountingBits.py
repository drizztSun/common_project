

# 338. Counting Bits

# Given a non negative integer number num. For every numbers i in the range 0 ? i ? num 
# calculate the number of 1's in their binary representation and return them as an array.

# Example:
# For num = 5 you should return [0,1,1,2,1,2].

# Follow up:

# It is very easy to come up with a solution with run time O(n*sizeof(integer)). 
# But can you do it in linear time O(n) /possibly in a single pass?
# Space complexity should be O(n).
# Can you do it like a boss? Do it without using any builtin 
# function like __builtin_popcount in c++ or in any other language.

class countBits:

# my thinking is that number is 2n / 2n+1.  n and 2n should have same bit numbers
    def doit(self, num):
        """
        :type num: int
        :rtype: List[int]
        """
        D = [0]
        for i in range(1, num+1):
            D.append(D[i // 2] + i % 2)

        return D



# i&(i-1) drops the lowest set bit. For example: i = 14, its binary representation is 1110, 
# so i-1 is 1101, i&(i-1) = 1100, the number of �1� in its binary representation decrease one, so ret[i] = ret[i&(i-1)] + 1. (Sorry, my English is so poor and I have tried my best to make it clearly, I hope you can understand my explanation)
    def doit1(self, num):
        """
        :type num: int
        :rtype: List[int]
        """
        D = [0] * (num+1)
        for i in range(1, num+1):
            D[i] = D[i & i-1] + 1

        return D

if __name__=="__main__":
    
    
    res = countBits().doit(5)

    pass