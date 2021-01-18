"""
556. Next Greater Element III

Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.

Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.

 

Example 1:

Input: n = 12
Output: 21
Example 2:

Input: n = 21
Output: -1
 

Constraints:

1 <= n <= 2^31 - 1

"""


class NextGreaterElement:
    
    def doit_number(self, n: int) -> int:
        nums = [ c for c in str(n) ]
        for l in range(len(nums) - 2, -1, -1):

            r = len(nums) - 1
            while l < r and nums[r] <= nums[l]:
                r -= 1

            if l != r:
                nums[l], nums[r] = nums[r], nums[l]
                nums[l+1:] = sorted(nums[l+1:])

                num = int(''.join(nums))
                return num if -2**31 - 1 <= num <= 2**31 -1 else -1
        
        return -1

    def doit_(self, n: int) -> int:

        nums = [c for c in str(n)]

        i = len(nums) - 2
        while i > -1 and nums[i] >= nums[i+1]:
            i -= 1
        
        if i == -1: return -1
            
        target = i+1
        for j in range(i, len(nums)):
            if nums[i] < nums[j]:
                target = j

        nums[i], nums[target] = nums[target], nums[i]

        nums[i+1:] = nums[i+1:][::-1]

        ans = int(''.join(str(c) for c in nums))
        
        return -1 if int(ans) >= 2**31 else int(ans)

    """
        Approach #2 Linear Solution

        Algorithm

        In this case as well, we consider the given number nn as a character array aa. First, we observe that for any given sequence that is in descending order, no next larger permutation is possible. For example, no next permutation is possible for the following array:

        [9, 5, 4, 3, 1]
        We need to find the first pair of two successive numbers a[i]a[i] and a[i-1]a[i−1], from the right, which satisfy a[i] > a[i-1]a[i]>a[i−1]. Now, no rearrangements to the right of a[i-1]a[i−1] can create a larger permutation since that subarray consists of numbers in descending order. Thus, we need to rearrange the numbers to the right of a[i-1]a[i−1] including itself.

        Now, what kind of rearrangement will produce the next larger number? We want to create the permutation just larger than the current one. Therefore, we need to replace the number a[i-1]a[i−1] with the number which is just larger than itself among the numbers lying to its right section, say a[j]a[j].

        Next Greater Element 

        We swap the numbers a[i-1]a[i−1] and a[j]a[j]. We now have the correct number at index i-1i−1. But still the current permutation isn't the permutation that we are looking for. We need the smallest permutation that can be formed by using the numbers only to the right of a[i-1]a[i−1]. Therefore, we need to place those numbers in ascending order to get their smallest permutation.

        But, recall that while scanning the numbers from the right, we simply kept decrementing the index until we found the pair a[i]a[i] and a[i-1]a[i−1] where, a[i] > a[i-1]a[i]>a[i−1]. Thus, all numbers to the right of a[i-1]a[i−1] were already sorted in descending order. Furthermore, swapping a[i-1]a[i−1] and a[j]a[j] didn't change that order. Therefore, we simply need to reverse the numbers following a[i-1]a[i−1] to get the next smallest lexicographic permutation.

        The following animation will make things clearer:

        Current
        1 / 14

        Complexity Analysis

        Time complexity : O(n). In worst case, only two scans of the whole array are needed. Here, nn refers to the number of digits in the given number.

        Space complexity : O(n). An array aa of size nn is used, where nn is the number of digits in the given number.

    """

    def doit_(self, n: int) -> int:

        nums = [c for c in str(n)]

        i = len(nums) - 2
        while i > -1 and nums[i] >= nums[i+1]:
            i -= 1
        
        if i == -1: return -1
        
        j = len(nums) - 1
        while j >= 0 and nums[j] <= nums[i]:
            j -= 1
            
        nums[i], nums[j] = nums[j], nums[i]

        nums[i+1:] = nums[i+1:][::-1]

        ans = int(''.join(str(c) for c in nums))
        
        return -1 if ans >= 2**31 else ans


