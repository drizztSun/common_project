# 1012. Numbers With Repeated Digits

# Given a positive integer N, return the number of positive integers less than or equal to N that have at least 1 repeated digit.


# Example 1:

# Input: 20
# Output: 1
# Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.

# Example 2:

# Input: 100
# Output: 10
# Explanation: The positive numbers (<= 100) with atleast 1 repeated digit are 11, 22, 33, 44, 55, 66, 77, 88, 99, and 100.

# Example 3:

# Input: 1000
# Output: 262


class NumDupDigitsAtMostN:

    """
    Intuition
    Count res the Number Without Repeated Digit
    Then the number with repeated digits = N - res

    Similar as
    788. Rotated Digits
    902. Numbers At Most N Given Digit Set

    Explanation:
    Transform N + 1 to arrayList
    Count the number with digits < n
    Count the number with same prefix
    For example,
    if N = 8765, L = [8,7,6,6],
    the number without repeated digit can the the following format:
    XXX
    XX
    X
    1XXX ~ 7XXX
    80XX ~ 86XX
    870X ~ 875X
    8760 ~ 8765

    Time Complexity:
    the number of permutations A(m,n) is O(1)
    We count digit by digit, so it's O(logN)
    """

    def doit(self, N):
        L = list(map(int, str(N + 1)))
        res, n = 0, len(L)

        # m is how many number to pick
        # n is how many pos is to use
        def A(m, n):
            return 1 if n == 0 else A(m, n - 1) * (m - n + 1)

        # How many number not repeated, without 'nth' digits, from n-1 ... 1
        for i in range(1, n):
            res += 9 * A(9, i - 1)

        s = set()
        for i, x in enumerate(L):
            for y in range(0 if i else 1, x):
                if y not in s:
                    res += A(9 - i, n - i - 1) # 9-i, because i's number has been used, n-i-1 how many pos to do
            if x in s:
                break
            s.add(x)
        return N - res

    def doit1(self, N):
        def f_no_repeat(N):
            # count of numbers with no repeat digits and having the same number of digits with N
            if N <= 9:
                return N
            a = N // 10
            b = N % 10
            a_digits = list(str(a))
            if len(set(a_digits)) < len(a_digits):
                if a == pow(10, len(a_digits) - 1):
                    return 0
                else:
                    return f_no_repeat(a - 1) * (10 - len(a_digits))
            else:
                used_digits = [v for v in a_digits if int(v) <= b]
                if a == 10:
                    return max(b - 1, 0)
                else:
                    return (
                        f_no_repeat(a - 1) * (10 - len(a_digits))
                        + b
                        + 1
                        - len(used_digits)
                    )

        if N <= 9:
            return 0
        k = 1
        m = 9
        while pow(10, k + 1) <= N:
            k += 1
            m += f_no_repeat(pow(10, k) - 1)
        m += f_no_repeat(N)

        return N - m


if __name__ == "__main__":

    res = NumDupDigitsAtMostN().doit(20)

    res = NumDupDigitsAtMostN().doit(100)

    res = NumDupDigitsAtMostN().doit(1000)

    res = NumDupDigitsAtMostN().doit(8765)

    pass
