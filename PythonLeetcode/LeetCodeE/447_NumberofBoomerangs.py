


# 447. Number of Boomerangs

# Given n points in the plane that are all pairwise distinct,
# a "boomerang" is a tuple of points (i, j, k) such that the distance between i and j
# equals the distance between i and k (the order of the tuple matters).

# Find the number of boomerangs. You may assume that n will be at most 500 and
# coordinates of points are all in the range [-10000, 10000] (inclusive).

# Example:
# Input:
# [[0,0],[1,0],[2,0]]
# Output:
# 2

# Explanation:
# The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]

import collections

class numberOfBoomerangs:

    def doit(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        res = 0
        for p in points:
            cmap = {}
            for s in points:
                d = (s[0]-c[0])**2 + (s[1]-c[1])**2
                cmap[d] = cmap.get(d, 0) + 1

            for k in cmap:
                res += cmap[k] * (cmap[k] - 1)

        return res
                


    def doit(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        D = collections.defaultdict(dict)

        for c in points:
            for s in points:
                if c == s:
                    continue
                distance = (s[0]-c[0])**2 + (s[1]-c[1])**2
                C, S = tuple(c), tuple(s)
                if C not in D[distance]:
                    D[distance][C] = set()
                D[distance][C].add(S) 

                
                if S not in D[distance]:
                    D[distance][S] = set()
                D[distance][S].add(C)

        res = 0
        dataSet = {}
        dataSet[2] = 2

        for distance in D.keys():
            if not D[distance]:
                continue

            for d in D[distance].keys():
                nums = len(D[distance][d])
                res += nums * (nums-1)

        return res
                


if __name__=="__main__":


    res = numberOfBoomerangs().doit([[0,0],[1,0],[2,0]])

    pass
        