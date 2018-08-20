# 552. Student Attendance Record II

# Given a positive integer n, return the number of all possible attendance
# records with length n, which will be regarded as rewardable.
# The answer may be very large, return it after mod 109 + 7.

# A student attendance record is a string that only contains the following three characters:

# 'A' : Absent.
# 'L' : Late.
# 'P' : Present.

# A record is regarded as rewardable if it doesn't contain more than one 'A' (absent)
# or more than two continuous 'L' (late).

# Example 1:
# Input: n = 2
# Output: 8 

# Explanation:
# There are 8 records with length 2 will be regarded as rewardable:
# "PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
# Only "AA" won't be regarded as rewardable owing to more than one absent times. 


class CheckRecord:

    # At time t where every report is length t, Let a, b, c be sequence types without an 'A' ending in N, NL, LL;
    # and d,e,f be sequence types with an 'A' ending in N, NL, LL. (Here, N will denote a non-'L' character.)
    # These types are disjoint, and exhaustive (their union is the set of all valid reports.)
    # At the beginning when t = 1, a = b = d = 1 and we should compute N-1 more steps.

    # From a sequence of type a, b, c, we can write an 'A' to give us a sequence of type d, or a 'P'
    # to give us a sequence of type a. From a sequence of type d, e, f, we can write a 'P'
    # to give us a sequence of type d. From a sequence of type a, b, d, e, we can write an 'L'
    # to give a sequence of (respectively) b, c, e, f.
    # These are all the letters we could write in any situation.
    # Working backwards, we can get the sums for a,b,c,d,e,f written below.
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        # When it starts, 'A', 'P', 'L' are the only possible
        N, NL, NLL = 1, 1, 0
        AN, ANL, ANLL = 1, 0, 0
        MOD = 10**9 + 7

        for _ in range(n-1):
            N, NL, NLL, AN, ANL, ANLL = (N + NL + NLL) % MOD, N, NL, (N + NL + NLL + AN + ANL + ANLL) % MOD, AN, ANL

        return (N + NL + NLL + AN + ANL + ANLL) % MOD


class Solution:

    # Let f[i][j][k] denote the # of valid sequences of length i where:

    # There can be at most j A's in the entire sequence.
    # There can be at most k trailing L's.
    # We give the recurrence in the following code, which should be self-explanatory, and the final answer is f[n][1][2].
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        fn = [[[0 for _ in range(3)] for _ in range(2)] for _ in range(n+1)]
        MOD = pow(10, 9) + 7

        for i in range(1, n+1):

            for A in range(2):
                for L in range(3):

                    val = fn[i-1][A][2] # ... + P

                    if L > 0:
                        val += (val + fn[i-1][A][L-1]) % MOD # .... + L

                    if A > 0:
                        val += (val + fn[i-1][A-1][2]) % MOD  # .. + A

                    fn[i][A][L] = val

        return fn[n][1][2]


    # The runtime of this solution is clearly O(n), using linear space (which can be easily optimized to O(1) though).
    # Now, let's see how to further improve the runtime.

    # In fact, if we treat f[i][][] and f[i-1][][] as two vectors, we can represent the recurrence of f[i][j][k] as follows:

    # f[i][0][0]   | 0 0 1 0 0 0 |   f[i-1][0][0]
    # f[i][0][1]   | 1 0 1 0 0 0 |   f[i-1][0][1]
    # f[i][0][2] = | 0 1 1 0 0 0 | * f[i-1][0][2]
    # f[i][1][0]   | 0 0 1 0 0 1 |   f[i-1][1][0]
    # f[i][1][1]   | 0 0 1 1 0 1 |   f[i-1][1][1]
    # f[i][1][2]   | 0 0 1 0 1 1 |   f[i-1][1][2]
    # Let A be the matrix above, then f[n][][] = A^n * f[0][][], where f[0][][] = [1 1 1 1 1 1].
    # The point of this approach is that we can compute A^n using exponentiating by squaring
    # (thanks to @StefanPochmann for the name correction), which will take O(6^3 * log n) = O(log n) time.
    # Therefore, the runtime improves to O(log n), which suffices to handle the case for much larger n, say 10^18.

    # Update: The final answer is f[n][1][2], which involves multiplying the last row of A^n and the column vector [1 1 1 1 1 1].
    # Interestingly, it is also equal to A^(n+1)[5][2] as the third column of A is just that vector. Credit to @StefanPochmann.
    #
    # https://leetcode.com/problems/student-attendance-record-ii/discuss/101633/Improving-the-runtime-from-O(n)-to-O(log-n)
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        import numpy as np
        A = np.matrix([[0, 0, 1, 0, 0, 0],
                       [1, 0, 1, 0, 0, 0],
                       [0, 1, 1, 0, 0, 0],
                       [0, 0, 1, 0, 0, 1],
                       [0, 0, 1, 1, 0, 1],
                       [0, 0, 1, 0, 1, 1]])

        power = A
        mod = 10**9 + 7

        while n:
            if n & 1:
                power = (power * A) % mod
            A = A**2 % mod
            n //= 2

        return int(power[5, 2])


class Solution1:

    def checkRecord(self, n):
        """
        :type n: int
        :rtype: int
        """
        def Mul(A, B) :
            C = list(zip(*B))
            mod = 1000000007
            return [[sum(a * b for a, b in zip(row, col)) % mod for col in C] for row in A]

        def Pow(A, b) :
            N = len(A)
            C = [[0] * r + [1] + [0] * (N - r - 1) for r in range(N)]

            while b > 0 :

                if b % 2 == 1 :
                    C = Mul(C, A)

                A = Mul(A, A)

                b //= 2

            return C

        A = [[1, 1, 1, 0, 0, 0],
             [1, 0, 0, 0, 0, 0],
             [0, 1, 0, 0, 0, 0],
             [1, 1, 1, 1, 1, 1],
             [0, 0, 0, 1, 0, 0],
             [0, 0, 0, 0, 1, 0]];

        return Pow(A, n + 1)[3][0]


if __name__ == "__main__":

    res = CheckRecord().doit(2)

    res = CheckRecord().doit(3)

    res = CheckRecord().doit(4)

    pass