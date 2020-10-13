"""
1246. Palindrome Removal

Given an integer array arr, in one move you can select a palindromic subarray arr[i], arr[i+1], ..., arr[j]
where i <= j, and remove that subarray from the given array. Note that after removing a subarray,
the elements on the left and on the right of that subarray move to fill the gap left by the removal.

Return the minimum number of moves needed to remove all numbers from the array.



Example 1:

Input: arr = [1,2]
Output: 2
Example 2:

Input: arr = [1,3,4,1,5]
Output: 3
Explanation: Remove [4] then remove [1,3,1] then remove [5].


Constraints:

1 <= arr.length <= 100
1 <= arr[i] <= 20


"""
import functools


class MinimumMoves:

    def doit_dp(self, arr):
        @functools.lru_cache(maxsize=None)
        def dp(i: int, j: int) -> int:
            if i >= j:
                return int(i == j)
            currMin = 1 + dp(i + 1, j)
            for k in range(i + 1, j + 1):
                if arr[i] == arr[k]:
                    currMin = min(currMin, max(1, dp(i + 1, k - 1)) + dp(k + 1, j))
            return currMin
        return dp(0, len(arr) - 1)

    def doit_dp_1(self, arr):
        """
        Idea is simple, we use DP array to memorize the status. DP[i][j] represents the minimum steps to remove this sub-array.
        Thus DP[0][len(arr)-1] should be the final result. For a sub-array [i, j]. We consider such scenarios:

        if arr[i] == arr[j], then we know after we transform [i+1][j-1] to a palindrome, the whole sub-array [i, j] will also be a palindrome.
        But we still need to testify each part of this sub-array from left to right. For example, if the sub-array is [1,4,1,1,2,3,2,1],
        we should split this array to [1,4,1] and [1,2,3,2,1]. So we traverse the whole array and try to split the array [i, j] to [i, k], [k+1, j],
        whereas i <= k < j.
        DP[i][j] should be the smallest value from previous two conditions.
        """
        dp = [[0] * len(arr) for _ in range(len(arr))]
        for j in range(len(arr)):
            for i in range(j, -1, -1):
                r = len(arr)
                if arr[i] == arr[j]:
                    r = 1 if i + 1 > j - 1 or dp[i+1][j-1] == 0 else dp[i+1][j-1]
                for k in range(i, j):
                    r = min(r, dp[i][k] + dp[k+1][j])
                dp[i][j] = r
        return dp[0][len(arr)-1]


if __name__ == '__main__':

    MinimumMoves().doit_dp([1, 3, 4, 1, 5])

    MinimumMoves().doit_dp([1,2])

