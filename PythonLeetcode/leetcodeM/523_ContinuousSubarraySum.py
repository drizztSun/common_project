"""
523. Continuous Subarray Sum

Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to a multiple of k, that is, sums up to n*k where n is also an integer.



Example 1:

Input: [23, 2, 4, 6, 7],  k=6
Output: True
Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
Example 2:

Input: [23, 2, 6, 4, 7],  k=6
Output: True
Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.


Constraints:

The length of the array won't exceed 10,000.
You may assume the sum of all the numbers is in the range of a signed 32-bit integer.
"""


class CheckSubarraySumOfMultipleK:

    """
        Approach 3: Using HashMap
        Algorithm

        In this solution, we make use of a HashMap that is used to store the cumulative sums upto the i^{th}i 
        th
        index after some processing along with the index ii. The processing done is taking the modulus of the the sum upto the i^{th}i 
        th
        index with the given kk. The reasoning behind this will become clear soon.

        We traverse over the given array, and keep on calculating the sum%ksum values upto the current index. Whenever we find a new sum%ksum value, which isn't present in the HashMap already, we make an entry in the HashMap of the form, (sum%k, i)(sum.

        Now, assume that the given sum%ksum value at the i^{th}i 
        th
        index be equal to remrem. Now, if any subarray follows the i^{th} element, which has a sum equal to the integer multiple of kk, say extending upto the j^{th}j 
        th
        index, the sum value to be stored in the HashMap for the j^{th} index will be: (rem + n*k)%k(rem+n∗k), where nn is some integer > 0. We can observe that (rem + n*k)%k = rem(rem+n∗k), which is the same value as stored corresponding to the i^{th}i 
        th
        index.

        From this observation, we come to the conclusion that whenever the same sum%ksum value is obtained corresponding to two indices ii and jj, it implies that sum of elements betweeen those indices is an integer multiple of kk. Thus, if the same sum%ksum value is encountered again during the traversal, we return a \text{True}True directly.

        The slideshow below depicts the process for the array nums: [2, 5, 33, 6, 7, 25, 15] and k=13.

        Current
        1 / 6

        Complexity Analysis

        Time complexity : O(n). Only one traversal of the array numsnums is done.

        Space complexity : O(min(n,k)). The HashMap can contain upto min(n,k) different pairings.

    """
    def doit_array(self, nums: list[int], k: int) -> bool:
        buff, runningtotals = {0: -1}, 0

        for i in range(len(nums)):

            runningtotals += nums[i]

            if k != 0:
                runningtotals %= k

            if runningtotals in buff:
                if i - buff[runningtotals] > 1:
                    return True

            buff[runningtotals] = i

        return False

    def doit_array_1(self, nums: list[int], k: int) -> bool:
        # Corner case 1  --> n can be 0
        # Corner case 2  --> k can be 0
        #   deal with them together:
        if any([x == y == 0 for x, y in zip(nums, nums[1:])]):
            return True

        if k == 0:
            return False

        # Corner case 3  --> k can be negative
        k = abs(k)

        # Corner case 4  --> sum[nums[:2]] satisfies the condition
        dindex = {0: -1}  # key is (prefixSum % k) ;  value is index
        dsum = {0: 0}  # key is (prefixSum % k) ;  value is prefixSum

        prefixSum = 0
        for i, x in enumerate(nums):
            prefixSum += x
            residual = prefixSum % k
            if residual in dindex:
                if prefixSum - dsum[residual] >= k and i - dindex[residual] >= 2:
                    return True
            else:
                dindex[residual] = i
                dsum[residual] = prefixSum

        return False
