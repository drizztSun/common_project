"""
1655. Distribute Repeating Integers

You are given an array of n integers, nums, where there are at most 50 unique values in the array. You are also given an array of m customer order quantities,
quantity, where quantity[i] is the amount of integers the ith customer ordered. Determine if it is possible to distribute nums such that:

The ith customer gets exactly quantity[i] integers,
The integers the ith customer gets are all equal, and
Every customer is satisfied.
Return true if it is possible to distribute nums according to the above conditions.



Example 1:

Input: nums = [1,2,3,4], quantity = [2]
Output: false
Explanation: The 0th customer cannot be given two different integers.
Example 2:

Input: nums = [1,2,3,3], quantity = [2]
Output: true
Explanation: The 0th customer is given [3,3]. The integers [1,2] are not used.
Example 3:

Input: nums = [1,1,2,2], quantity = [2,2]
Output: true
Explanation: The 0th customer is given [1,1], and the 1st customer is given [2,2].
Example 4:

Input: nums = [1,1,2,3], quantity = [2,2]
Output: false
Explanation: Although the 0th customer could be given [1,1], the 1st customer cannot be satisfied.
Example 5:

Input: nums = [1,1,1,1,1], quantity = [2,3]
Output: true
Explanation: The 0th customer is given [1,1], and the 1st customer is given [1,1,1].


Constraints:

n == nums.length
1 <= n <= 105
1 <= nums[i] <= 1000
m == quantity.length
1 <= m <= 10
1 <= quantity[i] <= 105
There are at most 50 unique values in nums.

"""


class CanDistribute:

    def canDistribute(self, nums: list, quantity: list) -> bool:

        from collections import Counter
        from heapq import heappop, heappush

        cnt = Counter(nums)
        vs = sorted(cnt.values())
        qt = tuple(sorted(quantity))
        cusum = [vs[0]] * len(vs)
        for i in range(1, len(vs)):
            cusum[i] = cusum[i - 1] + vs[i]

        def helper(qt, v):
            cands = set()
            seen = {qt}
            stack = [[qt, v]]
            while stack:
                cqt, cv = stack.pop()
                if cqt[0] > cv:
                    cands.add((sum(cqt), cqt))
                else:
                    for i in range(len(cqt)):
                        if cqt[i] <= cv:
                            nv = cv - cqt[i]
                            nqt = cqt[:i] + cqt[i + 1:]
                            if nqt not in seen:
                                seen.add(nqt)
                                stack.append([nqt, nv])
            return cands

        state = [[sum(qt), qt, len(vs) - 1]]
        while state:
            csum, cqt, j = heappop(state)
            rem = cusum[j]
            if j == 0:
                return rem >= csum
            rem -= cusum[j - 1]
            if rem >= csum:
                return True
            if cusum[j] >= csum and cqt[-1] <= vs[j]:
                cands = helper(cqt, vs[j])
                for nsum, nqt in cands:
                    if nsum <= cusum[j - 1] and nqt[-1] <= vs[j - 1]:
                        heappush(state, [nsum, nqt, j - 1])
        return False


    def doit_backtracking_dfs(self, nums: list, quantity: list) -> bool:
        pass

    def doit_dp_bitmask(self, nums: list, quantity: list) -> bool:
        from functools import lru_cache
        from collections import Counter

        values = list(Counter(nums).values())
        m = len(quantity)
        sums = [0] * (1 << m)
        for mask in range(1 << m):
            for j in range(m):
                if mask & (1 << j):
                    sums[mask] += quantity[j]

        @lru_cache(None)
        def search(mask, i):

            if not mask:
                return True

            if i < 0:
                return False

            cur = mask
            while cur:
                if sums[cur] <= values[i] and search(cur, i-1):
                    return True
                cur = (cur-1) & mask

            return search(mask, i - 1)

        return search((1<<m)-1, len(values)-1)


if __name__ == '__main__':

    CanDistribute().doit_dp_bitmask([1, 1, 1, 1, 1], [2, 3])
