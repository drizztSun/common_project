"""
# 128. Longest Consecutive Sequence

# Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

# For example,
# Given [100, 4, 200, 1, 3, 2],
# The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

# Your algorithm should run in O(n) complexity.

"""


class longestConsecutive:

    """
    # First turn the input into a set of numbers. That takes O(n) and then we can ask in O(1)
    # whether we have a certain number.
    # Then go through the numbers. If the number x is the start of a streak (i.e., x-1 is not in the set),
    # then test y = x+1, x+2, x+3, and stop at the first number y not in the set.
    # The length of the streak is then simply y-x and we update our global best with that.
    # Since we check each streak only once, this is overall O(n). This ran in 44 ms on the OJ, one of the fastest Python submissions.
    """
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


    """
    Approach 2: Sorting
    Intuition
    If we can iterate over the numbers in ascending order, then it will be easy to find sequences of consecutive numbers. 
    To do so, we can sort the array.
    
    Algorithm
    Before we do anything, we check for the base case input of the empty array. 
    The longest sequence in an empty array is, of course, 0, so we can simply return that. For all other cases, we sort nums and consider each number after the first (because we need to compare each number to its previous number). 
    If the current number and the previous are equal, then our current sequence is neither extended nor broken, so we simply move on to the next number. 
    If they are unequal, then we must check whether the current number extends the sequence (i.e. nums[i] == nums[i-1] + 1). 
    If it does, then we add to our current count and continue. Otherwise, the sequence is broken, so we record our current sequence and reset it to 1 (to include the number that broke the sequence). 
    It is possible that the last element of nums is part of the longest sequence, so we return the maximum of the current sequence and the longest one.
    
    Complexity Analysis

    Time complexity : O(nlgn).
    
    The main for loop does constant work nn times, so the algorithm's time complexity is dominated by the invocation of sort, which will run in O(nlgn)O(nlgn) time for any sensible implementation.
    
    Space complexity : O(1) (or O(n)O(n)).
    
    For the implementations provided here, the space complexity is constant because we sort the input array in place. If we are not allowed to modify the input array, we must spend linear space to store a sorted copy.
    """
    def doit_sort(self, nums):
        if not nums:
            return 0

        nums.sort()

        longest_streak = 1
        current_streak = 1

        for i in range(1, len(nums)):
            if nums[i] != nums[i-1]:
                if nums[i] == nums[i-1]+1:
                    current_streak += 1
                else:
                    longest_streak = max(longest_streak, current_streak)
                    current_streak = 1

        return max(longest_streak, current_streak)

    """
    Approach 3: HashSet and Intelligent Sequence Building
    Intuition
    
    It turns out that our initial brute force solution was on the right track, but missing a few optimizations necessary to reach O(n)O(n) time complexity.
    
    Algorithm
    
    This optimized algorithm contains only two changes from the brute force approach: the numbers are stored in a HashSet (or Set, in Python) to allow O(1)O(1) lookups, 
    and we only attempt to build sequences from numbers that are not already part of a longer sequence. 
    This is accomplished by first ensuring that the number that would immediately precede the current number in a sequence is not present, as that number would necessarily be part of a longer sequence.
    """
    def doit_hash(self, nums):
        longest_streak = 0
        num_set = set(nums)

        for num in num_set:
            if num - 1 not in num_set:
                current_num = num
                current_streak = 1

                while current_num + 1 in num_set:
                    current_num += 1
                    current_streak += 1

                longest_streak = max(longest_streak, current_streak)

        return longest_streak


if __name__=="__main__":

    res = longestConsecutive().doit([100, 4, 200, 1, 3, 2])