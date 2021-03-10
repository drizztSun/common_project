# 658. Find K Closest Elements

# Given a sorted array, two integers k and x, find the k closest elements to x in the array. 
# T# he result should also be sorted in ascending order. If there is a tie, the smaller elements are always preferred.

# Example 1:
# Input: [1,2,3,4,5], k=4, x=3
# Output: [1,2,3,4]
# Example 2:
# Input: [1,2,3,4,5], k=4, x=-1
# Output: [1,2,3,4]
# Note:
# The value k is positive and will always be smaller than the length of the sorted array.
# Length of the given array is positive and will not exceed 104
# Absolute value of elements in the array and x will not exceed 104


class FindClosestElements:

    # because it is sorted array, so binary search
    def doit_binary_search(self, arr, k, x):
        l, r = 0, len(arr) - k
        while l < r:
            m = l + (r - l) // 2
            if x - arr[m] > arr[m+k] - x:
                l = m + 1
            else:
                r = m

        return arr[l: l + k]

    def doit1(self, arr: 'List[int]', k: 'int', x: 'int') -> 'List[int]':
        buff = {}
        for c in arr:
            buff[abs(c-x)] = buff.get(abs(c-x), []) + [c]
            
        ans = []
        for s in sorted(buff.keys()):
            
            ans.extend(buff[s] if len(buff[s]) < k else buff[s][:k])
            
            k -= len(buff[s])
            
            if k <= 0:
                break
            
        return sorted(ans)


if __name__ == "__main__":

    res = FindClosestElements().doit([1, 2, 3, 4, 5], 4, 3)

    res = FindClosestElements().doit([1, 2, 3, 4, 5], 4, -1)
        