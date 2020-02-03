# 949. Largest Time for Given Digits

# Given an array of 4 digits, return the largest 24 hour time that can be made.

# The smallest 24 hour time is 00:00, and the largest is 23:59.
# Starting from 00:00, a time is larger if more time has elapsed since midnight.

# Return the answer as a string of length 5.  If no valid time can be made, return an empty string.


# Example 1:

# Input: [1,2,3,4]
# Output: "23:41"

# Example 2:

# Input: [5,5,5,5]
# Output: ""


# Note:

# A.length == 4
# 0 <= A[i] <= 9

from collections import Counter


class LargestTimeFromDigits:

    def doit(self, A):
        ans = -1
        for h1, h2, m1, m2 in itertools.permutations(A):
            hours = 10 * h1 + h2
            mins = 10 * m1 + m2
            time = 60 * hours + mins
            if 0 <= hours < 24 and 0 <= mins < 60 and time > ans:
                ans = time

        return "{:02}:{:02}".format(*divmod(ans, 60)) if ans >= 0 else ""

    def doit(self, A):

        hours, minutes = -1, -1
        for i in range(len(A)):
            for j in range(len(A)):
                if i == j:
                    continue
                for z in range(len(A)):
                    if z == i or z == j:
                        continue
                    for k in range(len(A)):
                        if k == i or k == j or k == z:
                            continue

                        hr = A[i] * 10 + A[j]
                        mins = A[z] * 10 + A[k]

                        if 0 <= hr < 24 and 0 <= mins < 60:
                            if hr > hours or (hours == hr and mins > minutes):
                                hours, minutes = hr, mins

        if hours == -1 and minutes == -1:
            return ''

        return "{:02}:{:02}".format(hours, minutes)


if __name__ == '__main__':

    res = LargestTimeFromDigits().doit([1, 2, 3, 4])  # "23:41"

    res = LargestTimeFromDigits().doit([5, 5, 5, 5])  # ""

    res = LargestTimeFromDigits().doit([2, 0, 6, 6])

    res = LargestTimeFromDigits().doit([0, 0, 0, 0])  # ""

    pass
