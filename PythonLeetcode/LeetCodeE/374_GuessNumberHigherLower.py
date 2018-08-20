

# 374. Guess Number Higher or Lower

# We are playing the Guess Game. The game is as follows:

# I pick a number from 1 to n. You have to guess which number I picked.

# Every time you guess wrong, I'll tell you whether the number is higher or lower.

# You call a pre-defined API guess(int num) which returns 3 possible results (-1, 1, or 0):

# -1 : My number is lower
# 1 : My number is higher
# 0 : Congrats! You got it!

# Example:
# n = 10, I pick 6.
# Return 6.

def guess(mid):
    """
    :type n: int
    :rtype: int
    # -1 : My number is lower
    # 1 : My number is higher
    # 0 : Congrats! You got it!
    """
    return mid   

class guessNumber(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        s, e = 1, n

        while s < e:
        
            mid = (s + e) // 2        
            r = guess(mid)

            if r == 0:
                return mid
            elif r == 1:
                s = mid+1
            elif r == -1:
                e = mid-1

        return s

    def doit1(self, n):
        """
        :type n: int
        :rtype: int
        """
        import bisect

        class C: __getitem__ = lambda _, i: -guess(i)

        return bisect.bisect(C(), -1, 1, n)


    def doit3(self, n):        
        """
        :type n: int
        :rtype: int
        """
        low, high = 1, n

        while low < high:
            mid = (low + high) // 2

            low, high = [(mid, mid), (mid+1, high), (low, mid-1)][guess(mid)]

        return low


# 375. Guess Number Higher or Lower II

# We are playing the Guess Game. The game is as follows:
# I pick a number from 1 to n. You have to guess which number I picked.
# Every time you guess wrong, I'll tell you whether the number I picked is higher or lower.
# However, when you guess a particular number x, and you guess wrong, you pay $x. 
# You win the game when you guess the number I picked.

# Example:

# n = 10, I pick 8.

# First round:  You guess 5, I tell you that it's higher. You pay $5.
# Second round: You guess 7, I tell you that it's higher. You pay $7.
# Third round:  You guess 9, I tell you that it's lower. You pay $9.

# Game over. 8 is the number I picked.

# You end up paying $5 + $7 + $9 = $21.
# Given a particular n >= 1, find out how much money you need to have to guarantee a win.

class getMoneyAmount(object):


    # <DP>
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        D = [[0] * (n+1) for _ in range(n+1)]

        for low in range(n, 0, -1):
        
            for high in range(low+1, n+1):

                D[low][high] = min([x + max( D[low][x-1], D[x+1][high] ) for x in range(low, high)])
 
        return D[1][n]


    def doit1(self, n):
        """
        :type n: int
        :rtype: int
        """
        pass

        
        



if __name__ == "__main__":


    res = guessNumber().doit(10)

    pass

        