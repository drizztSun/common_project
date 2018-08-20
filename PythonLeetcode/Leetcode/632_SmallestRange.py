


# 632. Smallest Range


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


class SmallestRange:

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

    pass

