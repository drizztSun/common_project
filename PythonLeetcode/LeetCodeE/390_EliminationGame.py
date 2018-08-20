


# 390. Elimination Game

# There is a list of sorted integers from 1 to n. Starting from left to right, 
# remove the first number and every other number afterward until you reach the end of the list.

# Repeat the previous step again, but this time from right to left, remove the right most number and every other number from the remaining numbers.

# We keep repeating the steps again, alternating left to right and right to left, until a single number remains.

# Find the last number that remains starting with a list of length n.

# Example:

# Input:
# n = 9,
# 1 2 3 4 5 6 7 8 9
# 2 4 6 8
# 2 6
# 6

# Output:
# 6

class lastRemaining:


    # First of all, if n is an odd number, then f(1�n) = f(1�n-1), because after the first round elimination, the last odd number will be removed.
    # So let�s consider even number.
    # If the number of remaining numbers is even after the first round, which means the number is divided by 4.

    # ex: 12. after first elimination, we have 2,4,6,8,10,12. then after the second round, we have 2, 6, 10.
    # ,start from the beginning again => f(1�12) = f(2,6,10) = 2* f(1,3,5) = 2* [f(2,4,6) - 1] = 2 * [2f(1,2,3) - 1] = 4f(1�3) - 2;
    # similarly we get f(n) = 4f(n/4) - 2. if n is divided by 4.

    # If it is odd after first round, which means the number can�t divided by 4, then during the second round,
    # odd positioned numbers will be eliminated either process from beginning or from the end. ex: 10. first=> 2,4,6,8,10, second => 4, 8 => f(10) = 4*f(1�2)
    # => f(n) = 4f(n/4)
    
    def doit(self, num):
        """
        :type n: int
        :rtype: int
        """
        def search(n):
            if n == 1:
                return 1

            if n <= 4:
                return 2

            if n % 2 != 0:
                n -= 1

            if n % 4 != 0:
                return 4 * search(n // 4)

            return 4 * search(n // 4) - 2

        return search(num)


    #2n for 1:n/2
    
    #if even: 4n-2 for 1:n/4
    
    #if odd: 4n for 1:n/4-1
    def doit2(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 1:
            return 1

        elif n == 2 or n == 3:
            return 2

        elif n % 2 == 1:
            n -= 1
            
        parity = (n//2) % 2


        if parity:
            # 4n for 1:n/4-1
            return 4*Solution().lastRemaining(n//4)
        else:
            # 4n-2 for 1:n/4
            return 4*Solution().lastRemaining(n//4)-2


    def doit1(self, n):
        """
        :type n: int
        :rtype: int
        """
        head, ind, step = 1, 1, 1
        while n > 1:
            if ind or n % 2 == 1:
                head += step

            ind, step, n = 1-ind, step * 2, n // 2
    
        return head


    def doit3(self, n):
        """
        :type n: int
        :rtype: int
        """
        return ((n | 0x55555555555555) & ((1 << (n.bit_length() - 1)) - 1)) + 1


    def doit3(self, num):
        """
        :type n: int
        :rtype: int
        """
        def search(n):
            return 1 if n == 1 else 2 * (1 + n / 2 - search(n / 2))

        return search(num)


if __name__=="__main__":


    res = lastRemaining().doit(9)

    res = lastRemaining().doit(10)

    pass