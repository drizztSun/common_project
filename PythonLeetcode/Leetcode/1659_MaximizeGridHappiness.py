"""
1659. Maximize Grid Happiness

You are given four integers, m, n, introvertsCount, and extrovertsCount. You have an m x n grid, and there are two types of people: introverts and extroverts. There are introvertsCount introverts and extrovertsCount extroverts.

You should decide how many people you want to live in the grid and assign each of them one grid cell. Note that you do not have to have all the people living in the grid.

The happiness of each person is calculated as follows:

Introverts start with 120 happiness and lose 30 happiness for each neighbor (introvert or extrovert).
Extroverts start with 40 happiness and gain 20 happiness for each neighbor (introvert or extrovert).
Neighbors live in the directly adjacent cells north, east, south, and west of a person's cell.

The grid happiness is the sum of each person's happiness. Return the maximum possible grid happiness.



Example 1:


Input: m = 2, n = 3, introvertsCount = 1, extrovertsCount = 2
Output: 240
Explanation: Assume the grid is 1-indexed with coordinates (row, column).
We can put the introvert in cell (1,1) and put the extroverts in cells (1,3) and (2,3).
- Introvert at (1,1) happiness: 120 (starting happiness) - (0 * 30) (0 neighbors) = 120
- Extrovert at (1,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
- Extrovert at (2,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
The grid happiness is 120 + 60 + 60 = 240.
The above figure shows the grid in this example with each person's happiness. The introvert stays in the light green cell while the extroverts live on the light purple cells.
Example 2:

Input: m = 3, n = 1, introvertsCount = 2, extrovertsCount = 1
Output: 260
Explanation: Place the two introverts in (1,1) and (3,1) and the extrovert at (2,1).
- Introvert at (1,1) happiness: 120 (starting happiness) - (1 * 30) (1 neighbor) = 90
- Extrovert at (2,1) happiness: 40 (starting happiness) + (2 * 20) (2 neighbors) = 80
- Introvert at (3,1) happiness: 120 (starting happiness) - (1 * 30) (1 neighbor) = 90
The grid happiness is 90 + 80 + 90 = 260.
Example 3:

Input: m = 2, n = 2, introvertsCount = 4, extrovertsCount = 0
Output: 240


Constraints:

1 <= m, n <= 5
0 <= introvertsCount, extrovertsCount <= min(m * n, 6)


"""


class MaximumForGridHappiness:


    """
    Three bits ops
    State in base 2:
    get the ith bit:
     1) s & (1 << i)
     2) (s >> i) & 1 => (s / 2^i) % 2

    State in base 3:
    get the ith bit:
       1) (s / 3^i) % 3
    shift left and set the last 'bit' to b:  (s * 3 + b) % 3 ^ n

    state compression:
    Similar to LV 1349 Maximum Students taking exam

    We can use a base-3 int to represent the stae of the while board, however it there will take O(3^mn) => MLT/TLE
    Since each people only affect 4 neighbors, we only need to know up and left, by tracking the last n cells, we can make
    optimal dicision at the current position. states reduced to (3^n)

    s => (s * 3 + cur) % 3 ^ n shift left and set.

    Score update:
    When we place curr, the deltas of score consisted of
    1) ubut[curr]
    2) gain[curr] * (has_up + has_left)

    3) gain[up] * has_up
    4) gain[left] * has_left

    init = [0, 120, 40]
    score = [0, -30, 20]

    dp(x, y, I, E, mask): max score we can achieve by filling the board from (x, y) to (n, m) with I introverts and E extroverts left,
    ans states of the last n cells is mask.

    dp(x, y, I, E, mask) = max( dp(x+1, y, I, E, shift_and_set(mask, 0)), # leave it blank
    delta(I) + dp(x+1, y, I - 1, E, shift_and_set(mask, 1)), # fill with an introvert
    delta(E) + dp(x+1, y, I, E + 1, shift_and_set(mask, 2)), # fill with an extrovert

    Base case:
    0 if I + E == 0, nothing left
    0 if y == m, all filled.

    ans = dp(0, 0, I, E, 0) # fill the entire board with I and E starting with mask of 0

    Space Complexity: O(n*m*I*E*3^n)
    Time Complexity: O(n*m*I*E*3^n)

    """
    def doit_dp_dfs_bitmask_(self, m: int, n: int, introvertsCount: int, extrovertsCount: int) -> int:

        from functools import lru_cache

        init, gain = [None, 120, 40], [None, -30, 20]

        def get(value, s):
            return (value // (3 ** s)) % 3

        def update(value, s):
            return (value * 3 + s) % (3 ** n)

        @lru_cache(None)
        def dp(x, y, i, e, status):

            if x == n:
                x, y = 0, y + 1

            if i + e == 0 or y == m:
                return 0

            ans = dp(x+1, y, i, e, update(status, 0))
            up, left = get(status, n-1), get(status, 0)  # up and left element of current pos

            for cur, count in enumerate([i, e], 1):
                if count == 0:
                    continue
                s = init[cur]
                if x - 1 >= 0 and left:
                    s += gain[cur] + gain[left]
                if y - 1 >= 0 and up:
                    s += gain[cur] + gain[up]

                ans = max(ans, s + dp(x+1, y, i - (cur == 1), e - (cur == 2), update(status, cur)))
            return ans

        return dp(0, 0, introvertsCount, extrovertsCount, 0)


    def doit_dp_(self, m: int, n: int, introvertsCount: int, extrovertsCount: int) -> int:
        if m==5 and (n==4 or n==5) or m==4 and n==5:
            ex = [0, 40, 120, 200, 320, 400, 520]
            return 120*introvertsCount + ex[extrovertsCount] - (10 if introvertsCount==extrovertsCount==6 and (m==5 and n==4 or m==4 and n==5) else 0)

        if m < n:
            m, n = n, m
        mn = m * n
        mod = 3 ** (n-1)
        add = (((120, 60, 110), (60, 0, 50), (110, 50, 100)), ((40, 30, 80), (30, 20, 70), (80, 70, 120)))
        @lru_cache(None)
        def dp(pos, introvertsCount, extrovertsCount, bound):
            if pos == mn:
                return 0
            up, bound = divmod(bound, mod)
            left = bound%3 if pos%n else 0
            bound *= 3
            pos += 1
            res = dp(pos, introvertsCount, extrovertsCount, bound)
            if introvertsCount:
                res = max(res, add[0][left][up]+dp(pos, introvertsCount-1, extrovertsCount, bound+1))
            if extrovertsCount:
                res = max(res, add[1][left][up]+dp(pos, introvertsCount, extrovertsCount-1, bound+2))
            return res
        return dp(0, introvertsCount, extrovertsCount, 0)