# 565. Array Nesting


# A zero-indexed array A of length N contains all integers from 0 to N-1. 
# Find and return the longest length of set S, where S[i] = {A[i], A[A[i]], A[A[A[i]]], ... } subjected to the rule below.

# Suppose the first element in S starts with the selection of element A[i] of index = i, 
# the next element in S should be A[A[i]], and then A[A[A[i]]]… By that analogy, 
# we stop adding right before a duplicate element occurs in S.

# Example 1:
# Input: A = [5,4,0,3,1,6,2]
# Output: 4
# Explanation: 
# A[0] = 5, A[1] = 4, A[2] = 0, A[3] = 3, A[4] = 1, A[5] = 6, A[6] = 2.

# One of the longest S[K]:
# S[0] = {A[0], A[5], A[6], A[2]} = {5, 6, 2, 0}
# Note:
# N is an integer within the range [1, 20,000].
# The elements of A are all distinct.
# Each element of A is an integer within the range [0, N-1].


class ArrayNesting(object):
    
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def search(nums, i, visited):

            if i in visited:
                return 0

            if dp[i] != -1:
                return dp[i]

            visited.add(i)
            dp[i] = 1 + search(nums, nums[i], visited)
            return dp[i]        


        dp = [-1 for _ in range(len(nums))]

        for i in range(len(nums)):

            if dp[i] != -1:
                continue

            search(nums, i, set())

        return max(dp)

    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) <= 1:
            return len(nums)

        visited = [False for _ in range(len(nums))]
        highest = 0

        for i in range(len(nums)):
            
            j = i
            if not visited[j]:
                count = 0
                while not visited[j]:
                    visited[j] = True
                    count += 1
                    j = nums[j]               

                highest = max(highest, count)
                            
        return highest

if __name__ == "__main__":

    res = ArrayNesting().doit([5,4,0,3,1,6,2])

    res = ArrayNesting().doit1([2, 0, 3, 4, 1, 5])

    res = 1

