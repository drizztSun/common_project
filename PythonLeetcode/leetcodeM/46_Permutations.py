"""
46. Permutations

Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]
Example 3:

Input: nums = [1]
Output: [[1]]
 

Constraints:

1 <= nums.length <= 6
-10 <= nums[i] <= 10
All the integers of nums are unique.
"""


class Permute:


    """
        Approach 1: Backtracking
        Backtracking is an algorithm for finding all solutions by exploring all potential candidates. If the solution candidate turns to be not a solution (or at least not the last one), 
        backtracking algorithm discards it by making some changes on the previous step, i.e. backtracks and then try again.

        Here is a backtrack function which takes the index of the first integer to consider as an argument backtrack(first).

        If the first integer to consider has index n that means that the current permutation is done.
        Iterate over the integers from index first to index n - 1.
        Place i-th integer first in the permutation, i.e. swap(nums[first], nums[i]).
        Proceed to create all permutations which starts from i-th integer : backtrack(first + 1).
        Now backtrack, i.e. swap(nums[first], nums[i]) back.
    """

    def doit_(self, nums: list) -> list:
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        def backtrack(first = 0):
            # if all integers are used up
            if first == n:  
                output.append(nums[:])
            for i in range(first, n):
                # place i-th integer first 
                # in the current permutation
                nums[first], nums[i] = nums[i], nums[first]
                # use next integers to complete the permutations
                backtrack(first + 1)
                # backtrack
                nums[first], nums[i] = nums[i], nums[first]
        
        n = len(nums)
        output = []
        backtrack()
        return output