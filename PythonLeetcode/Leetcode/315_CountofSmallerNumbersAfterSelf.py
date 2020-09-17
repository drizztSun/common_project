"""
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
"""


class BIT:

    def __init__(self, n):
        self.a = [0]*(n+1)
        self.n = n

    def add(self, i, val):
        i += 1
        while i <= self.n:
            self.a[i] += val
            i += i & -i

    def sum(self, i):
        i += 1
        s = 0
        while i > 0:
            s += self.a[i]
            i -= i & -i
        return s


class CountSmaller(object):

    def count_smaller(ns):
        enum = {v: i for i, v in enumerate(sorted(set(ns)), 1)}
        bit = BIT(len(enum))
        ret = [0] * len(ns)
        for i in range(len(ns) - 1, -1, -1):
            idx = enum[ns[i]]
            ret[i] = bit.sum(idx - 1)
            bit.add(idx, 1)
        return ret

    def doit_1(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        import bisect
        key = []
        result = [0 for _ in range(len(nums))]

        for i in reversed(range(len(nums))):
            pos = bisect.bisect_left(key, nums[i])
            result[i] = pos
            bisect.insort_left(key, nums[i])

        return result

    def doit_2(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        from bisect import bisect_left as bLeft
        A, result = sorted(nums), []
        for v in nums:
            pos = bLeft(A, v)
            result.append(pos)
            del A[pos]
        return result


if __name__=="__main__":

    res = CountSmaller().doit([5, 2, 6, 1])