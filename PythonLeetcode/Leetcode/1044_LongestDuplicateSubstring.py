# 1044. Longest Duplicate Substring

# Given a string S, consider all duplicated substrings: (contiguous) substrings of S that occur 2 or more times.
# (The occurrences may overlap.)

# Return any duplicated substring that has the longest possible length.
# (If S does not have a duplicated substring, the answer is "".)


# Example 1:

# Input: "banana"
# Output: "ana"

# Example 2:

# Input: "abcd"
# Output: ""


# Note:

# 2 <= S.length <= 10^5
# S consists of lowercase English letters.


class LongestDupSubstring:
    def doit(self, S):
        def search(L: int, a: int, modulus: int, n, nums):

            h = 0
            for i in range(L):
                h = (h * a + nums[i]) % modulus

            seen = {h}
            aL = pow(a, L, modulus)
            for start in range(1, n - L + 1):
                h = (h * a - nums[start - 1] * aL + nums[start + L - 1]) % modulus
                if h in seen:
                    return start
                seen.add(h)
            return -1

        n = len(S)
        nums = [ord(S[i]) - ord("a") for i in range(n)]
        a = 26
        modulus = 2 ** 32

        left, right = 1, n
        while left <= right:
            L = left + (right - left) // 2
            if search(L, a, modulus, n, nums) != -1:
                left = L + 1
            else:
                right = L - 1

        start = search(left - 1, a, modulus, n, nums)
        return S[start : start + left - 1]


if __name__ == "__main__":

    res = LongestDupSubstring().doit("banana")

    res = LongestDupSubstring().doit("abcd")

    pass

