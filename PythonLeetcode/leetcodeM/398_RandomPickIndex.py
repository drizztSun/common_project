"""
398. Random Pick Index

Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.

Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

Example:

int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);

// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);



"""


"""
Approach 2: Caching results using a hashmap
Intuition

In this approach, instead of extracting all the positions in the pick method where a given target is present, we'll pre-compute it. 
Hence for each of the number present in the array nums, we'll store all the positions (indices) where this number occurs. 
This will avoid unnecessary creation of indices array in case pick method is given a target value which is repeated. 
Since we are storing all the indices for each of the number, hence the space requirement for this approach is huge.

Algorithm

Below is the implementation of the above mentioned approach.

Complexity Analysis

Time Complexity

If NN represents the size of the nums array, building indices takes O(N) time.

pick method takes O(1) time.

Space Complexity: O(N) required for indices.


"""
class RandomPickIndex:

    def __init__(self, nums: list):
        from collections import defaultdict
        self._buff = defaultdict(list)
        for i in range(len(nums)):
            self._buff[nums[i]].append(i)

    def pick(self, target: int) -> int:
        import random
        if target not in self._buff:
            return -1
        base = len(self._buff[target])
        return self._buff[target][random.choice(range(base))]


