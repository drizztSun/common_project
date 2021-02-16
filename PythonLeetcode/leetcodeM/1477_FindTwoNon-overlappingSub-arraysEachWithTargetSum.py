"""
1477. Find Two Non-overlapping Sub-arrays Each With Target Sum


Given an array of integers arr and an integer target.

You have to find two non-overlapping sub-arrays of arr each with sum equal target. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.

Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.

 

Example 1:

Input: arr = [3,2,2,4,3], target = 3
Output: 2
Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.
Example 2:

Input: arr = [7,3,4,7], target = 7
Output: 2
Explanation: Although we have three non-overlapping sub-arrays of sum = 7 ([7], [3,4] and [7]), but we will choose the first and third sub-arrays as the sum of their lengths is 2.
Example 3:

Input: arr = [4,3,2,6,2,3,4], target = 6
Output: -1
Explanation: We have only one sub-array of sum = 6.
Example 4:

Input: arr = [5,5,4,4,5], target = 3
Output: -1
Explanation: We cannot find a sub-array of sum = 3.
Example 5:

Input: arr = [3,1,1,1,5,1,2,1], target = 3
Output: 3
Explanation: Note that sub-arrays [1,2] and [2,1] cannot be an answer because they overlap.
 

Constraints:

1 <= arr.length <= 10^5
1 <= arr[i] <= 1000
1 <= target <= 10^8




"""


class NonOverlappingTargetSum:

    def doit_slidingwindow_dp(self, arr: list, target: int) -> int:

        i, s = 0, 0
        # at pos i, prefix left side length of target, suffix right side has length of target
        prefix, suffix = [0] * len(arr), [0] * len(arr)

        for j in range(len(arr)):
            s += arr[j]
            while s >= target:
                if s == target:
                    if j < len(arr)-1: 
                        prefix[j+1] = j-i+1
                    suffix[i] = j-i+1
                
                s -= arr[i]
                i += 1
        
        # dplize the left
        for i in range(1, len(prefix)):
            if prefix[i] == 0:
                prefix[i] = prefix[i-1]
            else:
                if prefix[i-1] != 0:
                    prefix[i] = min(prefix[i-1],prefix[i])
        
        # dplize the right
        for i in range(len(suffix)-1)[::-1]:
            if suffix[i] == 0:
                suffix[i] = suffix[i+1]
            else:
                if suffix[i+1] != 0:
                    suffix[i] = min(suffix[i],suffix[i+1])
        

        return min([pre+suf for pre, suf in zip(prefix, suffix) if pre and suf] or [-1])


    def doit_dp(self, arr: list, target: int) -> int:
        from math import inf

        # p is dp array, for dp[i] until to i, minimum length will be
        res, cur, i, p = inf, 0, 0, [inf]

        # p DP array for left side minimum length of target subarray
        for j, a in enumerate(arr):
            cur += a
            while cur > target:
                cur -= arr[i]
                i += 1
            if cur == target:
                # res is result, length j - i + 1 and p[i] minimum length
                res = min(res, j-i+1+p[i])

                # save current minimum value
                p.append(min(p[-1], j-i+1))
            else:
                # keep updating p
                p.append(p[-1])
                
        return res if res < inf else -1


if __name__ == '__main__':

    NonOverlappingTargetSum().doit_([7,3,4,7], 7)

    NonOverlappingTargetSum().doit_([3,2,2,4,3], 3)

    NonOverlappingTargetSum().doit_([4,3,2,6,2,3,4], 6)