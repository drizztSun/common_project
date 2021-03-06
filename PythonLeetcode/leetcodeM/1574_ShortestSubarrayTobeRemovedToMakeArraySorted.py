"""
1574. Shortest Subarray to be Removed to Make Array Sorted

Given an integer array arr, remove a subarray (can be empty) from arr such that the remaining elements in arr are non-decreasing.

A subarray is a contiguous subsequence of the array.

Return the length of the shortest subarray to remove.

 

Example 1:

Input: arr = [1,2,3,10,4,2,3,5]
Output: 3
Explanation: The shortest subarray we can remove is [10,4,2] of length 3. The remaining elements after that will be [1,2,3,3,5] which are sorted.
Another correct solution is to remove the subarray [3,10,4].
Example 2:

Input: arr = [5,4,3,2,1]
Output: 4
Explanation: Since the array is strictly decreasing, we can only keep a single element. Therefore we need to remove a subarray of length 4, either [5,4,3,2] or [4,3,2,1].
Example 3:

Input: arr = [1,2,3]
Output: 0
Explanation: The array is already non-decreasing. We do not need to remove any elements.
Example 4:

Input: arr = [1]
Output: 0
 

Constraints:

1 <= arr.length <= 10^5
0 <= arr[i] <= 10^9

"""


class FindLengthOfShortestSubarray:
    
    """
        O(n)
    """
    def doit_search(self, arr: list) -> int:
        
        n = len(arr)
        left = 0
        while left < len(arr) - 1 and arr[left] <= arr[left+1]:
            left += 1
            
        if left == n-1: return 0
            
        right = len(arr) - 1
        while right >= left and arr[right] >= arr[right - 1]:
            right -= 1
            
        ans = min(n - 1 - left, right)    
        
        i, j = 0, right
        
        while i <= left and j < n:
            if arr[i] <= arr[j]:
                ans = min(ans, j - i - 1)
                i += 1
            else:
                j += 1
        
        return ans

    def doit_greedy(self, arr: list) -> int:

        j = len(arr) - 1
        while j > 0 and arr[j-1] <= arr[j]:
            j -= 1

        if j == 0: return 0

        ret, i = j, 0
        
        while i < len(arr):
            
            if i >= 1 and arr[i] < arr[i-1]: break
            
            while j < len(arr) and arr[i] > arr[j]:
                j += 1

            ret = min(ret, j - i - 1)
            i += 1

        return ret