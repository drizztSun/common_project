# 957. Prison Cells After N Days

# There are 8 prison cells in a row, and each cell is either occupied or vacant.

# Each day, whether the cell is occupied or vacant changes according to the following rules:

# If a cell has two adjacent neighbors that are both occupied or both vacant, then the cell becomes occupied.
# Otherwise, it becomes vacant.
# (Note that because the prison is a row, the first and the last cells in the row can't have two adjacent neighbors.)

# We describe the current state of the prison in the following way: cells[i] == 1 if the i-th cell is occupied, else cells[i] == 0.

# Given the initial state of the prison, return the state of the prison after N days (and N such changes described above.)


# Example 1:

# Input: cells = [0,1,0,1,1,0,0,1], N = 7
# Output: [0,0,1,1,0,0,0,0]
# Explanation:
# The following table summarizes the state of the prison on each day:
# Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
# Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
# Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
# Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
# Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
# Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
# Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
# Day 7: [0, 0, 1, 1, 0, 0, 0, 0]
# Day 8: [0, 0, 0, 0, 0, 1, 1, 0]


# Example 2:

# Input: cells = [1,0,0,1,0,0,1,0], N = 1000000000
# Output: [0,0,1,1,1,1,1,0]


class PrisonAfterNDays:

    """
    Approach 1: Simulation
    Intuition

    We simulate each day of the prison.

    Because there are at most 256 possible states for the prison, eventually the states repeat into a cycle rather quickly.
    We can keep track of when the states repeat to find the period t of this cycle, and skip days in multiples of t.

    Algorithm

    Let's do a naive simulation, iterating one day at a time. For each day, we will decrement N, the number of days remaining,
    and transform the state of the prison forward (state -> nextDay(state)).

    If we reach a state we have seen before, we know how many days ago it occurred, say t.
    Then, because of this cycle, we can do N %= t. This ensures that our algorithm only needs O(2**{\text{cells.length}})O(2∗∗cells.length) steps.

    Complexity Analysis

    Time Complexity: O(2^N) where NN is the number of cells in the prison.

    Space Complexity: O(2^N * N).
    """

    def doit(self, cells, N):

        def next_cell(cells):
            return [int(i > 1 and i < 7 and cell[i-1] == cell[i+1]) for i in range(8)]

        seen = {}
        while n > 0:

            c = tuple(cells)

            if c in seen:
                N %= seen[c] - N

            seen[N] = c

            if N >= 1:
                N -= 1
                cells = next_cell(cells)

        return cells


if __name__ == '__main__':

    res = PrisonAfterNDays().doit(cells=[0, 1, 0, 1, 1, 0, 0, 1], N=7)

    res = PrisonAfterNDays().doit(cells=[1, 0, 0, 1, 0, 0, 1, 0], N=1000000000)

    pass
