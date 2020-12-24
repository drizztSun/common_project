"""
78. Subsets

Given an integer array nums, return all possible subsets (the power set).

The solution set must not contain duplicate subsets.



Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
Example 2:

Input: nums = [0]
Output: [[],[0]]


Constraints:

1 <= nums.length <= 10
-10 <= nums[i] <= 10

"""


class Subsets:

    """
    Approach 1: Cascading

    Intuition

    Let's start from empty subset in output list. At each step one takes new integer into consideration and generates new subsets from the existing ones.

    Complexity Analysis

    Time complexity: O(N×2^N) to generate all subsets and then copy them into output list.

    Space complexity: O(N×2^N). This is exactly the number of solutions for subsets multiplied by the number NN of elements to keep for each subset.

    For a given number, it could be present or absent (i.e. binary choice) in a subset solution. As as result, for NN numbers, we would have in total 2^Nchoices (solutions).
    """
    def doit_1(self, nums: list) -> list:
        n = len(nums)
        output = [[]]

        for num in nums:
            output += [curr + [num] for curr in output]

        return output

    """
    Approach 2: Backtracking
    Algorithm
    
    Power set is all possible combinations of all possible lengths, from 0 to n.
    
    Given the definition, the problem can also be interpreted as finding the power set from a sequence.
    
    So, this time let us loop over the length of combination, rather than the candidate numbers, and generate all combinations for a given length with the help of backtracking technique.
    
    Algorithm

    We define a backtrack function named backtrack(first, curr) which takes the index of first element to add and a current combination as arguments.
    
    If the current combination is done, we add the combination to the final output.
    
    Otherwise, we iterate over the indexes i from first to the length of the entire sequence n.
    
    Add integer nums[i] into the current combination curr.
    
    Proceed to add more integers into the combination : backtrack(i + 1, curr).
    
    Backtrack by removing nums[i] from curr.
    
    Implementation
    """
    def doit_2(self, nums: list) -> list:
        def backtrack(first=0, curr=[]):
            # if the combination is done
            if len(curr) == k:
                output.append(curr[:])
            for i in range(first, n):
                # add nums[i] into the current combination
                curr.append(nums[i])
                # use next integers to complete the combination
                backtrack(i + 1, curr)
                # backtrack
                curr.pop()

        output = []
        n = len(nums)
        for k in range(n + 1):
            backtrack()
        return output

    """
    Approach 3: Lexicographic (Binary Sorted) Subsets
    Intuition
    
    The idea of this solution is originated from Donald E. Knuth.
    
    Algorithm

    Generate all possible binary bitmasks of length n.
    
    Map a subset to each bitmask: 1 on the ith position in bitmask means the presence of nums[i] in the subset, and 0 means its absence.
    
    Return output list.
    
    Implementation
    """
    def doit_3(self, nums: list) -> list:
        n = len(nums)
        output = []

        for i in range(2 ** n, 2 ** (n + 1)):
            # generate bitmask, from 0..00 to 1..11
            bitmask = bin(i)[3:]

            # append subset corresponding to that bitmask
            output.append([nums[j] for j in range(n) if bitmask[j] == '1'])

        return output