"""
1425. Constrained Subsequence Sum

Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence of that array such that for every two consecutive integers in the subsequence, 
nums[i] and nums[j], where i < j, the condition j - i <= k is satisfied.

A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.

 

Example 1:

Input: nums = [10,2,-10,5,20], k = 2
Output: 37
Explanation: The subsequence is [10, 2, 5, 20].
Example 2:

Input: nums = [-1,-2,-3], k = 1
Output: -1
Explanation: The subsequence must be non-empty, so we choose the largest number.
Example 3:

Input: nums = [10,-2,-10,-5,20], k = 2
Output: 23
Explanation: The subsequence is [10, -2, -5, 20].
 

Constraints:

1 <= k <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4

"""


class ConstrainedSubsetSum:


    """
        Intuition
        We need to know the maximum in the window of size k.
        Use heqp will be O(NlogN)
        Use TreeMap will be O(NlogK)
        Use deque will be O(N)
        Done. (If not done, continue read)


        Prepare
        How about google "sliding window maximum",
        and make sure you understand 239. Sliding Window Maximum
        Done. (If not done, continue read)


        Explanation
        Update res[i],
        where res[i] means the maximum result you can get if the last element is A[i].

        I directly modify on the input A,
        if you don't like it,
        use a copy of A

        Keep a decreasing deque q,
        deque[0] is the maximum result in the last element of result.

        If deque[0] > 0. we add it to A[i]

        In the end, we return the maximum res.


        Complexity
        Because all element are pushed and popped at most once.
        Time O(N)

        Because at most O(K) elements in the deque.
        Space O(K)


        More
        Deque can be widely used in all bfs problems.
        For more complecated usage,
        I recall this problem
        862. Shortest Subarray with Sum at Least K
    """
    def doit_(self, A: list, k: int) -> int:
        from collections import deque

        monque = deque()

        for i in range(len(A)):

            A[i] += monque[0] if monque else 0
            
            while len(deque) and A[i] > monque[-1]:
                monque.pop()
            
            if A[i] > 0:
                monque.append(A[i])
            
            if i >= k and monque and monque[0] == A[i - k]:
                monque.popleft()
        
        return max(A)