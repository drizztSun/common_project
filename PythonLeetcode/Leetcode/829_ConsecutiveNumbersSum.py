# 829. Consecutive Numbers Sum

# Given a positive integer N, how many ways can we write it as a sum of consecutive positive integers?

# Example 1:

# Input: 5
# Output: 2
# Explanation: 5 = 5 = 2 + 3

# Example 2:

# Input: 9
# Output: 3
# Explanation: 9 = 9 = 4 + 5 = 2 + 3 + 4
# Example 3:

# Input: 15
# Output: 4
# Explanation: 15 = 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5



# N = x + (x+1) +(x+2) + (x+3)+ ... + y 
# => N = (x+y) * (y-x+1) / 2 
# => 2 * N = (x+y) * (y-x+1) 
# x     |odd  |even |odd  |even
# y     |even |odd  |odd  |even 
# y-x+1 |even |even |odd  |odd
# y+x   |odd  |odd  |even |even 
# 2 * N |even |even |even |even 
# => let's say i = x+y, j = y-x+1, as long as not (i is odd and j is odd) or not (i is even and j is even)
# we have one more way to express N as consecutive numbers sum


class ConsecutiveNumbersSum:

    def doit(self, N):
        """
        :type N: int
        :rtype: int
        """
        ans, i, N = 0, 1, N * 2

        while i <= N ** 0.5:
            j = N / i
            ans += j == int(j) and j % 2 != i % 2
            i += 1

        return ans  
