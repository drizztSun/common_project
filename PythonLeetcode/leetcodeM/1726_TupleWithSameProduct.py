"""
1726. Tuple with Same Product

Given an array nums of distinct positive integers, return the number of tuples (a, b, c, d) such that a * b = c * d
where a, b, c, and d are elements of nums, and a != b != c != d.


Example 1:

Input: nums = [2,3,4,6]
Output: 8
Explanation: There are 8 valid tuples:
(2,6,3,4) , (2,6,4,3) , (6,2,3,4) , (6,2,4,3)
(3,4,2,6) , (4,3,2,6) , (3,4,6,2) , (4,3,6,2)
Example 2:

Input: nums = [1,2,4,5,10]
Output: 16
Explanation: There are 16 valids tuples:
(1,10,2,5) , (1,10,5,2) , (10,1,2,5) , (10,1,5,2)
(2,5,1,10) , (2,5,10,1) , (5,2,1,10) , (5,2,10,1)
(2,10,4,5) , (2,10,5,4) , (10,2,4,5) , (10,2,4,5)
(4,5,2,10) , (4,5,10,2) , (5,4,2,10) , (5,4,10,2)
Example 3:

Input: nums = [2,3,4,6,8,12]
Output: 40
Example 4:

Input: nums = [2,3,5,7]
Output: 0


Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 104
All elements in nums are distinct.

"""


class TupleSameProduct:

    """
        Here we take advantage of the fact that there 8 ways to reorganize a tuple of the form (a,b,c,d). I got to this from looking at the sub tuples (a,b) and (c,d) as a pair. 
        Thus there are 2 ways to rearrange each tuple pair and 2 ways to combine them (either a,b before c,d or a,b after c,d) W.L.O.G. Below is a numbered list view.

        (a,b,c,d)
        (a,b,d,c)
        (b,a,c,d)
        (b,a,d,c)
        (c,d,a,b)
        (c,d,b,a)
        (d,c,a,b)
        (d,c,b,a)
        Suppose you have a iterable A of length N such that every pair in that iterable evaluates to X. Then each time you add a new pair to that iterable you are effectively adding N unique possible tuples of the form/order (a,b,c,d). 
        Consequently, we track those with the count variable and multiply by 8 to get the combination of pairs listed above. Or at least that was my logic that seems to have worked.
    """
    def doit_hashtable(self, nums: list) -> int:

        from collections import defaultdict

        buff = defaultdict(int)

        for i in range(len(nums)):
            for j in range(i):
                buff[nums[i] * nums[j]] += 1

        ans = 0
        for k, v in buff.items():
            ans += 4 * v * (v - 1)

        return ans
