


# 401. Binary Watch

# A binary watch has 4 LEDs on the top which represent the hours (0-11),
# and the 6 LEDs on the bottom represent the minutes (0-59).

# Each LED represents a zero or one, with the least significant bit on the right.


# Given a non-negative integer n which represents the number of LEDs that are currently on,
# return all possible times the watch could represent.

# Example:

# Input: n = 1
# Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]


class readBinaryWatch:


    def doit(self, num):
        """
        :type num: int
        :rtype: List[str]
        """
        if num == 0:
            return ["0:00"]

        import itertools
        on = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        times = {1:1, 2:2, 3:4, 4:8, 5:1, 6:2, 7:4, 8:8, 9:16, 10:32}

        comb = list(itertools.combinations(on, num))
        res = []

        for c in comb:
            minutes, hours = 0, 0
            for i in c:
                if i > 4:
                    minutes += times[i]
                else:
                    hours += times[i]

            if minutes < 60 and hours < 12:
                res.append('%d:%02d' % (hours, minutes))

        return res


    def doit1(self, num):
        """
        :type num: int
        :rtype: List[str]
        """
        return ['%d:%02d' % (h, m)
                     for h in range(12) for m in range(60)
                     if (bin(h) + bin(m)).count('1') == num]
                    



if __name__=="__main__":


    res = readBinaryWatch().doit(1)

    res = readBinaryWatch().doit(2)


    pass


