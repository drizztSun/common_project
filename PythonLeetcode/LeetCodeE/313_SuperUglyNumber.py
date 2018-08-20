

# 263. Ugly Number
# Write a program to check whether a given number is an ugly number.
# Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.
# Note that 1 is typically treated as an ugly number.

class isUgly:
    def doit(self, num):
        """
        :type num: int
        :rtype: bool
        """
        if num == 0:
            return False

        while num % 5 == 0:
            num = num // 5

        while num % 3 == 0:
            num = num // 3


        while num % 2 == 0:
            num = num // 2

        return num == 1
        
    def doit1(self, num):
        """
        :type num: int
        :rtype: bool
        """
        if num == 0:
            return False

        while num != 1:

            if num % 5 == 0:
                num = num // 5
            elif num % 3 == 0:
                num = num // 3
            elif num % 2 == 0:
                num = num // 2
            else:
                return False

        return True


# 264. Ugly Number II
# Write a program to find the n-th ugly number.

# Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 
# For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

# Note that 1 is typically treated as an ugly number, and n does not exceed 1690.
class nthUglyNumber:
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        ugly = [1]
        t2, t3, t5 = 0, 0, 0

        while len(ugly) < n:

            minV = min(ugly[t2] * 2, ugly[t3] * 3, ugly[t5] * 5)

            if minV == ugly[t2] * 2:
                t2 += 1

            if minV == ugly[t3] * 3:
                t3 += 1

            if minV == ugly[t5] * 5:
                t5 += 1

            ugly.append(minV)

        return ugly[n-1]
            

# 313. Super Ugly Number


# Write a program to find the nth super ugly number.

# Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k.
# For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32] is the sequence of the first 12 super ugly numbers given primes = [2, 7, 13, 19] of size 4.

# Note:
# (1) 1 is a super ugly number for any given primes.
# (2) The given numbers in primes are in ascending order.
# (3) 0 < k ? 100, 0 < n ? 106, 0 < primes[i] < 1000.
# (4) The nth super ugly number is guaranteed to fit in a 32-bit signed integer.

# Credits:
# Special thanks to @dietpepsi for adding this problem and creating all test cases.
import headq

class nthSuperUglyNumber:
    def doit(self, n, primes):
        """
        :type n: int
        :type primes: List[int]
        :rtype: int
        """
        ugly = [1]
        pos = [0 for _ in range(len(primes))]
        
        while len(ugly) < n:

            minv = min([ugly[pos[x]] * primes[x] for x in range(len(primes))] )

            for x in range(len(pos)):
                if minv == ugly[pos[x]] * primes[x]:
                    pos[x] += 1

            ugly.append(minv)

        return ugly[n-1]


    def doit1(self, n, primes):
        """
        :type n: int
        :type primes: List[int]
        :rtype: int
        """
        que = []
        for p in primes:
            # (value, index, prime)
            heappush(que, (p, 1, p))
        
        ugly = [1]
        for i in range(1, n):

            val, idx, p = heappop(que)
            ugly.append(val)
            heappush(que, (ugly[idx]*p, idx+1, p))

            # skip duplicates
            while que[0][0] == ugly[-1]:

                val, idx, p = heappop(que)
                heappush(que, (ugly[idx]*p, idx+1, p))
            
        return ugly[-1]
        


if __name__=="__main__":

    res = nthUglyNumber().doit(4)

    res = nthUglyNumber().doit(7)

    res = nthSuperUglyNumber().doit(13, [2, 7, 13, 19])

    pass




