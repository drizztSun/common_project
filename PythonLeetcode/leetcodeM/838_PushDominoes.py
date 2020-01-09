# 838. Push Dominoes

# There are N dominoes in a line, and we place each domino vertically upright.

# In the beginning, we simultaneously push some of the dominoes either to the left or to the right.

# After each second, each domino that is falling to the left pushes the adjacent domino on the left.

# Similarly, the dominoes falling to the right push their adjacent dominoes standing on the right.

# When a vertical domino has dominoes falling on it from both sides, it stays still due to the balance of the forces.

# For the purposes of this question, we will consider that a falling domino expends no additional force to a falling or already fallen domino.

# Given a string "S" representing the initial state. S[i] = 'L', if the i-th domino has been pushed to the left; S[i] = 'R',

# if the i-th domino has been pushed to the right; S[i] = '.', if the i-th domino has not been pushed.

# Return a string representing the final state.

# Example 1:
# Input: ".L.R...LR..L.."
# Output: "LL.RR.LLRRLL.."

# Example 2:
# Input: "RR.L"
# Output: "RR.L"

# Explanation: The first domino expends no additional force on the second domino.
# Note:

# 0 <= N <= 10^5
# String dominoes contains only 'L', 'R' and '.'


class PushDominoes:

    def doit(self, dominos):
        N = len(dominos)

        left = [0] * N
        for i in range(N-1, -1, -1):
            if dominos[i] == 'L':
                left[i] = 0
            elif dominos[i] == 'R':
                left[i] = N
            else:
                left[i] = 0 if i == N-1 else (left[i+1] - 1)

        right = [0] * N
        for i in range(1, N):
            right[i] = (right[i-1] or dominos[i-1]
                        == 'R') and dominos[i] != 'L'

        ans = ''
        for i in range(N):
            if left[i] and right[i]:
                ans += dominos[i]
            elif left[i] and dominos[i] != 'R':
                ans += 'L'
            elif right[i] and dominos[i] != 'L':
                ans += 'R'
            else:
                ans += dominos[i]

        return ans

    """
    Approach #1: Adjacent Symbols [Accepted]
    Intuition

    Between every group of vertical dominoes ('.'), we have up to two non-vertical dominoes bordering this group. Since additional dominoes outside this group do not affect the outcome, we can analyze these situations individually: there are 9 of them (as the border could be empty). Actually, if we border the dominoes by 'L' and 'R', there are only 4 cases. We'll write new letters between these symbols depending on each case.

    Algorithm

    Continuing our explanation, we analyze cases:

    If we have say "A....B", where A = B, then we should write "AAAAAA".

    If we have "R....L", then we will write "RRRLLL", or "RRR.LLL" if we have an odd number of dots. If the initial symbols are at positions i and j, we can check our distance k-i and j-k to decide at position k whether to write 'L', 'R', or '.'.

    (If we have "L....R" we don't do anything. We can skip this case.)

    """

    def doit(self, dominoes):
        symbols = [(i, x) for i, x in enumerate(dominoes) if x != '.']
        symbols = [(-1, 'L')] + symbols + [(len(dominoes), 'R')]

        ans = list(dominoes)
        for (i, x), (j, y) in zip(symbols, symbols[1:]):
            if x == y:
                for k in range(i+1, j):
                    ans[k] = x
            elif x > y:  # RL
                for k in range(i+1, j):
                    ans[k] = '.LR'[cmp(k-i, j-k)]

        return "".join(ans)

    """
    Approach #2: Calculate Force [Accepted]
    Intuition

    We can calculate the net force applied on every domino.
    The forces we care about are how close a domino is to a leftward 'R', and to a rightward 'L': the closer we are, the stronger the force.

    Algorithm

    Scanning from left to right, our force decays by 1 every iteration, and resets to N if we meet an 'R',
    so that force[i] is higher (than force[j]) if and only if dominoes[i] is closer (looking leftward) to 'R' (than dominoes[j]).

    Similarly, scanning from right to left, we can find the force going rightward (closeness to 'L').

    For some domino answer[i], if the forces are equal, then the answer is '.'. Otherwise, the answer is implied by whichever force is stronger.

    Example

    Here is a worked example on the string S = 'R.R...L': We find the force going from left to right is [7, 6, 7, 6, 5, 4, 0].
    The force going from right to left is [0, 0, 0, -4, -5, -6, -7].
    Combining them (taking their vector addition), the combined force is [7, 6, 7, 2, 0, -2, -7], for a final answer of RRRR.LL.
    """

    def doit(self, dominoes):

        N = len(dominoes)
        force = [0] * N

        # Populate forces going from left to right
        f = 0
        for i in range(N):
            if dominoes[i] == 'R':
                f = N
            elif dominoes[i] == 'L':
                f = 0
            else:
                f = max(f-1, 0)
            force[i] += f

        # Populate forces going from right to left
        f = 0
        for i in range(N-1, -1, -1):
            if dominoes[i] == 'L':
                f = N
            elif dominoes[i] == 'R':
                f = 0
            else:
                f = max(f-1, 0)
            force[i] -= f

        return "".join('.' if f == 0 else 'R' if f > 0 else 'L'
                       for f in force)


if __name__ == '__main__':

    res = PushDominoes().doit1(".L.R...LR..L..")  # "LL.RR.LLRRLL.."

    res = PushDominoes().doit1("RR.L")  # "RR.L"

    res = PushDominoes().doit1("RL")  # "RL"

    pass
