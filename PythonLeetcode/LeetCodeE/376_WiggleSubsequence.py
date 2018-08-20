

# 376. Wiggle Subsequence

# A sequence of numbers is called a wiggle sequence if the differences between successive numbers strictly alternate between positive and negative.
# The first difference (if one exists) may be either positive or negative. A sequence with fewer than two elements is trivially a wiggle sequence.

# For example, [1,7,4,9,2,5] is a wiggle sequence because the differences (6,-3,5,-7,3) are alternately positive and negative.
# In contrast, [1,4,7,2,5] and [1,7,4,5,5] are not wiggle sequences, the first because its first two differences are positive 
# and the second because its last difference is zero.

# Given a sequence of integers, return the length of the longest subsequence that is a wiggle sequence.
# A subsequence is obtained by deleting some number of elements (eventually, also zero) from the original sequence,
# leaving the remaining elements in their original order.


# Examples:
# Input: [1,7,4,9,2,5]
# Output: 6
# The entire sequence is a wiggle sequence.

# Input: [1,17,5,10,13,15,10,5,16,8]
# Output: 7
# There are several subsequences that achieve this length. One is [1,17,10,13,10,16,8].

# Input: [1,2,3,4,5,6,7,8,9]
# Output: 2

import itertools

class wiggleMaxLength(object):
    

# Explanation / Proof:

# Imagine the given array contains [..., 10, 10, 10, 10, ...]. Obviously we can�t use more than one of those tens, 
# as that wouldn�t be wiggly. So right away we can ignore all consecutive duplicates.

# Imagine the given array contains [..., 10, 7, 11, 13, 17, 19, 23, 20, ...]. 
# So increasing from 7 to 23. What can we do with that? Well we can�t use more than two of those increasing numbers, 
# as that wouldn�t be wiggly. And if we do use two, we�d better use the 7 and the 23, as that offers the best extensibility
# (for example, the 19 wouldn�t allow to next pick the 20 for the wiggly subsequence).
# And if we do use only one, it still should be either the 7 or the 23, as the 7 is the best wiggle-low and the 23 is the best wiggle-high of them. So whether we actually use the 7 and the 23 or not, we definitely can and should remove the 11, 13, 17, and 19. So then we have [�, 10, 7, 23, 20, �]. Now, notice that the 7 is a local minimum (both the 10 and the 23 are larger) and the 23 is a local maximum. And if we do this with all increasing or decreasing streaks, i.e., keep only their first and last number, then all the numbers we have left are local extrema, either smaller than both neighbors or larger than both neighbors. Which means that at that point, we�re already fully wiggly. And we only removed as many numbers as we have to. So it�s a longest possible wiggly subsequence.

#My solution first computes differences of neighbors and throws out zeros (which does get rid of those useless consecutive duplicates). And then it just counts the local extrema (by checking two consecutive differences).

#I use nan for some convenience, I�ll let you figure that part out :-)
#<br>
#Alternative implementations not using the nan trick: First remove repetitions, then count the local extrema except the ends, and add the number of ends (because the ends are always local extrema)

    
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        norep = [num for num, _ in itertools.groupby(nums)]

        triples = zip(norep, norep[1:], norep[2:])

        return sum( [(b > a) == (c > b) for a, b, c in triples] ) + len(norep[:2])       


    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nano = float('nan')

        diff = [a-b for a, b in zip([nano] + nums, nums + [nano]) if a - b]

        return sum(not d * e >= 0 for d, e in zip(diff, diff[1:]))

    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if not nums: 
            return 0

        count_up, count_down = 1, 1

        for i in range(1, len(nums)):
            if nums[i] > nums[i-1]: 
                count_up = count_down + 1
            elif nums[i] < nums[i-1]: 
                count_down = count_up + 1

        return max(count_up, count_down)


if __name__ == "__main__":


    res = wiggleMaxLength().doit([1,7,4,9,2,5])

    res = wiggleMaxLength().doit([1,17,5,10,13,15,10,5,16,8])

    res = wiggleMaxLength().doit([1,2,3,4,5,6,7,8,9])



    pass