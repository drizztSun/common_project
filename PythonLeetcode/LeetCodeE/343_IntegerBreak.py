



# 343. Integer Break


# Given a positive integer n, break it into the sum of at least two positive integers
# and maximize the product of those integers. Return the maximum product you can get.

# For example, 
# given n = 2, return 1 (2 = 1 + 1); given n = 10, return 36 (10 = 3 + 3 + 4).
# Note: You may assume that n is not less than 2 and not larger than 58.

class integerBreak:

    # O(n**2)
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        
        D = [ 0 for _ in range(n + 1)]
        D[2] = 1        

        for i in range(3, n+1):

            for j in range(1, i):
                # Try to write i as: i = j + S where S=i-j corresponds to either one number or a sum of two or more numbers
                # Assuming that j+S corresponds to the optimal solution for maxArr[i], we have two cases:
                # (1) i is the sum of two numbers, i.e. S=i-j is one number, and so maxArr[i]=j*(i-j)
                # (2) i is the sum of at least three numbers, i.e. S=i-j is a sum of at least 2 numbers,
                # and so the product of the numbers in this sum for S is maxArr[i-j]
                # (=maximum product after breaking up i-j into a sum of at least two integers):
                # maxArr[i] = j*maxArr[i-j]
                D[i] = max(D[i], j * (i-j), j * D[i-j])
                # or
                D[i] = max(D[i], max(j, D[j]) * max(i-j, D[i-j]))

        return D[n]


    # O(n)
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        

        pass
        
                
        


if __name__=="__main__":


    res = integerBreak().doit(2)
        
    res = integerBreak().doit(10)
    


    pass