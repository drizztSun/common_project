"""
1067. Digit Count in Range

Given an integer d between 0 and 9, and two positive integers low and high as lower and upper bounds, respectively.
Return the number of times that d occurs as a digit in all integers between low and high, including the bounds low and high.


Example 1:

Input: d = 1, low = 1, high = 13
Output: 6
Explanation:
The digit d=1 occurs 6 times in 1,10,11,12,13. Note that the digit d=1 occurs twice in the number 11.
Example 2:

Input: d = 3, low = 100, high = 250
Output: 35
Explanation:
The digit d=3 occurs 35 times in 103,113,123,130,131,...,238,239,243.


Note:

0 <= d <= 9
1 <= low <= high <= 2×10^8

"""


class DigitsCount:

    """
    Rather than counting the occurence of d from each number, we count the the occurent of d on each digit from 1 to the number.

    Think about the form of the number abcTxyz and the current digit T, and we want to count the occurence of d on that position.
    1. If T>d, then from 000 to abc, each corresponds to 1000 counts
    2. If T==d, then from 000 to abc, each corresponds to 1000 counts except the last one, and xyz correponds to a count of abcT000 to abcTxyz, which is xyz+1 counts.
    3. If T<d, then only from 000 to abc(excluded), each corresponds to 1000 counts.

    Pay attention to d=0, for that case, we cannot start from 000, so we need to subtract them
    """
    def doit_math(self, d, low, high):
        """
        :type d: int
        :type low: int
        :type high: int
        :rtype: int
        """
        def getCounts(num):
            res, step, n = 0, 1, 0
            while num > 0:
                t = num % 10  # the current digit
                num = num // 10  # the num in front of the digit
                if t > d:  #
                    res += (1 + num - (d == 0)) * step
                elif t == d:  #
                    res += (num - (d == 0)) * step + n + 1
                else:
                    res += (num - (d == 0)) * step
                n += t * step  # update the number after the current digit
                step = 10 * step  # update the weight
            return res

        return getCounts(high) - getCounts(low - 1)

    def doit_math(self, d: int, low: int, high: int) -> int:

        def countDigitD(d, low, high):
            # Q0233, count num of digit d appearance on all positive integer x, 1 <= x <= n.
            count, m = 0, 1
            while n > m - 1:
                q, r = n // (10 * m), n % (10 * m)
                if d == 0:
                    count += (q * m) if r >= m else ((q - 1) * m + r + 1)
                else:
                    count += q * m + min(max(0, r - m * d + 1), m)
                m *= 10
            return count

        return countDigitD(high, d) - countDigitD(low - 1, d)

    def doit_dp(self, d: int, low: int, high: int):

        pass


if __name__ == '__main__':

    DigitsCount().doit(d = 1, low = 1, high = 13)

    DigitsCount().doit(d = 3, low = 100, high = 250)