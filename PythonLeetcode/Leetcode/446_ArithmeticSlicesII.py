"""
# 446. Arithmetic Slices II - Subsequence

# A sequence of numbers is called arithmetic if it consists of at least three elements and
# if the difference between any two consecutive elements is the same.

# For example, these are arithmetic sequences:

# 1, 3, 5, 7, 9
# 7, 7, 7, 7
# 3, -1, -5, -9
# The following sequence is not arithmetic.

# 1, 1, 2, 5, 7

# A zero-indexed array A consisting of N numbers is given. A subsequence slice of that array is any sequence of integers (P0, P1, ..., Pk) such that 0 ? P0 < P1 < ... < Pk < N.

# A subsequence slice (P0, P1, ..., Pk) of array A is called arithmetic if the sequence A[P0], A[P1], ..., A[Pk-1], A[Pk] is arithmetic. In particular, this means that k ? 2.

# The function should return the number of arithmetic subsequence slices in the array A.

# The input contains N integers. Every integer is in the range of -231 and 231-1 and 0 ? N ? 1000. The output is guaranteed to be less than 231-1.

# Example:

# Input: [2, 4, 6, 8, 10]

# Output: 7

# Explanation:
# All arithmetic subsequence slices are:
# [2,4,6]
# [4,6,8]
# [6,8,10]
# [2,4,6,8]
# [4,6,8,10]
# [2,4,6,8,10]
# [2,6,10]
"""


class NumberOfArithmeticSlices:

    """
    # We memoize with an array of dicts, dp, such that dp[i][j] stores the number of arithmetic slices
    # (including those with only length 2) whose constant difference is j ending at i.
    # The key is basically to store all 2±length arithmetic slices (which is helps to build up the solution from its sub-problems)
    # while only adding valid 3±length slices to the total.

    # The we iterate over all pairs in the array. Each (A[j], A[i]) is a 2-length slice with constant difference A[i] - A[j]
    # that we’ve never encountered before, so increment dp[i][A[i] - A[j]] by 1 (but leave the total as is, because its not length 3 or more).

    # If there are any slices with A[i] - A[j] length that finish at index j (if A[i]-A[j] in dp[j]:),
    # we ‘extend’ them to index i and add to the total, since any slice that terminated at index j would now have at least length 3 terminating at i.
    """
    def doit_dp(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        import collections

        dp = [collections.defaultdict(int) for _ in range(len(A))]
        result = 0

        for i in range(0, len(A)):
            for j in range(i):

                diff = A[i]-A[j]
                dp[i][diff] += 1

                if dp[j][diff] != 0:
                    dp[i][diff] += dp[j][diff]
                    result += dp[j][diff]

        return result

    # <DP>
    def doit(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        lookup = {}

        for i, a in enumerate(A):
            if a in lookup:
                lookup[a].append(i)
            else:
                lookup[a] = [i]

        dp = []
        for _ in range(len(A)):
            dp.append({})

        for k, num in enumerate(A):
            for i in range(0, k):
                diff = A[k] - A[i]
                X = A[i] - diff
                if X in lookup:
                    for index in lookup[X]:
                        if index < i:
                            dp[k][diff] = dp[k].get(diff, 0) + 1

                if diff in dp[i]:
                    dp[k][diff] = dp[k].get(diff, 0) + dp[i][diff]

        res = 0
        for x in dp:
            for k in x:
                res += x[k]

        return res

    """
    post / pre tells at position i, how many c we have after i and before i
    if current num[i] is b, there is c in pre, so 2* b - c = a is the target, we check in post
    if we have c in post, we need to build sequence count.
    n = pre[c], how many b it have before i, n means b - c, it will added to each pos[a] > i, (just 3 elements)
    if seq[i][b] (more then 3 element) already have some sequence, seq[j][b] should add seq[i][b] + n
    
    add all elements count together.
    """
    def doit_dp_2(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        from collections import defaultdict
        pre = defaultdict(int)
        post = defaultdict(int)
        pos = defaultdict(list)
        seq = [defaultdict(int) for _ in range(len(A))]
            
        for i, a in enumerate(A):
            post[a] += 1
            pos[a].append(i)
    
        for i, a in enumerate(A):
            post[a] -= 1

            for b in pre:
                c = (a << 1) - b

                if c in post and post[c] > 0:
                    n = pre[b]

                    if b in seq[i]:
                        n += seq[i][b]

                    for j in pos[c]:
                        if j > i:
                            seq[j][a] += n

            pre[a] += 1
            
        return sum([sum(p.values()) for p in seq])


if __name__=="__main__":

    res = NumberOfArithmeticSlices().doit([2, 4, 6, 8, 10])

    res = NumberOfArithmeticSlices().doit([0,1,2,2,2])

    res = NumberOfArithmeticSlices().doit([1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1])

    res = NumberOfArithmeticSlices().doit([79,20,64,28,67,81,60,58,97,85,92,96,82,89,46,50,15,2,36,44,54,2,90,37,7,79,26,40,34,67,64,28,60,89,46,31,9,95,43,19,47,64,48,95,80,31,47,19,72,99,28,46,13,9,64,4,68,74,50,28,69,94,93,3,80,78,23,80,43,49,77,18,68,28,13,61,34,44,80,70,55,85,0,37,93,40,47,47,45,23,26,74,45,67,34,20,33,71,48,96])
