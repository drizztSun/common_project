"""
1362. Closest Divisors


Given an integer num, find the closest two integers in absolute difference whose product equals num + 1 or num + 2.

Return the two integers in any order.



Example 1:

Input: num = 8
Output: [3,3]
Explanation: For num + 1 = 9, the closest divisors are 3 & 3, for num + 2 = 10, the closest divisors are 2 & 5, hence 3 & 3 is chosen.
Example 2:

Input: num = 123
Output: [5,25]
Example 3:

Input: num = 999
Output: [40,25]


Constraints:

1 <= num <= 10^9
"""


class ClosestDivisors:

    """
        Explanation
        Iterate a from sqrt(x+2) to 1, and check:
        if (x + 1) % a == 0, we directly return the pair [a, (x + 1) / a].
        if (x + 2) % a == 0, we directly return the pair [a, (x + 2) / a].
        The first valid pair we meet will have be the closet pair.


        Complexity
        Time O(sqrtX), Space O(1)


    """
    def doit_(self, x: int) -> list:

        return next([a, y / a] for a in range(int((x + 2) ** 0.5), 0, -1) for y in [x + 1, x + 2] if not y % a)

    def doit_(self, num: int) -> list:

        from math import sqrt

        for i in reversed(range(1, int(sqrt(num + 2)) + 1)):

            if (num + 1) % i == 0: return [i, (num + 1) // i]

            if (num + 2) % i == 0: return [i, (num + 2) // i]

        return []
