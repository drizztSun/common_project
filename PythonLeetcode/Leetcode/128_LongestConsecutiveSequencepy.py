


# 128. Longest Consecutive Sequence

# Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

# For example,
# Given [100, 4, 200, 1, 3, 2],
# The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

# Your algorithm should run in O(n) complexity.

class longestConsecutive:


# First turn the input into a set of numbers. That takes O(n) and then we can ask in O(1)
# whether we have a certain number.
# Then go through the numbers. If the number x is the start of a streak (i.e., x-1 is not in the set),
# then test y = x+1, x+2, x+3, and stop at the first number y not in the set.
# The length of the streak is then simply y-x and we update our global best with that.
# Since we check each streak only once, this is overall O(n). This ran in 44 ms on the OJ, one of the fastest Python submissions.

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums_map = set(nums)
        length = 0
        
        for n in nums:
            if n-1 not in nums_map:
                s = n + 1
                
                while s in nums_map:
                    s += 1
                
                length = max(length, s - n)
                    
        return length

                



if __name__=="__main__":


    res = longestConsecutive().doit([100, 4, 200, 1, 3, 2])


    pass