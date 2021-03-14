"""
1775. Equal Sum Arrays With Minimum Number of Operations


You are given two arrays of integers nums1 and nums2, possibly of different lengths. The values in the arrays are between 1 and 6, inclusive.

In one operation, you can change any integer's value in any of the arrays to any value between 1 and 6, inclusive.

Return the minimum number of operations required to make the sum of values in nums1 equal to the sum of values in nums2. Return -1​​​​​ if it is not possible to make the sum of the two arrays equal.

 

Example 1:

Input: nums1 = [1,2,3,4,5,6], nums2 = [1,1,2,2,2,2]
Output: 3
Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed.
- Change nums2[0] to 6. nums1 = [1,2,3,4,5,6], nums2 = [6,1,2,2,2,2].
- Change nums1[5] to 1. nums1 = [1,2,3,4,5,1], nums2 = [6,1,2,2,2,2].
- Change nums1[2] to 2. nums1 = [1,2,2,4,5,1], nums2 = [6,1,2,2,2,2].
Example 2:

Input: nums1 = [1,1,1,1,1,1,1], nums2 = [6]
Output: -1
Explanation: There is no way to decrease the sum of nums1 or to increase the sum of nums2 to make them equal.
Example 3:

Input: nums1 = [6,6], nums2 = [1]
Output: 3
Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed. 
- Change nums1[0] to 2. nums1 = [2,6], nums2 = [1].
- Change nums1[1] to 2. nums1 = [2,2], nums2 = [1].
- Change nums2[0] to 4. nums1 = [2,2], nums2 = [4].
 

Constraints:

1 <= nums1.length, nums2.length <= 10^5
1 <= nums1[i], nums2[i] <= 6
"""

class MinOperations:

    """
        1775.Equal-Sum-Arrays-With-Minimum-Number-of-Operations
        假设nums1比num2的sum要大，那么我们要将这两个sum更靠近，无非就是两种思路：要么将nums1里面的元素改小，要么将num2里面的元素改大。为了减少操作次数，我们必须最大化改动的效率。
        也就是说，如果选择将nums1里面的元素改小，那么我们一定会将最大的元素改成1；反之，我们也可以将nums2里面最小的元素改成6。至于这两种方案里面怎么选，自然是查看它们的变动幅度，看哪个更大一些。一旦改动幅度能够cover当前的diff，就说明可以将这两个sum变成一致的。

        所以我们将两个数组都排个序。对于nums1，我们从后往前改动；对于nums2，我们从前往后改动。于是本题本质就是一个双指针，每改动一次，就移动相应的一个指针。直至diff小于等于零（实现目标），或者两个指针都到了尽头（无法实现目标）。
    """

    def doit_(self, nums1: list, nums2: list) -> int:
        
        from collections import Counter;
        
        cnt1, cnt2 = Counter(nums1), Counter(nums2)
        sum1, sum2 = sum(nums1), sum(nums2)
        
        if sum1 > sum2:
            sum1, sum2 = sum2, sum1
            cnt1, cnt2 = cnt2, cnt1
        
        l1, l2 = len(nums1), len(nums2)
        if sum1 == sum2: return 0
        if 6 * l1 < l2 or 6 * l2 < l1: return -1
        
        ops = 0
        
        for i in range(1, 7):
            
            if sum1 + (6-i) * cnt1[i] >= sum2:
                return ops + (sum2 - sum1 - 1) // (6-i) + 1
            else:
                ops += cnt1[i]
                sum1 += (6-i) * cnt1[i]
                
            if sum2 - (6 - i) * cnt2[7-i] <= sum1:
                return ops + (sum2 - sum1 - 1) // (6-i) + 1
            else:
                ops += cnt2[7-i]
                sum2 -= (6 - i) * cnt2[7-i]
                
        return -1