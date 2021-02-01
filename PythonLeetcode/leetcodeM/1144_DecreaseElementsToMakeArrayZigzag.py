"""
1144. Decrease Elements To Make Array Zigzag

Given an array nums of integers, a move consists of choosing any element and decreasing it by 1.

An array A is a zigzag array if either:

Every even-indexed element is greater than adjacent elements, ie. A[0] > A[1] < A[2] > A[3] < A[4] > ...
OR, every odd-indexed element is greater than adjacent elements, ie. A[0] < A[1] > A[2] < A[3] > A[4] < ...
Return the minimum number of moves to transform the given array nums into a zigzag array.

 

Example 1:

Input: nums = [1,2,3]
Output: 2
Explanation: We can decrease 2 to 0 or 3 to 1.
Example 2:

Input: nums = [9,6,1,6,2]
Output: 4
 

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 1000
"""

class MovesToMakeZigzag:



    """
        Explanation
        Two options, either make A[even] smaller or make A[odd] smaller.
        Loop on the whole array A,
        find the min(A[i - 1],A[i + 1]),
        calculate that the moves need to make smaller than both side.
        If it's negative, it means it's already smaller than both side, no moved needed.
        Add the moves need to res[i%i].
        In the end return the smaller option.


        Complexity
        Time O(N) for one pass
        Space O(2) for two options

    """
    def doit_(self, A):
        A = [float('inf')] + A + [float('inf')]
        res = [0, 0]

        for i in range(1, len(A) - 1):
            res[i % 2] += max(0, A[i] - min(A[i - 1], A[i + 1]) + 1)
        
        return min(res)
    
    def doit_(self, nums: list) -> int:

        less, greater = 0, 0

        nums = [float('inf')] + nums + [float('inf')]

        for i in range(1, len(nums)-1):

            if i % 2 == 1:
                less += max(0, nums[i] - min(nums[i-1], nums[i+1]) + 1)
            else:
                greater += max(0, nums[i] - min(nums[i-1], nums[i+1]) + 1)

        return min(less, greater)




        

                
        