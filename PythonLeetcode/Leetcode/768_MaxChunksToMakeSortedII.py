# 768. Max Chunks To Make Sorted II

# Given an array arr of integers (not necessarily distinct),
# we split the array into some number of "chunks" (partitions),
# and individually sort each chunk.
# After concatenating them, the result equals the sorted array.

# What is the most number of chunks we could have made?

# Example 1:

# Input: arr = [5,4,3,2,1]
# Output: 1
# Explanation:
# Splitting into two or more chunks will not return the required result.
# For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.
# Example 2:

# Input: arr = [2,1,3,4,4]
# Output: 4
# Explanation:
# We can split into two chunks, such as [2, 1], [3, 4, 4].
# However, splitting into [2, 1], [3], [4], [4] is the highest number of chunks possible.
# Note:

# arr will have length in range [1, 2000].
# arr[i] will be an integer in range [0, 10**8].


class MaxChunksToSorted:

    def doit1(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        ans, n = 0, len(arr)
        leftmax, rightmin = [0] * n, [0] * n

        leftmax[0] = arr[0]
        for i in range(1, n):
            leftmax[i] = max(leftmax[i - 1], arr[i])

        rightmin[-1] = arr[-1]
        for i in range(n - 2, -1, -1):
            rightmin[i] = min(rightmin[i + 1], arr[i])

        for i in range(n - 1):
            if leftmax[i] <= rightmin[i + 1]:
                ans += 1

        return ans + 1

    def doit1(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        res = 0
        temp = sorted(arr)
        sum1, sum2 = 0, 0

        for i in range(0, len(arr)):
            sum1 += arr[i]
            sum2 += temp[i]

            if sum1 == sum2:
                res += 1

        return res

    def doit2(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        stack = []
        for num in arr:
            if len(stack) == 0 or stack[-1] <= num:
                stack.append(num)
            else:
                maxnum = stack.pop()
                while len(stack) > 0 and stack[-1]>num:
                    stack.pop()
                stack.append(maxnum)

        return len(stack)

    def doit(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        ans = 1
        leftmax = [float("-inf")]
        rightmin = [float("inf")]

        for i in range(len(arr)-1):
            leftmax.append(arr[i] if arr[i] > leftmax[-1] else leftmax[-1])

        for i in reversed(range(1, len(arr))):
            rightmin.insert(0, (arr[i] if arr[i] < rightmin[0] else rightmin[0]))

        for i in reversed(range(len(arr)-1)):

            if leftmax[i] > rightmin[i+1]:
                continue

            ans += 1

        return min(len(arr), ans)


if __name__ == "__main__":

    res = MaxChunksToSorted().doit([5, 4, 3, 2, 1])

    res = MaxChunksToSorted().doit([2, 1, 3, 4, 4])

    res = MaxChunksToSorted().doit([1, 1, 0, 0, 1])

    res = MaxChunksToSorted().doit([0, 0, 1, 1, 1])

    res = MaxChunksToSorted().doit([1, 0, 1, 3, 2])

    pass