"""
384. Shuffle an Array

Given an integer array nums, design an algorithm to randomly shuffle the array.

Implement the Solution class:

Solution(int[] nums) Initializes the object with the integer array nums.
int[] reset() Resets the array to its original configuration and returns it.
int[] shuffle() Returns a random shuffling of the array.
 

Example 1:

Input
["Solution", "shuffle", "reset", "shuffle"]
[[[1, 2, 3]], [], [], []]
Output
[null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]

Explanation
Solution solution = new Solution([1, 2, 3]);
solution.shuffle();    // Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3] must be equally likely to be returned. Example: return [3, 1, 2]
solution.reset();      // Resets the array back to its original configuration [1,2,3]. Return [1, 2, 3]
solution.shuffle();    // Returns the random shuffling of array [1,2,3]. Example: return [1, 3, 2]

 

Constraints:

1 <= nums.length <= 200
-106 <= nums[i] <= 106
All the elements of nums are unique.
At most 5 * 104 calls will be made to reset and shuffle.


"""


class Solution(object):

    def __init__(self, nums):
        """
        :type nums: List[int]
        """
        self.orig_ = nums[:]
        self.length_ = len(nums)

    def reset(self):
        """
        Resets the array to its original configuration and return it.
        :rtype: List[int]
        """
        return self.orig_

    def shuffle(self):
        """
        Returns a random shuffling of the array.
        :rtype: List[int]
        """
        import random
        nums = self.orig_
        res = []

        for _ in range(len(self.orig_)):
            i = random.randint(0, len(nums)-1)
            res.append(nums[i])
            nums = nums[:i] + nums[i+1:]

        return res


"""
Approach #2 Fisher-Yates Algorithm [Accepted]
Intuition

We can cut down the time and space complexities of shuffle with a bit of cleverness - namely, by swapping elements around within the array itself, we can avoid the linear space cost of the auxiliary array and the linear time cost of list modification.

Algorithm

The Fisher-Yates algorithm is remarkably similar to the brute force solution. On each iteration of the algorithm, we generate a random integer between the current index and the last index of the array. 
Then, we swap the elements at the current index and the chosen index - this simulates drawing (and removing) the element from the hat, as the next range from which we select a random index will not include the most recently processed one. 
One small, yet important detail is that it is possible to swap an element with itself - otherwise, some array permutations would be more likely than others. To see this illustrated more clearly, consider the animation below:

Current
1 / 18

Complexity Analysis

Time complexity : \mathcal{O}(n)O(n)

The Fisher-Yates algorithm runs in linear time, as generating a random index and swapping two values can be done in constant time.

Space complexity : \mathcal{O}(n)O(n)

Although we managed to avoid using linear space on the auxiliary array from the brute force approach, we still need it for reset, so we're stuck with linear space complexity.

"""
import random

class ShuffleArray:

    def __init__(self, nums):
        self.array = nums
        self.original = list(nums)

    def reset(self):
        self.array = self.original
        self.original = list(self.original)
        return self.array

    def shuffle(self):
        for i in range(len(self.array)):
            swap_idx = random.randrange(i, len(self.array))
            self.array[i], self.array[swap_idx] = self.array[swap_idx], self.array[i]
        return self.array
