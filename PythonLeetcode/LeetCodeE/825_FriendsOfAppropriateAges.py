# 825. Friends Of Appropriate Ages

# Some people will make friend requests. The list of their ages is given and ages[i] is the age of the ith person.

# Person A will NOT friend request person B (B != A) if any of the following conditions are true:

# age[B] <= 0.5 * age[A] + 7
# age[B] > age[A]
# age[B] > 100 && age[A] < 100
# Otherwise, A will friend request B.

# Note that if A requests B, B does not necessarily request A.  Also, people will not friend request themselves.

# How many total friend requests are made?

# Example 1:

# Input: [16,16]
# Output: 2
# Explanation: 2 people friend request each other.

# Example 2:

# Input: [16,17,18]
# Output: 2
# Explanation: Friend requests are made 17 -> 16, 18 -> 17.

# Example 3:

# Input: [20,30,100,110,120]
# Output:
# Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.


# Notes:

# 1 <= ages.length <= 20000.
# 1 <= ages[i] <= 120.

class NumFriendRequests:

    def doit(self, ages):

        count = [0]*121
        for age in ages:
            count[age] += 1

        total = 0
        sliding = 0
        for i in range(15, 121):
            sliding += count[i]
            if i % 2 == 0:
                sliding -= count[i//2 + 7]
            total += count[i] * (sliding - 1)
        return total

    def doit(self, ages):

        cnt = [0] * 121
        for c in ages:
            if c not in ages:
                cnt[c] = 0
            cnt[c] += 1

        ans = 0
        for ageA, cntA in enumerate(cnt):
            for ageB, cntB in enumerate(cnt):

                if ageB <= 0.5 * ageA + 7:
                    continue
                if ageB > ageA:
                    continue
                if ageA < 100 < ageB:
                    continue

                ans += cntA * cntB
                if ageA == ageB:
                    ans -= cntA

        return ans


if __name__ == '__main__':

    res = NumFriendRequests().doit([16, 16])  # 2

    res = NumFriendRequests().doit([16, 17, 18])  # 2

    res = NumFriendRequests().doit([20, 30, 100, 110, 120])  # 3
