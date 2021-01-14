"""
77. Combinations

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

You may return the answer in any order.

 

Example 1:

Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
Example 2:

Input: n = 1, k = 1
Output: [[1]]
 

Constraints:

1 <= n <= 20
1 <= k <= n

"""

class Combinations:

    """
        Approach 1: Backtracking
        Algorithm

        Backtracking is an algorithm for finding all solutions by exploring all potential candidates. 
        If the solution candidate turns to be not a solution (or at least not the last one), backtracking algorithm discards it by making some changes on the previous step, i.e. backtracks and then try again.

        Here is a backtrack function which takes a first integer to add and a current combination as arguments backtrack(first, curr).

        If the current combination is done - add it to output.

        Iterate over the integers from first to n.

        Add integer i into the current combination curr.

        Proceed to add more integers into the combination : backtrack(i + 1, curr).

        Backtrack by removing i from curr.

        Implementation
    """
    def doit_backtracking(self, n: int, k: int) -> list:

        def backtrack(first = 1, curr = []):
            # if the combination is done
            if len(curr) == k:  
                output.append(curr[:])
            for i in range(first, n + 1):
                # add i into the current combination
                curr.append(i)
                # use next integers to complete the combination
                backtrack(i + 1, curr)
                # backtrack
                curr.pop()
        
        output = []
        backtrack()
        return output

    """
        Approach 2: Lexicographic (binary sorted) combinations
        Intuition

        The idea here is not just to get the combinations but to generate them in a lexicographic sorted order.

        postorder

        Algorithm

        The algorithm is quite straightforward :

        Initiate nums as a list of integers from 1 to k. Add n + 1 as a last element, it will serve as a sentinel. Set the pointer in the beginning of the list j = 0.

        While j < k :

        Add the first k elements from nums into the output, i.e. all elements but the sentinel.

        Find the first number in nums such that nums[j] + 1 != nums[j + 1] and increase it by one nums[j]++ to move to the next combination.

        Implementation
    """
    def doit_(self, n: int, k: int) -> list:
        # init first combination
        nums = list(range(1, k + 1)) + [n + 1]
        
        output, j = [], 0
        while j < k:
            # add current combination
            output.append(nums[:k])
            # increase first nums[j] by one
            # if nums[j] + 1 != nums[j + 1]
            j = 0
            while j < k and nums[j + 1] == nums[j] + 1:
                nums[j] = j + 1
                j += 1
            nums[j] += 1
            
        return output