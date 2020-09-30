"""
# 373. Find K Pairs with Smallest Sums

# You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.
# Define a pair (u,v) which consists of one element from the first array and one element from the second array.
# Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

# Example 1:
# Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3
# Return: [1,2],[1,4],[1,6]

# The first 3 pairs are returned from the sequence:
# [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

# Example 2:
# Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2
# Return: [1,1],[1,1]

# The first 2 pairs are returned from the sequence:
# [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

# Example 3:
# Given nums1 = [1,2], nums2 = [3],  k = 3
# Return: [1,3],[2,3]

# All possible pairs are returned from the sequence:
# [1,3],[2,3]

"""
import itertools
import heapq


class kSmallestPairs:

    # Brute Force
    def doit(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[List[int]]
        """
        return sorted(itertools.product(nums1, nums2), key=sum)[:k]

    # clean Brute Force
    def doit(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[List[int]]
        """
        return map(list, heapq.nsmallest(k, itertools.product(nums1, nums2, key=sum)[:k]))

    # Less Brute Force
    def doit(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[List[int]]
        """
        return heapq.nsmallest(k, ([u, v] for u in nums1 for y in nums2), key=sum)

    # 
    def doit(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[List[int]]
        """
        streams = map(lambda u: ([u+v, u, v] for v in nums2), nums1)
        stream = heapq.merge(*streams)
        return [suv[1:] for suv in itertools.islice(stream, k)]


    def doit_heap(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[List[int]]
        """

        def push(i, j):
            if i < len(nums1) and j < len(nums2):
                heapq.heappush(queue, [nums1[i] + nums2[j], i, j])

        ans = []
        queue = []

        push(0, 0)
        while queue and len(ans) < k:

            _, i, j = heapq.heappop(queue)
            ans.append([nums1[i], nums2[j]])
            push(i, j + 1)

            # j == 0, heap (i+1, 0) then list all (i, 0..n). only if (i+1, 0) is smallest one, it will go next (i+2, 0)
            # it becomes a barrier.
            if j == 0:
                push(i + 1, 0)

        return ans




if __name__=="__main__":

    # [1,2],[1,4],[1,6]
    res = kSmallestPairs().doit([1,7,11], [2,4,6], 3)

    # [1,1],[1,1]
    res = kSmallestPairs().doit([1, 1, 2], [1, 2, 3], 2)

    # [1,3],[2,3]
    res = kSmallestPairs().doit([1,2], [3], 2)

    pass

