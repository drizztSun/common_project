"""
1053. Previous Permutation With One Swap


Given an array of positive integers arr (not necessarily distinct), return the lexicographically largest permutation that is smaller than arr, 
that can be made with exactly one swap (A swap exchanges the positions of two numbers arr[i] and arr[j]). 
If it cannot be done, then return the same array.

 

Example 1:

Input: arr = [3,2,1]
Output: [3,1,2]
Explanation: Swapping 2 and 1.
Example 2:

Input: arr = [1,1,5]
Output: [1,1,5]
Explanation: This is already the smallest permutation.
Example 3:

Input: arr = [1,9,4,6,7]
Output: [1,7,4,6,9]
Explanation: Swapping 9 and 7.
Example 4:

Input: arr = [3,1,1,3]
Output: [1,3,1,3]
Explanation: Swapping 1 and 3.
 

Constraints:

1 <= arr.length <= 10^4
1 <= arr[i] <= 10^4

"""


class PrevPermutationWithSwap:

    def doit_(self, arr: list) -> list:

        pos = len(arr)-1
        # find the first increasing one, [1,9,4,6,7], like 9
        while pos > 0 and arr[pos] >= arr[pos-1]:
            pos -= 1
            
        if pos > 0:
            j = len(arr)-1
            # find one less then pos-1
            while j > pos and (arr[j] >= arr[pos-1] or arr[j] == arr[j-1]):
                j -= 1
                
            arr[pos-1], arr[j] = arr[j], arr[pos-1]
            
        return arr