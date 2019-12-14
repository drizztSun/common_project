# 756. Pyramid Transition Matrix

# We are stacking blocks to form a pyramid. Each block has a color which is a one letter string.

# We are allowed to place any color block C on top of two adjacent blocks of colors A and B, if and only if ABC is an allowed triple.

# We start with a bottom row of bottom, represented as a single string. We also start with a list of allowed triples allowed. Each allowed triple is represented as a string of length 3.

# Return true if we can build the pyramid all the way to the top, otherwise false.


# Example 1:
# Input: bottom = "BCD", allowed = ["BCG", "CDE", "GEA", "FFF"]
# Output: true
# Explanation:
# We can stack the pyramid like this:
#     A
#    / \
#   G   E
#  / \ / \
# B   C   D

# We are allowed to place G on top of B and C because BCG is an allowed triple.  Similarly, we can place E on top of C and D, then A on top of G and E.

# Example 2:

# Input: bottom = "AABA", allowed = ["AAA", "AAB", "ABA", "ABB", "BAC"]
# Output: false
# Explanation:
# We can't stack the pyramid to the top.
# Note that there could be allowed triples (A, B, C) and (A, B, D) with C != D.

from collections import defaultdict
import itertools


class PyramidTransition:

    def doit5(self, bottom, allowed):

        chars, allowed = 'ABCDEFG', set(allowed)

        def dfs(r, q, i):
            if len(r) == 1:
                return True

            for c in chars:
                if r[i:i+2]+c in allowed and (i == len(r)-2 and dfs(q+c, "", 0) or dfs(r, q+c, i+1)):
                    return True
            return False
        return dfs(bottom, "", 0)

    def doit3(self, bottom, allowed):
        f = collections.defaultdict(lambda: defaultdict(list))
        for a, b, c in allowed:
            f[a][b].append(c)

        def helper(bottom):
            return len(bottom) == 1 or any(helper(i) for i in itertools.product(*(f[a][b] for a, b in zip(bottom, bottom[1:]))))

        return helper(bottom)

    def doit2(self, bottom, allowed):
        f = defaultdict(lambda: defaultdict(list))
        for a, b, c in allowed:
            f[a][b].append(c)

        def helper(bottom):
            if len(bottom) == 1:
                return True

            for i in itertools.product(*(f[a][b] for a, b in zip(bottom, bottom[1:]))):
                if helper(i):
                    return True

            return False

        return helper(bottom)

    def doit1(self, bottom, allowed):
        current = [set(c) for c in bottom]
        while len(current) > 1:
            current = [set(a[2] for a in allowed if a[0] in left and a[1] in right)
                       for left, right in zip(current[:-1], current[1:])]
        return current[0]

    def doit(self, bottom, allowed):

        colors_group = {}
        for c in allowed:
            if c[:2] not in colors_group:
                colors_group[c[:2]] = [c[2]]
            else:
                colors_group[c[:2]].append(c[2])

        def helper(s):
            if len(s) == 1:
                return True

            cur = []
            for i in range(len(s) - 1):

                if s[i:i+2] not in colors_group:
                    return False

                cur = [v + c for v in cur or ['']
                       for c in colors_group[s[i:i+2]]]

            for c in cur:
                if helper(c):
                    return True

            return False

        return helper(bottom)


if __name__ == "__main__":

    res = PyramidTransition().doit("BCD", ["BCG", "CDE", "GEA", "FFF"])

    res = PyramidTransition().doit("CCC", ["CBB", "ACB", "ABD", "CDB", "BDC", "CBC", "DBA",
                                           "DBB", "CAB", "BCB", "BCC", "BAA", "CCD", "BDD", "DDD", "CCA", "CAA", "CCC", "CCB"])

    pass
