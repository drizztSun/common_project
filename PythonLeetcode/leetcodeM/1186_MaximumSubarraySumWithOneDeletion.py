"""
1186. Maximum Subarray Sum with One Deletion

Given an array of integers, return the maximum sum for a non-empty subarray (contiguous elements) with at most one element deletion.
In other words, you want to choose a subarray and optionally delete one element from it so that there is still at least one element left and the sum of the remaining elements is maximum possible.

Note that the subarray needs to be non-empty after deleting one element.



Example 1:

Input: arr = [1,-2,0,3]
Output: 4
Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the subarray [1, 0, 3] becomes the maximum value.
Example 2:

Input: arr = [1,-2,-2,3]
Output: 3
Explanation: We just choose [3] and it's the maximum sum.
Example 3:

Input: arr = [-1,-1,-1,-1]
Output: -1
Explanation: The final subarray needs to be non-empty. You can't choose [-1] and delete -1 from it, then get an empty subarray to make the sum equals to 0.


Constraints:

1 <= arr.length <= 10^5
-10^4 <= arr[i] <= 10^4


"""


class MaxSumSubarrayWithOneDeletion:

    def maximumSum(self, arr) -> int:
        run_sum = 0
        fixed_sum = 0
        max_=arr[0]
        neg_n=0
        for i in range(len(arr)):
            run_sum+=arr[i]
            fixed_sum+=arr[i]
            if fixed_sum>max_:
                max_ = fixed_sum
            if arr[i]<0:
                if arr[i]<neg_n or (arr[i]>=neg_n and fixed_sum<run_sum-arr[i]):
                    fixed_sum = run_sum-arr[i]
                    neg_n = arr[i]
                if run_sum<0:
                    run_sum=0
        return max_

    def doit_dp_1(self, arr):

        delone, delzero = 0, arr[0]
        ans = delzero

        for n in arr[1:]:

            delzero, delone = delzero + n, max(delzero, delone + n)

            if delzero < n:
                delzero = n
            if delone < n:
                delone = 0

            ans = max(ans, delzero, delone)

        return ans

    def doit_dp(self, arr):

        delone, delzero = 0, arr[0]
        ans = delzero

        for n in arr[1:]:

            delzero, delone = max(n, delzero + n), max(delzero, delone + n)

            ans = max(ans, delzero, delone)

        return ans


if __name__ == '__main__':

    MaxSumSubarrayWithOneDeletion().doit_dp([1,-2,0,3])

    MaxSumSubarrayWithOneDeletion().doit_dp([1,-2,-2,3])

    MaxSumSubarrayWithOneDeletion().doit_dp([-1,-1,-1,-1])

    MaxSumSubarrayWithOneDeletion().doit_dp([2, 1, -2, -5, -2])