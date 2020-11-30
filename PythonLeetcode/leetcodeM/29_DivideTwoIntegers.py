"""
29. Divide Two Integers

Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero, which means losing its fractional part. For example, truncate(8.345) = 8 and truncate(-2.7335) = -2.

Note:

Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−231,  231 − 1].
For this problem, assume that your function returns 231 − 1 when the division result overflows.


Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = truncate(3.33333..) = 3.
Example 2:

Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = truncate(-2.33333..) = -2.
Example 3:

Input: dividend = 0, divisor = 1
Output: 0
Example 4:

Input: dividend = 1, divisor = 1
Output: 1
"""


class divide:

    def doit(self, dividend: int, divisor: int) -> int:
        positive = (dividend < 0) is (divisor < 0)
        dividend, divisor = abs(dividend), abs(divisor)
        res = 0
        while dividend >= divisor:
            curr_divisor, num_divisors = divisor, 1
            while dividend >= curr_divisor:
                dividend -= curr_divisor
                res += num_divisors

                curr_divisor += curr_divisor
                num_divisors += num_divisors

        if not positive:
            res = -res

        return min(max(-2147483648, res), 2147483647)

    """
    The best solution is to work with negative, instead of positive, numbers.
    This is allows us to use the largest possible range of numbers, and it covers all the ones we need.

    At the start of the algorithm, we'll instead convert both inputs to negative. Then, we'll need to modify the loop
    so that it subtracts the negative divisor from the negative dividend. At the end, we'll need to convert the result back
    to a positive if the number of negative signs in the input was not 1.

    The code for this is our complete approach 1, and can be found in the code box below.

    Algorithm

    Remember that we're converting the inputs to negative numbers. This is because we don't want separate code
    for all the possible combinations of positive/negative divisor and dividend. We converted them to negative instead of positive because the range of valid negative numbers is bigger, and therefore overflows can be cleanly avoided.

    The looping condition is while (dividend - divisor <= 0) because the difference is moving towards zero from the negative side.
    herefore, we want to continue while it is still under it. Once it goes over, we know we're done.

    """
    def doit(self, dividend: int, divisor: int):

        # Constants.
        MAX_INT = 2147483647  # 2**31 - 1
        MIN_INT = -2147483648  # -2**31

        # Special case: overflow.
        if dividend == MIN_INT and divisor == -1:
            return MAX_INT

        # We need to convert both numbers to negatives
        # for the reasons explained above.
        # Also, we count the number of negatives signs.
        negatives = 2
        if dividend > 0:
            negatives -= 1
            dividend = -dividend
        if divisor > 0:
            negatives -= 1
            divisor = -divisor

        # Count how many times the divisor has to be
        # added to get the dividend. This is the quotient.
        quotient = 0
        while dividend - divisor <= 0:
            quotient -= 1
            dividend -= divisor

        # If there was originally one negative sign, then
        # the quotient remains negative. Otherwise, switch
        # it to positive.
        return -quotient if negatives != 1 else quotient

    """
    Approach 3: Adding Powers of Two
    Intuition
    
    In the previous approach, we did repeated exponential searches for the largest value that would fit into the current dividend.
    
    However, notice that each time we do a search, we repeatedly go through the same doubles to find the largest. For example, consider the first and second step of our previous example: divide(93706, 157).
    
    On the first step we did this:
    
    157
    314
    628
    1256
    2512
    5024
    10048
    20096
    40192
    80384
    160768 # Too big
    This left us with a difference of 93706 - 80384 = 13322.
    
    On the second step we repeated this process again with 13322:
    
    157
    314
    628
    1256
    2512
    5024
    10048
    20096 # Too big
    Notice that we've just recomputed the first seven terms of the doubles again!
    
    Instead of doing this, we should find a way so that we can compute the sequence just once and then use the results from this to compute our quotient.
    
    In order to do this, we need to notice one more property about the difference. That property is that the difference will always be less than the previous doubling of the divisor that fits into it. Why? Well, if it were equal, or bigger, than the largest doubling, then we must've stopped doubling too soon. So, the difference is always less than the biggest doubling.
    
    So to use these properties, we'll put all the "doubles" of 157 into a List. Then we'll iterate backwards over the list taking all the numbers that will fit into the dividend. Here's an animation of the algorithm.
    
    Complexity Analysis

    Let nn be the absolute value of dividenddividend.
    
    Time Complexity : O(\log \, n)O(logn).
    
    We take O(\log \, n)O(logn) time in the first loop to create our list of doubles (and powers of two).
    
    For the second loop, because there's O(\log \, n)O(logn) items in the list of doubles, it only takes O(\log \, n)O(logn)time for this loop as well.
    
    Combined, our total time complexity is just O(\log \, n + \log \, n) = O(\log \, n)O(logn+logn)=O(logn).
    
    Space Complexity : O(\log \, n)O(logn).
    
    The length of the list of doubles of the divisor is proportional to O(\log \, n)O(logn) so our space complexity is O(\log \, n)O(logn).
    
    This approach is interesting in that the time complexity is lower than the previous one, but it requires a bit of space. Trading off space for time is very common practice.
    
    However, as we'll see in the next approach, we can modify the algorithm so that we don't need O(\log \, n)O(logn) space at all!
    
    """

    def doit(self, dividend: int, divisor: int) -> int:

        # Constants.
        MAX_INT = 2147483647  # 2**31 - 1
        MIN_INT = -2147483648  # -2**31
        HALF_MIN_INT = -1073741824  # MIN_INT // 2

        # Special case: overflow.
        if dividend == MIN_INT and divisor == -1:
            return MAX_INT

        # We need to convert both numbers to negatives.
        # Also, we count the number of negatives signs.
        negatives = 2
        if dividend > 0:
            negatives -= 1
            dividend = -dividend
        if divisor > 0:
            negatives -= 1
            divisor = -divisor

        doubles = []
        powersOfTwo = []

        # Nothing too exciting here, we're just making a list of doubles of 1 and
        # the divisor. This is pretty much the same as Approach 2, except we're
        # actually storing the values this time. */
        powerOfTwo = 1
        while divisor >= dividend:
            doubles.append(divisor)
            powersOfTwo.append(powerOfTwo)
            # Prevent needless overflows from occurring...
            if divisor < HALF_MIN_INT:
                break
            divisor += divisor  # Double divisor
            powerOfTwo += powerOfTwo

        # Go from largest double to smallest, checking if the current double fits.
        # into the remainder of the dividend.
        quotient = 0
        for i in reversed(range(len(doubles))):
            if doubles[i] >= dividend:
                # If it does fit, add the current powerOfTwo to the quotient.
                quotient += powersOfTwo[i]
                # Update dividend to take into account the bit we've now removed.
                dividend -= doubles[i]

        # If there was originally one negative sign, then
        # the quotient remains negative. Otherwise, switch
        # it to positive.
        return quotient if negatives != 1 else -quotient