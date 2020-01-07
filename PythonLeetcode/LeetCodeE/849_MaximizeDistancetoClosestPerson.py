# 849. Maximize Distance to Closest Person

# In a row of seats, 1 represents a person sitting in that seat, and 0 represents that the seat is empty.

# There is at least one empty seat, and at least one person sitting.

# Alex wants to sit in the seat such that the distance between him and the closest person to him is maximized.

# Return that maximum distance to closest person.

# Example 1:

# Input: [1,0,0,0,1,0,1]
# Output: 2
# Explanation:
# If Alex sits in the second open seat (seats[2]), then the closest person has distance 2.
# If Alex sits in any other open seat, the closest person has distance 1.
# Thus, the maximum distance to the closest person is 2.

# Example 2:

# Input: [1,0,0,0]
# Output: 3
# Explanation:
# If Alex sits in the last seat, the closest person is 3 seats away.
# This is the maximum distance possible, so the answer is 3.
# Note:

# 1 <= seats.length <= 20000
# seats contains only 0s or 1s, at least one 0, and at least one 1.


class MaxDistToClosest:

    def doit(self, seats):
        N = len(seats)
        left, right = [N] * N, [N] * N

        for i in range(N):
            if seats[i] == 1:
                left[i] = 0
            elif i > 0:
                left[i] = left[i-1] + 1

        for i in range(N-1, -1, -1):
            if seats[i] == 1:
                right[i] = 0
            elif i < N-1:
                right[i] = right[i+1] + 1

        return max(min(left[i], right[i])
                   for i, seat in enumerate(seats) if not seat)

    def doit(self, seats):

        s, ans = -1, -1

        for i in range(len(seats) + 1):
            if i == len(seats) or seats[i] == 1:
                if s != -1:
                    if (s == 0 or i == len(seats)) and i - s > ans:
                        ans = i - s
                    elif ans < (i-s + 1) // 2:
                        ans = (i-s + 1) // 2
                s = -1
            elif seats[i] == 0 and s == -1:
                s = i

        return ans

    def doit(self, seats):
        currmax = 1
        counter = 0
        flag = True
        first = 0
        for i in seats:
            if i == 1:
                if flag:
                    first = counter
                    flag = False
                if counter > currmax:
                    currmax = counter
                counter = 1
            else:
                counter += 1

        ans = max(first, counter-1, int(currmax/2))
        return ans


if __name__ == '__main__':

    res = MaxDistToClosest().doit([1, 0, 0, 0, 1, 0, 1])  # 2

    res = MaxDistToClosest().doit([1, 0, 0, 0])  # 3

    pass
