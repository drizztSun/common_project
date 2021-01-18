"""
688. Knight Probability in Chessboard




On an NxN chessboard, a knight starts at the r-th row and c-th column and attempts to make exactly K moves. The rows and columns are 0 indexed, so the top-left square is (0, 0), and the bottom-right square is (N-1, N-1).

A chess knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.

 



 

Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if the piece would go off the chessboard) and moves there.

The knight continues moving until it has made exactly K moves or has moved off the chessboard. Return the probability that the knight remains on the board after it has stopped moving.

 

Example:

Input: 3, 2, 0, 0
Output: 0.0625
Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
From each of those positions, there are also two moves that will keep the knight on the board.
The total probability the knight stays on the board is 0.0625.
 

Note:

N will be between 1 and 25.
K will be between 0 and 100.
The knight always initially starts on the board.

"""



class KnightProbability:


    """
        Approach #1: Dynamic Programming [Accepted]
        Intuition and Algorithm

        Let f[r][c][steps] be the probability of being on square (r, c) after steps steps. Based on how a knight moves, we have the following recursion:

        f[r][c][steps] = \sum_{dr, dc} f[r+dr][c+dc][steps-1] / 8.0f[r][c][steps]=∑ 
        dr,dc
        ​	
        f[r+dr][c+dc][steps−1]/8.0

        where the sum is taken over the eight (dr, dc)(dr,dc) pairs (2, 1),(2,1), (2, -1),(2,−1), (-2, 1),(−2,1), (-2, -1),(−2,−1), (1, 2),(1,2), (1, -2),(1,−2), (-1, 2),(−1,2), (-1, -2)(−1,−2).

        Instead of using a three-dimensional array f, we will use two two-dimensional ones dp and dp2, storing the result of the two most recent layers we are working on. dp2 will represent f[][][steps], and dp will represent f[][][steps-1].

        Complexity Analysis

        Time Complexity: O(N^2 K) where N, KN,K are defined as in the problem. We do O(1)O(1) work on each layer dp of N^2 elements, and there are KK layers considered.

        Space Complexity: O(N^2), the size of dp and dp2.

    """
    def doit_dp(self, N: int, K: int, r: int, c: int) -> float:

        dp = [[0 for _ in range(N)] for _ in range(N)]
        dp[r][c] = 1
        
        for _ in range(K):

            dp2 = [[0 for _ in range(N)] for _ in range(N)]

            for i in range(N):
                for j in range(N):
                    for delx, dely in ((2, 1), (2, -1), (-2, 1), (-2, -1), (1, 2), (1, -2), (-1, 2), (-1, -2)):
                        x, y = i + delx, j + dely
                        if 0 <= x < N and 0 <= y < N:
                            dp2[i][j] += dp[x][y] / 8.0

            dp = dp2

        return sum(map(sum, dp))





        