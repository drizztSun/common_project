"""
1248. Count Number of Nice Subarrays


Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.

Return the number of nice sub-arrays.

 

Example 1:

Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
Example 2:

Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There is no odd numbers in the array.
Example 3:

Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16
 

Constraints:

1 <= nums.length <= 50000
1 <= nums[i] <= 10^5
1 <= k <= nums.length

"""


class NiceSubarray:

    """
        Solution 1: atMost
        Have you read this? 992. Subarrays with K Different Integers
        Exactly K times = at most K times - at most K - 1 times


        Complexity
        Time O(N) for one pass
        Space O(1)
    """
    def doit_slidingwindow(self, A, k):
        def atMost(k):
            res = i = 0
            for j in range(len(A)):
                k -= A[j] % 2
                while k < 0:
                    k += A[i] % 2
                    i += 1
                res += j - i + 1
            return res

        return atMost(k) - atMost(k - 1)

    """
        Solution II: One pass
        Actually it's same as three pointers.
        Though we use count to count the number of even numebers.
        Insprired by @yannlecun.

        Time O(N) for one pass
        Space O(1)

    """
    def doit_slidingwindow_1(self, A, k):
        i = count = res = 0
        for j in range(len(A)):
            if A[j] & 1:
                k -= 1
                count = 0
            while k == 0:
                k += A[i] & 1
                i += 1
                count += 1
            res += count
        return res
    


if __name__ == '__main__':

    NiceSubarray().doit_slidingwindow_1([2, 2, 2, 1, 2, 2, 1, 2, 2, 2], 2)