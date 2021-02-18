"""
1508. Range Sum of Sorted Subarray Sums


Given the array nums consisting of n positive integers. You computed the sum of all non-empty continous subarrays from the array and then sort them in non-decreasing order, creating a new array of n * (n + 1) / 2 numbers.

Return the sum of the numbers from index left to index right (indexed from 1), inclusive, in the new array. Since the answer can be a huge number return it modulo 10^9 + 7.

 

Example 1:

Input: nums = [1,2,3,4], n = 4, left = 1, right = 5
Output: 13 
Explanation: All subarray sums are 1, 3, 6, 10, 2, 5, 9, 3, 7, 4. After sorting them in non-decreasing order we have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10]. The sum of the numbers from index le = 1 to ri = 5 is 1 + 2 + 3 + 3 + 4 = 13. 
Example 2:

Input: nums = [1,2,3,4], n = 4, left = 3, right = 4
Output: 6
Explanation: The given array is the same as example 1. We have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10]. The sum of the numbers from index le = 3 to ri = 4 is 3 + 3 = 6.
Example 3:

Input: nums = [1,2,3,4], n = 4, left = 1, right = 10
Output: 50
 

Constraints:

1 <= nums.length <= 10^3
nums.length == n
1 <= nums[i] <= 100
1 <= left <= right <= n * (n + 1) / 2

"""


class RangeSumOfSortedSubarraySums:

    def doit_bruteforce(self, nums: list, n: int, left: int, right: int) -> int:
        
        rs = []
        
        for i in range(len(nums)):
            s = 0
            for j in nums[i:]:
                s += j
                rs.append(s)
                
        rs.sort()
        return sum(rs[left-1:right]) % (10**9+7)
    
    """
        Explanation
        count_sum_under counts the number of subarray sums that <= score
        sum_k_sums returns the sum of k smallest sums of sorted subarray sums.
        kth_score returns the kth sum in sorted subarray sums.

        Oral explanation refers to youtube channel.


        Complexity
        Time O(NlogSum(A))
        Space O(N)
    """
    def rangeSum(self, A, n, left, right):
        # B: partial sum of A
        # C: partial sum of B
        # Use prefix sum to precompute B and C
        B, C = [0] * (n + 1), [0] * (n + 1)
        for i in range(n):
            B[i + 1] = B[i] + A[i]
            C[i + 1] = C[i] + B[i + 1]

        # Use two pointer to
        # calculate the total number of cases if B[j] - B[i] <= score
        def count_sum_under(score):
            res = i = 0
            for j in range(n + 1):
                while B[j] - B[i] > score:
                    i += 1
                res += j - i
            return int(res)

        # calculate the sum for all numbers whose indices are <= index k
        def sum_k_sums(k):
            score = kth_score(k)
            res = i = 0
            for j in range(n + 1):
                # Proceed until B[i] and B[j] are within score
                while B[j] - B[i] > score:
                    i += 1
                res += B[j] * (j - i + 1) - (C[j] - (C[i - 1] if i else 0))
            return int(res - (count_sum_under(score) - k) * score)

        # use bisearch to find how many numbers ae below k
        def kth_score(k):
            l, r = 0, B[n]
            while l < r:
                m = (l + r) / 2
                if count_sum_under(m) < k:
                    l = m + 1
                else:
                    r = m
            return int(l)

        # result between left and right can be converted to [0, right] - [0, left-1] (result below right - result below left-1)
        return int(sum_k_sums(right) - sum_k_sums(left - 1)) % (10**9 + 7)