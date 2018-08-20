


# 440. K-th Smallest in Lexicographical Order

# Given integers n and k, find the lexicographically k-th smallest integer in the range from 1 to n.

# Note: 1 < k < n < 109.

# Example:

# Input:
# n: 13   k: 2

# Output:
# 10

# Explanation:
# The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.

import heapq

# <hard> <important>
class findKthNumber(object):


    # <heap> <nlogn> <TLE> 
    def doit1(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        stack = []
        for i in range(1, n+1):
            heapq.heappush(stack, (str(i), i))

        key, val = '', 0
        for _ in range(k):
            key, val = heapq.heappop(stack)

        return val
        
        
# 1. Calculate the number of numbers that prefix with result.
# Numbers prefixed by result are the union of the following intervals:
# [result, result+1)
# [result*10, (result+1)*10 )
# [result*100, (result+1)*100 )
# 
# But they also shall belong to [1, n]
# Therefore, we can easily calculate the number of elements prefixed by result using the following code (not considering overflow):

    def doit(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """       
        for i in range(1, 10):
            cur, j = i, 0
            while k != 0 and cur < n:
                base = 10 ** j
                for c in range(i * base, (i+1) * base):
                    if c > n:
                        cur = n
                        break
                    k -= 1
                    if k == 0:
                        return c
                j += 1


# 2. Search the next prefix, or search more detailedly.

# If the number of numbers that prefixed by result is smaller than the remaining k,
# we do not need to consider the numbers prefixed by result any more, and march to the next prefix: result+1;
# Otherwise, we need to search more detailedly, by appending another digit to the prefix.
# Such search shall start with result*10. 

# [1, 10, 100, 10000...000] < [2, ]
# [110, 1100, 1101, 1102, 1103, 1104, 1105, 1106, 1107] < [1108] < [120]
# S0 BASE is [110, 120) == []


    def doit(self, n, k):
        result = 1;
        k -= 1
        while k > 0:

            count = 0
            interval = [result, result+1]

            while interval[0] <= n:
                count += (min(n+1, interval[1]) - interval[0])
                interval = [10 * interval[0], 10 * interval[1]]
            
            if k >= count:
                result += 1
                k -= count
            else:
                result *= 10
                k -= 1

        return result


# best one
# 
    def doit(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        import math
        def getSize(node, max_v):
            right_bound = node+1
            rval = 0
            while node <= max_v:
                rval += min(max_v+1, right_bound) - node
                right_bound, node = right_bound*10,node*10
            return rval

        prefix = 1
        while k > 0 :
            size = getSize(prefix, n)

            if size < k:
                k -= size
                prefix += 1
            else:
                k -= 1
                if k > 0:
                    prefix *= 10
                
        return prefix            
        

if __name__=="__main__":


    res = findKthNumber().doit(13, 2) # 10

    res = findKthNumber().doit(13, 3) # 10

    res = findKthNumber().doit(13, 4) # 10

    res = findKthNumber().doit(13, 5) # 10

    res = findKthNumber().doit(13, 5) # 10

    res = findKthNumber().doit(10, 3) # 2

    res = findKthNumber().doit(4289384, 1922239) # 2700016

    res = findKthNumber().doit(100, 10) # 17

    pass    
        