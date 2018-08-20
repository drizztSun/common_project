# 507. Perfect Number

# We define the Perfect Number is a positive integer that is equal to the sum of all its positive divisors except itself.

# Now, given an integer n, write a function that returns true when it is a perfect number and false when it is not.

# Example:
# Input: 28
# Output: True
# Explanation: 28 = 1 + 2 + 4 + 7 + 14
# Note: The input number n will not exceed 100,000,000. (1e8)



class PerfectNumber:

    def doit(self, num):

        if num <= 5:
            return False

        binary = bin(num)[2:]

        l = len(binary) // 2 +1

        return binary[:l] == "1" * l and binary[l:] == "0" * (l-1)


    def doit1(self, num):
        """
        :type num: int
        :rtype: bool
        """
        if num <= 1:
            return False

        i, total = 2, 1

        while i * i <= num:

            if num % i == 0:
                total += i + int(num // i)

            if i * i == num:
                total -= i

            i += 1

        return total == num

    def doit2(self, num):
        """
        :type num: int
        :rtype: bool
        """
        if num<= 0:
            return False
        if num == 6:
            return True
        sum1 = 0
        value = int(pow(num,0.5))
        for i in range(1,value):
            if num%i == 0:
                sum1 = sum1 + i
                if(i*i != num):
                    sum1 = sum1 + num/i
        return((sum1-num) == num)

if __name__ == "__main__":

    res = PerfectNumber().doit(28)

    pass
                    

    