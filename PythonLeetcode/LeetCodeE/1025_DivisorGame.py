# 1025. Divisor Game

# Alice and Bob take turns playing a game, with Alice starting first.

# Initially, there is a number N on the chalkboard.  On each player's turn, that player makes a move consisting of:

# Choosing any x with 0 < x < N and N % x == 0.
# Replacing the number N on the chalkboard with N - x.
# Also, if a player cannot make a move, they lose the game.

# Return True if and only if Alice wins the game, assuming both players play optimally.


# Example 1:

# Input: 2
# Output: true
# Explanation: Alice chooses 1, and Bob has no more moves.

# Example 2:

# Input: 3
# Output: false
# Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.


class DivisorGame:

    def doit(self, N):
        return N % 2 == 0

    def doit(self, N):
        l = [False]*(N+1)
        for i in range(2, N+1):
            t = [l[i-j] for j in range(1, i) if i % j == 0]
            l[i] = not all(t)
        return l[N]


if __name__ == '__main__':

    res = DivisorGame().doit(2)

    res = DivisorGame().doit(3)

    pass
