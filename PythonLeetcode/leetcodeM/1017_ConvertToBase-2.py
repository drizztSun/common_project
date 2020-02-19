# 1017. Convert to Base -2

# Given a number N, return a string consisting of "0"s and "1"s that represents its value in base -2 (negative two).

# The returned string must have no leading zeroes, unless the string is "0".


# Example 1:

# Input: 2
# Output: "110"
# Explantion: (-2) ^ 2 + (-2) ^ 1 = 2

# Example 2:

# Input: 3
# Output: "111"
# Explantion: (-2) ^ 2 + (-2) ^ 1 + (-2) ^ 0 = 3

# Example 3:

# Input: 4
# Output: "100"
# Explantion: (-2) ^ 2 = 4


# Note:

# 0 <= N <= 10^9

class BaseNeg2:

    # go back from 0 -> n position in binary
    # if remainder == 1, There is (-2) ^ n, it means to remove it (-2) ^ n
    # if remainder == 0，There is no (-2) ^ n
    def doit(self, N: int):
        if N == 0:
            return '0'

        ans = []
        while N:

            if abs(N % 2) == 1:
                ans.append('1')
                N -= 1
            else:
                ans.append('0')

            N //= -2

        return ''.join(reversed(ans))


if __name__ == '__main__':

    res = BaseNeg2().doit(2)

    res = BaseNeg2().doit(3)

    res = BaseNeg2().doit(4)

    pass
