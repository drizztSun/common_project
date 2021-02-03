"""
1390. Four Divisors


Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors.

If there is no such integer in the array, return 0.

 

Example 1:

Input: nums = [21,4,7]
Output: 32
Explanation:
21 has 4 divisors: 1, 3, 7, 21
4 has 3 divisors: 1, 2, 4
7 has 2 divisors: 1, 7
The answer is the sum of divisors of 21 only.
 

Constraints:

1 <= nums.length <= 10^4
1 <= nums[i] <= 10^5

"""

class SumFourDivisors:

    def doit_(self, nums: list) -> int:
        from math import sqrt

        total = 0

        for num in nums:

            tmp = []
            for i in range(1, int(sqrt(num)) + 1):

                if num % i == 0:
                    if num // i == i:
                        tmp.append(i)
                    else:
                        tmp.extend([num // i, i])

                if len(tmp) > 4:
                    break

            if len(tmp) == 4:
                total += sum(tmp)
                
        return total
        