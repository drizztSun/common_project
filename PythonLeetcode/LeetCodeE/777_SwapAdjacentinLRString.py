# 777. Swap Adjacent in LR String

# In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL",
# a move consists of either replacing one occurrence of "XL" with "LX", or replacing one occurrence of "RX" with "XR".
# Given the starting string start and the ending string end,
# return True if and only if there exists a sequence of moves to transform one string to the other.

# XL => LX
# RX => XR

# Example:

# Input: start = "RXXLRXRXL", end = "XRLXXRRLX"
# Output: True
# Explanation:
# We can transform start to end following these steps:
# RXXLRXRXL ->
# XRXLRXRXL ->
# XRLXRXRXL ->
# XRLXXRRXL ->
# XRLXXRRLX

# Note:

# 1 <= len(start) = len(end) <= 10000.
# Both start and end will only consist of characters in {'L', 'R', 'X'}.


class CanTransform:

    # TimeLimitExceeded
    def doit2(self, start, end):

        buff = set()

        def dfs(current, end):
            if current == end:
                return True

            if current in buff:
                return False

            buff.add(current)

            for i in range(len(current)-1):

                if current[i:i+2] == 'XL' and dfs(current[:i] + 'LX' + current[i+2:], end):
                    return True

                if current[i:i+2] == 'RX' and dfs(current[:i] + 'XR' + current[i+2:], end):
                    return True

            return False

        return dfs(start, end)

    def doitbfs(self, start, end):

        visited = set()
        buff = [start]

        while buff:
            for c in buff:
                if c == end:
                    return True

                if c in visited:
                    continue

                visited.add(c)
                tmp = []
                for i in range(len(c) - 1):
                    if c[i:i+2] in ('XL', 'RX'):
                        l = c[:i] + ('LX' if c[i:i+2] ==
                                     'XL' else 'XR') + c[i+2:]
                        if l not in visited:
                            tmp.append(l)
        buff = tmp

        return False

    def doit(self, start, end):

        L, R = 0, 0
        for s, e in zip(start, end):
            L += (e == 'L') - (s == 'L')
            R += (s == 'R') - (e == 'R')

            if L < 0 or L > 0 and s == 'R' or R < 0 or R > 0 and s == 'L':
                return False

        return not R and not L

    # We can only move "R" backwards and "L" forward as we can convert "XL" to "LX" and "RX" to "XR"

    # - Maintain count of R's found in the "start" string to match with "end"
    # - BECAUSE WE CAN ONLY MOVE "R" BACK WE INC THEM WHEN WE FIND THEM IN "start" AND DECREMENT IN "end" (matching step)

    # - Maintain count of L's found in the "end" string to match with "start"
    # - BECAUSE WE CAN ONLY MOVE "L" FWD WE INC THEM WHEN WE FIND THEM IN "end" AND DECREMENT IN "start" (matching step)

    # - If at any point  we have unmatched "R" or "L" we can return false
    def doit(self, start, end):

        if len(start) != len(end):
            return False

        fwdL, bwdR = 0, 0
        for i in range(len(start)):

            if start[i] == 'R':
                bwdR += 1

            if start[i] == 'L':
                fwdL -= 1

            if end[i] == 'R':
                bwdR -= 1

            if end[i] == 'L':
                fwdL += 1

            # If we have more R's or L's that can be matched or if a cross over b/w R & L has occured (indicated by both +ve) we can't transform further
            if (fwdL > 0 and bwdR > 0) or (fwdL < 0 or bwdR < 0):
                return False

        return fwdL == 0 and bwdR == 0


if __name__ == '__main__':

    res = CanTransform().doit("RXXLRXRXL", "XRLXXRRLX")

    pass
