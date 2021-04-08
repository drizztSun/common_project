"""
1803. Count Pairs With XOR in a Range


Given a (0-indexed) integer array nums and two integers low and high, return the number of nice pairs.

A nice pair is a pair (i, j) where 0 <= i < j < nums.length and low <= (nums[i] XOR nums[j]) <= high.



Example 1:

Input: nums = [1,4,2,7], low = 2, high = 6
Output: 6
Explanation: All nice pairs (i, j) are as follows:
    - (0, 1): nums[0] XOR nums[1] = 5
    - (0, 2): nums[0] XOR nums[2] = 3
    - (0, 3): nums[0] XOR nums[3] = 6
    - (1, 2): nums[1] XOR nums[2] = 6
    - (1, 3): nums[1] XOR nums[3] = 3
    - (2, 3): nums[2] XOR nums[3] = 5
Example 2:

Input: nums = [9,8,4,2,1], low = 5, high = 14
Output: 8
Explanation: All nice pairs (i, j) are as follows:
​​​​​    - (0, 2): nums[0] XOR nums[2] = 13
    - (0, 3): nums[0] XOR nums[3] = 11
    - (0, 4): nums[0] XOR nums[4] = 8
    - (1, 2): nums[1] XOR nums[2] = 12
    - (1, 3): nums[1] XOR nums[3] = 10
    - (1, 4): nums[1] XOR nums[4] = 9
    - (2, 3): nums[2] XOR nums[3] = 6
    - (2, 4): nums[2] XOR nums[4] = 5


Constraints:

1 <= nums.length <= 2 * 104
1 <= nums[i] <= 2 * 104
1 <= low <= high <= 2 * 104



"""
from collections import defaultdict, Counter


class CountPairsWithXOR:

    def doit_hash(self, nums: list, low: int, high: int):

        count = Counter(nums)
        high += 1
        res = 0
        while high:
            if high & 1:
                y = high - 1
                res += sum(count[a] * count[y ^ a] for a in count)
            if low & 1:
                y = low - 1
                res -= sum(count[a] * count[y ^ a] for a in count)
            count = Counter({a >> 1: count[a] + count[a ^ 1] for a in count})
            high >>= 1
            low >>= 1
        return res // 2

    def doit_trie(self, nums: list, low: int, high: int) -> int:

        class trie:
            def __init__(self):
                self._child = [None, None]
                self._count = 0

        def cal(root, num, th):
            cur = root
            cnt = 0

            for i in reversed(range(32)):

                a = num >> i & 1
                b = th >> i & 1
                c = a ^ b

                if b == 1 and c == 1:
                    if cur._child[0]:
                        cnt += cur._child[0]._count
                    if cur._child[1]:
                        cur = cur._child[1]
                    else:
                        break
                elif b == 0 and c == 1:
                    if cur._child[1]:
                        cur = cur._child[1]
                    else:
                        break
                elif b == 1 and c == 0:
                    if cur._child[1]:
                        cnt += cur._child[1]._count
                    if cur._child[0]:
                        cur = cur._child[0]
                    else:
                        break
                elif b == 0 and c == 0:
                    if cur._child[0]:
                        cur = cur._child[0]
                    else:
                        break
            return cnt

        def insert(root, num):
            cur = root
            for i in reversed(range(32)):
                base = num >> i & 1
                if not cur._child[base]:
                    cur._child[base] = trie()
                cur = cur._child[base]
                cur._count += 1

        def lessthan(limit):
            cnt = 0
            root = trie()
            for c in nums:
                cnt += cal(root, c, limit)
                insert(root, c)
            return cnt

        return lessthan(high + 1) - lessthan(low)

    class TrieNode:
        def __init__(self):
            self.nodes = defaultdict(TrieNode)
            self.cnt = 0

    class Trie:

        def __init__(self):
            self.root = TrieNode()

        def insert(self, val):
            cur = self.root
            for i in reversed(range(15)):
                bit = val >> i & 1
                cur.nodes[bit].cnt += 1
                cur = cur.nodes[bit]

        def count(self, val, high):
            res = 0
            cur = self.root
            for i in reversed(range(15)):
                if not cur:
                    break
                bit = val >> i & 1
                cmp = high >> i & 1
                if cmp:
                    res += cur.nodes[bit].cnt
                    cur = cur.nodes[1 ^ bit]
                else:
                    cur = cur.nodes[bit]
            return res

    def countPairs(self, nums: List[int], low: int, high: int) -> int:
        trie = Trie()
        res = 0
        for num in nums:
            res += trie.count(num, high + 1) - trie.count(num, low)
            trie.insert(num)

        return res