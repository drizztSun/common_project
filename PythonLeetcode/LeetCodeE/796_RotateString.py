# 796. Rotate String

# We are given two strings, A and B.

# A shift on A consists of taking string A and moving the leftmost character to the rightmost position.
# For example, if A = 'abcde', then it will be 'bcdea' after one shift on A. Return True if and only if A can become B after some number of shifts on A.

# Example 1:
# Input: A = 'abcde', B = 'cdeab'
# Output: true

# Example 2:
# Input: A = 'abcde', B = 'abced'
# Output: false
# Note:

# A and B will have length at most 100.


class RotateString:

    def doit3(self, A, B):
        return B in A+A if len(A) == len(B) else False

    def doit1(self, A, B):
        la = len(A)
        lb = len(B)
        if la != lb:
            return False
        if la == 1:
            return A == B
        hashmap = dict()
        hashmapb = dict()
        for i in range(la):
            if A[i] not in hashmap:
                hashmap[A[i]] = set(A[i-1])
            else:
                hashmap[A[i]].add(A[i-1])

            if B[i] not in hashmapb:
                hashmapb[B[i]] = set(B[i-1])
            else:
                hashmapb[B[i]].add(B[i-1])
        if hashmap == hashmapb:
            return True

        return False

    # II). Brute Force
    # | O(T): O(n ^ 2) | O(S): O(n) | Rt: 20ms |
    def doit(self, A, B):
        if len(A) != len(B):
            return False

        if not B and not A:
            return True

        for s in range(len(B)):

            e = s
            for i in range(len(A)):
                if B[e] != A[i]:
                    break

                e += 1
                if e == len(B):
                    e = 0

                if e == s:
                    return True

        return False

    # III). Pair Up with Set
    # | O(T): O(n) | O(S): O(n) | Rt: 20ms |
    def doit2(self, A, B):
        if A == B:
            return True
        if len(A) != len(B):
            return False

        sa = set([(i, j) for i, j in zip(A, A[1:])] + [(A[-1], A[0])])
        sb = set([(i, j) for i, j in zip(B, B[1:])] + [(B[-1], B[0])])
        return sa == sb


if __name__ == '__main__':

    res = RotateString().doit('abcde', 'cdeab')

    res = RotateString().doit('abcde', 'abced')

    res = RotateString().doit1("aaaecaaaafcaa", "aaaaaaaecaafc")

    res = RotateString().doit2("aaaecaaaafcaa", "aaaaaaaecaafc")

    res = RotateString().doit3("aaaecaaaafcaa", "aaaaaaaecaafc")

    pass
