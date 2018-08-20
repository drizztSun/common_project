# 519. Random Flip Matrix

# You are given the number of rows n_rows and number of columns n_cols of a 2D binary matrix where all values are initially 0. 
# Write a function flip which chooses a 0 value uniformly at random, changes it to 1, and then returns the position [row.id, col.id] of that value.
# Also, write a function reset which sets all values back to 0. 
# Try to minimize the number of calls to system's Math.random() and optimize the time and space complexity.

#Note:

# 1 <= n_rows, n_cols <= 10000
# 0 <= row.id < n_rows and 0 <= col.id < n_cols
# flip will not be called when the matrix has no 0 values left.
# the total number of calls to flip and reset will not exceed 1000.

# Example 1:

# Input: 
# ["Solution","flip","flip","flip","flip"]
# [[2,3],[],[],[],[]]
# Output: [null,[0,1],[1,2],[1,0],[1,1]]

# Example 2:

# Input: 
# ["Solution","flip","flip","reset","flip"]
# [[1,2],[],[],[],[]]
# Output: [null,[0,0],[0,1],null,[0,0]]
# Explanation of Input Syntax:

# The input is two lists: the subroutines called and their arguments. Solution's constructor has two arguments, n_rows and n_cols. 
# flip and reset have no arguments. Arguments are always wrapped with a list, even if there aren't any.



# Fisher–Yates shuffle
# https://en.wikipedia.org/wiki/Fisher–Yates_shuffle
#
#

import random

class RandomFlipMatrix:

    def __init__(self, n_rows, n_cols):
        """
        :type n_rows: int
        :type n_cols: int
        """
        self.c = n_cols
        self.end = n_rows * n_cols - 1
        self.d = {}
        self.start = 0
        
    def flip(self):
        """
        :rtype: List[int]
        """
        rand = random.randint(self.start, self.end)
        res = self.d.get(rand, rand)
        self.d[rand] = self.d.get(self.start, self.start)
        self.start += 1
        return divmod(res, self.c)
    
    def reset(self):
        """
        :rtype: void
        """
        self.d = {}
        self.start = 0


class RandomFlipMatrix(object):

    def __init__(self, n_rows, n_cols):
        """
        :type n_rows: int
        :type n_cols: int
        """
        self.m, self.n = n_rows, n_cols
        self.reset()

    def flip(self):
        """
        :rtype: List[int]
        """
        r = random.choice(range(self.index + 1))
        val = self.mapping.get(r, r)

        self.mapping[r] = self.mapping.get(self.index, self.index)
        self.index -= 1

        return divmod(val, self.n)
        

    def reset(self):
        """
        :rtype: void
        """
        self.index = self.m * self.n - 1
        self.mapping = {}

if __name__ == "__main__":

    obj = RandomFlipMatrix(2, 3)

    res = obj.flip()

    

# Your Solution object will be instantiated and called as such:
# obj = Solution(n_rows, n_cols)
# param_1 = obj.flip()
# obj.reset()