


# 384. Shuffle an Array


# Shuffle a set of numbers without duplicates.

# Example:

# // Init an array with set 1, 2, and 3.
# int[] nums = {1,2,3};
# Solution solution = new Solution(nums);

# // Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3] must equally likely to be returned.
# solution.shuffle();

# // Resets the array back to its original configuration [1,2,3].
# solution.reset();

# // Returns the random shuffling of array [1,2,3].
# solution.shuffle();


import random

class ShuffleanArray(object):

    def __init__(self, nums):
        self.orig_ = list(nums)
        self.current_ = list(nums)

    def reset(self):
        self.current_ = list(self.orig_)
        return self.current_

    def shuffle(self):
        random.shuffle(self.current_)
        return self.current_



class ShuffleanArray(object):

    def __init__(self, nums):
        """
        :type nums: List[int]
        """
        self.orig_ = nums.copy()

    #def permutation(self):
    #    nums = self.orig_

    #    def build(nums):
    #        if len(nums) == 1:
    #            return [nums]

    #        res = [] 
    #        for i, c in enumerates(nums):
    #            for f in build(nums[:i] + nums[i+1:]):
    #                res.append([c] + f)

    #        return res
        
    #    self.permutations_ = build(nums)

    def reset(self):
        """
        Resets the array to its original configuration and return it.
        :rtype: List[int]
        """
        return self.orig_

    def shuffle(self):
        """
        Returns a random shuffling of the array.
        :rtype: List[int]
        """
        import random
        nums = self.orig_
        res = []
        for _ in range(len(self.orig_)):
            i = random.randint(0, len(nums)-1)
            res.append(nums[i])
            nums = nums[:i] + nums[i+1:]

        return res

    def shuffle2(self):
        
        nums = list(self.orig_)
        res = []
        for _ in range(len(self.orig_)):

            x = random.choice(nums)
            res.append(x)
            nums.remove(x)

        return res

        
        
        



if __name__=="__main__":

    nums = [1, 2, 3]

    obj = ShuffleanArray(nums)

    obj.shuffle()

    obj.reset()

    obj.shuffle()

    pass