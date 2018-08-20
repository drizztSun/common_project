
# 564. Find the Closest Palindrome

# Given an integer n, find the closest integer (not including itself), which is a palindrome.

# The 'closest' is defined as absolute difference minimized between two integers.

# Example 1:
# Input: "123"
# Output: "121"

# Note:
# The input n is a positive integer represented by string, whose length will not exceed 18.
# If there is a tie, return the smaller one as answer.


class NearestPalindromic:


# Let�s build a list of candidate answers for which the final answer must be one of those candidates. Afterwards,
# choosing from these candidates is straightforward.

# If the final answer has the same number of digits as the input string S, then
# the answer must be the middle digits + (-1, 0, or 1) flipped into a palindrome.
# For example, 23456 had middle part 234, and 233, 234, 235 flipped into a palindrome yields 23332, 23432, 23532.
# Given that we know the number of digits, the prefix 235 (for example) uniquely determines the corresponding palindrome 23532, so all palindromes with larger prefix like 23732 are strictly farther away from S than 23532 >= S.

# If the final answer has a different number of digits, it must be of the form 999....999 or 1000...0001, as any palindrome smaller than 99....99 or bigger than 100....001 will be farther away from S.

    def doit(self, n):
        """
        :type n: str
        :rtype: str
        """
        K = len(n)
        candidates = [str(10**k + d) for k in (K-1, K) for d in (-1, 1)]

        Prefix = int(n[:(K+1)//2])

        for start in map(str, [Prefix - 1, Prefix, Prefix + 1]):
            candidates.append(str(start) + (start[:-1] if K % 2 == 1 else start)[::-1])

        ans, diff = 0, float('inf')
        base = int(n)

        for C in candidates:
            b = int(C)
            d = abs(b - base)

            if d == 0 or d > diff or (d == diff and b > ans):
                continue

            ans = int(C)
            diff = d

        return str(ans)


    def doit1(self, num):
        """
        :type
        n: str
        :rtype: str
        """
        K = len(num)
        candidates = set([10**K + 1, 10**(K-1) - 1])
        Prefix = int(num[:(K+1)//2])

        for start in map(str, [Prefix-1, Prefix, Prefix+1]):
            candidates.add(start + [start, start[:-1]][K & 1][::-1])

        candidates.discard(num)

        return str(min(candidates, key=lambda x: (abs(int(x) - int(num)), int(x))))






if __name__ == "__main__":

res = NearestPalindromic().doit("1")

res = NearestPalindromic().doit("123")

res = NearestPalindromic().doit("70000")

res = NearestPalindromic().doit("700002")

pass

