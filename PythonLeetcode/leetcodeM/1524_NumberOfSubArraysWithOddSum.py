"""
1524. Number of Sub-arrays With Odd Sum

Given an array of integers arr. Return the number of sub-arrays with odd sum.

As the answer may grow large, the answer must be computed modulo 10^9 + 7.



Example 1:

Input: arr = [1,3,5]
Output: 4
Explanation: All sub-arrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
All sub-arrays sum are [1,4,9,3,8,5].
Odd sums are [1,9,3,5] so the answer is 4.
Example 2:

Input: arr = [2,4,6]
Output: 0
Explanation: All sub-arrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
All sub-arrays sum are [2,6,12,4,10,6].
All sub-arrays have even sum and the answer is 0.
Example 3:

Input: arr = [1,2,3,4,5,6,7]
Output: 16
Example 4:

Input: arr = [100,100,99,99]
Output: 4
Example 5:

Input: arr = [7]
Output: 1


Constraints:

1 <= arr.length <= 10^5
1 <= arr[i] <= 100

"""


class OddNumberSubarray:

    """
    Counting + mod 1e9+7 => DP

    ans can be as large as O(n^2)

    We would like to know how many subarrays end with arr[i] have odd or even sums.

    dp[i][0] := # end with arr[i] has even num
    dp[i][1] := # end with arr[i] has odd sum

    if arr[i] is even:
        dp[i][0] = dp[i-1][0] + 1, dp[i][1] = dp[i-1][1]
    else:
        dp[i][0] = dp[i-1][1], dp[i][1] = dp[i-1][0] + 1

    +1 is including itself.

    ans = sum(dp[i][1])

    Time complexity: O(n)
    Space complexity: O(n) -> O(1)
    """
    def doit_dp(self, arr: list) -> list:

        odd, even = 0, 0
        ans, hmod = 0, 10**9 + 7

        for c in arr:

            if c % 2 == 1:
                odd, even = even + 1, odd
            else:
                odd, even = odd, even + 1

            ans = (ans + odd) % hmod

        return ans


    """
    dp[i][0] := how many subarry[0:..] has odd number
    dp[i][1] := how many subarry[0:..] has even number

    so ans is gonna plus (current sum minus dp[i-1][even or odd] number)
    """
    def doit_dp_1(self, arr: list) -> int:
        cache = [[0, 1]]
        total, ans = 0, 0
        hmod = 1e9 + 7

        for c in arr:

            total += c

            ans = (ans + (cache[-1][0] if total % 2 == 0 else cache[-1][1])) % hmod

            cache.append([cache[-1][0] + (total % 2 == 1), cache[-1][1] + (total % 2 == 0)])

        return int(ans)


