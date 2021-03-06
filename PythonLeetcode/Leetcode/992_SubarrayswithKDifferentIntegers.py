# 992. Subarrays with K Different Integers

# Given an array A of positive integers, call a (contiguous, not necessarily distinct) subarray of
# A good if the number of different integers in that subarray is exactly K.

# (For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)

# Return the number of good subarrays of A.


# Example 1:

# Input: A = [1,2,1,2,3], K = 2
# Output: 7
# Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].

# Example 2:

# Input: A = [1,2,1,3,4], K = 3
# Output: 3
# Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].

from collections import Counter


class SubarraysWithKDistinct:

    """
        992.Subarrays-with-K-Different-Integers
        此题的解法非常巧妙.它代表了一类思想:求关于K的解,是否可以化成求at most K的解减去求at most K-1的解.本题恰好就是用到这个方法.我们需要写一个helper函数,计算数组A里面最多含有K个不同数字的subarray的个数.于是最终答案就是helper(K)-helper(K-1).

        对于这个helper函数,标准答案很显然就是用双指针和滑动窗口的方法.遍历右指针,考察对应的最大的滑窗是多少.于是在该右边界固定的条件下,满足题意的subarray的个数就是count+=右指针-左指针+1
    """
    def doit_slidingwindow(self, A:list, K:int) -> int:

        from collections import defaultdict

        def atmost(k):
            i, cnt, res = 0, defaultdict(int), 0
            length = 0
            
            for j in range(len(A)):
                
                cnt[A[j]] += 1
                if cnt[A[j]] == 1:
                    length += 1

                while length > k:
                    cnt[A[i]] -= 1
                    if cnt[A[i]] == 0:
                        length -= 1
                    i += 1

                res += j - i + 1
            return res

        return atmost(K) - atmost(K-1)

    """
        I republished this post.
        The original one is deleded by Leetcode without any notification or information.
        The only reason that, I included my youtube channel link.
        Excusem me, What the HACK!?


        Intuition:
        First you may have feeling of using sliding window.
        Then this idea get stuck in the middle.

        This problem will be a very typical sliding window,
        if it asks the number of subarrays with at most K distinct elements.

        Just need one more step to reach the folloing equation:
        exactly(K) = atMost(K) - atMost(K-1)


        Explanation
        Write/copy a helper function of sliding window,
        to get the number of subarrays with at most K distinct elements.
        Done.

        Complexity:
        Time O(N) for two passes.
        Space O(K) at most K elements in the counter

        Of course, you can merge 2 for loops into one, if you like.
    """
     def subarraysWithKDistinct(self, A, K):
        
        def atMostK(A, K):
            import collections
            count = collections.Counter()
            res = i = 0
            for j in range(len(A)):
                if count[A[j]] == 0: K -= 1
                count[A[j]] += 1
                while K < 0:
                    count[A[i]] -= 1
                    if count[A[i]] == 0: K += 1
                    i += 1
                res += j - i + 1
            return res

        return atMostK(A, K) - atMostK(A, K - 1)







    '''
        Use two left pointers and one right pointer to maintain two sliding windows
        A[left_L:right+1] is the longest subarray with K different int
        A[left_S:right+1] is the shortest subarray with K different int
        Move left_L right only if there are more than K distinct int
        Move left_S right as long as there are K or more distinct int
        Create two dicts for these two sliding windows
        Time: O(n)
        Space: O(n)
    '''
    def doit_slidingwindow(self, A: list, K: int) -> int:

        left_long, left_short = {}, {}
        cnt_long, cnt_short = 0, 0
        ans = 0
        long, short = 0, 0

        for i, v in enumerate(A):

            left_long[v] = left_long.get(v, 0) + 1
            left_short[v] = left_short.get(v, 0) + 1

            if left_long[v] == 1:
                cnt_long += 1
            if left_short[v] == 1:
                cnt_short += 1

            while cnt_long > K:
                left_long[A[long]] -= 1
                if left_long[A[long]] == 0:
                    cnt_long -= 1
                long += 1

            while cnt_short >= K:
                left_short[A[short]] -= 1
                if left_short[A[short]] == 0:
                    cnt_short -= 1
                short += 1

            ans += short - long

        return ans

    def doit_twopointers(self, A, K):
        res, len_A = 0, len(A)
        seen_L, seen_S = {}, {}
        left_L, left_S = 0, 0
        cnt_L, cnt_S = 0, 0

        for right, num in enumerate(A):

            seen_L[num] = seen_L.get(num, 0) + 1
            seen_S[num] = seen_S.get(num, 0) + 1

            if seen_L[num] == 1:
                cnt_L += 1

            if seen_S[num] == 1:
                cnt_S += 1

            while cnt_L > K:
                seen_L[A[left_L]] -= 1
                if seen_L[A[left_L]] == 0:
                    cnt_L -= 1
                left_L += 1

            while cnt_S >= K:
                seen_S[A[left_S]] -= 1
                if seen_S[A[left_S]] == 0:
                    cnt_S -= 1
                left_S += 1  # Actually left_S stops one step right

            res += (left_S - left_L)

        return res


"""
Approach 1: Sliding Window
Intuition

For convenience, let's denote subarrays by tuples: (i,j) = [A[i], A[i+1], ..., A[j]], and call a subarray valid if it has K different integers.

For each j, let's consider the set S_j of all i such that the subarray (i, j) is valid.

Firstly, S_j must be a contiguous interval. 
If i1 < i2 < i3, (i1,j) and (i3,j) are valid, but (i2,j) is not valid, this is a contradiction because (i2,j) must contain more than K different elements [as (i3,j) contains K], 
but (i1,j) [which is a superset of (i2,j)] only contains K different integers.

So now let's write S_j as intervals: S_j = [left1_j, left2_j]

The second observation is that the endpoints of these intervals must be monotone increeasing - namely, left1j, left2j are monotone increasing.
With similar logic to the above, we could construct a proof of this fact, but the intuition is that after adding an extra element to our subarrays, they are already valid, or we need to shrink them a bit to keep them valid.

Algorithm

We'll maintain two sliding windows, corresponding to left1j and left2j
Each sliding window will be able to count how many different elements there are in the window, and add and remove elements in a queue-like fashion.
"""


class Window:
    def __init__(self):
        self.count = Counter()
        self.nonzero = 0

    def add(self, x):
        self.count[x] += 1
        if self.count[x] == 1:
            self.nonzero += 1

    def remove(self, x):
        self.count[x] -= 1
        if self.count[x] == 0:
            self.nonzero -= 1


class SubarraysWithKDistinct1:
    def doit(self, A, K):
        window1 = Window()
        window2 = Window()
        ans = left1 = left2 = 0

        for right, x in enumerate(A):
            window1.add(x)
            window2.add(x)

            while window1.nonzero > K:
                window1.remove(A[left1])
                left1 += 1

            while window2.nonzero >= K:
                window2.remove(A[left2])
                left2 += 1

            ans += left2 - left1

        return ans


if __name__ == "__main__":

    res = SubarraysWithKDistinct().doit(A=[1, 2, 1, 2, 3], K=2)

    res = SubarraysWithKDistinct().doit(A=[1, 2, 1, 3, 4], K=3)