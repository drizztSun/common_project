"""
 632. Smallest Range


# You have k lists of sorted integers in ascending order.
# Find the smallest range that includes at least one number from each of the k lists.

# We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.

# Example 1:
# Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
# Output: [20,24]
# Explanation:

# List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
# List 2: [0, 9, 12, 20], 20 is in range [20,24].
# List 3: [5, 18, 22, 30], 22 is in range [20,24].

# Note:
# The given list may contain duplicates, so ascending order means >= here.
# 1 <= k <= 3500
# -105 <= value of elements <= 105.
# For Java users, please note that the input type has been changed to List<List<Integer>>.
# And after you reset the code template, you'll see this point.

"""


class SmallestRange:

    """

    Approach #4 Using Priority Queue [Accepted]:
    Algorithm

    In the last approach, at each step, we update the pointer corresponding to the current minimum element and traverse over the whole nextnext array to determine the new maximum and minimum values. We can do some optimization here, by making use of a simple observation.

    Whenever we update a single entry of nextnext to consider the new maximum and minimum values(if we already know the last maximum and minimum values),
    all the elements to be considered for finding the maximum and minimum values remain the same except the new element being pointed by a single updated entry in nextnext.
    This new entry is certainly larger than the last minimum value(since that was the reasoning behind the updation).

    Thus, we can't be sure whether this is the new minimum element or not. But, since it is larger than the last value being considered, it could be a potential competitor for the new maximum value.
    Thus, we can directly compare it with the last maximum value to determine the current maximum value.

    Now, we're left with finding the minimum value iteratively at every step. To avoid this iterative process, a better idea is to make use of a Min-Heap,
    which stores the values being pointed currently by the nextnext array. Thus, the minimum value always lies at the top of this heap, and we need not do the iterative search process.

    At every step, we remove the minimum element from this heap and find out the range formed by the current maximum and minimum values, and compare it with the minimum range found so far to determine the required minimum range.
    We also update the increment the index in nextnext corresponding to the list containing this minimum entry and add this element to the heap as well.

    The rest of the process remains the same as the last approach.

    Complexity Analysis

    Time complexity :O(n∗log(m)). Heapification of mm elements requires O(log(m)) time.
    This step could be done for all the elements of the given lists in the worst case. Here, nn refers to the total number of elements in all the lists. mm refers to the total number of lists.

    Space complexity : O(m)O(m). nextnext array of size mm is used. A Min-Heap with mm elements is also used.

    """

    # Keep a heap of the smallest elements. As we pop element A[i][j], we'll replace it with A[i][j+1].
    # For each such element left, we want right, the maximum of the closest value in each row of the array
    # that is >= left, which is also equal to the current maximum of our heap.
    # We�ll keep track of right as we proceed.

    def doit(self, nums):
        """
        :type nums: List[List[int]]
        :rtype: List[int]
        """
        import heapq
        buff = [(num[0], i, 0) for i, num in enumerate(nums)]
        heapq.heapify(buff)
        ans = [-1e9, 1e9]
        right = max(b[0] for b in nums)

        while buff:
            left, i, j = heapq.heappop(buff)

            if right - left < ans[1] - ans[0]:
                ans = [left, right]

            if j + 1 == len(nums[i]):
                break
            
            right = max(right, nums[i][j+1])
            heapq.heappush(buff, (nums[i][j+1], i, j+1))
            
        return ans


if __name__ == "__main__":

    res = SmallestRange().doit([[4,10,15,24,26], [0,9,12,20], [5,18,22,30]])