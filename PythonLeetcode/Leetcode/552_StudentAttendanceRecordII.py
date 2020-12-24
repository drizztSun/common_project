"""
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

"""


class CheckRecord:

    """
    Approach #2 Using Recursive formulae [Time Limit Exceeded]
    Algorithm

    The given problem can be solved easily if we can develop a recurring relation for it.

    Firstly, assume the problem to be considering only the characters LL and PP in the strings. i.e. The strings can contain only LL and PP. The effect of AA will be taken into account later on.

    In order to develop the relation, let's assume that f[n] represents the number of possible rewardable strings(with LL and PP as the only characters) of length nn. Then, we can easily determine the value of f[n]f[n] if we know the values of the counts for smaller values of nn. To see how it works, let's examine the figure below:

    Recurrence

    The above figure depicts the division of the rewardable string of length nn into two strings of length n-1n−1 and ending with LL or PP. The string ending with PP of length nn is always rewardable provided the string of length n-1n−1 is rewardable. Thus, this string accounts for a factor of f[n-1]f[n−1] to f[n]f[n].

    For the first string ending with LL, the rewardability is dependent on the further strings of length n-3n−3. Thus, we consider all the rewardable strings of length n-3n−3 now. Out of the four combinations possible at the end, the fourth combination, ending with a LLLL at the end leads to an unawardable string. But, since we've considered only rewardable strings of length n-3n−3, for the last string to be rewardable at length n-3n−3 and unawardable at length n-1n−1, it must be preceded by a PP before the LLLL.

    Thus, accounting for the first string again, all the rewardable strings of length n-1n−1, except the strings of length n-4n−4 followed by PLLPLL, can contribute to a rewardable string of length nn. Thus, this string accounts for a factor of f[n-1] - f[n-4]f[n−1]−f[n−4] to f[n]f[n].

    Thus, the recurring relation becomes:

    f[n] = 2f[n-1] - f[n-4]

    We store all the f[i]f[i] values in an array. In order to compute f[i]f[i], we make use of a recursive function func(n) which makes use of the above recurrence relation.

    Now, we need to put the factor of character AA being present in the given string. We know, atmost one AA is allowed to be presnet in a rewardable string. Now, consider the two cases.

    No AA is present: In this case, the number of rewardable strings is the same as f[n]f[n].

    A single AA is present: Now, the single AA can be present at any of the nn positions. If the AA is present at the i^{th}i
    th
      position in the given string, in the form: "<(i-1) characters>, A, <(n-i) characters>", the total number of rewardable strings is given by: f[i-1] * f[n-i]f[i−1]∗f[n−i]. Thus, the total number of such substrings is given by: \sum_{i=1}^{n} (f[i-1] * f[n-i])∑
    i=1
    n
    ​
     (f[i−1]∗f[n−i]).
    """
    def doit_dp(self, n):

        M = 10**9 + 7
        def search(n):
            if n == 0:
                return 1
            if n == 1:
                return 2
            if n == 2:
                return 4
            if n == 3:
                return 7
            return (2*search(n-1) - search(n-4)) % M

        dp = [0] * (n+1)
        dp[0] = 1
        for i in range(1, n+1):
            dp[i] = search(i)

        total = dp[n]
        for i in range(1, n+1):
            total = (dp[i-1] * dp[n-i]) % M
        return total % M

    """
    Approach #3 Using Dynamic Programming [Accepted]
    Algorithm

    In the last approach, we calculated the values of f[i]f[i] everytime using the recursive function, which goes till its root depth everytime.
    But, we can reduce a large number of redundant calculations, if we use the results obtained for previous f[j]f[j] values directly
    to obtain f[i]f[i] as f[i] = 2f[i-1] + f[i-4].

    **Complexity Analysis**
    Time complexity : O(n). One loop to fill f array and one to calculate sum
    Space complexity : O(n). f array of size nn is used.
    """
    def doit_dp(self, n):
        M = 10**9 + 7
        dp = [0] * (6 if n <= 5 else n+1)

        dp[0] = 1
        dp[1] = 2
        dp[2] = 4
        dp[3] = 7

        for i in range(4, n+1):
            dp[i] = ((2 * dp[i-1]) % M + (M - dp[i-4])) % M

        total = dp[n]
        for i in range(1, n+1):
            total += (dp[i-1] * dp[n-i]) % M # we only consider L and P, so we have to add 1 A into the result. so it is dp[0..i-1] + A + dp[i...j]

        return total % M

    """
    Approach #4 Dynamic Programming with Constant Space [Accepted]
    Algorithm
    
    We can observe that the number and position of PP's in the given string is irrelevant. Keeping into account this fact, 
    we can obtain a state diagram that represents the transitions between the possible states as shown in the figure below:
    
    This state diagram contains the states based only upon whether an AA is present in the string or not, and on the number of LL's that occur at the trailing edge of the string formed till now. The state transition occurs whenver we try to append a new character to the end of the current string.

    Based on the above state diagram, we keep a track of the number of unique transitions from which a rewardable state can be achieved. We start off with a string of length 0 and keep on adding a new character to the end of the string till we achieve a length of nn. At the end, we sum up the number of transitions possible to reach each rewardable state to obtain the required result.
    
    We can use variables corresponding to the states. axlyaxly represents the number of strings of length ii containing x a's and ending with yy l's
    """

    def doit_dp_status(self, n):

        M = 10 ** 9 + 7
        a0l0, a0l1, a0l2, a1l0, a1l1, a1l2 = 1, 0, 0, 0, 0, 0

        for i in range(1, n+1):
            a0l0, a0l1, a0l2, a1l0, a1l1, a1l2  = (a0l1 + a0l2 + a0l0) % M, a0l0, a0l1, (a0l0 + a0l1 + a0l2 + a1l0 + a1l1 + a1l2) % M, a1l0, a1l1

        return (a0l0 + a0l1 + a0l2 + a1l0 + a1l1 + a1l2) % M






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


    """
    # Let f[i][j][k] denote the # of valid sequences of length i where:

    # There can be at most j A's in the entire sequence.
    # There can be at most k trailing L's.
    # We give the recurrence in the following code, which should be self-explanatory, and the final answer is f[n][1][2].
    """
    def doit_dp(self, n):
        """
        :type n: int
        :rtype: int
        """
        fn = [[[0 for _ in range(3)] for _ in range(2)] for _ in range(n+1)]
        MOD = pow(10, 9) + 7

        for i in range(n+1):
            fn[i][0][0] = 1

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
    def doit_dp_fastpower(self, n):
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
             [0, 0, 0, 0, 1, 0]]

        return Pow(A, n + 1)[3][0]


if __name__ == "__main__":

    res = CheckRecord().doit(2)

    res = CheckRecord().doit(3)

    res = CheckRecord().doit(4)

    pass