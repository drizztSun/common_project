"""
1411. Number of Ways to Paint N × 3 Grid

You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colours:
Red, Yellow or Green while making sure that no two adjacent cells have the same colour (i.e no two cells that share vertical or horizontal sides have the same colour).

You are given n the number of rows of the grid.

Return the number of ways you can paint this grid. As the answer may grow large, the answer must be computed modulo 10^9 + 7.



Example 1:

Input: n = 1
Output: 12
Explanation: There are 12 possible way to paint the grid as shown:

Example 2:

Input: n = 2
Output: 54
Example 3:

Input: n = 3
Output: 246
Example 4:

Input: n = 7
Output: 106494
Example 5:

Input: n = 5000
Output: 30228214


Constraints:

n == grid.length
grid[i].length == 3
1 <= n <= 5000

"""


class NumOfWays:

    """
        i-1, 2 colors,   3 colors
         i,   2 colors,   3 colors

         ABA(2 colors) => CAC, BCB, BAB (2 colors) or BAC, CAB (3 colors)

         ABC(3 colors) => BAB, BCB, (2 colors) or BCA, CAB (3 colors)

         dp2[i] = 2 * dp3[i-1] + 3 * dp2[i-1]
         dp3[i] = 2 * dp2[i-1] + 2 * dp3[i-1]

    O(n)
    """
    def doit_dp(self, n: int) -> int:
        M = 10 ** 9 + 7
        color2, color3 = 6, 6

        for _ in range(1, n):
            last2, last3 = color2, color3
            color2, color3 = (3 * last2 + 2 * last3) % M, (2 * last2 + 2 * last3) % M;

        return (color2 + color3) % M

    """
    
    O( log(n) )
    
    Transform below
         dp2[i] = 3 * dp2[i-1] + 2 * dp3[i-1]
         dp3[i] = 2 * dp2[i-1] + 2 * dp3[i-1]
         
    into matrix multiple ops: vector V {dp2, dp3} * { {3, 2} {2, 2} }
         
    We can see the colors ways between i-1, and i can be described as Matrix ops
    
    { X2[i], X3[i] } = {x2[i-1], x3[i-2]} * { {3, 2, {2, 2} }
         
    """
    def doit_dp_fastpower(self, n: int) -> int:

        def multiply(A, B):
            m, n, p = len(A), len(B), len(B[0])
            C = [[0 for _ in range(p)] for _ in range(m)]

            for i in range(m):
                for j in range(p):
                    for k in range(n):
                        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % kMod
            return C

        n -= 1
        ans = [[6, 6]]
        base = [[3, 2], [2, 2]]
        kMod = 10 ** 9 + 7

        while n > 0:

            if n % 2 == 1:
                ans = multiply(ans, base)
            base = multiply(base, base)
            n >>= 1

        return (ans[0][0] + ans[0][1]) % kMod


if __name__ == '__main__':

    NumOfWays().doit_dp_fastpower(1)

    NumOfWays().doit_dp_fastpower(2)

    NumOfWays().doit_dp_fastpower(3)