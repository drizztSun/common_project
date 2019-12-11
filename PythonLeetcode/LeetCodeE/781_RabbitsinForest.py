# 781. Rabbits in Forest

# In a forest, each rabbit has some color. Some subset of rabbits (possibly all of them) tell
# you how many other rabbits have the same color as them. Those answers are placed in an array.

# Return the minimum number of rabbits that could be in the forest.

# Examples:
# Input: answers = [1, 1, 2]
# Output: 5
# Explanation:
# The two rabbits that answered "1" could both be the same color, say red.
# The rabbit than answered "2" can't be red or the answers would be inconsistent.
# Say the rabbit that answered "2" was blue.
# Then there should be 2 other blue rabbits in the forest that didn't answer into the array.
# The smallest possible number of rabbits in the forest is therefore 5: 3 that answered plus 2 that didn't.

# Input: answers = [10, 10, 10]
# Output: 11

# Input: answers = []
# Output: 0
# Note:

# answers will have length at most 1000.
# Each answers[i] will be an integer in the range [0, 999].

from collections import Counter


class NumRabbits:

    def doit(self, answers):
        cnt = Counter(answers)
        total = 0
        for k, num in cnt.items():
            if num <= k:
                total += k + 1
            else:
                d, r = divmod(num, k+1)
                total += d * (k + 1)
                if r != 0:
                    total += k + 1

        return total

    def doit1(self, answers):
        D, Rabbits = {}, 0
        for i in Answers:
            if not i in D:
                D[i] = 1
            else:
                D[i] += 1

        for i in D:
            Rabbits += (D[i]//(i + 1))*(i + 1) + min(D[i] % (i + 1), 1)*(i + 1)

        return Rabbits


if __name__ == '__main__':

    res = NumRabbits().doit([1, 1, 2])

    res = NumRabbits().doit([10, 10, 10])

    pass
