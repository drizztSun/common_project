# 859. Buddy Strings

# Given two strings A and B of lowercase letters, return true if and only if we can swap two letters in A so that the result equals B.


# Example 1:

# Input: A = "ab", B = "ba"
# Output: true

# Example 2:

# Input: A = "ab", B = "ab"
# Output: false

# Example 3:

# Input: A = "aa", B = "aa"
# Output: true

# Example 4:

# Input: A = "aaaaaaabc", B = "aaaaaaacb"
# Output: true

# Example 5:

# Input: A = "", B = "aa"
# Output: false


# Note:

# 0 <= A.length <= 20000
# 0 <= B.length <= 20000
# A and B consist only of lowercase letters.

"""
Approach 1: Enumerate Cases
Intuition

Let's say i is matched if A[i] == B[i], otherwise i is unmatched. A buddy string has almost all matches, because a swap only affects two indices.

If swapping A[i] and A[j] would demonstrate that A and B are buddy strings, then A[i] == B[j] and A[j] == B[i].
That means among the four free variables A[i], A[j], B[i], B[j], there are only two cases: either A[i] == A[j] or not.

Algorithm

Let's work through the cases.

In the case A[i] == A[j] == B[i] == B[j], then the strings A and B are equal. So if A == B, we should check each index i for two matches with the same value.

In the case A[i] == B[j], A[j] == B[i], (A[i] != A[j]), the rest of the indices match.
So if A and B have only two unmatched indices (say i and j), we should check that the equalities A[i] == B[j] and A[j] == B[i] hold.

Complexity Analysis

Time Complexity: O(N), where NN is the length of A and B.

Space Complexity: O(1).

"""


class buddyStrings:
    def doit(self, A, B):
        if len(A) != len(B):
            return False
        if A == B:
            seen = set()
            for a in A:
                if a in seen:
                    return True
                seen.add(a)
            return False
        else:
            pairs = []
            for a, b in itertools.izip(A, B):
                if a != b:
                    pairs.append((a, b))
                if len(pairs) >= 3:
                    return False
            return len(pairs) == 2 and pairs[0] == pairs[1][::-1]

    def doit(self, A, B):

        if len(A) != len(B):
            return False

        if A == B:
            seen = set()
            for c in A:
                if c in seen:
                    return True
                seen.add(c)
            return False

        st = []
        for i in range(len(A)):
            if A[i] != B[i]:
                st.append(i)

            if len(st) > 2:
                break

        if len(st) != 2:
            return False

        return A[st[0]] == B[st[1]] and A[st[1]] == B[st[0]]

    def doit(self, A, B):
        if len(A) != len(B):
            return False
        d = {}

        for i in range(len(A)):
            if A[i] != B[i]:
                d[i] = A[i]

        if len(d) == 2:
            i, j = d.keys()
            A = list(A)
            A[i], A[j] = A[j], A[i]
            return ''.join(A) == B
        elif len(d) == 0 and A == B and len(A) > len(set(A)):
            return True
        else:
            return False


if __name__ == '__main__':

    res = buddyStrings().doit(A="ab", B="ba")  # true

    res = buddyStrings().doit(A="ab", B="ab")  # false

    res = buddyStrings().doit(A="aa", B="aa")  # true

    res = buddyStrings().doit(A="aaaaaaabc", B="aaaaaaacb")  # true

    res = buddyStrings().doit(A="", B="aa")  # false

    pass
