


# 354. Russian Doll Envelopes

# You have a number of envelopes with widths and heights given as a pair of integers (w, h).
# One envelope can fit into another if and only if both the width and height of one envelope 
# is greater than the width and height of the other envelope.

# What is the maximum number of envelopes can you Russian doll? (put one inside other)

# Example:
# Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).


class maxEnvelopes(object):


# The idea is to order the envelopes and then calculate the longest increasing subsequence (LISS).
# We first sort the envelopes by width, and we also make sure that when the width is the same,
# the envelope with greater height comes first.

# 300. Longest Increasing Subsequence (reference)

# Why? This makes sure that when we calculate the LISS, we don’t have a case such as [3, 4] [3, 5]
# (we could increase the LISS but this would be wrong as the width is the same. It can’t happen when [3, 5] comes first in the ordering).

# We could calculate the LISS using the standard DP algorithm (quadratic runtime),
# but we can just use the tails array method with a twist: we store the index of the tail,
# and we do leftmost insertion point as usual to find the right index in nlogn time.
# Why not rightmost? Think about the case [1, 1], [1, 1], [1, 1].


# Sort the array. Ascend on width and descend on height if width are same.
# Find the longest increasing subsequence based on height.
# Since the width is increasing, we only need to consider height.
# [3, 4] cannot contains [3, 3], so we need to put [3, 4] before [3, 3] when sorting otherwise 
# it will be counted as an increasing number if the order is [3, 3], [3, 4]


    def doit(self, envelopes):
        """
        :type envelopes: List[List[int]]
        :rtype: int
        """
        def lmip(envelopes, tail, c):
            s, e = 0, len(tail) - 1
            while s <= e:
                m = (s + e) // 2
                if envelopes[tail[m]][1] >= c[1]:
                    e = m-1
                else:
                    s = m+1

            return s                

        envelopes.sort(key=lambda x: (x[0], -x[1]))        
        tail = []

        for i, c in enumerate(envelopes):

            index = lmip(envelopes, tail, c)
            if index >= len(tail):
                tail.append(index)
            else:
                tail[index] = i

        return len(tail)
    
    # <DP>
    def doit1(self, envelopes):
        """
        :type envelopes: List[List[int]]
        :rtype: int
        """
        envelopes.sort(key=lambda x: (x[0], x[1]))
        DP = [1 for _ in range(envelopes)]
        maxV = 0

        for i in range(len(envelopes)):
            for j in range(i):
                if envelopes[j][0] < envelopes[i][0] and envelopes[j][1] < envelopes[i][1]: 
                    DP[i] = max(DP[j] + 1, DP[i])

            maxV = max(maxV, DP[i])

        return maxV

    # <DFS> <DP> <TLE>
    def doit1(self, envelopes):
        """
        :type envelopes: List[List[int]]
        :rtype: int
        """
        NewOrderedArray = sorted(envelopes, key = lambda x: (x[1], x[0]), reverse = 1)
        NewOrderedArray = [[float('inf'), float('inf')]] + NewOrderedArray
        D = {}        

        def search(A, i):

            if (tuple(A[i]), i) in D:
                return D[(tuple(A[i]), i)]

            if i == len(NewOrderedArray):
                return 0
            
            res = 0
            for s in range(i+1, len(A)):
               if A[s][0] < A[i][0] and A[s][1] < A[i][1]:
                   res = max(res, search(A, s) + 1)

            D[(tuple(A[i]), i)] = res

            return res

        return search(NewOrderedArray, 0)


    #
    def doit2(self, envs):
        """
        :type envelopes: List[List[int]]
        :rtype: int
        """
        def liss(envs):
            def lmip(envs, tails, k):
                b, e = 0, len(tails) - 1
                while b <= e:
                    m = (b + e) >> 1
                    if envs[tails[m]][1] >= k[1]:
                        e = m - 1
                    else:
                        b = m + 1
                return b
            
            tails = []
            for i, env in enumerate(envs):
                idx = lmip(envs, tails, env)
                if idx >= len(tails):
                    tails.append(i)
                else:
                    tails[idx] = i
            return len(tails)
        
        
        def f(x, y):
            return -1 if (x[0] < y[0] or x[0] == y[0] and x[1] > y[1]) else 1
            
        envs.sort(cmp=f)
        return liss(envs)

# Best        
class Solution:
    def longestIncreasingSequence(self, A):
        B = []
        for n in A:
            i = bisect.bisect_left(B, n)
            if i == len(B):
                B.append(n)
            else:
                B[i] = n
        return len(B)
        
    def maxEnvelopes(self, envelopes):
        """
        :type envelopes: List[List[int]]
        :rtype: int
        """
        return self.longestIncreasingSequence([t[1] for t in sorted(envelopes, key=lambda t: (t[0], -t[1]))])


if __name__=="__main__":


    res = maxEnvelopes().doit([[5,4],[6,4],[6,7],[2,3]])

    res = maxEnvelopes().doit([[5,4],[6,4],[6,7],[2,3]])

    pass
