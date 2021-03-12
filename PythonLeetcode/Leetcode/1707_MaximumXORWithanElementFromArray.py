"""
1707. Maximum XOR With an Element From Array

You are given an array nums consisting of non-negative integers. You are also given a queries array, where queries[i] = [xi, mi].

The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums that does not exceed mi. In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in nums are larger than mi, then the answer is -1.

Return an integer array answer where answer.length == queries.length and answer[i] is the answer to the ith query.



Example 1:

Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
Output: [3,3,7]
Explanation:
1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
2) 1 XOR 2 = 3.
3) 5 XOR 2 = 7.
Example 2:

Input: nums = [5,2,4,6,6,3], queries = [[12,4],[8,1],[6,3]]
Output: [15,-1,5]


Constraints:

1 <= nums.length, queries.length <= 105
queries[i].length == 2
0 <= nums[j], xi, mi <= 109
"""


class MaximizeXor:

    def doit_trie(self, nums: list, queries: list) -> list:

        from collections import defaultdict

        trie = defaultdict(dict)

        nums.sort()
        ans = [-1] * len(queries)
        queries = sorted([[i, c[0], c[1]] for i, c in enumerate(queries)], key=lambda a: a[2])

        def insert(num):

            mask, p = 0, trie
            for i in reversed(range(32)):
                b = int(num >> i & 1)
                if b not in p:
                    p[b] = {}
                p = p[b]
            p[-1] = num

        def build(num):

            p = trie

            for i in reversed(range(32)):
                b = int(num >> i & 1)

                if not p: return -1

                if 1-b in p:
                    p = p[1 - b]
                else:
                    p = p[b]

            return p[-1] ^ num

        i = 0
        for index, num, limit in queries:

            while i < len(nums) and nums[i] <= limit:
                insert(nums[i])
                i += 1

            ans[index] = build(num)

        return ans


if __name__ == '__main__':

    MaximizeXor().doit_trie([0,1,2,3,4], [[3,1],[1,3],[5,6]])

    MaximizeXor().doit_trie([5,2,4,6,6,3], [[12,4],[8,1],[6,3]])