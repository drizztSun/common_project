

# 664. Strange Printer


# There is a strange printer with the following two special requirements:

# The printer can only print a sequence of the same character each time.
# At each turn, the printer can print new characters starting from and ending at any places, 
# and will cover the original existing characters.
# Given a string consists of lower English letters only, your job is to count the minimum number of turns the printer needed in order to print it.

# Example 1:
# Input: "aaabbb"
# Output: 2
# Explanation: Print "aaa" first and then print "bbb".

# Example 2:
# Input: "aba"
# Output: 2
# Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.

# Hint: Length of the given string will not exceed 100.



class StrangePrinter:

# Let dp(i, j) be the number of turns needed to print S[i:j+1].

# Note that whichever turn creates the final print of S[i], might as well be the first turn, 
# and also there might as well only be one print, since any later prints on interval [i, k] could just be on [i+1, k].

# So suppose our first print was on [i, k]. We only need to consider prints where S[i] == S[k],
# because we could instead take our first turn by printing up to the last printed index where S[k] == S[i] to get the same result.

# Then, when trying to complete the printing of interval [i, k] (with S[i] == S[k]),
# the job will take the same number of turns as painting [i, k-1].
# This is because it is always at least as good to print [i, k] first in one turn rather than separately.

# Also, we would need to complete [k+1, j]. 
# So in total, our candidate answer is dp(i, k-1) + dp(k+1, j).

# Of course, when k == i, our candidate is 1 + dp(i+1, j): we paint S[i] in one turn, then paint the rest in dp(i+1, j) turns.

    # <DP>
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """ 
        memo = {}

        def dp(i, j):
            if i > j:
                return 0

            if (i, j) in memo:
                return memo[(i, j)]

            ans = dp(i+1, j) + 1
            
            for k in range(i+1, j+1):
                
                if s[i] == s[k]:
                    ans = min(ans, dp(i, k-1) + dp(k+1, j))

            dp[(i, j)] = ans
        
            return ans

        return dp(0, len(s) - 1)


if __name__ == "__main__":

    res = StrangePrinter().doit("aaabbb")

    res = StrangePrinter().doit("aba")

    pass