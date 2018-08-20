


# 397. Integer Replacement

# Given a positive integer n and you can do operations as follow:

# If n is even, replace n with n/2.
# If n is odd, you can replace n with either n + 1 or n - 1.
# What is the minimum number of replacements needed for n to become 1?

# Example 1:

# Input:
# 8

# Output:
# 3

# Explanation:
# 8 -> 4 -> 2 -> 1
# Example 2:

# Input:
# 7

# Output:
# 4

# Explanation:
# 7 -> 8 -> 4 -> 2 -> 1
# or
# 7 -> 6 -> 3 -> 2 -> 1


class integerReplacement(object):
    

# Denote f(n) the minimum number of jumps from n to 1.

# By definition, we have the recurrence
# f(1) = 0, f(2n) = 1 + f(n), f(2n + 1) = min(f(2n) + 1, f(2n + 2) + 1).

# First notice that this sequence is well defined because f(2n + 2) = f(n + 1) + 1,
# so f(2n + 1) = min(f(2n) + 1, f(n + 1) + 2). Every element is defined by some element before it.

# We want to show (*):
# If n % 4 = 3 and n != 3, then f(n) = f(n + 1) + 1.
# If n % 4 = 1 or n = 3, then f(n) = f(n - 1) + 1.

# This gives us an O(log n) time, O(1) space solution.
 
   def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        rtn = 0

        while n > 1:

            rtn += 1

            if n % 2 == 0:
                n //= 2

            elif n % 4 == 1 or n == 3:
                n -= 1

            else:
                n += 1

        return rtn



    # <recursion>
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        def search(n):
            if n <= 2:
                return n - 1

            if n % 2 == 1:
                return 1 + min(search(n+1), search(n-1))
            else:
                return 1 + search(int(n//2))

        return search(n)


    # <DP>
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n <= 2:
            return n - 1

        end = n+1 if n % 2 == 1 else n

        D = [0 for _ in range(end+1)]
        D[1], D[2] = 1, 1

        for i in range(3, end+1, 2):

            D[i+1] = 1 + D[int((i+1)//2)]

            D[i] = 1 + min(D[i+1], D[i-1])
        
        return D[n]

if __name__ == "__main__":

    res = integerReplacement().doit(1)

    res = integerReplacement().doit(2)

    res = integerReplacement().doit(3)

    res = integerReplacement().doit(4)

    res = integerReplacement().doit(5)

    res = integerReplacement().doit(6)

    res = integerReplacement().doit(7)

    res = integerReplacement().doit(8)

    res = integerReplacement().doit(9)


    pass