"""
1722. Minimize Hamming Distance After Swap Operations


You are given two integer arrays, source and target, both of length n. 

You are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi] indicates that you are allowed to swap the elements at index ai and index bi (0-indexed) of array source. 

Note that you can swap elements at a specific pair of indices multiple times and in any order.

The Hamming distance of two arrays of the same length, source and target, is the number of positions where the elements are different. 

Formally, it is the number of indices i for 0 <= i <= n-1 where source[i] != target[i] (0-indexed).

Return the minimum Hamming distance of source and target after performing any amount of swap operations on array source.

 

Example 1:

Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
Output: 1
Explanation: source can be transformed the following way:
- Swap indices 0 and 1: source = [2,1,3,4]
- Swap indices 2 and 3: source = [2,1,4,3]
The Hamming distance of source and target is 1 as they differ in 1 position: index 3.
Example 2:

Input: source = [1,2,3,4], target = [1,3,2,4], allowedSwaps = []
Output: 2
Explanation: There are no allowed swaps.
The Hamming distance of source and target is 2 as they differ in 2 positions: index 1 and index 2.
Example 3:

Input: source = [5,1,2,4,3], target = [1,5,4,2,3], allowedSwaps = [[0,4],[4,2],[1,3],[1,4]]
Output: 0
 

Constraints:

n == source.length == target.length

1 <= n <= 10^5
1 <= source[i], target[i] <= 10^5
0 <= allowedSwaps.length <= 10^5

allowedSwaps[i].length == 2
0 <= ai, bi <= n - 1
ai != bi

"""


class MinimumHammingDistance:

    """
        1722.Minimize-Hamming-Distance-After-Swap-Operations
        我们将所有互相连接的allowedSwap的位置都union起来，这些位置上的数字其实都是可以任意重新排列的。我们只需要将source里这些位置上的元素集合，与target里这些位置上的元素集合进行比较，数一下有多少不同元素，就是Hamming distances.
    """
    def doit_disjoint(self, source: list, target: list, allowedSwaps: list) -> int:

        from collections import defaultdict, Counter

        father = [i for i in range(len(source))]

        def find(i):
            while father[i] != i:
                father[i] = father[father[i]]
                i = father[i]
            return father[i]

        def union(i, j):
            pi, pj = find(i), find(j)
            if pi == pj: return

            if pi < pj:
                father[pj] = pi
            else:
                father[pi] = pj

        for c in allowedSwaps:
            union(c[0], c[1])

        groups = defaultdict(list)

        for i in range(len(father)):
            groups[find(i)].append(i)

        ans = 0
        for k, v in groups.items():

            group = defaultdict(int)
            for c in v:
                group[source[c] ]+= 1

            for i in v:
                if target[i] in group:
                    group[target[i]] -= 1
                    if group[target[i]] == 0:
                        del group[target[i]]

            ans += sum(c for c in group.values())

        return ans