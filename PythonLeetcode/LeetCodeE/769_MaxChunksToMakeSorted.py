# 769. Max Chunks To Make Sorted


# Given an array arr that is a permutation of [0, 1, ..., arr.length - 1], we split the array into some number of "chunks" (partitions), and individually sort each chunk.
# After concatenating them, the result equals the sorted array.

# What is the most number of chunks we could have made?

# Example 1:

# Input: arr = [4,3,2,1,0]
# Output: 1
# Explanation:
# Splitting into two or more chunks will not return the required result.
# For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.

# Example 2:

# Input: arr = [1,0,2,3,4]
# Output: 4
# Explanation:
# We can split into two chunks, such as [1, 0], [2, 3, 4].
# However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks possible.

# Note:

# arr will have length in range [1, 10].
# arr[i] will be a permutation of [0, 1, ..., arr.length - 1].

import collections


class MaxChunksToSorted:

    def doit(self, arr):

        maxi = -1
        ans = 0

        for i in range(len(arr)):

            if maxi < arr[i]:
                maxi = arr[i]

            if maxi == i:
                ans += 1
                maxi = -1

        return ans

    def doit1(self, arr):
        od = collections.OrderedDict()
        for i in range(len(arr)):
            od[i] = True

        locations = {}
        chunks = 0
        start = 0
        nextMin = 0
        currentMax = arr[start]
        while start < len(arr):

            nextMinEle = od.popitem(last=False)[0]
            if currentMax < nextMinEle:
                chunks += 1
                currentMax = arr[start]

            while arr[nextMin] != nextMinEle:
                if arr[nextMin] > currentMax:
                    currentMax = arr[nextMin]
                del od[arr[nextMin]]

                nextMin += 1
            start = nextMin + 1
            nextMin += 1
        return chunks + 1


if __name__ == '__main__':

    res = MaxChunksToSorted().doit([1, 2, 0, 3])

    res = MaxChunksToSorted().doit([4, 3, 2, 1, 0])

    res = MaxChunksToSorted().doit([1, 0, 2, 3, 4])

    res = MaxChunksToSorted().doit([2, 1, 0, 3, 4])

    pass
