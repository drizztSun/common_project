"""
1711. Count Good Meals


A good meal is a meal that contains exactly two different food items with a sum of deliciousness equal to a power of two.

You can pick any two different foods to make a good meal.

Given an array of integers deliciousness where deliciousness[i] is the deliciousness of the i​​​​​​th​​​​​​​​ item of food, return the number of different good meals you can make from this list modulo 10^9 + 7.

Note that items with different indices are considered different even if they have the same deliciousness value.



Example 1:

Input: deliciousness = [1,3,5,7,9]
Output: 4
Explanation: The good meals are (1,3), (1,7), (3,5) and, (7,9).
Their respective sums are 4, 8, 8, and 16, all of which are powers of 2.
Example 2:

Input: deliciousness = [1,1,1,3,3,3,7]
Output: 15
Explanation: The good meals are (1,1) with 3 ways, (1,3) with 9 ways, and (1,7) with 3 ways.


Constraints:

1 <= deliciousness.length <= 105
0 <= deliciousness[i] <= 220


"""


class CountPairs:

    def doit_hashtable(self, deliciousness: list) -> int:
        from math import log2
        from collections import Counter

        cnt = Counter()
        res = 0
        mod = 10 ** 9 + 7

        for c in deliciousness:

            """
                How to donngrade n^2 to O(n). It we need to check all the values created in hashtable before to make sure a pair or cond.
                It could bring O(n^2) Complexoty. 
                but if Target is a O(n) or O(1) amount, we can use (target, cur) to generate possible we need and check if it exisited in hashtable.
                Then we will downgrade compare from O(n) -> O(1)
                And then it downgrades the whole compare to be O(n) 
            """

            for k in range(22):
                if (2 ** k - c) in cnt:
                    res += cnt[2 ** k - c]

            cnt[c] += 1

        return res % mod



