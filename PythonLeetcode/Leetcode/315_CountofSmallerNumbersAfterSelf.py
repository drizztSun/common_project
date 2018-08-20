


# 315. Count of Smaller Numbers After Self

# You are given an integer array nums and you have to return a new counts array.
# The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

# Example:

# Given nums = [5, 2, 6, 1]

# To the right of 5 there are 2 smaller elements (2 and 1).
# To the right of 2 there is only 1 smaller element (1).
# To the right of 6 there is 1 smaller element (1).
# To the right of 1 there is 0 smaller element.

# Return the array [2, 1, 1, 0].


class countSmaller(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        #import collections
        #D = collections.defaultdict(int)

        import bisect
        key = []
        result = [0 for _ in range(len(nums))]

        for i in reversed(range(len(nums))):

            pos = bisect.bisect_left(key, nums[i])
            
            result[i] = pos

            bisect.insort_left(key, nums[i])

        return result

    # <QuickSort> <K insert>
    def doit(self, nums):

        for i in reversed(range(len(nums)):

            
        


if __name__=="__main__":

    res = countSmaller().doit([5, 2, 6, 1])

    pass