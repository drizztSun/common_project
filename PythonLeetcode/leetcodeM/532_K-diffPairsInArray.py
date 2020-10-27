"""
532. K-diff Pairs in an Array

Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.

A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:

0 <= i, j < nums.length
i != j
|nums[i] - nums[j]| == k
Notice that |val| denotes the absolute value of val.



Example 1:

Input: nums = [3,1,4,1,5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.
Example 2:

Input: nums = [1,2,3,4,5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
Example 3:

Input: nums = [1,3,1,5,4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).
Example 4:

Input: nums = [1,2,4,4,3,3,0,9,2,3], k = 3
Output: 2
Example 5:

Input: nums = [-1,-2,-3], k = 1
Output: 2


Constraints:

1 <= nums.length <= 104
-107 <= nums[i] <= 107
0 <= k <= 107

"""


class KthdiffPairs:


    """
    Approach 2: Two Pointers
    Intuition

    We can do better than quadratic runtime in Approach 1. Rather than checking for every possible pair, we can have two pointers to point the left number and right number that should be checked in a sorted array.

    First, we have to initialize the left pointer to point the first element and the right pointer to point the second element of nums array. The way we are going to move the pointers is as follows:

    Take the difference between the numbers which left and right pointers point.

    If it is less than k, we increment the right pointer.
    If left and right pointers are pointing to the same number, we increment the right pointer too.
    If it is greater than k, we increment the left pointer.
    If it is exactly k, we have found our pair, we increment our placeholder result and increment left pointer.
    The idea behind the behavior of incrementing left and right pointers in the manner above is similar to:

    Extending the range between left and right pointers when the difference between left and right pointers is less than k (i.e. the range is too small).
    Therefore, we extend the range (by incrementing the right pointer) when left and right pointer are pointing to the same number.
    Contracting the range between left and right pointers when the difference between left and right pointers is more than k (i.e. the range is too large).
    This is the core of the idea but there is another issue which we have to take care of to make everything work correctly. We have to make sure duplicate pairs are not counted repeatedly.
    In order to do so, whenever we have a pair whose difference matches with k, we keep incrementing the left pointer as long as the incremented left pointer points to the number which is equal to the previous number.

    For nums = [2,5,1,2,8,1,3,5,7,1] and k = 2:

    Complexity Analysis

    Time complexity : O(NlogN) where NN is the size of nums. The time complexity for sorting is O(NlogN) while the time complexity for going through nums is O(N).
    One might mistakenly think that it should be O(N^2) since there is another while loop inside the first while loop.
    The while loop inside is just incrementing the pointer to skip numbers which are the same as the previous number. The animation should explain this behavior clearer.
     Therefore, the final time complexity is O(N \log N) + O(N) \approx O(N \log N)O(NlogN)+O(N)≈O(NlogN).

    Space complexity : O(N) where NN is the size of nums. Similar to approach 1, this space complexity is incurred by the sorting algorithm.
    Space complexity is bound to change depending on the sorting algorithm you use.
    There is no additional space required for the part where two pointers are being incremented, apart from a single variable result.
    Therefore, the final space complexity is O(N) + O(1) \approx O(N)O(N)+O(1)≈O(N).

    """
    def doit_twopointer(self, nums, k):

        nums.sort()

        left, right = 0, 1
        res = 0

        while left < len(nums) and right < len(nums):

            if left == right or nums[right] - nums[left] < k:
                right += 1

            elif nums[right] - nums[left] > k:
                left += 1

            else:
                res += 1
                left += 1
                while left < len(nums) and nums[left] == nums[left-1]:
                    left += 1

        return res


    """
    Approach 3: Hashmap
    Intuition

    This method removes the need to sort the nums array. Rather than that, we will be building a frequency hash map.
    This hash map will have every unique number in nums as keys and the number of times each number shows up in nums as values.

    For example:

    nums = [2,4,1,3,5,3,1], k = 3
    hash_map = {1: 2,
                2: 1,
                3: 2,
                4: 1,
                5: 1}
    Next, we look at a key (let's call x) in the hash map and ask whether:

    There is a key in the hash map which is equal to x+k IF k > 0.
    For example, if a number in nums is 1 (x=1) and k is 3, you would need to have 4 to satisfy this condition
    (thus, we need to look for 1+3 = 4 in the hash map). Using addition to look for a complement pair has the advantage of not double-counting the same pair,
    but in reverse order (i.e. if we have found a pair (1,4), we won't be counting (4,1)).

    There is more than one occurrence of x IF k = 0.
    For example, if we have nums = [1,1,1,1] and k = 0, we have one unique (1,1) pair. In this case, our hash map will be {1: 4},
    and this condition is satisfied since we have more than one occurrence of number 1.
    If we can satisfy either of the above conditions, we can increment our placeholder result variable.

    Then we look at the next key in the hash map.

    Complexity Analysis

    Let NN be the number of elements in the input list.

    Time complexity : O(N)O(N).

    It takes O(N)O(N) to create an initial frequency hash map and another O(N)O(N) to traverse the keys of that hash map.
    One thing to note about is the hash key lookup. The time complexity for hash key lookup is O(1)O(1) but if there are hash key collisions,
    the time complexity will become O(N)O(N). However those cases are rare and thus, the amortized time complexity is O(2N) \approx O(N)O(2N)≈O(N).
    Space complexity : O(N)O(N)

    We keep a table to count the frequency of each unique number in the input. In the worst case, all numbers are unique in the array.
    As a result, the maximum size of our table would be O(N).

    """
    def doit_hashmap(self, nums, k):

        from collections import Counter
        cnt = Counter(nums)
        res = 0

        for c in cnt:
            if k == 0:
                res += 1 if cnt[c] > 1 else 0
            elif c + k in cnt:
                res += 1
        return res


if __name__ == "__main__":

    KthdiffPairs().doit(nums = [3,1,4,1,5], k = 2)

    KthdiffPairs().doit(nums = [1,2,3,4,5], k = 1)

    KthdiffPairs().doit(nums = [1,3,1,5,4], k = 0)

    KthdiffPairs().doit(nums = [1,2,4,4,3,3,0,9,2,3], k = 3)

    KthdiffPairs().doit(nums = [-1,-2,-3], k = 1)
