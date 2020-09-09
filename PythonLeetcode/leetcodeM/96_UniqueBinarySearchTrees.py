"""
96. Unique Binary Search Trees

Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?

Example:

Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
"""


class NumTrees:

    def doit_dp(self, n: int) -> int:
        """
        :type n: int
        :rtype: int
        """

        def find(s, e, buff):
            if s >= e:
                return 1

            if (e - s) in buff:
                return buff[e - s]

            res = 0
            for i in range(s, e + 1):
                l = find(s, i - 1, buff)
                r = find(i + 1, e, buff)

                res += l * r

            buff[e - s] = res
            return res

        return find(1, n, {})

    def doit_dp1(self, n: int) -> int:
        """
        :type n: int
        :rtype: int
        """
        arr = [-1] * (n + 1)
        arr[0] = arr[1] = 1

        def count(n, arr):

            if arr[n] != -1:
                return arr[n]

            c = 0
            for i in range(1, n + 1):
                c += count(i - 1, arr) * count(n - i, arr)
            arr[n] = c
            return c

        return count(n, arr)



