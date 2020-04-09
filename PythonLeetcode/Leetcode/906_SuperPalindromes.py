# 906. Super Palindromes

# Let's say a positive integer is a superpalindrome if it is a palindrome, and it is also the square of a palindrome.

# Now, given two positive integers L and R (represented as strings),
# return the number of superpalindromes in the inclusive range [L, R].


# Example 1:

# Input: L = "4", R = "1000"
# Output: 4
# Explanation: 4, 9, 121, and 484 are superpalindromes.
# Note that 676 is not a superpalindrome: 26 * 26 = 676, but 26 is not a palindrome.


class SuperpalindromesInRange:

    """
    Approach 1: Mathematical
    Intuition

    Say P = R^2 is a superpalindrome.
    Because R is a palindrome, the first half of the digits in R determine R up to two possibilities.
    We can iterate through these digits: let k be the first half of the digits in R.
    For example, if k = 1234, then R = 1234321 or R = 12344321. Each possibility has either an odd or an even number of digits in R.

    Notice because P<10^18, R < (10^{18})^0.5 = 10^9, and R = k | k'(concatenation), where k' is k reversed (and also possibly truncated by one digit); 
    so that k < 10^5 = MAGIC, our magic constant.

    Algorithm

    For each 1≤k<MAGIC, let's create the associated palindrome R, and check whether R^2 is a palindrome.

    We should handle the odd and even possibilities separately, as we would like to break early so as not to do extra work.
    To check whether an integer is a palindrome, we could check whether it is equal to its reverse. To create the reverse of an integer, we can do it digit by digit.

    Complexity Analysis

    Time Complexity: O(W^(1/4) ∗ logW), where W = 10^18 is our upper limit for R. The log(W) term comes from checking whether each candidate is the root of a palindrome.

    Space Complexity: O(logW), the space used to create the candidate palindrome.
    """

    def doit(self, L, R):
        L, R = int(L), int(R)
        MAGIC = 100000

        def reverse(x):
            a = 0
            while x > 0:
                a = a * 10 + x % 10
                x //= 10
            return a

        def is_palindrome(x):
            return x == reverse(x)

        ans = 0
        for i in range(1, MAGIC):

            v = str(i)
            v += v[::-1]
            v = int(v) ** 2

            if v > R:
                break

            if v >= L and is_palindrome(v):
                ans += 1

        for i in range(1, MAGIC):

            v = str(i)
            v = v + v[-2::-1]
            v = int(v) ** 2

            if v > R:
                break

            if v >= L and is_palindrome(v):
                ans += 1

        return ans


    """
    And then I tried to print out all valid super palindromes and it’s root square to see if there is any pattern.
    
    # n, n^2
    (1, 1)
    (2, 4)
    (3, 9)
    (11, 121)
    (22, 484)
    (101, 10201)
    (111, 12321)
    (121, 14641)
    (202, 40804)
    (212, 44944)
    (1001, 1002001)
    (1111, 1234321)
    (2002, 4008004)
    It’s interesting to find out all the sqrt of super palindromes except (1,4 9) are only consist of 0, 1, 2, and surrounded by 1 or 2.
    
    By using this finding, we can easily generate all possible sqrt of super Palindromes with BFS in range sqrt(R)
    
    """
    def doit(self, L, R):

        lb, ub = int(L) ** 0.5, int(R) ** 0.5
        sq, ans = ['1', '2'], int(lb <= 3 <= ub)
        is_palindrome = lambda s: s == s[::-1]

        for s in sq:

            if int(s) > ub:
                break

            if int(s) >= lb:
                ans += is_palindrome(str(int(s)**2))

            L, odd = divmod(len(s), 2)

            if odd:
                sq += [s[:L+1] + s[-(L+1):]]
            else:
                sq += [s[:L] + d + s[-L:] for d in '012']

        return ans

    def doit1(self, L, R):
        from math import sqrt
        from itertools import product
        a,l,r,s=['012']*(((len(R)+1)//2+1)//2),int(sqrt(int(L))),int(sqrt(int(R))),0
        for x in product(*a):
            x=''.join(x).lstrip('0') or '0'
            for y in (int(x+x[::-1]),int(x[:-1]+x[-1]+x[:-1][::-1])):
                if l<=y<=r and str(y*y)==str(y*y)[::-1]: s+=1
        return s+(int(L)<=9<=int(R))


if __name__ == '__main__':

    res = SuperpalindromesInRange().doit(L="4", R="1000")
