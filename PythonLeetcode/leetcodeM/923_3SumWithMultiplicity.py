# 923. 3Sum With Multiplicity

# Given an integer array A, and an integer target, return the number of tuples i, j, k  such that i < j < k and A[i] + A[j] + A[k] == target.

# As the answer can be very large, return it modulo 10^9 + 7.


# Example 1:

# Input: A = [1,1,2,2,3,3,4,4,5,5], target = 8
# Output: 20
# Explanation:
# Enumerating by the values (A[i], A[j], A[k]):
# (1, 2, 5) occurs 8 times;
# (1, 3, 4) occurs 8 times;
# (2, 2, 4) occurs 2 times;
# (2, 3, 3) occurs 2 times.

# Example 2:

# Input: A = [1,1,2,2,2,2], target = 5
# Output: 12
# Explanation:
# A[i] = 1, A[j] = A[k] = 2 occurs 12 times:
# We choose one 1 from [1,1] in 2 ways,
# and two 2s from [2,2,2,2] in 6 ways.


# Note:

# 3 <= A.length <= 3000
# 0 <= A[i] <= 100
# 0 <= target <= 300


class ThreeSumMulti:

    """
    Approach 1: Three Pointer
    Intuition and Algorithm

    Sort the array. For each i, set T = target - A[i], the remaining target. We can try using a two-pointer technique to find A[j] + A[k] == T. This approach is the natural continuation of trying to make the two-pointer technique we know from previous problems, work on this problem.

    Because some elements are duplicated, we have to be careful. In a typical case, the target is say, 8, and we have a remaining array (A[i+1:]) of [2,2,2,2,3,3,4,4,4,5,5,5,6,6]. We can analyze this situation with cases.

    Whenever A[j] + A[k] == T, we should count the multiplicity of A[j] and A[k]. In this example, if A[j] == 2 and A[k] == 6, the multiplicities are 4 and 2, and the total number of pairs is 4 * 2 = 8. We then move to the remaining window A[j:k+1] of [3,3,4,4,4,5,5,5].

    As a special case, if A[j] == A[k], then our manner of counting would be incorrect. If for example the remaining window is [4,4,4], there are only 3 such pairs.

    In general, when A[j] == A[k], we have M ∗ (M−1) // 2 pairs (j,k) (with j < k) that satisfy A[j] + A[k] == T, where M is the multiplicity of A[j] (in this case M=3M=3).

    For more details, please see the inline comments.

    Complexity Analysis

    Time Complexity: O(N^2), where N is the length of A.

    Space Complexity: O(1).

    """
    # O(n^2)

    def doit(self, A, target):
        MOD = 10 ** 9 + 7
        A.sort()
        ans = 0

        for i in range(len(A)):

            T = target - A[i]
            j, k = i + 1, len(A) - 1

            while j < k:

                if A[j] + A[k] < T:
                    j += 1
                elif A[j] + A[k] > T:
                    k -= 1
                elif A[j] != A[k]:

                    n1 = j
                    while j < k and A[j] == A[n1]:
                        j += 1
                    n1 = j - n1

                    n2 = k
                    while k >= j and A[k] == A[n2]:
                        k -= 1
                    n2 = n2 - k

                    ans += n1 * n2
                    ans %= MOD

                else:

                    ans += (k - j + 1) * (k - j) // 2
                    ans %= MOD
                    break

        return ans

    """
    Approach 2: Counting with Cases
    Intuition and Algorithm

    Let count[x] be the number of times that x occurs in A. For every x+y+z == target, we can try to count the correct contribution to the answer. There are a few cases:

    If x, y, and z are all different, then the contribution is count[x] * count[y] * count[z].

    If x == y != z, the contribution is \binom{\text{count[x]}}{2} * \text{count[z]}(
    2
    count[x]
    ​
    )∗count[z].

    If x != y == z, the contribution is \text{count[x]} * \binom{\text{count[y]}}{2}count[x]∗(
    2
    count[y]
    ​
    ).

    If x == y == z, the contribution is \binom{\text{count[x]}}{3}(
    3
    count[x]
    ​	
    ).

    (Here, \binom{n}{k}(
    k
    n
    ​
    ) denotes the binomial coefficient \frac{n!}{(n-k)!k!}
    (n−k)!k!
    n!
    ​
    .)

    Each case is commented in the implementations below.

    Complexity Analysis

    Time Complexity: O(N + W^2)O(N+W
    2
    ), where NN is the length of A, and WW is the maximum possible value of A[i]. (Note that this solution can be adapted to be O(N^2)O(N 
    2
    ) even in the case that WW is very large.)

    Space Complexity: O(W).
    """

    def doit(self, A, target):
        MOD = 10**9 + 7
        count = [0] * 101
        for x in A:
            count[x] += 1

        ans = 0

        # All different
        for x in range(101):
            for y in range(x+1, 101):
                z = target - x - y
                if y < z <= 100:
                    ans += count[x] * count[y] * count[z]
                    ans %= MOD

        # x == y
        for x in range(101):
            z = target - 2*x
            if x < z <= 100:
                ans += count[x] * (count[x] - 1) // 2 * count[z]
                ans %= MOD

        # y == z
        for x in range(101):
            if (target - x) % 2 == 0:
                y = (target - x) // 2
                if x < y <= 100:
                    ans += count[x] * count[y] * (count[y] - 1) // 2
                    ans %= MOD

        # x == y == z
        if target % 3 == 0:
            x = target // 3
            if 0 <= x <= 100:
                ans += count[x] * (count[x] - 1) * (count[x] - 2) // 6
                ans %= MOD

        return ans

    def doit1(self, A, target):

        cnt = {}
        for c in A:
            cnt[c] = cnt.get(c, 0) + 1

        ans = 0
        MOD = 10 ** 9 + 7
        keys = sorted(cnt.keys())

        # x,y,z
        for i in range(len(keys)):
            for j in range(i+1, len(keys)):
                z = target - keys[i] - keys[j]
                if z in cnt and z > keys[j]:
                    ans += cnt[z] * cnt[keys[i]] * cnt[keys[j]]
                    ans %= MOD
        # x==y, z
        for c in keys:
            z = target - 2 * c
            if z in cnt and c < z:
                ans += cnt[c] * (cnt[c] - 1) * cnt[z] // 2
                ans %= MOD
        # x, y == z
        for c in keys:
            if (target - c) % 2 == 0:
                y = (target - c) // 2
                if y in cnt and c < y:
                    ans += cnt[c] * cnt[y] * (cnt[y] - 1) // 2
                    ans %= MOD
        # x == y == z
        if target % 3 == 0:
            x == target // 3
            if x in cnt:
                ans += cnt[x] * (cnt[x] - 1) * (cnt[x] - 2) // 6
                ans %= MOD

        return ans


if __name__ == '__main__':

    res = ThreeSumMulti().doit(A=[1, 1, 2, 2, 3, 3, 4, 4, 5, 5], target=8)

    res = ThreeSumMulti().doit1(A=[1, 1, 2, 2, 2, 2], target=5)

    pass
