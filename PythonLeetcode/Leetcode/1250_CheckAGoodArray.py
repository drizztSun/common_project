"""
1250. Check If It Is a Good Array

Given an array nums of positive integers. Your task is to select some subset of nums,
multiply each element by an integer and add all these numbers.
The array is said to be good if you can obtain a sum of 1 from the array by any possible subset and multiplicand.

Return True if the array is good otherwise return False.



Example 1:

Input: nums = [12,5,7,23]
Output: true
Explanation: Pick numbers 5 and 7.
5*3 + 7*(-2) = 1
Example 2:

Input: nums = [29,6,10]
Output: true
Explanation: Pick numbers 29, 6 and 10.
29*1 + 6*(-3) + 10*(-1) = 1
Example 3:

Input: nums = [3,6]
Output: false


Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9

"""


class GoodArray:

    """
    Read (https://brilliant.org/wiki/bezouts-identity/, https://en.wikipedia.org/wiki/Bézout's_identity)

    The basic idea is that for integers a and b, if gcd(a,b) = d, then there exist integers x and y, s.t a * x + b * y = d;

    This can be generalized for (n >= 2) . e.g. if gcd(a,b,c) = d, then there exist integers x, y, and z, s.t, a* x + b*y + c * z = d.

    Now this problem is just asking if gcd(x1, ......, xn) = 1
    """

    def doit_math(self, nums: list) -> bool:
        from functools import reduce

        def gcd(a, b):
            while b:
                a, b = b, a % b
            return a

        return reduce(gcd, nums) == 1
