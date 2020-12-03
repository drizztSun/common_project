"""
479. Largest Palindrome Product

Find the largest palindrome made from the product of two n-digit numbers.

Since the result could be very large, you should return the largest palindrome mod 1337.



Example:

Input: 2

Output: 987

Explanation: 99 x 91 = 9009, 9009 % 1337 = 987



Note:

The range of n is [1,8].
"""


class LargestPalindrome:

    """

    I got the idea from @nizametdinov and @CerebrumMaize's posts.
    largest_palindrome = first_number * second_number = (10^n - x)*(10^n - y) where x,y are integers,
    and we want to keep them as small as possible to get the largest palindrome

    some algebra:
    largest_palindrome = 10^(2n) - 10^n * (x+y) + xy = 10^n * (10^n - (x+y)) + xy
    Interestingly this palindrome has been expressed as two numbers left and right, where
    left = 10^n - (x+y), right = xy and right = int(str(left)[::-1])
    e.g. palindrome ABCCBA = (10^3)*ABC+ CBA where ABC = 10^3-(x+y) and CBA = xy where n=3
    Let's define z=x+y, some algebra:
    left = 10^n - z
    right = x(z-x) = -x^2 + zx ==> x^2 - zx + right = 0
    right = int(str(left)[::-1]) (link left with right)

    It becomes a quadratic equation of x, recall x = 10^n - first_number, x has to be an integer. Hence we set z as the integer parameter
    to increment from lowest possible value of 2 (we want to keep multiplication of (10^n - x)*(10^n - y) as large as possible).
    When z is defined as integer parameter, hence we can guarantee y is also integer if x is integer.
    Hence the problem becomes searching for integer solution of x when z increments from 2.

    CAVEAT: There is an underlying assumption that restrict the use case to n <= 8, reason being we need (x+y) < 10^n and xy < 10^n
    to make sure largest palindrome can be represented in the format of 10^n * left + right when n = 9 ,
    such assumption is violated. as x = 19653 , y = 79683 and xy=1566009999 > 10^9.
    The largest palindrome product being (10^9-19653) * (10^9-79683) = 999900665566009999 Thanks to @hvsavage for pointing out!

    Math solution:
    Let Palindrome = X * Y, both have n digits, and assume they are very close to 10^n
    Denote X = 10^n - i, Y = 10^n - j, with assumption: i*j < 10^n
    Palindrome = upper*10^n + lower = (10^n - i)*(10^n - j) = (10^n-i-j)*10^n + i*j
    therefore: upper = 10^n-i-j, lower = i*j
    Let a = i + j, then lower = i*(a-i), upper = 10^n-a

    Algorithm: we iterate a and search for an integer i
    i^2 - a*i + lower = 0 => (i-a/2)^2 = 0.25*a^2 - lower
    Given a start from 2, check if sqrt(a^2 - lower*4) is an integer, then return upper*10^n + lower
    """
    def doit_math(self, n: int) -> int:
        if n == 1:
            return 9

        a = 2
        while a < 10 ** n:
            upper = 10 ** n - a
            lower = int(str(upper)[::-1])
            if a ** 2 - lower * 4 >= 0 and (a ** 2 - lower * 4) ** 0.5 == int((a ** 2 - lower * 4) ** 0.5):
                return (upper * 10 ** n + lower) % 1337
            a += 1

    """
    Non-math solution:
    maximum assumed palindrom: iterate by the first half of maxNumber
    a palindrome with an even number of digits is a multiple of 11
    """
    def doit_nonmath(self, n: int) -> int:
        if n == 1:
            return 9

        hi = 10 ** n - 1
        lo = 10 ** (n - 1)
        maxNum = hi * hi
        firstHalf = maxNum // (10 ** n)

        for first in range(firstHalf, lo - 1, -1):
            second = str(first)[::-1]
            num = int(str(first) + second)
            y_hi = hi // 11 * 11
            for y in range(y_hi, lo - 1, -11):
                if num % y == 0 and lo <= num // y <= hi:
                    return num % 1337
                if num // y > hi:
                    break