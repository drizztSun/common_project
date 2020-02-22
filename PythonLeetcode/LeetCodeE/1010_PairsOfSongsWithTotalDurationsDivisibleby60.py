# 1010. Pairs of Songs With Total Durations Divisible by 60

# In a list of songs, the i-th song has a duration of time[i] seconds.

# Return the number of pairs of songs for which their total duration in seconds is divisible by 60.
# Formally, we want the number of indices i < j with (time[i] + time[j]) % 60 == 0.


# Example 1:

# Input: [30,20,150,100,40]
# Output: 3
# Explanation: Three pairs have a total duration divisible by 60:
# (time[0] = 30, time[2] = 150): total duration 180
# (time[1] = 20, time[3] = 100): total duration 120
# (time[1] = 20, time[4] = 40): total duration 60

# Example 2:

# Input: [60,60,60]
# Output: 3
# Explanation: All three pairs have a total duration of 120, which is divisible by 60.


# Note:

# 1 <= time.length <= 60000
# 1 <= time[i] <= 500

from collections import Counter

class NumPairsDivisibleBy60:

    def doit(self, time):

        ans = 0
        seconds = {}
        for c in time:
            c %= 60
            ans += seconds.get((60 - c) % 60, 0)
            seconds[c] = seconds.get(c, 0) + 1

        return ans

    def doit(self, time):

        time = list(map(lambda v: v % 60, time))
        c = Counter(time)
        count = 0
        for key in c:
            if key == (60 - key) % 60:
                count += (c[key]) * (c[key] - 1)
            else:
                count += c[key] * c[(60 - key) % 60]
        return count // 2


if __name__ == '__main__':

    res = NumPairsDivisibleBy60().doit([30, 20, 150, 100, 40])

    res = NumPairsDivisibleBy60().doit([60, 60, 60])

    pass
