# 1033. Moving Stones Until Consecutive

# Three stones are on a number line at positions a, b, and c.

# Each turn, you pick up a stone at an endpoint (ie., either the lowest or highest position stone), and move it to an unoccupied position between those endpoints.  Formally, let's say the stones are currently at positions x, y, z with x < y < z.  You pick up the stone at either position x or position z, and move that stone to an integer position k, with x < k < z and k != y.

# The game ends when you cannot make any more moves, ie. the stones are in consecutive positions.

# When the game ends, what is the minimum and maximum number of moves that you could have made?
# Return the answer as an length 2 array: answer = [minimum_moves, maximum_moves]


# Example 1:

# Input: a = 1, b = 2, c = 5
# Output: [1,2]
# Explanation: Move the stone from 5 to 3, or move the stone from 5 to 4 to 3.

# Example 2:

# Input: a = 4, b = 3, c = 2
# Output: [0,0]
# Explanation: We cannot make any moves.

# Example 3:

# Input: a = 3, b = 5, c = 1
# Output: [1,2]
# Explanation: Move the stone from 1 to 4; or move the stone from 1 to 2 to 4.


class NumMovesStones:

    def doit(self, a, b, c):

        pos = sorted([a, b, c])
        pab = pos[1] - pos[0]
        pbc = pos[2] - pos[1]

        if pab == 1 and pbc == 1:
            return [0, 0]

        if pab == 1 or pbc == 1:
            return [1, pab + pbc - 2]
        elif pab == 2 or pbc == 2:
            return [1, pab + pbc - 2]
        else:
            return [2, pab + pbc - 2]

    def doit(self, a: int, b: int, c: int):
        '''
        Input: original index of three stones
        Output: (min_moves, max_mvoes) to make three stones consecutive
        '''

        original_place = sorted([a, b, c])
        # Denote sorted index as A, B, C

        min_move, max_move = 0, 0
        gap_AB = (original_place[1]-original_place[0]-1)
        gap_BC = (original_place[2]-original_place[1]-1)

        if (not gap_AB) and (not gap_BC):
            # ABC
            #min_move, max_move = 0, 0
            return [min_move, max_move]

        if (not gap_AB) or (not gap_BC):
                        # AB_..._C or A_..._BC
            min_move = 1
            max_move = gap_AB + gap_BC

            return [min_move, max_move]

        else:

            if (gap_AB == 1) or (gap_BC == 1):
                # A_B_..._C or A_..._B_C
                min_move = 1
                max_move = gap_AB + gap_BC

            else:
                                # A_..._B_..._C
                min_move = 2
                max_move = gap_AB + gap_BC

            return [min_move, max_move]


if __name__ == '__main__':

    res = NumMovesStones().doit(a=1, b=2, c=5)

    res = NumMovesStones().doit(a=4, b=3, c=2)

    res = NumMovesStones().doit(a=3, b=5, c=1)
