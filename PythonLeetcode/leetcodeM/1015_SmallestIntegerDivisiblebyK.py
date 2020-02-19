# 1015. Smallest Integer Divisible by K

# Given a positive integer K, you need find the smallest positive integer N such that N is divisible by K,
# and N only contains the digit 1.

# Return the length of N.  If there is no such N, return -1.


# Example 1:

# Input: 1
# Output: 1
# Explanation: The smallest answer is N = 1, which has length 1.

# Example 2:

# Input: 2
# Output: -1
# Explanation: There is no such positive integer N divisible by 2.

# Example 3:

# Input: 3
# Output: 3
# Explanation: The smallest answer is N = 111, which has length 3.


# Note:

# 1 <= K <= 10^5

class SmallestRepunitDivByK:

    """
    Explanation:
    First observe that integers that end in 1 are never divisible by 2 or 5. Thus the program starts by checking if K is divisisble by 2 or 5.
    If it is, then K cannot be a factor of a number that ends in 1, and we return -1.

    Next, since we only care about divisibility by K and not the actual value of n, we can do everything modulo K.
    Starting with n = 1, the recursion n = 10n + 1, leads to n = 1, 11, 111, 1111, etc.
    Thus this recursion is an easy way to generate potential values of n.
    To avoid n getting too big we can replace (10n + 1) with (10n + 1) % K during each iteration.
    The value in i simply records the number of iterations done so far which is equivalent to the length of n.
    The while loop will keep occurring until n is divisible by K for the first time. The value of i that is returned corresponds to the shortest length of n.
    """

    def doit(self, K):
        if K % 2 == 0 or K % 5 == 0:
            return -1

        i = n = 1
        while n % K != 0:
            n, i = (10*n + 1) % K, i + 1

        return i


if __name__ == '__main__':

    res = SmallestRepunitDivByK().doit(1)

    res = SmallestRepunitDivByK().doit(2)

    res = SmallestRepunitDivByK().doit(3)

    pass
