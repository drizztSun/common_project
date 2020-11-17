"""
1095. Find in Mountain Array

(This problem is an interactive problem.)

You may recall that an array A is a mountain array if and only if:

A.length >= 3
There exists some i with 0 < i < A.length - 1 such that:
A[0] < A[1] < ... A[i-1] < A[i]
A[i] > A[i+1] > ... > A[A.length - 1]
Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) == target.  If such an index doesn't exist, return -1.

You can't access the mountain array directly.  You may only access the array using a MountainArray interface:

MountainArray.get(k) returns the element of the array at index k (0-indexed).
MountainArray.length() returns the length of the array.
Submissions making more than 100 calls to MountainArray.get will be judged Wrong Answer.  Also, any solutions that attempt to circumvent the judge will result in disqualification.



Example 1:

Input: array = [1,2,3,4,5,3,1], target = 3
Output: 2
Explanation: 3 exists in the array, at index=2 and index=5. Return the minimum index, which is 2.
Example 2:

Input: array = [0,1,2,4,2,1], target = 3
Output: -1
Explanation: 3 does not exist in the array, so we return -1.


Constraints:

3 <= mountain_arr.length() <= 10000
0 <= target <= 10^9
0 <= mountain_arr.get(index) <= 10^9


"""


# """
# This is MountainArray's API interface.
# You should not implement it, or speculate about its implementation
# """
class MountainArray:

    def __init__(self, array):
        self._array = array

    def get(self, index: int):
        return self._array[index]

    def length(self) -> int:
        return len(self._array)


class FindInMountainArray:

    def doit_binary_search(self, target: int, mountain_arr: 'MountainArray') -> int:

        length = mountain_arr.length()

        def find_peak():
            low, high = 0, length

            while low < high:

                mid = (low + high) // 2

                midv = mountain_arr.get(mid)

                if mid == length - 1:
                    break

                midr = mountain_arr.get(mid + 1)

                if midr > midv:
                    low = mid + 1
                else:
                    high = mid

            return low

        def search(low, high, ascend):

            l, h = low, high

            while l < h:

                mid = (l + h) // 2
                res = mountain_arr.get(mid)
                if res == target:
                    return mid

                if res > target and ascend or res < target and not ascend:
                    h = mid
                elif res < target and ascend or res > target and not ascend:
                    l = mid + 1

            return -1

        peak = find_peak()
        if mountain_arr.get(peak) == target:
            return peak

        a, b = search(0, peak, True), search(peak + 1, length, False)

        return a if a != -1 else b

    def findInMountainArray(self, target: int, mountain_arr: 'MountainArray') -> int:

        def findPeak(mountain_arr, arrLen):
            left = 0
            right = arrLen - 1
            while left < right:
                mid = (left + right) // 2
                temp = mountain_arr.get(mid)
                if mid + 1 < arrLen and temp < mountain_arr.get(mid + 1):
                    left = mid + 1
                else:
                    right = mid
            return left

        def fingTargetLeft(mountain_arr, target, peakIndex):
            start = 0
            end = peakIndex
            while start < end:
                mid = (start + end) // 2
                temp = mountain_arr.get(mid)
                if temp == target:
                    return mid
                elif temp < target:
                    start = mid + 1
                else:
                    end = mid
            return -1

        def fingTargetRight(mountain_arr, target, peakIndex, arrayLength):
            start = peakIndex
            end = arrayLength
            while start < end:
                mid = (start + end) // 2
                temp = mountain_arr.get(mid)
                if temp == target:
                    return mid
                elif temp < target:
                    end = mid
                else:
                    start = mid + 1
            return -1

        arrayLength = mountain_arr.length()
        peakIndex = findPeak(mountain_arr, arrayLength)
        print(peakIndex)
        result1 = fingTargetLeft(mountain_arr, target, peakIndex)
        if result1 != -1:
            return result1
        else:
            return fingTargetRight(mountain_arr, target, peakIndex, arrayLength)




if __name__ == '__main__':

    FindInMountainArray().doit_binary_search(3, MountainArray([1,2,3,4,5,3,1]))
