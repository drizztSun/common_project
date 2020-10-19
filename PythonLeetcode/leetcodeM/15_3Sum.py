"""
15. 3Sum

Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Notice that the solution set must not contain duplicate triplets.



Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Example 2:

Input: nums = []
Output: []
Example 3:

Input: nums = [0]
Output: []
"""

"""
Solution
This problem is a follow-up of Two Sum, and it is a good idea to first take a look at Two Sum and Two Sum II. 
An interviewer may ask to solve Two Sum first, and then throw 3Sum at you. Pay attention to subtle differences in problem description and try to re-use existing solutions!

Two Sum, Two Sum II and 3Sum share a similarity that the sum of elements must match the target exactly. A difference is that, instead of exactly one answer, we need to find all unique triplets that sum to zero.

Before jumping in, let's check the existing solutions and determine the best conceivable runtime (BCR) for 3Sum:

Two Sum uses a hashmap to find complement values, and therefore achieves \mathcal{O}(N)O(N) time complexity.
Two Sum II uses the two pointers pattern and also has \mathcal{O}(N)O(N) time complexity for a sorted array. We can use this approach for any array if we sort it first, which bumps the time complexity to \mathcal{O}(n\log{n})O(nlogn).
Considering that there is one more dimension in 3Sum, it sounds reasonable to shoot for \mathcal{O}(n^2)O(n 
2
 ) time complexity as our BCR.
 
 
 
"""


class ThreeSum:

    """
    Approach 1: Two Pointers
    We will follow the same two pointers pattern as in Two Sum II. It requires the array to be sorted, so we'll do that first. As our BCR is \mathcal{O}(n^2)O(n
    2
     ), sorting the array would not change the overall time complexity.

    To make sure the result contains unique triplets, we need to skip duplicate values. It is easy to do because repeating values are next to each other in a sorted array.

    If you are wondering how to solve this problem without sorting the array, go over the "No-Sort" approach below. There are cases when that approach is preferable, and your interviewer may probe your knowledge there.

    After sorting the array, we move our pivot element nums[i] and analyze elements to its right. We find all pairs whose sum is equal -nums[i] using the two pointers pattern, so that the sum of the pivot element (nums[i]) and the pair (-nums[i]) is equal to zero.

    As a quick refresher, the pointers are initially set to the first and the last element respectively. We compare the sum of these two elements to the target. If it is smaller, we increment the lower pointer lo.
    Otherwise, we decrement the higher pointer hi. Thus, the sum always moves toward the target, and we "prune" pairs that would move it further away. Again, this works only if the array is sorted. Head to the Two Sum II solution for the detailed explanation.

    Algorithm

    The implementation is straightforward - we just need to modify twoSumII to produce triplets and skip repeating values.

    For the main function:

    Sort the input array nums.
    Iterate through the array:
    If the current value is greater than zero, break from the loop. Remaining values cannot sum to zero.
    If the current value is the same as the one before, skip it.
    Otherwise, call twoSumII for the current position i.
    For twoSumII function:

    Set the low pointer lo to i + 1, and high pointer hi to the last index.
    While low pointer is smaller than high:
    If sum of nums[i] + nums[lo] + nums[hi] is less than zero, increment lo.
    If sum is greater than zero, decrement hi.
    Otherwise, we found a triplet:
    Add it to the result res.
    Decrement hi and increment lo.
    Increment lo while the next value is the same as before to avoid duplicates in the result.
    Return the result res.
    """

    def doit_dp(self, nums):

        def twoSumII(nums, i, res):
            lo, hi = i + 1, len(nums) - 1
            while (lo < hi):
                sum = nums[i] + nums[lo] + nums[hi]
                if sum < 0:
                    lo += 1
                elif sum > 0:
                    hi -= 1
                else:
                    res.append([nums[i], nums[lo], nums[hi]])
                    lo += 1
                    hi -= 1
                    while lo < hi and nums[lo] == nums[lo - 1]:
                        lo += 1
        res = []
        nums.sort()
        for i in range(len(nums)):
            if nums[i] > 0:
                break
            if i == 0 or nums[i - 1] != nums[i]:
                twoSumII(nums, i, res)
        return res


    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        res = []
        nums.sort()

        for i, a in enumerate(nums):
            # meet bigger than 0, on left side, the rest is greater than 0. drop
            if a > 0:
                break

            # The all rest is the same, break
            if i > 0 and a == nums[i - 1]:
                continue

            l, r = i + 1, len(nums) - 1
            while l < r:
                threeSum = a + nums[l] + nums[r]
                if threeSum > 0:
                    r -= 1
                elif threeSum < 0:
                    l += 1
                else:
                    res.append([a, nums[l], nums[r]])
                    l += 1
                    r -= 1
                    while nums[l] == nums[l - 1] and l < r:
                        l += 1
                    while nums[r] == nums[r + 1] and l < r:
                        r -= 1

        return res

    """
    Approach 2: Hashset
    Since triplets must sum up to the target value, we can try the hash table approach from the Two Sum solution. This approach won't work, however, if the sum is not necessarily equal to the target, like in 3Sum Smaller and 3Sum Closest.
    
    We move our pivot element nums[i] and analyze elements to its right. We find all pairs whose sum is equal -nums[i] using the Two Sum: One-pass Hash Table approach, so that the sum of the pivot element (nums[i]) and the pair (-nums[i]) is equal to zero.
    
    To do that, we process each element nums[j] to the right of the pivot, and check whether a complement -nums[i] - nums[j] is already in the hashset. If it is, we found a triplet. Then, we add nums[j] to the hashset, so it can be used as a complement from that point on.
    
    Like in the approach above, we will also sort the array so we can skip repeated values. We provide a different way to avoid duplicates in the "No-Sort" approach below.
    
    Algorithm
    
    The main function is the same as in the Two Pointers approach above. Here, we use twoSum (instead of twoSumII), modified to produce triplets and skip repeating values.
    
    For the main function:
    
    Sort the input array nums.
    Iterate through the array:
    If the current value is greater than zero, break from the loop. Remaining values cannot sum to zero.
    If the current value is the same as the one before, skip it.
    Otherwise, call twoSum for the current position i.
    For twoSum function:
    
    For each index j > i in A:
    Compute complement value as -nums[i] - nums[j].
    If complement exists in hashset seen:
    We found a triplet - add it to the result res.
    Increment j while the next value is the same as before to avoid duplicates in the result.
    Add nums[j] to hashset seen
    Return the result res.
    
    
    """
    def threeSum(self, nums):

        def twoSum(nums, i, res):
            seen = set()
            j = i + 1
            while j < len(nums):
                complement = -nums[i] - nums[j]
                if complement in seen:
                    res.append([nums[i], nums[j], complement])
                    while j + 1 < len(nums) and nums[j] == nums[j + 1]:
                        j += 1
                seen.add(nums[j])
                j += 1
        res = []
        nums.sort()
        for i in range(len(nums)):
            if nums[i] > 0:
                break
            if i == 0 or nums[i - 1] != nums[i]:
                twoSum(nums, i, res)
        return res

