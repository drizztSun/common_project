


# 412. Fizz Buzz

# Write a program that outputs the string representation of numbers from 1 to n.

# But for multiples of three it should output �Fizz� instead of the number and
# for the multiples of five output Buzz. For numbers which are multiples of both three and five output �FizzBuzz�.

# Example:

# n = 15,

# Return:
# [
#    "1",
#    "2",
#    "Fizz",
#    "4",
#    "Buzz",
#    "Fizz",
#    "7",
#    "8",
#    "Fizz",
#    "Buzz",
#    "11",
#    "Fizz",
#    "13",
#    "14",
#    "FizzBuzz"
# ]


class fizzBuzz:
    def doit(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        res = []
        for c in range(n):
            num = c + 1
            item = ''

            if num % 3 == 0:
                item = 'Fizz'
            elif num % 5 == 0:
                item = 'Buzz'
            else:
                item = str(num)

            if num % 3 == 0 and num % 5 == 0:
                item = 'FizzBuzz'
        
                       
            res.append(item)

        return res



if __name__=="__main__":


    res = fizzBuzz().doit(15)

    pass
        