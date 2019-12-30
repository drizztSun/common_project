# 799. Champagne Tower

# We stack glasses in a pyramid, where the first row has 1 glass, the second row has 2 glasses, and so on until the 100th row.
# Each glass holds one cup (250ml) of champagne.

# Then, some champagne is poured in the first glass at the top.
# When the top most glass is full, any excess liquid poured will fall equally to the glass immediately to the left and right of it.
# When those glasses become full, any excess champagne will fall equally to the left and right of those glasses, and so on.
# (A glass at the bottom row has it's excess champagne fall on the floor.)

# For example, after one cup of champagne is poured, the top most glass is full.
# After two cups of champagne are poured, the two glasses on the second row are half full.
# After three cups of champagne are poured, those two cups become full - there are 3 full glasses total now.
# After four cups of champagne are poured, the third row has the middle glass half full, and the two outside glasses are a quarter full, as pictured below.


# Now after pouring some non-negative integer cups of champagne, return how full the j-th glass in the i-th row is (both i and j are 0 indexed.)

# Example 1:
# Input: poured = 1, query_glass = 1, query_row = 1
# Output: 0.0
# Explanation: We poured 1 cup of champange to the top glass of the tower (which is indexed as (0, 0)).
# There will be no excess liquid so all the glasses under the top glass will remain empty.

# Example 2:
# Input: poured = 2, query_glass = 1, query_row = 1
# Output: 0.5
# Explanation: We poured 2 cups of champange to the top glass of the tower (which is indexed as (0, 0)).
# There is one cup of excess liquid. The glass indexed as (1, 0) and the glass indexed as (1, 1) will share the excess liquid equally, and each will get half cup of champange.

class ChampagneTower:

    def doit1(self, poured, query_row, query_glass):

        glasses = [[0 for _ in range(101)] for _ in range(101)]
        glasses[0][0] = poured

        for i in range(100):
            for j in range(101):
                if glasses[i][j] > 1:

                    glasses[i+1][j] += (glasses[i][j] - 1) / 2
                    glasses[i+1][j+1] += (glasses[i][j] - 1) / 2
                    glasses[i][j] = 1

        return glasses[query_row][query_glass]

    def doit(self, poured, query_row, query_glass):
        dp = [poured]
        for i in range(1, query_row + 1):
            ndp = [0.0] * (i+1)
            for j in range(len(dp)):
                if dp[j] > 1.0:
                    v = (dp[j] - 1.0) / 2
                    ndp[j] += v
                    ndp[j+1] += v
            dp = ndp
        return min(1.0, dp[query_glass])

    def doit(self, poured, query_row, query_glass):

        import collections

        def cup_vol(poured, raw, glass):
            if glass < 0 or glass > raw:
                return 0

            if glass == 0 and raw == 0:
                return poured

            if glass not in memo[raw]:

                left = cup_vol(poured, raw - 1, glass-1)
                right = cup_vol(poured, raw-1, glass)

                left = (left - 1) / 2.0 if left > 1 else 0
                right = (right - 1) / 2.0 if right > 1 else 0

                memo[raw][glass] = left + right

            return memo[raw][glass]

        memo = collections.defaultdict(dict)
        res = cup_vol(poured, query_row, query_glass)
        return res if res < 1.0 else 1.0


if __name__ == "__main__":

    res = ChampagneTower().doit1(poured=1, query_glass=1, query_row=1)  # 0.0

    res = ChampagneTower().doit1(poured=2, query_glass=1, query_row=1)  # 0.5

    res = ChampagneTower().doit1(1000000000, 99, 99)

    pass
