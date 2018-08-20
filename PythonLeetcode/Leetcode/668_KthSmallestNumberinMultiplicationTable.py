


# 668. Kth Smallest Number in Multiplication Table

# 719. Find K-th Smallest Pair Distance

# <Multiplication Table>
# https://en.wikipedia.org/wiki/Multiplication_table

# Nearly every one have used the Multiplication Table. But could you find out 
# the k-th smallest number quickly from the multiplication table?

# Given the height m and the length n of a m * n Multiplication Table, and a positive integer k, 
# you need to return the k-th smallest number in this table.

# Example 1:
# Input: m = 3, n = 3, k = 5
# Output: 
# Explanation: 
# The Multiplication Table:
# 1	 2	3
# 2	 4	6
# 3	 6	9

# The 5-th smallest number is 3 (1, 2, 2, 3, 3).

# Example 2:
# Input: m = 2, n = 3, k = 6
# Output: 
# Explanation: 
# The Multiplication Table:
# 1	 2	3
# 2	 4	6

# The 6-th smallest number is 6 (1, 2, 2, 3, 4, 6).

import heapq

class findKthNumber:



# Let’s binary search for the answer A.

# Say enough(x) is true if and only if there are k or more values in the multiplication table that are less than or equal to x.
# Colloquially, enough describes whether x is large enough to be the k-th value in the multiplication table.

# Then (for our answer A), whenever x >= A, enough(x) is True; and whenever x < A, enough(x) is False.

# In our binary search, our loop invariant is that enough(hi) = True.
# More specifically, if we were to apply enough onto each argument in the interval [lo, hi], we would see 0 or more False, followed by 1 or more True.
# Once lo == hi, we know that enough(lo) = True, and it must have been the smallest such one, because lo must have been hi-1 or hi-2 at some point,
# and mi = hi-1 would have been checked.

# This leaves us with the task of counting how many values are less than or equal to x.
# For each of m rows, the i-th row looks like [i, 2*i, 3*i, ..., n*i], and there are min(x // i, n) values in that row that are less than or equal to x.

    def doit(self, m, n, k):
        """
        :type m: int
        :type n: int
        :type k: int
        :rtype: int
        """
        def enough(x):
            return sum(min(x//i, n) for i in range(1, m+1)) >= k
        
        lo, hi = 1, m * n
        while lo < hi:
            mid = (lo + hi) // 2
            if not enough(mid):
                lo = mid + 1
            else:
                hi = mid

        return lo
            
        
    def doit1(self, m, n, k):
        """
        :type m: int
        :type n: int
        :type k: int
        :rtype: int
        """
        if m > n: n, m = m, n
        left, right = 1, k
        while left < right:
            mid = (left + right) // 2
            
            cnt = 0
            for i in range(1, m + 1):
                # if mid // i <= n:
                if mid <= i * n:
                    cnt += mid // i 
                else:
                    cnt += n 
                    
            if cnt < k:
                left = mid + 1
            else:
                right = mid 
        return left

    # <TLE>
    def doit1(self, m, n, k):
        """
        :type m: int
        :type n: int
        :type k: int
        :rtype: int
        """
        def push(i, j):
            if i < m and j < n:
                heapq.heappush(buff, [(i+1)*(j+1), i, j])

        buff = []
        for i in range(m):
            push(i, 0)

        ans = -1
        while buff and k > 0:
            ans, i, j = heapq.heappop(buff)
            push(i, j+1)
            k -= 1

        return ans
        


if __name__=="__main__":

    res = findKthNumber().doit1(3, 3, 5)
    
    res = findKthNumber().doit1(2, 3, 6)

    res = findKthNumber().doit(98995, 28405, 100787757)

    pass