"""

 1444. Number of Ways of Cutting a Pizza


 Given a rectangular pizza represented as a rows x cols matrix containing the following characters: 'A' (an apple) and '.' (empty cell) and given the integer k. You have to cut the pizza into k pieces using k-1 cuts.

 For each cut you choose the direction: vertical or horizontal, then you choose a cut position at the cell boundary and cut the pizza into two pieces.
 If you cut the pizza vertically, give the left part of the pizza to a person. If you cut the pizza horizontally, give the upper part of the pizza to a person. Give the last piece of pizza to the last person.

 Return the number of ways of cutting the pizza such that each piece contains at least one apple. Since the answer can be a huge number, return this modulo 10^9 + 7.



 Example 1:

 Input: pizza = ["A..","AAA","..."], k = 3
 Output: 3
 Explanation: The figure above shows the three ways to cut the pizza. Note that pieces must contain at least one apple.
 Example 2:

 Input: pizza = ["A..","AA.","..."], k = 3
 Output: 1
 Example 3:

 Input: pizza = ["A..","A..","..."], k = 1
 Output: 1


 Constraints:

 1 <= rows, cols <= 50
 rows == pizza.length
 cols == pizza[i].length
 1 <= k <= 10
 pizza consists of characters 'A' and '.' only.



"""


class NumberOfWaysOfCuttingPizza:

    def doit_dp(self, pizza: list, k: int) -> int:

        from functools import lru_cache

        M, N = len(pizza), len(pizza[0])
        kMod = 1e9 + 7
        apples = [[0 for _ in range(N+1)] for _ in range(M+1)]

        for i in range(M):
            for j in range(N):
                apples[i+1][j+1] = int(pizza[i][j] == 'A') + apples[i][j+1] + apples[i+1][j] - apples[i][j]

        def hasapples(m1, n1, m2, n2):
            return (apples[m2+1][n2+1] - apples[m2+1][n1] - apples[m1][n2+1] + apples[m1][n1]) > 0

        @lru_cache(None)
        def search(m, n, k):

            if k == 0:
                return hasapples(m, n, M-1, N-1)

            ans = 0
            # cut horizontal
            for y in range(m, M-1):
                ans = (ans + hasapples(m, n, y, N-1) * search(y+1, n, k-1)) % kMod

            # cut vertically
            for x in range(n, N-1):
                ans = (ans + hasapples(m, n, M-1, x) * search(m, x+1, k-1)) % kMod

            return ans

        return int(search(0, 0, k-1))


if __name__ == '__main__':

    NumberOfWaysOfCuttingPizza().doit_dp(pizza = ["A..","AAA","..."], k = 3)

    NumberOfWaysOfCuttingPizza().doit_dp(pizza = ["A..","AA.","..."], k = 3)