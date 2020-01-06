# 823. Binary Trees With Factors

# Given an array of unique integers, each integer is strictly greater than 1.

# We make a binary tree using these integers and each number may be used for any number of times.

# Each non-leaf node's value should be equal to the product of the values of it's children.

# How many binary trees can we make?  Return the answer modulo 10 ** 9 + 7.

# Example 1:

# Input: A = [2, 4]
# Output: 3
# Explanation: We can make these trees: [2], [4], [4, 2, 2]

# Example 2:

# Input: A = [2, 4, 5, 10]
# Output: 7
# Explanation: We can make these trees: [2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5, 2].


# Note:

# 1 <= A.length <= 1000.
# 2 <= A[i] <= 10 ^ 9.

"""
Approach #1: Dynamic Programming [Accepted]
Intuition

The largest value v used must be the root node in the tree. Say dp(v) is the number of ways to make a tree with root node v.

If the root node of the tree (with value v) has children with values x and y (and x * y == v), then there are dp(x) * dp(y) ways to make this tree.

In total, there are \sum_{\substack{x * y = v}} \text{dp}(x) * \text{dp}(y) ways to make a tree with root node v.

Algorithm

Actually, let dp[i] be the number of ways to have a root node with value A[i].

Since in the above example we always have x < v and y < v, we can calculate the values of dp[i] in increasing order using dynamic programming.

For some root value A[i], let's try to find candidates for the children with values A[j] and A[i] / A[j] (so that evidently A[j] * (A[i] / A[j]) = A[i]).
To do this quickly, we will need index which looks up this value: if A[k] = A[i] / A[j], then index[A[i] / A[j]] = k`.

After, we'll add all possible dp[j] * dp[k] (with j < i, k < i) to our answer dp[i]. In our Java implementation, we carefully used long so avoid overflow issues.

Complexity Analysis

Time Complexity: O(N**2), where NN is the length of A. This comes from the two for-loops iterating i and j.

Space Complexity: O(N), the space used by dp and index.

"""
import collections


class NumFactoredBinaryTrees:

    def doit(self, A):
        A.sort()
        counts = collections.defaultdict(int)
        result = len(A)
        products = self.get_products(A)

        for i, num in enumerate(A):
            for a, b in products[i]:
                counts[num] += (counts[a] + 1) * \
                    (counts[b] + 1) * ((a != b) + 1)

        return (result + sum(counts.values())) % (10 ** 9 + 7)

        def get_products(self, A):
            products = {num: [] for num in A}

            for i in range(len(A)-1):
                for j in range(i, len(A)):
                    prod = A[i] * A[j]
                    if prod in products:
                        products[prod].append((A[i], A[j]))
                    elif prod > A[-1]:
                        break

            return list(products.values())

    def doit(self, A):
        MOD = 10 ** 9 + 7
        N = len(A)
        A.sort()
        dp = [1] * N
        index = {x: i for i, x in enumerate(A)}
        for i, x in enumerate(A):
            for j in range(i):
                if x % A[j] == 0:  # A[j] will be left child
                    right = x / A[j]
                    if right in index:
                        dp[i] += dp[j] * dp[index[right]]
                        dp[i] %= MOD

        return sum(dp) % MOD

    """
    sort the array
    and use HashMap to record each Integer, and the number of trees with that Integer as root
    (1) each integer A[i] will always have one tree with only itself
    (2) if A[i] has divisor (n) in the dict, and if A[i]/n also in the dict
    then a can be the root of its left subtree, and A[i]/n can be the root of its right subtree;
    the number of such tree is ct_dict[n] * ct_dict[root / n]
    (3) sum values in dict
    """

    def doit1(self, A):
        A.sort()
        ct_dict = {}
        for root in A:
            ct = 1  # each num in A can build a tree at least.
            for n in ct_dict.keys():
                if root % n == 0 and root / n in ct_dict:
                    ct += ct_dict[n] * ct_dict[root / n]
            ct_dict[root] = ct
        return sum(ct_dict.values()) % (10**9 + 7)


if __name__ == '__main__':

    res = NumFactoredBinaryTrees().doit(A=[2, 4])  # 3

    res = NumFactoredBinaryTrees().doit(A=[2, 4, 5, 10])  # 7

    res = NumFactoredBinaryTrees().doit([45, 42, 2, 18, 23, 1170, 12, 41, 40, 9, 47, 24, 33, 28, 10, 32, 29, 17, 46, 11,
                                         759, 37, 6, 26, 21, 49, 31, 14, 19, 8, 13, 7, 27, 22, 3, 36, 34, 38, 39, 30, 43, 15, 4, 16, 35, 25, 20, 44, 5, 48])

    pass
