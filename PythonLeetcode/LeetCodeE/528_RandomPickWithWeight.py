
# 528. Random Pick with Weight

# Given an array w of positive integers, where w[i] describes the weight of index i, 
# write a function pickIndex which randomly picks an index in proportion to its weight.

# Note:

# 1 <= w.length <= 10000
# 1 <= w[i] <= 10^5
# pickIndex will be called at most 10000 times.

# Example 1:

# Input: 
# ["Solution","pickIndex"]
# [[[1]],[]]
# Output: [null,0]

# Example 2:

# Input: 
# ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
# [[[1,3]],[],[],[],[],[]]
# Output: [null,0,1,1,1,0]
# Explanation of Input Syntax:

# The input is two lists: the subroutines called and their arguments. Solution's constructor has one argument, the array w. 
# pickIndex has no arguments. Arguments are always wrapped with a list, even if there aren't any.

import random
import bisect
class RandomPickWeight:

    def __init__(self, w):
        """
        :type w: List[int]
        """
        self.w = w
        for i in range(1, len(w)):
            self.w[i] += self.w[i-1]

    def pickIndex(self):
        """
        :rtype: int
        """
        r = random.randint(1, self.w[-1])
        return bisect.bisect_left(self.w, r)


class Solution:
    def __init__(self, w):
        """
        :type w: List[int]
        """
        self.pro = [0] * len(w)
        s = float(sum(w))
        for i, weight in enumerate(w):
            self.pro[i] = weight / s
        for i in range(1, len(self.pro)):
            self.pro[i] += self.pro[i - 1]

    def pickIndex(self):
        """
        :rtype: int
        """
        ran = random.random()
        return bisect.bisect_left(self.pro, ran)
        
        

if __name__ == "__main__":

    obj = RandomPickWeight([1])
    res = obj.pickIndex()

    obj = RandomPickWeight([1, 3])
    res = obj.pickIndex()
    res = obj.pickIndex()

    pass