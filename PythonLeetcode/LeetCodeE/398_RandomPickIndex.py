


# 398. Random Pick Index

# Given an array of integers with possible duplicates, randomly output the index of a given target number.
# You can assume that the given target number must exist in the array.

# Note:
# The array size can be very large. Solution that uses too much extra space will not pass the judge.

# Example:

# int[] nums = new int[] {1,2,3,3,3};
# Solution solution = new Solution(nums);

# // pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
# solution.pick(3);

# // pick(1) should return 0. Since in the array only nums[0] is equal to 1.
# solution.pick(1);

import random
import collections



# MTL Memory out of limit
class Solution(object):

    def __init__(self, nums):
        """
        
        :type nums: List[int]
        :type numsSize: int
        """
        self.c_ = collections.defaultdict(list)
        for i, c in enumerate(nums):
            self.c_[c].append(i) 

    def pick(self, target):
        """
        :type target: int
        :rtype: int
        """
        return random.choice(self.c_[target])

class RandomPickIndex(object):

    def __init__(self, nums):
        self.index = {}
        for i, c in enumerate(nums):
            if c not in self.index:
                self.index[c] = [i]
            else:
                self.index[c].append(i)

    def pick(self, target):
        import random
        return random.choice(self.index)


# ######        
class RandomPickIndex(object):
    
    def __init__(self, nums):
        self.nums_ = nums[:]

    def pick(self, target):
        import random
        return random.choice([i for i, v in enumerate(self.nums_) if v == target])


# ########
# <steve>
class Solution(object):
    
    def __init__(self, nums):
        indexes = self.indexes = {}
        for i, num in enumerate(nums):
            I = indexes.get(num)
            if I is None:
                indexes[num] = i
            elif isinstance(I, int):
                indexes[num] = [I, i]
            else:
                indexes[num].append(i)

    def pick(self, target):
        I = self.indexes[target]
        return I if isinstance(I, int) else random.choice(I)

# ########
class RandomPickIndex(object):

    def __init__(self, nums):
        self.nums_ = nums[:]
        

    def pick(self, target):
        res = []
        for i, c in enumerate(self.nums_):
            if c == target:
                res.append(i)
                
        return random.choice(res)


# sorted way
class RandomPickIndex(object):

    def __init__(self, nums):
        self.sortedNums_ = []
        for i, c in enumerate(nums):
            self.sortedNums_.append((c, i))

        self.sortedNums_.sort(key=lambda x : x[0])
        self.keys_ = [x[0] for x in self.sortedNums_]
        self.pos_ = [x[1] for x in self.sortedNums_]


    def pick(self, target):

        import bisect
        s = bisect.bisect_left(self.keys_, target)
        e = bisect.bisect_right(slef.keys_, target)
        pos = random.randint(s, e-1)
        return self.pos_[pos]

        

if __name__=="__main__":


    obj = RandomPickIndex([1, 2, 3, 3, 3])

    for _ in range(100):
        res = obj.pick(3)
    


    pass