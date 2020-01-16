# 866. Prime Palindrome

# Find the smallest prime palindrome greater than or equal to N.

# Recall that a number is prime if it's only divisors are 1 and itself, and it is greater than 1.

# For example, 2,3,5,7,11 and 13 are primes.

# Recall that a number is a palindrome if it reads the same from left to right as it does from right to left.

# For example, 12321 is a palindrome.


# Example 1:

# Input: 6
# Output: 7

# Example 2:

# Input: 8
# Output: 11

# Example 3:

# Input: 13
# Output: 101


# Note:

# 1 <= N <= 10^8
# The answer is guaranteed to exist and be less than 2 * 10^8.


class PrimePalindrome:

    """
    Approach 2: Brute Force with Mathematical Shortcut
    Intuition

    Our brute force works except when NN is 8 digits
    (as explained in Approach Framework when we established that all 8 digit palindromes are not prime), so we can skip all 8 digit numbers.

    Algorithm
    For each number, check whether it is a palindrome. If it is, check whether it is a prime. If the number is 8 digits, skip to the 9 digit numbers.
    """

    def doit(self, N):

        def isprime(n):
            for d in range(2, int(n**0.5)+1):
                if n % d == 0:
                    return False
            return n > 1

        def reverse(x):
            ans = 0
            while x:
                ans = ans * 10 + x % 10
                x //= 10
            return ans

        while True:
            if isprime(N) and N == reverse(N):
                return N

            N += 1
            if 10**7 < N < 10**8:
                N = 10**8

    def doit(self, N):
        def isPrime(x):
            if x < 2 or x % 2 == 0:
                return x == 2
            for i in range(3, int(x**0.5) + 1, 2):
                if x % i == 0:
                    return False
            return True

        if 8 <= N <= 11:
            return 11

        for x in range(int(10 ** (len(str(N)) / 2)), int(10**5)):
            y = int(str(x) + str(x)[-2::-1])
            if y >= N and isPrime(y):
                return y

    """
    Approach 1: Iterate Palindromes
    Intuition

    Say we have a palindrome XX. What is the next palindrome?

    Each palindrome of dd digits has a palindromic root, it's first k = \frac{d+1}{2}k=
    2
    d+1
    ​
    digits. The next palindrome is formed by the next root.

    For example, if 123123 is a root for the 5 digit palindrome 1232112321, then the next palindrome is 1242112421 with root 124124.

    Notice that roots and palindromes are not a bijection, as palindromes 123321123321 and 1232112321 have the same root.

    Algorithm

    For each palindromic root, let's find the two associated palindromes (one with an odd number of digits, and one with an even number.) For roots with kk digits, they will generate palindromes of 2*k - 12∗k−1 and 2*k2∗k digits.

    If we didn't know that palindromes with an even number of digits (and greater than 11) are never prime, we're still fine - we can just check both possibilities. When checking both possibilities, we check the palindromes with 2k - 12k−1 digits first, as they are all smaller than the palindromes with 2k2k digits.

    We'll use an idea from [LeetCode Problem: Reverse an Integer], in order to check whether an integer is a palindrome. We could have also converted the integer to a string, and checked the indices directly.

    As for testing primes with isPrime(N), we'll use the standard O(\sqrt{N})O( 
    N
    ​
    ) check: testing whether every number \leq \sqrt{N}≤
    N
​
    is a divisor of NN.

    """


if __name__ == '__main__':

    res = PrimePalindrome().doit(6)  # 7

    res = PrimePalindrome().doit(8)  # 11

    res = PrimePalindrome().doit(13)  # 101
