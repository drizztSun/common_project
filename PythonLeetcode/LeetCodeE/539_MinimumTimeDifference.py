# 539. Minimum Time Difference


# Given a list of 24-hour clock time points in "Hour:Minutes" format, 
# find the minimum minutes difference between any two time points in the list.
# Example 1:
# Input: ["23:59","00:00"]
# Output: 1
# Note:
# The number of time points in the given list is at least 2 and won't exceed 20000.
# The input time is legal and ranges from 00:00 to 23:59.



class MinusDifference:
    def doit(self, timePoints):
        """
        :type timePoints: List[str]
        :rtype: int
        """
        timings = []
        for c in timePoints:
            r = c.split(':')
            timings.append(int(r[0]) * 60 + int(r[1]))
            
        timings.sort()
        timings.append(timings[0])
        minv = 2 ** 31
        for i in range(1, len(timings)):
            diff = abs(timings[i] - timings[i-1])
            if diff > 12 * 60:
                diff = 24 * 60 - diff
            minv = min(minv, diff)
            
        return minv
            

    def doit1(self, timePoints):
        """
        :type timePoints: List[str]
        :rtype: int
        """
        # day_min = 24 * 60
        def get_min(time_str):
            time_str = time_str.split(':')
            time_hour = int(time_str[0])
            time_min = int(time_str[1])
            time_min = time_hour * 60 + time_min
            return [time_min]

        if len(timePoints) > 24 * 60:
            return 0
        
        min_list = []
        for c_t in timePoints:
            min_list += get_min(c_t)
            
        min_list = sorted(min_list)
        
        re_val = 24 * 60
        for p_m, c_m in zip(min_list, min_list[1:] + min_list[0:]):
            c_d = (c_m - p_m) % (24 * 60)
            if c_d == 0:
                return 0
            if c_d < re_val:
                re_val = c_d

        return re_val


if __name__ == "__main__":

    res = MinusDifference().doit(["23:59","00:00"])