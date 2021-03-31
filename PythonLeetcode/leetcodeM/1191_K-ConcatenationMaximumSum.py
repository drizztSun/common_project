"""
1191. K-Concatenation Maximum Sum

Given an integer array arr and an integer k, modify the array by repeating it k times.

For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].

Return the maximum sub-array sum in the modified array. Note that the length of the sub-array can be 0 and its sum in that case is 0.

As the answer can be very large, return the answer modulo 109 + 7.



Example 1:

Input: arr = [1,2], k = 3
Output: 9
Example 2:

Input: arr = [1,-2,1], k = 5
Output: 2
Example 3:

Input: arr = [-1,-2], k = 7
Output: 0


Constraints:

1 <= arr.length <= 105
1 <= k <= 105
-104 <= arr[i] <= 104

"""


class KConcatenationMaxSum:

    def doit_(self, arr: list, k: int) -> int:

        if k == 1:
            nums = arr * k
            maxi = nums[0]
            summ = 0
            for i in range(len(nums)):
                summ = summ + nums[i]
                if maxi < summ:
                    maxi = summ
                if summ < 0:
                    summ = 0
            return (maxi) % (10 ** 9 + 7)

        nums = arr * 2
        maxi = nums[0]
        summ = 0
        for i in range(len(nums)):
            summ = summ + nums[i]
            if maxi < summ:
                maxi = summ
            if summ < 0:
                summ = 0

        if sum(arr) > 0:
            return (maxi + (k - 2) * sum(arr)) % (10 ** 9 + 7)
        else:
            print(maxi)
            if maxi < 0:
                return 0
            return maxi % (10 ** 9 + 7)

    def doit_greedy(self, arr: list, k: int) -> int:

        i, sz = 0, len(arr);
        maxv, sums, onesums = 0, 0, 0

        while i < min(2, k) * sz:
            sums = max(sums + arr[i % sz], arr[i % sz])
            maxv = max(maxv, sums)

            if i < sz:
                onesums += arr[i]

            i += 1

        if onesums > 0 and k > 2:
            maxv += (k - 2) * onesums

        return maxv % (10 ** 9 + 7)

