"""
1301. Number of Paths with Max Score

You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.

You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either
with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.

Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect,
and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.

In case there is no path, return [0, 0].



Example 1:

Input: board = ["E23","2X2","12S"]
Output: [7,1]
Example 2:

Input: board = ["E12","1X1","21S"]
Output: [4,2]
Example 3:

Input: board = ["E11","XXX","11S"]
Output: [0,0]


Constraints:

2 <= board.length == board[i].length <= 100



"""


class PathsWithMaxScore:

    """
    Solution DP

    Max Score only -> Medium

    dp[i][j] := max score when reach (j, i)
    count[i][j] := path to reach (j, i) with max score

    m = max(dp[i + 1][j], dp[i][j+1], dp[i+1][j+1])
    dp[i][j] = board[i][j] + m

    count[i][j] += count[i+1][j] if dp[i+1][j] == m
    count[i][j] += count[i][j+1] if dp[i][j+1] == m
    count[i][j] += count[i+1][j+1] if dp[i+1][j+1] == m

    Time complexity: O(n^2)
    Space complexity: O(n^2)

    """

    def doit_dp(self, board: list) -> list:

        N = len(board)
        dp = [[0 for _ in range(N+1)] for _ in range(N+1)]
        cc = [[0 for _ in range(N+1)] for _ in range(N+1)]

        hMod = 10**9 + 7
        board[0] = '0' + board[0][1:]
        board[N-1] = board[N-1][0:-1] + '0'
        cc[N-1][N-1] = 1

        for i in range(N-1, -1, -1):
            for j in range(N-1, -1, -1):

                if board[i][j] == 'X':
                    continue

                candidate = max(dp[i+1][j+1], dp[i+1][j], dp[i][j+1])

                if candidate == dp[i+1][j+1]:
                    cc[i][j] = (cc[i][j] + cc[i+1][j+1]) % hMod

                if candidate == dp[i+1][j]:
                    cc[i][j] = (cc[i][j] + cc[i+1][j]) % hMod

                if candidate == dp[i][j+1]:
                    cc[i][j] = (cc[i][j] + cc[i][j+1]) % hMod

                dp[i][j] = candidate + ord(board[i][j]) - ord('0')

        return [dp[0][0], cc[0][0]] if cc[0][0] else [0, 0]


if __name__ == '__main__':

    PathsWithMaxScore().doit_dp(board = ["E11","XXX","11S"])

    PathsWithMaxScore().doit_dp(board = ["E23","2X2","12S"])

