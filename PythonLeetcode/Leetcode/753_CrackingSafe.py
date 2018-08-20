# 753. Cracking the Safe

# There is a box protected by a password. The password is n digits,
# where each letter can be one of the first k digits 0, 1, ..., k-1.

# You can keep inputting the password, the password will automatically be matched against the last n digits entered.

# For example, assuming the password is "345", I can open it when I type "012345", but I enter a total of 6 digits.

# Please return any string of minimum length that is guaranteed to open the box after the entire string is inputted.

# Example 1:
# Input: n = 1, k = 2
# Output: "01"
# Note: "10" will be accepted too.

# Example 2:
# Input: n = 2, k = 2
# Output: "00110"
# Note: "01100", "10011", "11001" will be accepted too.

# Note:
# n will be in the range [1, 4].
# k will be in the range [1, 10].
# k^n will be at most 4096.


class CrackSafe:

    def doit(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        ans = '0' * (n-1)
        visited = set()

        for _ in range(k**n):
            current = ans[-n+1:] if n > 1 else ''

            for s in range(k-1, -1, -1):
                if current + str(s) not in visited:
                    ans += str(s)
                    visited.add(current + str(s))
                    break

        return ans

    def doit1(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        ans = str(k - 1) * n
        visited = set([ans])

        for _ in range(k ** n):
            current = ans[-n + 1:] if n > 1 else ''

            for s in '0123456789'[:k]:
                if current + s not in visited:
                    ans += s
                    visited.add(current + s)
                    break

        return ans


if __name__ == "__main__":

    res = CrackSafe().doit(1, 2)

    res = CrackSafe().doit(2, 2)

    pass