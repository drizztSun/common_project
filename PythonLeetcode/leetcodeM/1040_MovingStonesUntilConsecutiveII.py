# 1040. Moving Stones Until Consecutive II


# On an infinite number line, the position of the i-th stone is given by stones[i].
# Call a stone an endpoint stone if it has the smallest or largest position.

# Each turn, you pick up an endpoint stone and move it to an unoccupied position so that it is no longer an endpoint stone.

# In particular, if the stones are at say, stones = [1, 2, 5], you cannot move the endpoint stone at position 5,
# since moving it to any position(such as 0, or 3) will still keep that stone as an endpoint stone.

# The game ends when you cannot make any more moves, ie. the stones are in consecutive positions.

# When the game ends, what is the minimum and maximum number of moves that you could have made?
# Return the answer as an length 2 array: answer = [minimum_moves, maximum_moves]


# Example 1:

# Input: [7, 4, 9]
# Output: [1, 2]
# Explanation:
# We can move 4 -> 8 for one move to finish the game.
# Or, we can move 9 -> 5, 4 -> 6 for two moves to finish the game.
# Example 2:

# Input: [6, 5, 4, 3, 10]
# Output: [2, 3]
# We can move 3 -> 8 then 10 -> 7 to finish the game.
# Or, we can move 3 -> 7, 4 -> 8, 5 -> 9 to finish the game.
# Notice we cannot move 10 -> 2 to finish the game, because that would be an illegal move.
# Example 3:

# Input: [100, 101, 104, 102, 103]
# Output: [0, 0]

class NumMovesStonesII:

    """
    For minimum number of moves, the final arrangement will be of the form [a, a+1, a+2, ... a+L-1] for L stones for some 'a'.
    The possible values of 'a' are all the stone positions in the given input array.
    For each possible 'a' check how many positions (from a to a+L-1) already have stones. We need to fill in the missing remaining positions.
    Thus if there are K missing positions we need K moves to fill them. Compute K for each value of 'a' and take their minimum.

    For maximum it is just the sum of the gaps between each stone. But if we take the 1st stone then we cannot count the gaps betwwen 1st and 2nd stone.
    Similarly if we take the last stone then we cannot count the gaps between last and 2nd last stone. Thus we need to take the maximum of these two cases.
    """

    def doit(self, stones):

        stones.sort()

        gaps = [stones[i+1] - stones[i] - 1 for i in range(len(stones)-1)]

        max_cnts = max(sum(c for c in gaps[1:]), sum(c for c in gaps[:-1]))

        min_cnts = float('Inf')
        s, e = 0, 1
        cnts = 1

        while e <= len(stones):

            if e == len(stones) or stones[e] - stones[s] >= len(stones):

                rem = len(stones) - cnts

                if rem != 1 or stones[e-1] - stones[s] == len(stones) - 1:
                    min_cnts = min(min_cnts, rem)

                s += 1
                cnts -= 1

                if e == len(stones):
                    break

            else:

                e += 1
                cnts += 1

        return [min_cnts, max_cnts]

    def doit(self, s):
        s.sort()
        n, i = len(s), 0
        for j in range(n):
            if s[j] - s[i] >= n:
                i += 1

        maxv = s[-1] - s[0] - n - min(s[1] - s[0], s[-1] - s[-2]) + 2
        minv = 2 if i == 1 and s[-1] - s[0] != n and (s[-2] - s[0] == n-2 or s[-1] - s[1] == n-2) else i
        return [minv, maxv]


if __name__ == '__main__':

    res = NumMovesStonesII().doit([7, 4, 9])

    res = NumMovesStonesII().doit([6, 5, 4, 3, 10])

    pass
