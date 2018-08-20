

# 765. Couples Holding Hands

# N couples sit in 2N seats arranged in a row and want to hold hands.
# We want to know the minimum number of swaps so that every couple is sitting side by side.
#
# A swap consists of choosing any two people, then they stand up and switch seats.

# The people and seats are represented by an integer from 0 to 2N-1, the couples are numbered in order,
# the first couple being (0, 1), the second couple being (2, 3), and so on with the last couple being (2N-2, 2N-1).

# The couples' initial seating is given by row[i] being the value of the person
# who is initially sitting in the i-th seat.

# Example 1:

# Input: row = [0, 2, 1, 3]
# Output: 1
# Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
# Example 2:

# Input: row = [3, 2, 0, 1]
# Output: 0
# Explanation: All couples are already seated side by side.

# Note:
# len(row) is even and in the range of [4, 60].
# row is guaranteed to be a permutation of 0...len(row)-1.


class MinSwapsCouples:

    # The idea is simple, we firstly build a position map for each person (each person with number 0, 1, ... , n-1.
    # The key is the person's number, the value is the index in the array.

    # We loop through every even index (starting from 0), look at the person to its right: if it's the correct partner, continue; 
    # otherwise find where its partner sits, swap its partner with the person to its right. For example, for row [0, 2, 4, 5, 1, 3],

    # we start with person 0. We see that the person sitting next to person 0 is 2, which is the wrong partner, so we look up where person 1 sits, which is index 4.
    # So we swap index 1 and index 4, and update person 2's index to 4. Now we have [0, 1, 4, 5, 2, 3]. 
    # Next we jump to index 2, person 4 has the right partner, then we jump to index 4, person 2 also has the right partner. We're done!
    def doit(self, row):
        """
        :type row: List[int]
        :rtype: int
        """
        pos = {c: i for i, c in enumerate(row)}
        ans = 0

        for i in range(0, len(row), 2):
            one, two = row[i], -1

            if row[i] % 2 == 0:
                two = one + 1
            else:
                two = one - 1

            if two != row[i+1]:

                ans += 1

                oldpos, oldval = pos[two], row[i+1]

                row[i+1], row[pos[two]] = row[pos[two]], row[i+1]

                pos[oldval], pos[two] = oldpos, i+1

        return ans

    def doit(self, row):
        """
        :type row: List[int]
        :rtype: int
        """
        lookup = {}
        for i, x in enumerate(row):
            lookup[x] = i

        steps = 0
        for now in range(0, len(row), 2):
            if (row[now] ^ row[now + 1]) == 1:
                continue
            else:
                target = lookup[row[now] ^ 1]
                row[now + 1], row[target] = row[target], row[now + 1]
                lookup[row[target]] = target
                steps += 1

        return steps


if __name__ == "__main__":

    res = MinSwapsCouples().doit([0, 2, 1, 3])

    res = MinSwapsCouples().doit([3, 2, 0, 1])

    pass
