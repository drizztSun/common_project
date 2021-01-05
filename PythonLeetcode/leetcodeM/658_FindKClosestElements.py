"""
658. Find K Closest Elements


Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array. The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b
 

Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]
Example 2:

Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]
 

Constraints:

1 <= k <= arr.length
1 <= arr.length <= 104
Absolute value of elements in the array and x will not exceed 104

"""


class FindKClosestElemeents:


    """
        Intuition
        The array is sorted.
        If we want find the one number closest to x,
        we don't have to check one by one.
        it's straightforward to use binary research.

        Now we want the k closest,
        the logic should be similar.


        Explanation
        Assume we are taking A[i] ~ A[i + k -1].
        We can binary research i
        We compare the distance between x - A[mid] and A[mid + k] - x

        @vincent_gui listed the following cases:
        Assume A[mid] ~ A[mid + k] is sliding window

        case 1: x - A[mid] < A[mid + k] - x, need to move window go left
        -------x----A[mid]-----------------A[mid + k]----------

        case 2: x - A[mid] < A[mid + k] - x, need to move window go left again
        -------A[mid]----x-----------------A[mid + k]----------

        case 3: x - A[mid] > A[mid + k] - x, need to move window go right
        -------A[mid]------------------x---A[mid + k]----------

        case 4: x - A[mid] > A[mid + k] - x, need to move window go right
        -------A[mid]---------------------A[mid + k]----x------

        If x - A[mid] > A[mid + k] - x,
        it means A[mid + 1] ~ A[mid + k] is better than A[mid] ~ A[mid + k - 1],
        and we have mid smaller than the right i.
        So assign left = mid + 1.

        Important
        Note that, you SHOULD NOT compare the absolute value of abs(x - A[mid]) and abs(A[mid + k] - x).
        It fails at cases like A = [1,1,2,2,2,2,2,3,3], x = 3, k = 3

        The problem is interesting and good.
        Unfortunately the test cases is terrible.
        The worst part of Leetcode test cases is that,
        you submit a wrong solution but get accepted.

        You didn't read my post and up-vote carefully,
        then you miss this key point.   


        Complexity
        Time O(log(N - K)) to binary research and find result
        Space O(K) to create the returned list.
    """
    def doit_binary_search(self, arr: List[int], k: int, x: int) -> List[int]:
        l, r = 0, len(arr) - k
        while l < r:
            m = l + (r - l) // 2
            if x - arr[m] > arr[m+k] - x:
                l = m + 1
            else:
                r = m

        return arr[l: l + k]


    def findClosestElements(self, arr: 'List[int]', k: 'int', x: 'int') -> 'List[int]':
        
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