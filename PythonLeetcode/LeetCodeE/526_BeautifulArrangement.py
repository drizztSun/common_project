# 526. Beautiful Arrangement

# Suppose you have N integers from 1 to N. We define a beautiful arrangement as an array that is constructed
# by these N numbers successfully if one of the following is true for the ith position (1 <= i <= N) in this array:

# The number at the ith position is divisible by i.
# i is divisible by the number at the ith position.
# Now given N, how many beautiful arrangements can you construct

# Example 1:
# Input: 2
# Output: 2
# Explanation: 

# The first beautiful arrangement is [1, 2]:

# Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).

# Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).

# The second beautiful arrangement is [2, 1]:

# Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).

# Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.
# Note:
# N is a positive integer and will not exceed 15.


class CountArrangement(object):
    def doit(self, N):
        """
        :type N: int
        :rtype: int
        """
        cache = {}

        def helper(i, x, cache):

            if i == 1:
                return 1

            if (i, x) in  cache:
                return cache[(i, x)]
            
            ans = 0
            for j in range(len(x)):

                if x[j] % i == 0 and i % x[j] == 0:
                   ans += helper(i - 1, x[:j] + x[j+1:], cache)

            cache[(i, x)] = ans
            return ans

        return helper(N, tuple(range(1, N + 1)), cache)



    # My X is the set of still available numbers. Gets accepted in about 230 ms:

    def doit1(self, N):
        def count(i, X):
            if i == 1:
                return 1
            return sum(count(i - 1, X - {x})
                       for x in X
                       if x % i == 0 or i % x == 0)

        return count(N, set(range(1, N + 1)))
    # Note that my i goes downwards, from N to 1. Because position i = 1 can hold any number, 
    # so I don't even have to check whether the last remaining number fits there. 
    # Also, position i = 2 happily holds every second number and i = 3 happily holds every third number, 
    # so filling the lowest positions last has a relatively high chance of success. 
    # In other words, it's relatively hard to end up with dead ends this way.

    # If I go upwards (from 1 to N), it takes about 2300 ms:

    def doit2(self, N):
        def count(i, X):
            if i > N:
                return 1
            return sum(count(i + 1, X - {x})
                       for x in X
                       if x % i == 0 or i % x == 0)
        return count(1, set(range(1, N + 1)))




if __name__ == "__main__":

    res = CountArrangement().doit(2)

    res = CountArrangement().doit(10)
        