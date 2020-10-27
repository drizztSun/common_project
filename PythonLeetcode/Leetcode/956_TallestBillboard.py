# 956. Tallest Billboard

# You are installing a billboard and want it to have the largest height.
# The billboard will have two steel supports, one on each side.  Each steel support must be an equal height.

# You have a collection of rods which can be welded together.
# For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.

# Return the largest possible height of your billboard installation.  If you cannot support the billboard, return 0.


# Example 1:

# Input: [1, 2, 3, 6]
# Output: 6
# Explanation: We have two disjoint subsets {1, 2, 3} and {6}, which have the same sum = 6.

# Example 2:

# Input: [1, 2, 3, 4, 5, 6]
# Output: 10
# Explanation: We have two disjoint subsets {2, 3, 5} and {4, 6}, which have the same sum = 10.

# Example 3:

# Input: [1, 2]
# Output: 0
# Explanation: The billboard cannot be supported, so we return 0.

class TallestBillboard:

    '''
    The problem is to divide the numbers into two groups, naming as left and right groups, and make sure their totals are equal.
    Also, make their total as large as possible.

    Apply DP to solve this problem.
    For each rod, there are three choices: give it to left; give it to right; discard it.
    Let DP[w,i] = h, which means:

    after examing the ith rod;
    sum(left) - sum(right) == w;
    maximal of sum(left) is h, with sum(left) - sum(right) == w

    Taking [1,2,3] as example:
    rod left_sum right_sum DP
    1       1         0    DP[1,1] = 1 (add 1 to left)
            0         0    DP[0,1] = 0 (discard)
            0         1    DP[-1,1] = 0 (add 1 to right)
    2       3         0    DP[3,2] = 3 (add 2 to left)
            2         0    DP[2,2] = 2 (add 2 to left)
            2         1    DP[1,2] = 2 (add 2 to left)
            1         0    DP[1,2] = 1 (discard)
            0         0    DP[0,2] = 0 (discard)
            0         1    DP[-1,2] = 0 (discard)
            1         2    DP[-1,2] = 1 (add 2 to right)
            0         2    DP[-2,2] = 0 (add 2 to right)
            0         3    DP[-3,2] = 0 (add 2 to right)
    Note: we need merge duplicate DP[-1,2] and DP[1,2] with max value, so DP[-1,2] = 1 and DP[1,2] = 2
    3       6         0    DP[6,3] = 6 (add 3 to left)
            5         0    DP[5,3] = 5 (add 3 to left)
            5         1    DP[4,3] = 4 (add 3 to left)
            4         0    DP[4,3] = 4 (add 3 to left)
            3         0    DP[3,3] = 3 (add 3 to left)
            3         1    DP[2,3] = 3 (add 3 to left)
            4         2    DP[2,3] = 4 (add 3 to left)
            3         2    DP[1,2] = 3 (add 3 to left)
            3         3    DP[0,3] = 3 (add 3 to left) <- this is the answer for [1,2,3]
                        ..........
    Since we need make sure both group has the same sum, it's also to use the right group's sum in the DP function.
    return DP[0, len(rods)] as result.
    Because DP[w,i] only depends on DP[w, i-1], we can reuse a DP dict to store previous DP values.
    And don't forget to use max() to make sure DP[w,i] has the max height of left group among many cases with the same w.
    Time: O(3**N)
    Space: O(3**N)
    '''

    def doit(self, rods):
    
        # key is difference of left - right, value is left side total
        DP = {0: 0}

        for r in rods:

            newDP = {}

            for k, v in DP.items():

                # Add rod r to left group. Before that left group height is v, sum(left) - sum(right) = k
                # Now height is v + r, sum(left) - sum(right) = k + r

                newDP[k+r] = max(newDP.get(k+r, 0), v+r)

                # Discard rod r, left group height or sum(left) - sum(right) won't change
                newDP[k] = max(newDP.get(k, 0), v)

                # Add rod r to right group. Before that left group height is v, sum(left) - sum(right) = k
                # Left group height is still v, sum(left) - sum(right) = k - r
                newDP[k-r] = max(newDP.get(k-r, 0), v)

            DP = newDP

        return DP[0]

    '''
    Inspired by solution of votrubac's, DFS + Memo is easier to understand than DP.
    Remember the current difference of left and right legs. In each iteration, the rod can be

    added to the longer side (diff + rod)
    added to the shorter side (|diff - rod|)
    Not use it (diff)

    Any case, no need to consider exact value of left and right leg.
    Only need to remember their diff and pass it to the next iteration.
    When adding to shorter side, the return value should be increased by the difference covered by such action.
    '''

    def doit(self, rods):
        import functools

        @functools.lru_cache(None)
        def dfs(i, diff):
            if i >= len(rods):
                return -math.inf if diff else 0

            add_to_long = dfs(i+1, diff + rods[i])

            add_to_short = dfs(i+1, abs(diff - rods[i])) + min(diff, rods[i])

            drop_it = dfs(i+1, diff)

            return max(add_to_long, add_to_short, drop_it)

        return dfs(0, 0)

    def doit(self, rods):
        import itertools
        rods.sort(reverse=True)
        for l in range(len(rods), 1, -1):
            for comb in itertools.combinations(rods, l):
                s = sum(comb)
                if s % 2 == 0:
                    s //= 2
                    X = set([s])
                    for x in comb:
                        print(X)
                        if x in X:
                            return s
                        else:
                            Y = [y - x for y in X if y > x]
                            X.update(Y)
        return 0


if __name__ == '__main__':

    res = TallestBillboard().doit([1, 2, 3, 6])

    res = TallestBillboard().doit([1, 2, 3, 4, 5, 6])

    res = TallestBillboard().doit([1, 2])

    pass
